//
//  METAL_TEST.hpp
//  MetalTestOSX
//
//  Created by Christophe Bernard on 16/10/2019.
//  Copyright © 2019 Christophe Bernard. All rights reserved.
//

#ifndef METAL_TEST_hpp
#define METAL_TEST_hpp

#include "CORE_RUNTIME_ENVIRONMENT.h"
#include "CORE_APPLICATION.h"
#include "CORE_FILESYSTEM.h"
#include "GRAPHIC_UI_ELEMENT.h"
#include "GRAPHIC_CAMERA_ORTHOGONAL.h"
#include "ASSET_SCREEN.h"
#include "CORE_DATA_TYPES.h"
#include "CORE_HELPERS_COLOR.h"
#include "GRAPHIC_UI_TEXT.h"
#include "GRAPHIC_MESH_MANAGER.h"
#include "RESOURCE_CONTAINER.h"
#include "GRAPHIC_RENDERER.h"
#include "GRAPHIC_UI_SYSTEM.h"
#include "CORE_HELPERS_CALLBACK.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "CORE_DATA_LOADER.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME_MANAGER.h"
#include "CORE_ABSTRACT_RUNTIME_LUA.h"
#include "CORE_DATA_JSON.h"
#include "GRAPHIC_RENDER_TARGET.h"
#include "GRAPHIC_RENDERER_TECHNIQUE.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(METAL_TEST, CORE_APPLICATION)

    METAL_TEST();
    virtual ~METAL_TEST();

    virtual void Initialize() override;
    virtual void Finalize() override;

    virtual void Update( float time_step ) override;
    virtual void Render() override;
    void RenderTechnique( GRAPHIC_RENDERER & renderer );

    CORE_FILESYSTEM
        DefaultFileystem;

private:

    GRAPHIC_SHADER_EFFECT::PTR
        Effect;
    GRAPHIC_OBJECT::PTR
        AnimatedObject;
    GRAPHIC_RENDER_TARGET
        PrimaryRenderTarget;
    GRAPHIC_RENDERER_TECHNIQUE
        DefaultTechnique;
    GRAPHIC_OBJECT_SHAPE_PLAN
        PlanObject;
    CORE_MATH_MATRIX m1,m2;
/*
GRAPHIC_CAMERA_ORTHOGONAL
    * InterfaceCamera,
    * RenderTargetCamera;
GRAPHIC_SHADER_LIGHT
    Directional,
    Ambient;
GRAPHIC_OBJECT_SHAPE_PLAN
    PlanObject;
GRAPHIC_OBJECT_SHAPE_SPHERE
    SphereObject;
    FinalRenderTarget,
    LightRenderTarget,
    SpecularRenderTarget,
    BloomRenderTarget,
    ShadowMapRenderTarget1,
    ShadowMapRenderTarget2,
    ShadowMapRenderTarget3;
GRAPHIC_TEXTURE_BLOCK::PTR
    TextureBlock1,
    TextureBlock2,
    TextureBlock3,
    TextureBlock4;
GRAPHIC_SHADER_EFFECT::PTR
    UIShaderTextured;
GRAPHIC_RENDERER_TECHNIQUE
    TransparentTechnique;
GRAPHIC_RENDERER_TECHNIQUE_SPEEDBLUR
    SpeedBlurTechnique;
GRAPHIC_RENDERER_TECHNIQUE_BLOOM
    BloomTechnique;
GRAPHIC_RENDERER_TECHNIQUE_CASCADE_SHADOW_MAP
    CascadeShadowMapTechnique;
GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING
    DeferredShadingTechnique;
GRAPHIC_RENDER_TECHNIQUE_SSAO
    SSAOTechnique;*/


XS_CLASS_END

#endif /* METAL_TEST_hpp */
