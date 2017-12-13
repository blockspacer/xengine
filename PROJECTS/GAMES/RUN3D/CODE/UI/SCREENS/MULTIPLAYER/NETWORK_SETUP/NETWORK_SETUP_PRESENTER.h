//
//  NETWORK_SETUP_PRESENTER.hpp
//  RUN3D
//
//  Created by Christophe Bernard on 19/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef NETWORK_SETUP_PRESENTER_hpp
#define NETWORK_SETUP_PRESENTER_hpp

#include "GRAPHIC_UI_PRESENTER.h"
#include "NETWORK_PLAYER.h"
#include "NETWORK_SERVER.h"
#include "NETWORK_CLIENT.h"
#include "R3D_BASE_PRESENTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( NETWORK_SETUP_PRESENTER, R3D_BASE_PRESENTER)

    NETWORK_SETUP_PRESENTER( GRAPHIC_UI_FRAME * view );
    virtual ~NETWORK_SETUP_PRESENTER();

    virtual void Configure() override;
    void Update( const float step );

    void GameStarted( std::vector<NETWORK_PLAYER *> & players, int seed);

    void StartGameButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_EVENT event );
    void SelectGameButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_EVENT event );
    void OnBackButtonClicked( GRAPHIC_UI_ELEMENT * clicked_element, GRAPHIC_UI_ELEMENT_EVENT event );

    void OnClientConnected(NETWORK_PLAYER * player);
    void OnClientDisconnected(NETWORK_PLAYER * player);
    void OnChatMessageReceived(NETWORK_PLAYER * player, const char * message);
    void OnGameStarting();
    void OnStoppedGameStarting();

private:

    bool
        NavigationIsRequested,
        GameIsStarting;
    float
        CountDown;
    NETWORK_SERVER
        * Server;
    NETWORK_CLIENT
        * Client;

XS_CLASS_END

#endif /* NETWORK_SETUP_PRESENTER_hpp */
