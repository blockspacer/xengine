//
//  MULTIPLAYER_GAME_LAUNCH_VALIDATOR.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 8/01/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#ifndef MULTIPLAYER_GAME_LAUNCH_VALIDATOR_hpp
#define MULTIPLAYER_GAME_LAUNCH_VALIDATOR_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_PRESENTER.h"

XS_CLASS_BEGIN(MULTIPLAYER_GAME_LAUNCH_VALIDATOR)

MULTIPLAYER_GAME_LAUNCH_VALIDATOR();

void Validate( GRAPHIC_UI_PRESENTER * presenter );

XS_CLASS_END

#endif /* MULTIPLAYER_GAME_LAUNCH_VALIDATOR_hpp */
