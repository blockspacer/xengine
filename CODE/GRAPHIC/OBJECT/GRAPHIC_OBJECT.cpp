//
//  GRAPHIC_OBJECT.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include <math.h>

#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "CORE_MATH_MATRIX.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_MATH_MATRIX.h"
#include "GRAPHIC_MATERIAL_RESOURCE_LOADER.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_JSON.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GRAPHIC_OBJECT )
    XS_DEFINE_ClassMember( "MeshTable", std::vector< GRAPHIC_MESH * > , MeshTable )
    XS_DEFINE_ClassMember( "JointTable", std::vector< GRAPHIC_MESH_ANIMATION_JOINT *>, JointTable )
XS_END_INTERNAL_MEMORY_LAYOUT

GRAPHIC_OBJECT::GRAPHIC_OBJECT() :
    GR_O_ANCESTOR_TYPE(),
    MeshTable(),
    JointTable()
#if __COMPILE_WITH__COLLADA__
    ,AnimationTable()
#endif
{
    
    JointTable.resize(0);
}

GRAPHIC_OBJECT::GRAPHIC_OBJECT( const GRAPHIC_OBJECT & other) :
    GR_O_ANCESTOR_TYPE(),
    MeshTable( other.MeshTable),
    JointTable(other.JointTable)
    #if __COMPILE_WITH__COLLADA__
        ,AnimationTable( other.AnimationTable)
    #endif
{
    
    JointTable.resize(0);
}

GRAPHIC_OBJECT::~GRAPHIC_OBJECT() {
    
    Release();
    
    for ( size_t i = 0; i < MeshTable.size(); i++ ) {

        CORE_MEMORY_ObjectSafeDeallocation( MeshTable[ i ] );
    }

    for ( size_t i = 0; i < JointTable.size(); i++ ) {

        CORE_MEMORY_ObjectSafeDeallocation( JointTable[ i ] );
    }
    
    #if __COMPILE_WITH__COLLADA__
        for ( size_t i = 0; i < AnimationTable.size(); i++ ) {
            
            CORE_MEMORY_ObjectSafeDeallocation( AnimationTable[ i ] );
        }
    #endif
}

void GRAPHIC_OBJECT::AddNewMesh( GRAPHIC_MESH * mesh ) {
    
    MeshTable.push_back(mesh);
}

void GRAPHIC_OBJECT::Render( GRAPHIC_RENDERER & renderer, const GRAPHIC_OBJECT_RENDER_OPTIONS & options, GRAPHIC_SHADER_EFFECT * effect ) {
    
    for ( size_t i = 0; i < MeshTable.size(); i++ ) {
        
        CORE_MATH_MATRIX
            result,
            object;
        
        effect->Apply( renderer, renderer.IsLightingEnabled(), options.IsTexturingEnabled() );
        
        GRAPHIC_SHADER_ATTRIBUTE & mvp_matrix = effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::MVPMatrix );
        GRAPHIC_SHADER_ATTRIBUTE & model_matrix = effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::ModelMatrix );
        GRAPHIC_SHADER_ATTRIBUTE & view_matrix = effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::ViewMatrix );
        GRAPHIC_SHADER_ATTRIBUTE & time_mod = effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::TimeModulator );
        GRAPHIC_SHADER_ATTRIBUTE & projection_matrix = effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::ProjectionMatrix );

        ComputeModelViewProjection( options, MeshTable[i]->GetTransform(), renderer, result, object );
        
        effect->UpdateMatrix( renderer, mvp_matrix, &result[0] );
        effect->UpdateMatrix( renderer, projection_matrix, &renderer.GetCamera()->GetProjectionMatrix()[0]);
        effect->UpdateMatrix( renderer, model_matrix, &object[0]);
        effect->UpdateMatrix( renderer, view_matrix, &renderer.GetCamera()->GetViewMatrix()[0]);
        effect->UpdateFloat( renderer, time_mod, time_mod.AttributeValue.Value.FloatValue );

        GRAPHIC_SHADER_ATTRIBUTE * depth[3];

        depth[0] = &effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::DepthTexture );
        depth[1] = &effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::DepthTexture1 );
        depth[2] = &effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::DepthTexture2 );
        
        for ( int cascade_index = 0; cascade_index < renderer.GetNumCascade(); cascade_index++ ) {
            
            CORE_MATH_MATRIX
                depthMVP,
                depthBias;

            GRAPHIC_SHADER_ATTRIBUTE & shadowmap_mvp = effect->GetProgram().getShaderAttribute( renderer.GetShadowMapMVPName( cascade_index ) );
            GRAPHIC_SHADER_ATTRIBUTE & end_clip_space = effect->GetProgram().getShaderAttribute( GRAPHIC_SHADER_PROGRAM::CascadeEndClipSpace );
            
            //Depth Textures are always last
            renderer.GetDepthTexture( cascade_index )->ApplyDepth(effect->GetMaterial()->GetTextureCount() + cascade_index , depth[cascade_index]->AttributeIndex );
            
            static const CORE_MATH_MATRIX
                biasMatrix(
                    0.5f, 0.0f, 0.0f, 0.5f,
                    0.0f, 0.5f, 0.0f, 0.5f,
                    0.0f, 0.0f, 0.5f, 0.5f,
                    0.0f, 0.0f, 0.0f, 1.0f );
            
            depthMVP = renderer.GetShadowMapCamera( cascade_index ).GetProjectionMatrix() * renderer.GetShadowMapCamera( cascade_index ).GetViewMatrix() * object;
            
            depthBias = biasMatrix * depthMVP;
            
            float cascade_end[8];
            
            for (int ci = 0; ci < renderer.GetNumCascade(); ci++) {
                
                CORE_MATH_VECTOR vvv( 0.0f, 0.0f, renderer.GetCascadeEnd( ci + 1 ), 0.0f ), vres;
                
                vres = renderer.GetCamera()->GetProjectionMatrix() * vvv;
                
                cascade_end[ci] = -vres.Z();//Why is it negative? -> Bullshit in matrix vect mul
            }
            
            effect->UpdateMatrix( renderer, shadowmap_mvp, &depthBias[0] );
            effect->UpdateFloatArray( renderer, end_clip_space, renderer.GetNumCascade(), cascade_end );
        }
        
        MeshTable[ i ]->ApplyBuffers( renderer );
    }
    
    effect->Discard();
}

void GRAPHIC_OBJECT::ComputeModelViewProjection( const GRAPHIC_OBJECT_RENDER_OPTIONS & options, const CORE_MATH_MATRIX & transform, GRAPHIC_RENDERER & renderer, CORE_MATH_MATRIX & mvp, CORE_MATH_MATRIX & object_matrix ) {
    
    CORE_MATH_MATRIX
        scaling_matrix,
        translation_matrix,
        parent_matrix,
        orientation_mat;
    
    if ( options.GetParent() ) {
        
        CORE_MATH_VECTOR cp = options.GetPosition() * orientation_mat;
        
        options.GetParent()->GetOrientation().ToMatrix( &orientation_mat[0] );
        object_matrix.Translate( options.GetParent()->GetPosition() );
        object_matrix *= orientation_mat;
        
        options.GetOrientation().ToMatrix( &orientation_mat[0] );
        
        scaling_matrix.Scale( options.GetScaleFactor() );
        translation_matrix.Translate( options.GetPosition() );
        
        object_matrix *= translation_matrix * orientation_mat * scaling_matrix;
        
        if ( !transform.IsIdentity() ) {
            
            object_matrix *= transform;
        }
    }
    else {
        
        options.GetOrientation().ToMatrix( &orientation_mat[0] );
        
        scaling_matrix.Scale( options.GetScaleFactor() );
        translation_matrix.Translate( options.GetPosition() );
        
        object_matrix = translation_matrix * orientation_mat * scaling_matrix;
        
        if ( !transform.IsIdentity() ) {
            
            object_matrix *= transform;
        }
    }
    
    //---------------
    //MVPmatrix = projection * view * model; // Remember : inverted !
    
    mvp = renderer.GetCamera()->GetProjectionMatrix() * renderer.GetCamera()->GetViewMatrix() * object_matrix;
}

void GRAPHIC_OBJECT::ComputeAABBox( CORE_MATH_SHAPE & box ) {
    
    for ( size_t i = 0; i < MeshTable.size(); i++ ) {
        
        box.AggregateWithBox( MeshTable[ i ]->GetBoundingShape() );
    }
}

void GRAPHIC_OBJECT::Release() {
    
    for ( size_t i = 0; i < MeshTable.size(); i++ ) {
        
        MeshTable[i]->ReleaseBuffers();
    }
}

void GRAPHIC_OBJECT::SetTesselation( bool enable ) {
    
    for ( size_t i = 0; i < MeshTable.size(); i++ ) {
        
        MeshTable[i]->SetPolygonRenderMode( GRAPHIC_MESH_POLYGON_RENDER_MODE_TesselationPatches );
    }
}

GRAPHIC_SHADER_BIND & GRAPHIC_OBJECT::GetShaderBindParameter() {
    
    return MeshTable[0]->GetVertexComponent();
}
