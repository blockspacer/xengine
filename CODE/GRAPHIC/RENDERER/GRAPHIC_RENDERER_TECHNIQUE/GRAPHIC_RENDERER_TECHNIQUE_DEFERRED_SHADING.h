//
//  GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 5/06/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING_hpp
#define GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING_hpp

#include "GRAPHIC_RENDERER_TECHNIQUE.h"
#include "GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING_TEXTURE_TYPE.h"
#include "GRAPHIC_RENDER_TARGET.h"
#include "GRAPHIC_MATERIAL.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_OBJECT_SHAPE_SPHERE.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_DEFERRED_POINT_SHADING.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING, GRAPHIC_RENDERER_TECHNIQUE )

    GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING();
    virtual ~GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING();

public:

    virtual void Initialize( GRAPHIC_RENDERER & renderer );
    virtual void ApplyFirstPass( GRAPHIC_RENDERER & renderer );
    virtual void ApplySecondPass( GRAPHIC_RENDERER & renderer );

    void ApplyPointLightPass( GRAPHIC_RENDERER & renderer );
    void ApplySpotLightPass( GRAPHIC_RENDERER & renderer );

    float CalculatePointLightSphereAndExtent(const GRAPHIC_SHADER_LIGHT &);

    GRAPHIC_MATERIAL
        Material;
    GRAPHIC_CAMERA::PTR
        GameCamera;
    GRAPHIC_OBJECT_SHAPE_PLAN::PTR
        PlanObject;
    GRAPHIC_OBJECT_SHAPE_SPHERE::PTR
        SphereObject;
    GRAPHIC_TEXTURE_BLOCK
        TextureBlock1,
        TextureBlock2,
        TextureBlock3,
        TextureBlock4,
        TextureBlock5;
    GRAPHIC_SHADER_EFFECT::PTR
        AmbientDirectionalDefferedEffect,
        SpotDeferredEffect,
        PointDefferedEffect;
    /*GRAPHIC_SHADER_EFFECT_DEFERRED_POINT_SHADING::PTR
        PointDefferedEffect;*/
    GRAPHIC_RENDER_TARGET
        RenderTarget;
    GRAPHIC_RENDER_TARGET::PTR
        FinalRenderTarget;

XS_CLASS_END

#endif /* GRAPHIC_RENDERER_TECHNIQUE_DEFERRED_SHADING_hpp */