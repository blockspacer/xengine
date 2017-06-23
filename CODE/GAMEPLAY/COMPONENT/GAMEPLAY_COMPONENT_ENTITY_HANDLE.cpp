//
//  GAMEPLAY_COMPONENT_ENTITY_HANDLE.cpp
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 20/06/17.
//  Copyright © 2017 Christophe Bernard. All rights reserved.
//

#include "GAMEPLAY_COMPONENT_ENTITY_HANDLE.h"

XS_IMPLEMENT_INTERNAL_MEMORY_LAYOUT( GAMEPLAY_COMPONENT_ENTITY_HANDLE )
    XS_DEFINE_ClassMember( int, Offset )
    XS_DEFINE_ClassMember( int, Index )
XS_END_INTERNAL_MEMORY_LAYOUT

GAMEPLAY_COMPONENT_ENTITY_HANDLE::GAMEPLAY_COMPONENT_ENTITY_HANDLE() :
    Offset( -1 ),
    Index( -1 ) {
    
}

GAMEPLAY_COMPONENT_ENTITY_HANDLE::GAMEPLAY_COMPONENT_ENTITY_HANDLE( int index, int offset ) :
    Offset( offset ),
    Index( index ) {
    
}

GAMEPLAY_COMPONENT_ENTITY_HANDLE::GAMEPLAY_COMPONENT_ENTITY_HANDLE( const GAMEPLAY_COMPONENT_ENTITY_HANDLE & other ) :
    Offset( other.Offset ),
    Index( other.Index ) {
    
}

GAMEPLAY_COMPONENT_ENTITY_HANDLE::~GAMEPLAY_COMPONENT_ENTITY_HANDLE() {
    
}

bool operator < (const GAMEPLAY_COMPONENT_ENTITY_HANDLE & first, const GAMEPLAY_COMPONENT_ENTITY_HANDLE & second ) {
    return first.GetOffset() < second.GetOffset() || first.GetIndex() < second.GetIndex();
}
