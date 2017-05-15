//
//  GRAPHIC_OBJECT_SHAPE.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE__
#define __GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE__

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_OBJECT.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(GRAPHIC_OBJECT_SHAPE, GRAPHIC_OBJECT)

    GRAPHIC_OBJECT_SHAPE();
    virtual ~GRAPHIC_OBJECT_SHAPE();

    virtual void InitializeShape( GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR shader);
    virtual void Render( GRAPHIC_RENDERER & renderer ) override;

    void BindShaderColorAttribute();

    inline void SetTextureBlock( GRAPHIC_TEXTURE_BLOCK * block ) { TextureBlock = block; }
    inline void SetSecondTextureBlock( GRAPHIC_TEXTURE_BLOCK * block ) { SecondTextureBlock = block; }
    inline void SetThirdTextureBlock( GRAPHIC_TEXTURE_BLOCK * block ) { ThirdTextureBlock = block; }

    inline void SetEffect( GRAPHIC_SHADER_EFFECT * effect ) { Effect = effect; }

protected :

    //Texture blocks must not be used here
    GRAPHIC_TEXTURE_BLOCK
        * TextureBlock,
        * SecondTextureBlock,
        * ThirdTextureBlock;
    GRAPHIC_SHADER_EFFECT
        * Effect;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_OBJECT_SHAPE__) */
