//
//  OPENGL_2.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 1/12/13.
//  Copyright (c) 2013 Christophe Bernard. All rights reserved.
//

#include "OPENGLES_2.h"
#include "GRAPHIC_TEXTURE.h"
#include "GRAPHIC_TEXTURE_LOADER.h"
#include "GRAPHIC_RENDER_TARGET.h"
#include "GRAPHIC_SHADER_ATTRIBUTE.h"
#include "GRAPHIC_SHADER_PROGRAM.h"
#include "GRAPHIC_SHADER_LIGHT.h"
#include "GRAPHIC_MESH.h"

#if OPENGLES2

CORE_PARALLEL_LOCK_MUTEX GRAPHIC_SYSTEM::GraphicSystemLock;
const char * GRAPHIC_SYSTEM::ShaderDirectoryPath = "OPENGLES2";
CORE_HELPERS_COLOR GRAPHIC_SYSTEM::ClearColor = CORE_COLOR_Blue;

GRAPHIC_SYSTEM::~GRAPHIC_SYSTEM() {

}

void GRAPHIC_SYSTEM::Initialize( const char * app_name, int app_version  ) {

}

void GRAPHIC_SYSTEM::Finalize() {

}

GLenum OPENGLES_2_GetFiltermode( const GRAPHIC_TEXTURE_FILTERING mode ) {
    
    static GLenum filter_mode[] { GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR };
    
    return filter_mode[ mode ];
}

GLenum OPENGLES_2_GetWrapMode( const GRAPHIC_TEXTURE_WRAP mode ) {
    
    static GLenum filter_mode[] { GL_CLAMP_TO_EDGE, GL_REPEAT, GL_MIRRORED_REPEAT };
    
    return filter_mode[ mode ];
}

GLint OPENGLES_2_GetTextureFormat( GRAPHIC_TEXTURE_IMAGE_TYPE image_tye ) {
    
    static GLint image_type_mapping[] = { GL_RGB, GL_RGBA, -1, -1, -1 };
    
    return image_type_mapping[ image_tye ];
}

GLenum OPENGLES_2_GetCompareOperation( const GRAPHIC_SYSTEM_COMPARE_OPERATION operation ) {
    
    static GLenum compare_operation[] { GL_NEVER, GL_LESS, GL_EQUAL, GL_LEQUAL, GL_GREATER, GL_NOTEQUAL, GL_GEQUAL, GL_ALWAYS, 0, 0 };
    
    return compare_operation[ operation ];
}

GLenum OPENGLES_2_GetBlendOperation( const GRAPHIC_SYSTEM_BLEND_OPERATION operation ) {
    
    static GLint blend_operation[] = { GL_ZERO, GL_ONE, GL_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA };
    
    return blend_operation[ operation ];
}

GLenum OPENGLES_2_GetFillMode( const GRAPHIC_SYSTEM_POLYGON_FILL_MODE mode ) {
    
    static GLenum fill_mode[] { GL_POINTS, GL_LINES };
    
    return fill_mode[ mode ];
}

void GRAPHIC_SYSTEM::EnableBlend( const GRAPHIC_SYSTEM_BLEND_OPERATION source, const GRAPHIC_SYSTEM_BLEND_OPERATION destination ) {
    
    GFX_CHECK( glEnable( GL_BLEND ); )
    GFX_CHECK( glBlendFunc( OPENGLES_2_GetBlendOperation( source ), OPENGLES_2_GetBlendOperation( destination ) ); )
}

void GRAPHIC_SYSTEM::DisableBlend() {
    
    GFX_CHECK( glDisable( GL_BLEND ); )
}

void GRAPHIC_SYSTEM::EnableDepthTest( const GRAPHIC_SYSTEM_COMPARE_OPERATION operation, bool mask, float range_begin, float range_end ) {
    
    GFX_CHECK( glEnable( GL_DEPTH_TEST ); )
    
    GFX_CHECK( glDepthFunc( OPENGLES_2_GetCompareOperation( operation ) ); )
    GFX_CHECK( glDepthMask( mask ? GL_TRUE : GL_FALSE ); )
    GFX_CHECK( glDepthRangef(range_begin, range_end); )
}

void GRAPHIC_SYSTEM::EnableBackfaceCulling() {
    
    GFX_CHECK( glEnable( GL_CULL_FACE ); )
    GFX_CHECK( glCullFace( GL_BACK ); )
    GFX_CHECK( glFrontFace( GL_CCW ); )
}

void GRAPHIC_SYSTEM::DisableFaceCulling() {
    
    GFX_CHECK( glDisable( GL_CULL_FACE ); )
}

void GRAPHIC_SYSTEM::SetPolygonMode( const GRAPHIC_SYSTEM_POLYGON_FILL_MODE fill_mode ) {
    
    //There is no polygon mode in gles :
    //http://stackoverflow.com/questions/4627770/any-glpolygonmode-alternative-on-iphone-opengl-es
}

void GRAPHIC_SYSTEM::DisableDepthTest() {
    
    GFX_CHECK( glDisable( GL_DEPTH_TEST ); )
}

void GRAPHIC_SYSTEM::CreateTexture( GRAPHIC_TEXTURE * texture ) {
    
    GFX_CHECK( glActiveTexture(GL_TEXTURE0); )
    GFX_CHECK( glGenTextures( 1, &texture->GetTextureHandle() ); )
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    GFX_CHECK( glBindTexture( GL_TEXTURE_2D, texture->GetTextureHandle() ); )
    
    GRAPHIC_TEXTURE_INFO & info = texture->GetTextureInfo();
    
    GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); )
    GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); )
    
    GFX_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); )
    GFX_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); )
    
    GFX_CHECK( glTexImage2D( GL_TEXTURE_2D, 0, OPENGLES_2_GetTextureFormat(info.ImageType), info.Width, info.Height, 0, OPENGLES_2_GetTextureFormat(info.ImageType), GL_UNSIGNED_BYTE, NULL ); )
}

void GRAPHIC_SYSTEM::CreateDepthTexture( GRAPHIC_TEXTURE * texture, GRAPHIC_TEXTURE_IMAGE_TYPE type ) {
    
    GRAPHIC_TEXTURE_INFO & info = texture->GetTextureInfo();
    
    GFX_CHECK( glGenTextures(1, &texture->GetDepthTextureHandle() ); )
    GFX_CHECK( glBindTexture(GL_TEXTURE_2D, texture->GetDepthTextureHandle() ); )
    
    GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST ); )
    GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST ); )
    GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE ); )
    GFX_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); )
    GFX_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); )
    
    GFX_CHECK( glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, info.Width, info.Height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL); )
}

void GRAPHIC_SYSTEM::CreateTexture( GRAPHIC_TEXTURE * texture, CORE_DATA_STREAM & texture_data, bool generate_mipmap ) {
    
    GFX_CHECK( glActiveTexture(GL_TEXTURE0); )
    GFX_CHECK( glGenTextures( 1, &texture->GetTextureHandle() ); )
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    GFX_CHECK( glBindTexture( GL_TEXTURE_2D, texture->GetTextureHandle() ); )
    
    //static float pixels[] = { 0.0f, 0.0f,0.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
    // Give the image to OpenGL
    
    GRAPHIC_TEXTURE_INFO & info = texture->GetTextureInfo();
    
    GFX_CHECK( glTexImage2D( GL_TEXTURE_2D, 0, OPENGLES_2_GetTextureFormat(info.ImageType), info.Width, info.Height, 0, OPENGLES_2_GetTextureFormat(info.ImageType), GL_UNSIGNED_BYTE, texture_data ); )
    //GFX_CHECK( glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data ); )
    
    // TODO: generate mipmap -> disable for interface elements
    if ( false ) { //generate_mipmap ) {
        
        //GFX_CHECK( glGenerateMipmap(GL_TEXTURE_2D); )
    }
    
    
    GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); )
    
    if ( false ) { //generate_mipmap ) {
        GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST ); )
    }
    else {
        
        GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); )
    }
    
    GFX_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); )
    GFX_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); )
}

void GRAPHIC_SYSTEM::CreateSubTexture( GRAPHIC_TEXTURE * sub_texture, const GRAPHIC_TEXTURE & texture, const CORE_MATH_VECTOR & offset, const CORE_MATH_VECTOR & size, const void * data ) {
    
    GFX_CHECK( glActiveTexture(GL_TEXTURE0); )
    GFX_CHECK( glGenTextures( 1, &sub_texture->GetTextureHandle() ); )
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    GFX_CHECK( glBindTexture( GL_TEXTURE_2D, sub_texture->GetTextureHandle() ); )
    
    GFX_CHECK( glTexSubImage2D( GL_TEXTURE_2D,
                               0,
                               offset[0],
                               offset[1],
                               size[0],
                               size[1],
                               OPENGLES_2_GetTextureFormat( texture.GetTextureInfo().ImageType ),
                               GL_UNSIGNED_BYTE,
                               data ); )
}

void GRAPHIC_SYSTEM::ApplyTexture( GRAPHIC_TEXTURE * texture, int texture_index, int shader_texture_attribute_index ) {
    
    GFX_CHECK( glActiveTexture( GL_TEXTURE0 + texture_index ); )
    GFX_CHECK( glBindTexture( GL_TEXTURE_2D, texture->GetTextureHandle() ); )
    GFX_CHECK( glUniform1i( shader_texture_attribute_index, texture_index ); )
}

void GRAPHIC_SYSTEM::SetTextureOptions( GRAPHIC_TEXTURE * texture, GRAPHIC_TEXTURE_FILTERING filtering, GRAPHIC_TEXTURE_WRAP wrap ) {
    
    GLenum filter = OPENGLES_2_GetFiltermode( filtering );
    GLenum wrap_mode = OPENGLES_2_GetWrapMode( wrap );
    
    GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); )
    GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); )
    
    GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode ); )
    GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode ); )
}

void GRAPHIC_SYSTEM::DiscardTexture( GRAPHIC_TEXTURE * texture ) {
    
    GFX_CHECK( glBindTexture( GL_TEXTURE_2D, 0 ); )
}


/*void GRAPHIC_SYSTEM::CreateTexture( GRAPHIC_TEXTURE * texture, const void * texture_data, bool generate_mipmap ) {
    
    GFX_CHECK( glActiveTexture(GL_TEXTURE0); )
    GFX_CHECK( glGenTextures( 1, &texture->GetTextureHandle() ); )
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    GFX_CHECK( glBindTexture( GL_TEXTURE_2D, texture->GetTextureHandle() ); )
    
    //static float pixels[] = { 0.0f, 0.0f,0.0f, 0.0f, 0.0f, 0.0f,0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
    // Give the image to OpenGL
    
    GRAPHIC_TEXTURE_INFO & info = texture->GetTextureInfo();
    
    GFX_CHECK( glTexImage2D( GL_TEXTURE_2D, 0, OPENGLES_2_GetTextureFormat(info.ImageType), info.Width, info.Height, 0, OPENGLES_2_GetTextureFormat(info.ImageType), GL_UNSIGNED_BYTE, texture_data ); )
    //GFX_CHECK( glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data ); )
    
    GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST ); )
    GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST ); )
}

void GRAPHIC_SYSTEM::CreateTexture( GRAPHIC_TEXTURE * texture, bool creates_depth_texture ) {
    
    GFX_CHECK( glActiveTexture(GL_TEXTURE0); )
    GFX_CHECK( glGenTextures( 1, &texture->GetTextureHandle() ); )
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    GFX_CHECK( glBindTexture( GL_TEXTURE_2D, texture->GetTextureHandle() ); )
    
    GRAPHIC_TEXTURE_INFO & info = texture->GetTextureInfo();
    
    GFX_CHECK( glTexImage2D( GL_TEXTURE_2D, 0, OPENGLES_2_GetTextureFormat(info.ImageType), info.Width, info.Height, 0, OPENGLES_2_GetTextureFormat(info.ImageType), GL_UNSIGNED_BYTE, 0 ); )
    
    GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); )
    GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); )
    
    GFX_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); )
    GFX_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); )
    
    {
        GFX_CHECK( glGenTextures(1, &texture->GetDepthTextureHandle() ); )
        GFX_CHECK( glBindTexture(GL_TEXTURE_2D, texture->GetDepthTextureHandle() ); )
        
        GFX_CHECK( glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24_OES, info.Width, info.Height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL); )
        
        GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); )
        GFX_CHECK( glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); )
        
        GFX_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); )
        GFX_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); )
    }
}*/

void GRAPHIC_SYSTEM::CreateVertexBuffer(GRAPHIC_MESH &mesh) {
    // Create Vertex Array Object
    
    GLuint & vb = mesh.GetVertexBuffer();
    GRAPHIC_SHADER_BIND components = mesh.GetVertexComponent();
    int stride = mesh.GetVertexStride();
    
    GFX_CHECK( glGenBuffers( 1, &vb); )
    GFX_CHECK( glBindBuffer( GL_ARRAY_BUFFER, vb); )
    GFX_CHECK( glBufferData( GL_ARRAY_BUFFER, mesh.GetVertexCoreBuffer()->GetSize(), mesh.GetVertexCoreBuffer()->getpointerAtIndex((unsigned int)0), GL_STATIC_DRAW ); )
    
    //GFX_CHECK( glGenVertexArrays(1, &mesh.GetVertexArrays()); )
    //GFX_CHECK( glBindVertexArray( mesh.GetVertexArrays()); )
    
    int vertex_offset = 0;
    
    if ( components & GRAPHIC_SHADER_BIND_Position ) {
        
        GFX_CHECK( glEnableVertexAttribArray(GRAPHIC_SHADER_BIND_OPENGLES2_Position); )
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGLES2_Position, 4, GL_FLOAT, GL_FALSE, stride* sizeof(GLfloat), (void*) vertex_offset); )
        
        vertex_offset += 4;
    }
    
    if ( components & GRAPHIC_SHADER_BIND_Normal ) {
        
        GFX_CHECK( glEnableVertexAttribArray(GRAPHIC_SHADER_BIND_OPENGLES2_Normal); )
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGLES2_Normal, 4, GL_FLOAT, GL_FALSE, stride* sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 4;
    }
    
    if ( components & GRAPHIC_SHADER_BIND_Texcoord0 ) {
        
        GFX_CHECK( glEnableVertexAttribArray(GRAPHIC_SHADER_BIND_OPENGLES2_Texcoord0); )
        GFX_CHECK( glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGLES2_Texcoord0, 2, GL_FLOAT, GL_FALSE, stride* sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 2;
    }
    
    if ( components & GRAPHIC_SHADER_BIND_SkinWeight ) {
        
        GFX_CHECK( glEnableVertexAttribArray(GRAPHIC_SHADER_BIND_OPENGLES2_SkinWeight); )
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGLES2_SkinWeight, 4, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 4;
    }
    
    if ( components & GRAPHIC_SHADER_BIND_JointIndices ) {
        
        GFX_CHECK( glEnableVertexAttribArray(GRAPHIC_SHADER_BIND_OPENGLES2_JointIndices); )
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGLES2_JointIndices, 4, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat)));
                  )
        
        vertex_offset += 4;
    }
    
    if ( components & GRAPHIC_SHADER_BIND_Tangents ) {
        
        GFX_CHECK( glEnableVertexAttribArray(GRAPHIC_SHADER_BIND_OPENGLES2_Tangents); )
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGLES2_Tangents, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 3;
    }
    
    if ( components & GRAPHIC_SHADER_BIND_Bitangents ) {
        
        GFX_CHECK( glEnableVertexAttribArray( GRAPHIC_SHADER_BIND_OPENGLES2_Bitangents); )
        GFX_CHECK( glVertexAttribPointer( GRAPHIC_SHADER_BIND_OPENGLES2_Bitangents, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 3;
    }
}

void GRAPHIC_SYSTEM::CreateIndexBuffer(GRAPHIC_MESH &mesh) {
    
    GFX_CHECK( glGenBuffers( 1, &mesh.GetIndexBuffer() ); )
    GFX_CHECK( glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndexBuffer()); )
    GFX_CHECK( glBufferData( GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndexCoreBuffer()->GetSize(), mesh.GetIndexCoreBuffer()->getpointerAtIndex((unsigned int)0), GL_STATIC_DRAW ); )
}

void GRAPHIC_SYSTEM::UpdateVertexBuffer( GRAPHIC_MESH * mesh, CORE_DATA_BUFFER & data ) {
    
    mesh->SetVertexCoreBuffer( &data );
    
    GFX_CHECK( glBindBuffer( GL_ARRAY_BUFFER, mesh->GetVertexBuffer()); )
    GFX_CHECK( glBufferData( GL_ARRAY_BUFFER, mesh->GetVertexCoreBuffer()->GetSize(), mesh->GetVertexCoreBuffer()->getpointerAtIndex((unsigned int)0), GL_STATIC_DRAW ); )
}

void GRAPHIC_SYSTEM::ApplyLightDirectional( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program ) {
    
    GRAPHIC_SHADER_ATTRIBUTE & directional_light_color = program.GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::DirectionalLightColor );
    GRAPHIC_SHADER_ATTRIBUTE & directional_light_direction = program.GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::DirectionalLightDirection );
    GRAPHIC_SHADER_ATTRIBUTE & directional_light_diffuse_intensity = program.GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::DirectionalLightDiffuseIntensity );
    GRAPHIC_SHADER_ATTRIBUTE & directional_light_ambient_intensity = program.GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::DirectionalLightAmbientIntensity );
    
    /*if ( directional_light_color.AttributeIndex != -1 ) {
        
        GFX_CHECK( glUniform4fv(
                                directional_light_color.AttributeIndex,
                                1,
                                (const GLfloat * )&light.InternalLight.Directional.Color); )
        
        GFX_CHECK( glUniform4fv(
                                directional_light_direction.AttributeIndex,
                                1,
                                (const GLfloat * )&light.InternalLight.Directional.Direction); )
        
        GFX_CHECK( glUniform1f( directional_light_ambient_intensity.AttributeIndex,
                               light.InternalLight.Directional.AmbientIntensity); )
        
        GFX_CHECK( glUniform1f( directional_light_diffuse_intensity.AttributeIndex,
                               light.InternalLight.Directional.DiffuseIntensity); )
    }*/
}

void GRAPHIC_SYSTEM::ApplyLightAmbient( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program ) {
    
    GRAPHIC_SHADER_ATTRIBUTE & ambient_light = program.GetShaderAttribute( GRAPHIC_SHADER_PROGRAM::AmbientLight );
    
    GRAPHIC_SYSTEM_ApplyMatrix(
        ambient_light.AttributeIndex,
        1,
        0,
        (const GLfloat * )&light.InternalLight.Ambient);
}

void GRAPHIC_SYSTEM::ApplyLightPoint( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program, int index ) {
    
    GRAPHIC_SHADER_ATTRIBUTE & point_light_position = program.GetShaderAttribute( index ? GRAPHIC_SHADER_PROGRAM::PointLight1Position : GRAPHIC_SHADER_PROGRAM::PointLight0Position );
    GRAPHIC_SHADER_ATTRIBUTE & point_light_color = program.GetShaderAttribute( index ? GRAPHIC_SHADER_PROGRAM::PointLight1Color : GRAPHIC_SHADER_PROGRAM::PointLight0Color );
    GRAPHIC_SHADER_ATTRIBUTE & point_light_diffuse_intensity = program.GetShaderAttribute( index ? GRAPHIC_SHADER_PROGRAM::PointLight1DiffuseIntensity : GRAPHIC_SHADER_PROGRAM::PointLight0DiffuseIntensity );
    GRAPHIC_SHADER_ATTRIBUTE & point_light_ambient_intensity = program.GetShaderAttribute( index ? GRAPHIC_SHADER_PROGRAM::PointLight1AmbientIntensity : GRAPHIC_SHADER_PROGRAM::PointLight0AmbientIntensity );
    
    GRAPHIC_SHADER_ATTRIBUTE & point_light_exp = program.GetShaderAttribute( index ? GRAPHIC_SHADER_PROGRAM::PointLight1Exp : GRAPHIC_SHADER_PROGRAM::PointLight0Exp );
    GRAPHIC_SHADER_ATTRIBUTE & point_light_linear = program.GetShaderAttribute( index ? GRAPHIC_SHADER_PROGRAM::PointLight1Linear : GRAPHIC_SHADER_PROGRAM::PointLight0Linear );
    GRAPHIC_SHADER_ATTRIBUTE & point_light_constant = program.GetShaderAttribute( index ? GRAPHIC_SHADER_PROGRAM::PointLight1Constant : GRAPHIC_SHADER_PROGRAM::PointLight0Constant );
    
    if ( point_light_position.AttributeIndex > 0 ) {
        
        GFX_CHECK( glUniform4fv(
                                point_light_position.AttributeIndex,
                                1,
                                (const GLfloat * )&light.InternalLight.Point.Position); )
        GFX_CHECK( glUniform4fv(
                                point_light_color.AttributeIndex,
                                1,
                                (const GLfloat * )&light.InternalLight.Point.Color); )
        
        GFX_CHECK( glUniform1f( point_light_ambient_intensity.AttributeIndex,
                               light.InternalLight.Point.AmbientIntensity); )
        GFX_CHECK( glUniform1f( point_light_diffuse_intensity.AttributeIndex,
                               light.InternalLight.Point.DiffuseIntensity); )
        
        GFX_CHECK( glUniform1f( point_light_exp.AttributeIndex,
                               light.InternalLight.Point.Exp); )
        GFX_CHECK( glUniform1f( point_light_linear.AttributeIndex,
                               light.InternalLight.Point.Linear); )
        GFX_CHECK( glUniform1f( point_light_constant.AttributeIndex,
                               light.InternalLight.Point.Constant); )
    }
}

void GRAPHIC_SYSTEM::ApplyLightSpot( const GRAPHIC_SHADER_LIGHT & light, GRAPHIC_SHADER_PROGRAM & program, int index ) {
    
    GRAPHIC_SHADER_ATTRIBUTE & spot_light_position = program.GetShaderAttribute( index ? GRAPHIC_SHADER_PROGRAM::SpotLight1Position : GRAPHIC_SHADER_PROGRAM::SpotLight0Position );
    GRAPHIC_SHADER_ATTRIBUTE & spot_light_direction = program.GetShaderAttribute( index ? GRAPHIC_SHADER_PROGRAM::SpotLight1Direction : GRAPHIC_SHADER_PROGRAM::SpotLight0Direction );
    GRAPHIC_SHADER_ATTRIBUTE & spot_light_color = program.GetShaderAttribute( index ? GRAPHIC_SHADER_PROGRAM::SpotLight1Color : GRAPHIC_SHADER_PROGRAM::SpotLight0Color );
    GRAPHIC_SHADER_ATTRIBUTE & spot_light_diffuse_intensity = program.GetShaderAttribute( index ? GRAPHIC_SHADER_PROGRAM::SpotLight1DiffuseIntensity : GRAPHIC_SHADER_PROGRAM::SpotLight0DiffuseIntensity );
    GRAPHIC_SHADER_ATTRIBUTE & spot_light_ambient_intensity = program.GetShaderAttribute( index ? GRAPHIC_SHADER_PROGRAM::SpotLight1AmbientIntensity : GRAPHIC_SHADER_PROGRAM::SpotLight0AmbientIntensity );
    
    GRAPHIC_SHADER_ATTRIBUTE & spot_light_exp = program.GetShaderAttribute( index ? GRAPHIC_SHADER_PROGRAM::SpotLight1Exp : GRAPHIC_SHADER_PROGRAM::SpotLight0Exp );
    GRAPHIC_SHADER_ATTRIBUTE & spot_light_linear = program.GetShaderAttribute( index ? GRAPHIC_SHADER_PROGRAM::SpotLight1Linear : GRAPHIC_SHADER_PROGRAM::SpotLight0Linear );
    GRAPHIC_SHADER_ATTRIBUTE & spot_light_constant = program.GetShaderAttribute( index ? GRAPHIC_SHADER_PROGRAM::SpotLight1Constant : GRAPHIC_SHADER_PROGRAM::SpotLight0Constant );
    GRAPHIC_SHADER_ATTRIBUTE & spot_light_cutoff = program.GetShaderAttribute( index ? GRAPHIC_SHADER_PROGRAM::SpotLight1Cutoff : GRAPHIC_SHADER_PROGRAM::SpotLight0Cutoff );
    
    if ( spot_light_position.AttributeIndex > 0 ) {
        
        GFX_CHECK( glUniform4fv(
                                spot_light_position.AttributeIndex,
                                1,
                                (const GLfloat * )&light.InternalLight.Spot.Position); )
        GFX_CHECK( glUniform4fv(
                                spot_light_direction.AttributeIndex,
                                1,
                                (const GLfloat * )&light.InternalLight.Spot.Direction); )
        GFX_CHECK( glUniform4fv(
                                spot_light_color.AttributeIndex,
                                1,
                                (const GLfloat * )&light.InternalLight.Spot.Color); )
        
        GFX_CHECK( glUniform1f( spot_light_ambient_intensity.AttributeIndex,
                               light.InternalLight.Spot.AmbientIntensity); )
        GFX_CHECK( glUniform1f( spot_light_diffuse_intensity.AttributeIndex,
                               light.InternalLight.Spot.DiffuseIntensity); )
        
        GFX_CHECK( glUniform1f( spot_light_exp.AttributeIndex,
                               light.InternalLight.Spot.Exp); )
        GFX_CHECK( glUniform1f( spot_light_linear.AttributeIndex,
                               light.InternalLight.Spot.Linear); )
        GFX_CHECK( glUniform1f( spot_light_constant.AttributeIndex,
                               light.InternalLight.Spot.Constant); )
        GFX_CHECK( glUniform1f( spot_light_cutoff.AttributeIndex,
                               light.InternalLight.Spot.Cutoff); )
    }
}

void GRAPHIC_SYSTEM::ApplyShaderAttributeVector( const float * vector, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {
    
    GFX_CHECK( glUniform4fv(
                            attribute.AttributeIndex,
                            1,
                            (const GLfloat * ) vector ); )
}

void GRAPHIC_SYSTEM::ApplyShaderAttributeFloat( const float value, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {
    
    GFX_CHECK( glUniform1f( attribute.AttributeIndex,
                           (const GLfloat ) value ); )
}

void GRAPHIC_SYSTEM::ApplyShaderAttributeMatrix( const float * matrix, GRAPHIC_SHADER_ATTRIBUTE & attribute ) {
    
    GRAPHIC_SYSTEM_ApplyMatrix(
        attribute.AttributeIndex,
        1,
        0,
        (const GLfloat * ) matrix);
}

void GRAPHIC_SYSTEM::ReleaseTexture( GRAPHIC_TEXTURE * texture ) {
    
    if ( texture->GetTextureHandle() ) {
        
        GFX_CHECK( glDeleteTextures( 1, &texture->GetTextureHandle()); )
    }
    
    if ( texture->GetDepthTextureHandle() ) {
        
        GFX_CHECK( glDeleteTextures( 1, &texture->GetDepthTextureHandle()
                                    ); )
    }
}

void GRAPHIC_SYSTEM::ApplyBuffers(GRAPHIC_MESH &mesh) {
    
    GFX_CHECK(glBindBuffer(GL_ARRAY_BUFFER, mesh.GetVertexBuffer()); )
    
    int vertex_offset = 0;
    GRAPHIC_SHADER_BIND component = mesh.GetVertexComponent();
    int stride = mesh.GetVertexStride();
    
    if ( component & GRAPHIC_SHADER_BIND_Position ) {
        
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGLES2_Position, 4, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*) 0); )
        
        vertex_offset += 4;
    }
    
    if ( component & GRAPHIC_SHADER_BIND_Normal ) {
        
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGLES2_Normal, 4, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 4;
    }
    
    if ( component & GRAPHIC_SHADER_BIND_Texcoord0 ) {
        
        GFX_CHECK( glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGLES2_Texcoord0, 2, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 2;
    }
    
    if ( component & GRAPHIC_SHADER_BIND_SkinWeight ) {
        
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGLES2_SkinWeight, 4, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 4;
    }
    
    if ( component & GRAPHIC_SHADER_BIND_JointIndices ) {
        
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGLES2_JointIndices, 4, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat)));
                  )
        
        vertex_offset += 4;
    }
    
    if ( component & GRAPHIC_SHADER_BIND_Tangents ) {
        
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGLES2_Tangents, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 3;
    }
    
    if ( component & GRAPHIC_SHADER_BIND_Bitangents ) {
        
        GFX_CHECK(glVertexAttribPointer(GRAPHIC_SHADER_BIND_OPENGLES2_Bitangents, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (void*)(vertex_offset * sizeof(GLfloat))); )
        
        vertex_offset += 3;
    }
    
    //GFX_CHECK( glBindBuffer(GL_ARRAY_BUFFER, 0); )
    
    GFX_CHECK( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.GetIndexBuffer()) ; )
    
    GFX_CHECK( glDrawElements(
                              GRAPHIC_MESH_POLYGON_RENDER_MODE_GetForOpenglES2( mesh.GetPolygonRenderMode() ),      // mode
                              mesh.GetIndexCoreBuffer()->GetSize() / 4,    // count
                              GL_UNSIGNED_INT,   // type
                              (void*)0); )
}

void GRAPHIC_SYSTEM::ReleaseBuffers(GRAPHIC_MESH &mesh) {
    
    GFX_CHECK( glDeleteBuffers(1, &mesh.GetIndexBuffer()); )
    GFX_CHECK( glDeleteBuffers(1, &mesh.GetVertexBuffer()); )
}

void GRAPHIC_SYSTEM::ApplyDepthTexture( GRAPHIC_TEXTURE * texture, int texture_index, int shader_texture_attribute_index ) {
    
    GFX_CHECK( glActiveTexture( texture_index == 0 ? GL_TEXTURE0 : GL_TEXTURE1 ); )
    GFX_CHECK( glBindTexture( GL_TEXTURE_2D, texture->GetDepthTextureHandle() ); )
    GFX_CHECK( glUniform1i( shader_texture_attribute_index, texture_index ); )
}

void GRAPHIC_SYSTEM::EnableScissor(bool enable) {
    if ( enable ) {
        
        GFX_CHECK( glEnable( GL_SCISSOR_TEST ); )
    }
    else {
        GFX_CHECK( glDisable( GL_SCISSOR_TEST ); )
    }
}

void GRAPHIC_SYSTEM::SetScissorRectangle( float x, float y, float width, float height ) {
    
    GFX_CHECK( glScissor((GLint)x, (GLint)y, (GLsizei)width, (GLsizei)height); )
}

#endif
