//
//  GAMEPLAY_COMPONENT_ANIMATION_CONTROLLER.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 31/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_ANIMATION__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_ANIMATION__

#include "GAMEPLAY_COMPONENT.h"
#include "GRAPHIC_MESH_ANIMATION_CONTROLLER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR_WITH_COPY( GAMEPLAY_COMPONENT_ANIMATION, GAMEPLAY_COMPONENT )

    GAMEPLAY_COMPONENT_ANIMATION();
    virtual ~GAMEPLAY_COMPONENT_ANIMATION();

    CORE_HELPERS_FACTORY_Element(GAMEPLAY_COMPONENT_ANIMATION, GAMEPLAY_COMPONENT, GAMEPLAY_COMPONENT_TYPE, GAMEPLAY_COMPONENT_TYPE_Animation)

    void Update( float time_step, GRAPHIC_MESH_SKELETON_JOINT * skeleton );

    inline void SetAnimation( const GRAPHIC_MESH_ANIMATION_CONTROLLER & animation ) { Animation = animation; }
    inline GRAPHIC_MESH_ANIMATION_CONTROLLER & GetAnimation() { return Animation; }
    inline void SetSpeed( float speed ) { Speed = speed; }

    virtual void Reset() override {
        Animation.Initialize();
    }

private :

    GRAPHIC_MESH_ANIMATION_CONTROLLER
        Animation;
    float
        Speed;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_ANIMATION__) */
