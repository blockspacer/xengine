//
//  GAMEPLAY_RULE_START.cpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 25/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#include "GAMEPLAY_RULE_START.h"
#include "APPLICATION_CONFIGURATION.h"
#include "GAMEPLAY_PLAYER.h"
#include "GAMEPLAY_GAME_BOARD_CELL.h"

GAMEPLAY_RULE_START::GAMEPLAY_RULE_START() :
    GAMEPLAY_RULE() {
    
}

GAMEPLAY_RULE_START::~GAMEPLAY_RULE_START() {
    
}

void GAMEPLAY_RULE_START::OnPassOntoCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
    player->AddMoney( APPLICATION_CONFIGURATION_OPTIONS::GetInstance().StartCellMoney );
}

void GAMEPLAY_RULE_START::OnLeftCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player )  {
    
    if ( APPLICATION_CONFIGURATION_OPTIONS::GetInstance().StopOnStartGivesMoreMoney ) {
        
        player->AddMoney( APPLICATION_CONFIGURATION_OPTIONS::GetInstance().StartCellMoney );
    }
}

void GAMEPLAY_RULE_START::OnStoppedCell( GAMEPLAY_GAME_BOARD_CELL * cell, GAMEPLAY_PLAYER * player ) {
    
}
