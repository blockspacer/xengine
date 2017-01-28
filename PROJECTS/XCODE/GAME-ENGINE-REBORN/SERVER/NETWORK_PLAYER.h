//
//  NETWORK_PLAYER.hpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 30/10/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef NETWORK_PLAYER_hpp
#define NETWORK_PLAYER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "CORE_DATA_STREAM.h"
#include "SERVICE_NETWORK_COMMAND.h"
#include "SERVICE_NETWORK_CONNECTION.h"
#include "CORE_HELPERS_UNIQUE_IDENTIFIER.h"
#include <string>
#include "CORE_DATA_MODEL.h"

#define OUTGOING_MESSAGE_QUEUE_SIZE 36

XS_CLASS_BEGIN_WITH_ANCESTOR(NETWORK_PLAYER, CORE_DATA_MODEL)

XS_DEFINE_SERIALIZABLE

NETWORK_PLAYER();

NETWORK_PLAYER( SERVICE_NETWORK_CONNECTION * connexion, int player_id, bool is_active, bool is_host );

NETWORK_PLAYER(int player_id, bool is_active);

CORE_DATA_STREAM & PrepareMessage();

const CORE_HELPERS_UNIQUE_IDENTIFIER & GetUniqueId() const { return UniqueId; }
const std::string & GetName() const { return Name; }
void AppendMessage(SERVICE_NETWORK_COMMAND * message );
SERVICE_NETWORK_CONNECTION * GetNetworkConnexion() { return CurrentNewtorkStream; }
void SetNetworkConnexion( SERVICE_NETWORK_CONNECTION *connection ) { CurrentNewtorkStream = connection; }

private :

std::string
    Name;
int
    OutGoingMessageQueueIterator;
bool
    IsActive,
    IsHost;
CORE_DATA_STREAM
    OutGoingMessage;
std::array< SERVICE_NETWORK_COMMAND *, OUTGOING_MESSAGE_QUEUE_SIZE>
    OutGoingMessageQueue;
SERVICE_NETWORK_CONNECTION
    * CurrentNewtorkStream;
CORE_HELPERS_UNIQUE_IDENTIFIER
    UniqueId;

XS_CLASS_END

#endif /* NETWORK_PLAYER_hpp */
