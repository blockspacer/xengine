//
//  R3D_LEVEL_HELPER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 18/01/18.
//  Copyright © 2018 IGZ. All rights reserved.
//

#include "R3D_LEVEL_HELPER.h"
#include "R3D_LEVEL_TRACK.h"
#include "GAMEPLAY_HELPER.h"

CORE_ABSTRACT_PROGRAM_BINDER_DECLARE_CLASS( R3D_LEVEL_HELPER )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_YIELD_METHOD_2( GAMEPLAY_COMPONENT_ENTITY::PTR, R3D_LEVEL_HELPER, Create, const char *, const CORE_MATH_VECTOR & )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_VOID_METHOD_1( R3D_LEVEL_HELPER, AddToSystemRenderAndPhysics, GAMEPLAY_COMPONENT_ENTITY::PTR )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_VOID_METHOD_1( R3D_LEVEL_HELPER, AddToSystemRender, GAMEPLAY_COMPONENT_ENTITY::PTR )
    CORE_ABSTRACT_PROGRAM_BINDER_DEFINE_STATIC_YIELD_METHOD_1( GAMEPLAY_COMPONENT_ENTITY::PTR, R3D_LEVEL_HELPER, Clone, GAMEPLAY_COMPONENT_ENTITY::PTR )
CORE_ABSTRACT_PROGRAM_BINDER_END_CLASS( R3D_LEVEL_HELPER )

R3D_LEVEL_HELPER::R3D_LEVEL_HELPER() {
    
}

R3D_LEVEL_HELPER::~R3D_LEVEL_HELPER() {
    
}

GAMEPLAY_COMPONENT_ENTITY::PTR R3D_LEVEL_HELPER::Create( const char * type, const CORE_MATH_VECTOR & position ) {
    
    auto entity = new GAMEPLAY_COMPONENT_ENTITY;
    
    GAMEPLAY_HELPER::CreateComponent_PositionRenderPhysics( entity );
    
    GAMEPLAY_HELPER::Set3DObject( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( type ) );
    GAMEPLAY_HELPER::SetEffect( entity, CORE_HELPERS_UNIQUE_IDENTIFIER( "shader" ) );
    GAMEPLAY_HELPER::SetShadowmapEffect( entity );
    GAMEPLAY_HELPER::SetTexture( entity, "spaceship1_diffuse", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048", "png", "TEXTURES" ) );
    GAMEPLAY_HELPER::SetNormal( entity, "spaceship1_normal", CORE_FILESYSTEM_PATH::FindFilePath( "BitsUV2048-normal", "png", "TEXTURES" ) );
    
    GAMEPLAY_HELPER::SetPhysicsObject( entity, position, 0.0f );
    //GAMEPLAY_HELPER::SetPhysicsBoxObject(this, position   , CORE_MATH_VECTOR( 0.5f, 0.5f, 0.5f, 0.0f), CORE_MATH_QUATERNION(), 0.0f);
    //GAMEPLAY_HELPER::SetPhysicsCustomMaterialCallback( this );
    
    entity->SetPosition( position );
    
    return entity;
}

GAMEPLAY_COMPONENT_ENTITY::PTR R3D_LEVEL_HELPER::Clone( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    return GAMEPLAY_COMPONENT_MANAGER::GetInstance().CloneEntity< GAMEPLAY_COMPONENT_ENTITY >( entity );
}

void R3D_LEVEL_HELPER::AddToSystemRenderAndPhysics( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    GAMEPLAY_HELPER::AddStaticToPhysics( entity, PHYSICS_COLLISION_TYPE_WALL, PHYSICS_COLLISION_TYPE_WEAPONSHIP );
    GAMEPLAY_HELPER::AddToWorld( entity );
}

void R3D_LEVEL_HELPER::AddToSystemRender( GAMEPLAY_COMPONENT_ENTITY::PTR entity ) {
    
    GAMEPLAY_HELPER::AddToWorld( entity );
}