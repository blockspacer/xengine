//
//  GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 31/03/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION__
#define __GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION__

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT_SYSTEM.h"
#include "GRAPHIC_RENDERER.h"
#include "CORE_HELPERS_UNIQUE.h"
#ifndef PLATFORM_WINDOWS
    #include "TOOL_BULLET_GL_DEBUGGER.h"
#endif

#ifdef __BULLET_PHYSICS__
    #include "btBulletDynamicsCommon.h"
#endif

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION, GAMEPLAY_COMPONENT_SYSTEM )

    GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION();
    virtual ~GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION();

    virtual void Initialize() override;
    virtual void Update( float time_step ) override;
    virtual void Render( GRAPHIC_RENDERER & renderer ) override;
    virtual void Finalize() override;

    inline void SetGravity( const float gravity ) { Gravity = gravity; }
    inline void SetRenderer( GRAPHIC_RENDERER * renderer ) { Renderer = renderer; }

    #ifdef __BULLET_PHYSICS__
        void SetCollisionFilter( btOverlapFilterCallback * callback );

        btDiscreteDynamicsWorld * GetDynamicsWorld() { return DynamicsWorld; }

        inline void SetNearCallback( btNearCallback & callback ) {
            
            NearCallback = &callback;
        }

    #endif

    virtual void AddEntity( GAMEPLAY_COMPONENT_ENTITY_HANDLE & handle, GAMEPLAY_COMPONENT_ENTITY * entity) override { abort(); }
    void AddEntity( GAMEPLAY_COMPONENT_ENTITY_HANDLE & handle, GAMEPLAY_COMPONENT_ENTITY * entity, int group, int mask );
    void AddStaticEntity( GAMEPLAY_COMPONENT_ENTITY_HANDLE & handle, GAMEPLAY_COMPONENT_ENTITY * entity, int group, int mask );

    void DebugDrawWorld();

private :

    GRAPHIC_RENDERER
        * Renderer;
    float
        Gravity;

#ifdef __BULLET_PHYSICS__
    btDiscreteDynamicsWorld
        * DynamicsWorld;
    btNearCallback
        * NearCallback;

    #if DEBUG && !defined(PLATFORM_WINDOWS)
        TOOL_BULLET_GL_DEBUGGER
            Debugger;
    #endif
#endif

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GAMEPLAY_COMPONENT_SYSTEM_COLLISION_DETECTION__) */
