//
//  R3D_SETUP_NETWORK_CLIENT_DELEGATE.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 20/12/17.
//  Copyright © 2017 IGZ. All rights reserved.
//

#ifndef R3D_SETUP_NETWORK_CLIENT_DELEGATE_hpp
#define R3D_SETUP_NETWORK_CLIENT_DELEGATE_hpp

#include "NETWORK_CLIENT_DELEGATE.h"

class NETWORK_SETUP_PRESENTER;

XS_CLASS_BEGIN_WITH_ANCESTOR( R3D_SETUP_NETWORK_CLIENT_DELEGATE, NETWORK_CLIENT_DELEGATE )

    R3D_SETUP_NETWORK_CLIENT_DELEGATE();
    virtual ~R3D_SETUP_NETWORK_CLIENT_DELEGATE() {
        
    }

    virtual void OnServerDiscovered( SERVICE_NETWORK_COMMAND * connexion ) override;
    virtual void OnServerRefused() override;
    virtual void OnServerInfo( GAMEPLAY_ACTION_COMMAND_SERVER_INFO * info ) override;
    virtual void OnServerAccepted( NETWORK_PLAYER * player ) override;
    virtual void OnServerDisconnected() override;
    virtual void OnGameStarted() override;

    NETWORK_SETUP_PRESENTER * Presenter;

XS_CLASS_END

#endif /* R3D_SETUP_NETWORK_CLIENT_DELEGATE_hpp */
