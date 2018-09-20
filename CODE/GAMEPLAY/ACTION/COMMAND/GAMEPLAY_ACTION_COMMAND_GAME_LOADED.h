//
//  GAMEPLAY_ACTION_COMMAND_CLIENT_GAME_LOADED.hpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 11/02/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#ifndef GAMEPLAY_ACTION_COMMAND_CLIENT_GAME_LOADED_hpp
#define GAMEPLAY_ACTION_COMMAND_CLIENT_GAME_LOADED_hpp

#include "GAMEPLAY_ACTION.h"
#include "NETWORK_PLAYER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_ACTION_COMMAND_GAME_LOADED, GAMEPLAY_ACTION )

    GAMEPLAY_ACTION_COMMAND_GAME_LOADED();
    GAMEPLAY_ACTION_COMMAND_GAME_LOADED( NETWORK_PLAYER * player );
    ~GAMEPLAY_ACTION_COMMAND_GAME_LOADED();

    XS_DEFINE_SERIALIZABLE

    CORE_HELPERS_FACTORY_Element( GAMEPLAY_ACTION_COMMAND_GAME_LOADED, GAMEPLAY_ACTION, GAMEPLAY_ACTION_TYPE, GAMEPLAY_ACTION_TYPE_GameLoaded )

    virtual void Apply() override;

    SimpleTrickForSerialization()

    NETWORK_PLAYER
        *Player;

XS_CLASS_END

#endif /* GAMEPLAY_ACTION_COMMAND_CLIENT_GAME_LOADED_hpp */