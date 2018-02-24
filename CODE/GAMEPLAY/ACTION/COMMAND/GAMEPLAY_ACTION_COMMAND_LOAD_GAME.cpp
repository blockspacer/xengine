//
//  GAMEPLAY_ACTION_COMMAND_LOAD_GAME.cpp
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 11/02/18.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_ACTION_COMMAND_LOAD_GAME.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_ACTION_COMMAND_LOAD_GAME )
    XS_DEFINE_ClassMember( "Players", std::vector<NETWORK_PLAYER *>, Players )
XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation( GAMEPLAY_ACTION_COMMAND_LOAD_GAME, GAMEPLAY_ACTION_TYPE_LoadGame )

GAMEPLAY_ACTION_COMMAND_LOAD_GAME::GAMEPLAY_ACTION_COMMAND_LOAD_GAME() :
    GAMEPLAY_ACTION(),
    Players() {
    
}

GAMEPLAY_ACTION_COMMAND_LOAD_GAME::GAMEPLAY_ACTION_COMMAND_LOAD_GAME( std::vector<NETWORK_PLAYER*> & players ) : 
    GAMEPLAY_ACTION(),
    Players() {
        
    Players = players;
}

GAMEPLAY_ACTION_COMMAND_LOAD_GAME::GAMEPLAY_ACTION_COMMAND_LOAD_GAME( const GAMEPLAY_ACTION_COMMAND_LOAD_GAME & other) :
    GAMEPLAY_ACTION(),
    Players() {
    
    abort();
}


GAMEPLAY_ACTION_COMMAND_LOAD_GAME::~GAMEPLAY_ACTION_COMMAND_LOAD_GAME() {
    
}

void GAMEPLAY_ACTION_COMMAND_LOAD_GAME::Apply() {
    
}
