//
//  GAMEPLAY_GAME.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 30/01/2020.
//  Copyright © 2020 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_GAME_hpp
#define GAMEPLAY_GAME_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_FIXED_STATE_MACHINE.h"
#include "CORE_FIXED_STATE_EVENT.h"
#include "GAMEPLAY_SCENE.h"
#include "GRAPHIC_RENDERER.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION.h"
#include "PERIPHERIC_INTERACTION_SYSTEM.h"
#include "GAMEPLAY_ACTION_SYSTEM.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_LIGHTING.h"
#include "GAMEPLAY_COMPONENT_SYSTEM_RENDERER.h"

XS_CLASS_BEGIN( GAMEPLAY_GAME )

    GAMEPLAY_GAME();
    ~GAMEPLAY_GAME();

    void Render( GRAPHIC_RENDERER & renderer, int transparent_mask );
    void Update( const float step );

    void Initialize();
    void Finalize();

    inline GAMEPLAY_SCENE & GetScene() { return Scene; }

    //inline GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION * GetBulletSystem() { return BulletSystem; }

    //inline GAMEPLAY_COMPONENT_SYSTEM_LIGHTING * GetLightingSystem() { return (GAMEPLAY_COMPONENT_SYSTEM_LIGHTING *) Scene.GetRenderableSystemTable()[0]; }


    /*CORE_FIXED_STATE_MACHINE_DefineEvent( UPDATE_EVENT, const float )
    CORE_FIXED_STATE_MACHINE_DefineEventVoid( PAUSE_EVENT )

    CORE_FIXED_STATE_MACHINE_DeclareBaseState(GAME_BASE_STATE, R3D_GAMEPLAY_GAME )
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_End()

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, IDLE_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( IDLE_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, GAME_STARTING )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( GAME_STARTING )

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, GAME_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( PAUSE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( GAME_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, PAUSE_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( PAUSE_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( GAME_BASE_STATE, END_GAME_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( END_GAME_STATE )*/

protected:

    /*CORE_FIXED_STATE_MACHINE<GAME_BASE_STATE, R3D_GAMEPLAY_GAME>
        StateMachine;*/
    GAMEPLAY_SCENE
        Scene;
    GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION
        * BulletSystem;

XS_CLASS_END

#endif /* GAMEPLAY_GAME_hpp */
