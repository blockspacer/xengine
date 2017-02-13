//
//  SERVICE_NETWORK_LOBBY.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 2/09/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "SERVICE_NETWORK_LOBBY.h"

SERVICE_NETWORK_LOBBY::SERVICE_NETWORK_LOBBY() :
    ConnectionPool(),
    UDPBroadcastConnection( NULL ),
    TCPClientConnection( NULL ),
    OnTCPNewConnectionCallback(),
    OnTCPConnectionLostCallback(),
    OnTCPConnectionResumedCallback(),
    OnTCPNetworkCommandReceivedCallback(),
    OnUdpBroadcastMessageReceivedCallback(),
    UdpBroadcastMinimumInterval(),
    UDPBroadcastMessage(),
    MaxPoolSize( 0 ),
    UdpBroadcastTask(),
    UdpBroadcastThread(),
    TcpNewConnectionThread() {
    
}

SERVICE_NETWORK_LOBBY::~SERVICE_NETWORK_LOBBY() {

}

void SERVICE_NETWORK_LOBBY::Initialize( int max_pool_size, const char * discover_message, const float interval ) {
    
    #if !PLATFORM_ANDROID
        assert( max_pool_size > 0 && max_pool_size <= NETWORK_SERVICE_LOBBY_MAX_CONNECTIONS );
    #endif
    
    for (int i = 0; i < NETWORK_SERVICE_LOBBY_MAX_CONNECTIONS; i++) {
        
        ConnectionPool[i] = NULL;
    }
    MaxPoolSize = max_pool_size;
    
    UdpBroadcastMinimumInterval = interval;
    
    char * t = (char*) CORE_MEMORY_ALLOCATOR_Allocate((int) strlen(discover_message));
    strcpy(t, discover_message);
    
    UDPBroadcastMessage.Open();
    UDPBroadcastMessage.InputBytes( (char*) t, (int) strlen( discover_message ) );
    UDPBroadcastMessage.Close();
    UDPBroadcastMessage.ResetOffset();
    
    for ( int i = 0; i < ConnectionPool.size(); i++ ) {
        
        ConnectionPool[ i ] = NULL;
    }
    
    SERVICE_NETWORK_SYSTEM::GetInstance().OnTCPDataReceivedCallback = new CORE_HELPERS_CALLBACK_2< SERVICE_NETWORK_COMMAND *, uv_stream_t * >( Wrapper2< SERVICE_NETWORK_LOBBY, SERVICE_NETWORK_COMMAND *, uv_stream_t *, &SERVICE_NETWORK_LOBBY::OnTCPDataReceived >, this );
    
    CORE_MEMORY_ALLOCATOR_Free( t );
}

void SERVICE_NETWORK_LOBBY::Finalize() {
    
    if ( UDPBroadcastConnection ) {
        
        UDPBroadcastConnection->Stop();
    }
    
    CORE_MEMORY_ObjectSafeDeallocation( OnTCPNetworkCommandReceivedCallback );
    CORE_MEMORY_ObjectSafeDeallocation( UDPBroadcastConnection );
    
    OnTCPConnectionLostCallback.Disconnect();
    OnTCPConnectionResumedCallback.Disconnect();
    OnTCPNewConnectionCallback.Disconnect();
    OnUdpBroadcastMessageReceivedCallback.Disconnect();
    
    OnTCPNetworkCommandReceivedCallback = NULL;
    UDPBroadcastConnection = NULL;
    UDPBroadcastConnection = NULL;
    
    //SERVICE_NETWORK_SYSTEM::GetInstance().Update( false );
    
    for ( int i = 0; i < ConnectionPool.size(); i++ ) {
        
        if ( ConnectionPool[ i ] ) {
            
            ConnectionPool[ i ]->Stop();
            
            delete ConnectionPool[ i ];
            ConnectionPool[ i ] = NULL;
        }
    }
}

void SERVICE_NETWORK_LOBBY::Update( const float time_step ) {
    
    static float accumulated_interval = 0.0f;
    
    if ( UDPBroadcastConnection ) {
    
        accumulated_interval += time_step;
        
        if ( accumulated_interval > UdpBroadcastMinimumInterval ) {
            
            UDPBroadcastConnection->Send( UDPBroadcastMessage );
            
            accumulated_interval = 0.0f;
        }
    }
}

void SERVICE_NETWORK_LOBBY::StartTCPListen() {
    
    SERVICE_NETWORK_SYSTEM::GetInstance().OnNewTCPConnectionCallback = new CORE_HELPERS_CALLBACK_1< uv_stream_t * >( &Wrapper1< SERVICE_NETWORK_LOBBY, uv_stream_t *, &SERVICE_NETWORK_LOBBY::OnTCPNewConnection>, this );
    
    TCPClientConnection = SERVICE_NETWORK_SYSTEM::GetInstance().CreateConnection(
        SERVICE_NETWORK_CONNECTION_TYPE_Tcp,
        SERVICE_NETWORK_SYSTEM::AllInterfaces,
        SERVICE_NETWORK_SYSTEM::AllInterfaces,
        1339,
        0,
        true );
    
    TCPClientConnection->Start();
}

void SERVICE_NETWORK_LOBBY::StopTCPListen() {
    
    SERVICE_NETWORK_SYSTEM::GetInstance().OnNewTCPConnectionCallback = NULL;
    
    for ( int i = 0; i < ConnectionPool.size(); i++ ) {
        
        if ( ConnectionPool[ i ] != NULL ) {
            
            ConnectionPool[ i ]->Stop();
        }
    }
}

void SERVICE_NETWORK_LOBBY::StartBroadcast() {
    
    UDPBroadcastConnection = SERVICE_NETWORK_SYSTEM::GetInstance().CreateConnection(
        SERVICE_NETWORK_CONNECTION_TYPE_Udp,
        SERVICE_NETWORK_SYSTEM::AllBroadcastAddress,
        SERVICE_NETWORK_SYSTEM::AllInterfaces,
        1338,
        SERVICE_NETWORK_SYSTEM::BroadcastPortDefault,
        false,
        true );
}

void SERVICE_NETWORK_LOBBY::StopBroadcast() {
    
    if ( UDPBroadcastConnection ) {
        
        UDPBroadcastConnection->Stop();
    }
}

void SERVICE_NETWORK_LOBBY::OnTCPNewConnection( uv_stream_t * server ) {
    
    for(int i = 0; i < NETWORK_SERVICE_LOBBY_MAX_CONNECTIONS; i++ ) {
        
        if ( ConnectionPool[ i ] == NULL ) {
            
            ConnectionPool[ i ] = SERVICE_NETWORK_SYSTEM::GetInstance().CreateConnection(
                SERVICE_NETWORK_CONNECTION_TYPE_TcpAccept,
                SERVICE_NETWORK_SYSTEM::AllInterfaces,
                SERVICE_NETWORK_SYSTEM::AllInterfaces,
                1339,
                0,
                true,
                false,
                true );
            
            ConnectionPool[ i ]->UVConnection.TCPType.TCPServer = server;
            
            int code = uv_accept( ConnectionPool[ i ]->UVConnection.TCPType.TCPServer,
                                 ( uv_stream_t * ) &ConnectionPool[ i ]->UVConnection.TCPType.TCPSocket );
            
            UV_CHECK_ERROR( code; )
            
            if ( code == 0 ) {
                
                UV_CHECK_ERROR( uv_read_start( ( uv_stream_t * ) &ConnectionPool[ i ]->UVConnection.TCPType.TCPSocket, &SERVICE_NETWORK_CONNECTION::AllocateReceiveBuffer, &SERVICE_NETWORK_CONNECTION::TCPReceivePacket ); )
                
                ConnectionPool[ i ]->InitializeCommunicationThread();
                
                if ( OnTCPNewConnectionCallback.IsConnected() ) {
                    
                    OnTCPNewConnectionCallback( ConnectionPool[ i ] );
                }
            }
            else {
                
                uv_close( ( uv_handle_t * ) &ConnectionPool[ i ]->UVConnection.TCPType.TCPSocket, NULL );
            }
            
            break;
        }
    }
}

void SERVICE_NETWORK_LOBBY::OnTCPDataReceived( SERVICE_NETWORK_COMMAND * command, uv_stream_t * tcp_stream) {
    
    for(int i = 0; i < NETWORK_SERVICE_LOBBY_MAX_CONNECTIONS; i++ ) {
        
        uv_stream_t * st = (( uv_stream_t * ) &ConnectionPool[ i ]->UVConnection.TCPType.TCPSocket);
        
        if ( ConnectionPool[ i ] != NULL && st == tcp_stream ) {
            
            command->Connection = ConnectionPool[ i ];
            
            break;
        }
    }
    
    (*OnTCPNetworkCommandReceivedCallback)( command );
}

void SERVICE_NETWORK_LOBBY::SendTcpCommand( CORE_DATA_STREAM & data_to_send, SERVICE_NETWORK_CONNECTION * connexion ) {

    if ( data_to_send.GetSize() > 0  || data_to_send.GetOffset() > 0) {
        
        const char * end = "--END--";
        
        data_to_send.InputBytes( (char*) end, 7);
        
        connexion->Send( data_to_send );
    }
}
