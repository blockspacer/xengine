//
//  GAMEPLAY_ACTION_COMMAND_START_GAME.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 6/03/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_ACTION_COMMAND_START_GAME.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_ACTION_COMMAND_START_GAME )
    XS_DEFINE_ClassMember(std::vector<NETWORK_PLAYER *>, Players )
    XS_DEFINE_ClassMember(int, Seed )
XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(GAMEPLAY_ACTION_COMMAND_START_GAME, GAMEPLAY_ACTION_TYPE_ClientRejected)

GAMEPLAY_ACTION_COMMAND_START_GAME::GAMEPLAY_ACTION_COMMAND_START_GAME() :
    GAMEPLAY_ACTION(),
    Players(),
    Seed() {
}

GAMEPLAY_ACTION_COMMAND_START_GAME::GAMEPLAY_ACTION_COMMAND_START_GAME( std::vector<NETWORK_PLAYER*> & players, int seed ) :
    GAMEPLAY_ACTION(),
    Players(),
    Seed( seed ){
    
    Players = players;
}

GAMEPLAY_ACTION_COMMAND_START_GAME::~GAMEPLAY_ACTION_COMMAND_START_GAME() {
    
}

void GAMEPLAY_ACTION_COMMAND_START_GAME::Apply() {
    
    GameStartingCallback( Players, Seed );
}

CORE_HELPERS_CALLBACK_2< std::vector< NETWORK_PLAYER* > &, int > GAMEPLAY_ACTION_COMMAND_START_GAME::GameStartingCallback;