//
//  APPLICATION_NETWORK_COMMAND_CLIENT_REJECTED.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 29/12/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_ACTION_COMMAND_CLIENT_REJECTED.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_ACTION_COMMAND_CLIENT_REJECTED )

XS_END_INTERNAL_MEMORY_LAYOUT

ImplementTrickFroSerializeation(GAMEPLAY_ACTION_COMMAND_CLIENT_REJECTED, GAMEPLAY_ACTION_TYPE_ClientRejected)

GAMEPLAY_ACTION_COMMAND_CLIENT_REJECTED::GAMEPLAY_ACTION_COMMAND_CLIENT_REJECTED() :
    GAMEPLAY_ACTION(){
    
}

GAMEPLAY_ACTION_COMMAND_CLIENT_REJECTED::~GAMEPLAY_ACTION_COMMAND_CLIENT_REJECTED() {
    
}

void GAMEPLAY_ACTION_COMMAND_CLIENT_REJECTED::Apply() {
    
    ClientFromServerConnectionResponseCallback( NULL );
}

CORE_HELPERS_CALLBACK_1< NETWORK_PLAYER * >
    GAMEPLAY_ACTION_COMMAND_CLIENT_REJECTED::ClientFromServerConnectionResponseCallback;