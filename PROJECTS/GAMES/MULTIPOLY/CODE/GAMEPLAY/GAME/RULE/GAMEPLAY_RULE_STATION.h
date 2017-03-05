//
//  GAMEPLAY_RULE_STATION.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 25/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_RULE_STATION_hpp
#define GAMEPLAY_RULE_STATION_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_RULE_PROPERTY.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GAMEPLAY_RULE_STATION, GAMEPLAY_RULE_PROPERTY )

    GAMEPLAY_RULE_STATION( int amount, int mortgage_price, GAMEPLAY_RULE_PROPERTY_GROUP * group );
    ~GAMEPLAY_RULE_STATION();

    virtual bool CanBuyHouse( GAMEPLAY_PLAYER * player ) override;
    virtual int CalculateAmount( GAMEPLAY_PLAYER * player ) override;

XS_CLASS_END

#endif /* GAMEPLAY_RULE_STATION_hpp */
