//
//  GAMEPLAY_COMPONENT_RENDER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 1/04/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_RENDER__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_RENDER__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_FACTORY.h"
#include "GAMEPLAY_COMPONENT.h"
#include "GAMEPLAY_COMPONENT_TYPE.h"
#include "CORE_HELPERS_SCALAR.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "CORE_MATH_SHAPE.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GRAPHIC_MATERIAL.h"
#include "RESOURCE_PROXY.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_COMPONENT_RENDER, GAMEPLAY_COMPONENT )

    GAMEPLAY_COMPONENT_RENDER();
    virtual ~GAMEPLAY_COMPONENT_RENDER();

    XS_DEFINE_SERIALIZABLE

    void * operator new(size_t size);
    void operator delete  ( void* ptr );

    CORE_HELPERS_FACTORY_Element(GAMEPLAY_COMPONENT_RENDER, GAMEPLAY_COMPONENT, GAMEPLAY_COMPONENT_TYPE, GAMEPLAY_COMPONENT_TYPE_Render)

    void Render( GRAPHIC_RENDERER &renderer, GAMEPLAY_COMPONENT_POSITION * component, GAMEPLAY_COMPONENT_POSITION * parent );

    struct INTERNAL_ARRAY_R{
        int LastIndex;
        GAMEPLAY_COMPONENT_RENDER * MemoryArray;
    };

    void SetObject( RESOURCE_PROXY & object ) { ObjectProxy = object; }
    void SetEffect( RESOURCE_PROXY & effect ) { EffectProxy = effect; }
    void SetShadowmapEffect( RESOURCE_PROXY & effect ) { ShadowmapEffectProxy = effect; }

    RESOURCE_PROXY & GetObject() { return ObjectProxy; }
    RESOURCE_PROXY & GetEffect() { return EffectProxy; }

    inline void SetScaleFactor( float scale_factor ) { ScaleFactor = scale_factor; }

    virtual GAMEPLAY_COMPONENT * GetComponentAt( int index, int offset ) override {

        return (GAMEPLAY_COMPONENT *) &(*InternalVector)[index].MemoryArray[offset];
    }

    static void Clear();
    static void SaveToStream( CORE_DATA_STREAM & stream );
    static void LoadFromStream( CORE_DATA_STREAM & stream );

    static int
        LastIndex,
        LastOffset;

private :

    RESOURCE_PROXY
        ObjectProxy,
        EffectProxy,
        ShadowmapEffectProxy;
    CORE_MATH_SHAPE
        BoundingObject;
    float
        ScaleFactor;
    static std::vector< INTERNAL_ARRAY_R >
        * InternalVector;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_RENDER__) */
