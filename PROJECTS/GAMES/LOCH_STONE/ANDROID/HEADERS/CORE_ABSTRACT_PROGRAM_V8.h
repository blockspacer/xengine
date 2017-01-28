//
//  CORE_ABSTRACT_PROGRAM_V8.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 8/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_ABSTRACT_PROGRAM_V8__
#define __GAME_ENGINE_REBORN__CORE_ABSTRACT_PROGRAM_V8__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_ABSTRACT_PROGRAM_FACTORY.h"

XS_CLASS_BEGIN_WITH_ANCESTOR(CORE_ABSTRACT_PROGRAM_V8, CORE_ABSTRACT_PROGRAM_FACTORY)

    CORE_HELPERS_FACTORY_Element(CORE_ABSTRACT_PROGRAM_V8, CORE_ABSTRACT_PROGRAM_FACTORY, CORE_ABSTRACT_PROGRAM_RUNTIME_TYPE, CORE_ABSTRACT_PROGRAM_RUNTIME_V8)

    CORE_ABSTRACT_PROGRAM_V8();

    virtual void Load( const char *, const CORE_ABSTRACT_BASE_PROGRAM_RUNTIME &);
    virtual void Execute();

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_ABSTRACT_PROGRAM_V8__) */
