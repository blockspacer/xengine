//
//  SERVICE_NETWORK_COMMAND.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 26/08/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "SERVICE_NETWORK_COMMAND.h"
#include "SERVICE_NETWORK_SYSTEM.h"
#include "CORE_DATA_STREAM.h"
#include "CORE_DATA_BUFFER.h"

XS_CLASS_SERIALIZER_TemplateScalar( SERVICE_NETWORK_CONNECTION_TYPE )

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( SERVICE_NETWORK_COMMAND )
    XS_DEFINE_ClassMember( SERVICE_NETWORK_CONNECTION_TYPE , Type )
    XS_DEFINE_ClassMember( int, Size )
    XS_DEFINE_ClassMemberArray( char, (char **) &Data, Size )
XS_END_INTERNAL_MEMORY_LAYOUT

SERVICE_NETWORK_COMMAND::SERVICE_NETWORK_COMMAND() :
    Type( SERVICE_NETWORK_CONNECTION_TYPE_None ),
    Data( NULL ),
    Size( 0 ),
    Address() {
    
}

SERVICE_NETWORK_COMMAND::~SERVICE_NETWORK_COMMAND() {

}

float SERVICE_NETWORK_COMMAND::ServiceVersion = NETWORK_SERVICE_VERSION;