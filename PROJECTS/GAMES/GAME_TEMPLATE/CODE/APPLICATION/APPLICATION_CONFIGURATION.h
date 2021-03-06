//
//  APPLICATION_CONFIGURATION.h
//  MULTIPOLY
//
//  Created by Christophe Bernard on 22/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef APPLICATION_CONFIGURATION_h
#define APPLICATION_CONFIGURATION_h

#define APPLICATION_PLAYER_BASE_MONEY 1500
#define APPLICATION_PRISON_CELL_INDEX 10
#define APPLICATION_LAST_CELL 39
#define APPLICATION_SPECIAL_ADVANCE_1 24
#define APPLICATION_SPECIAL_ADVANCE_2 11
#define APPLICATION_SPECIAL_ADVANCE_3 15

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"

class APPLICATION_CONFIGURATION_OPTIONS {
    
public :
    
    XS_DEFINE_UNIQUE( APPLICATION_CONFIGURATION_OPTIONS )
    
    bool StopOnStartGivesMoreMoney;
    int StartCellMoney;
    int StartUpMoney;
};

#endif /* APPLICATION_CONFIGURATION_h */
