//
//  AUDIO_SOUND.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 24/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#include "AUDIO_SOUND.h"
#include "CORE_MEMORY.h"

AUDIO_SOUND::AUDIO_SOUND() :
    Data( NULL ),
    Mono( false ),
    Compressed( false ),
    Looping( false ),
    BufferWidth( 1024 ),
    Size( 0 ),
    Frequency( 0 ),
    CurrentChunkIndex( 0 ) {
    
}

AUDIO_SOUND::~AUDIO_SOUND() {
    
    Finalize();
    
    if ( Data ) {
        
        CORE_MEMORY_ALLOCATOR_Free( Data );
        Data = NULL;
    }
    
    if ( SoundChunksTable.size() ) {
        
        std::vector< AUDIO_SOUND_CHUNK::PTR >::iterator it = SoundChunksTable.begin();
        
        while (it != SoundChunksTable.end() ) {
            
            delete *it;
            
            it++;
        }
    }
}
