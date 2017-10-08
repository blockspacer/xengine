//
//  R3D_PLAYER.cpp
//  Run3d
//
//  Created by Christophe Bernard on 10/07/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#include "R3D_PLAYER.h"
#include "GAMEPLAY_COMPONENT_MANAGER.h"

R3D_PLAYER::R3D_PLAYER() :
    Ship( NULL ) {
    
}

void R3D_PLAYER::Initialize() {
    
    Ship = GAMEPLAY_COMPONENT_MANAGER::GetInstance().CreateEntity< R3D_PLAYER_SHIP >();
    Ship->Initialize();
}
