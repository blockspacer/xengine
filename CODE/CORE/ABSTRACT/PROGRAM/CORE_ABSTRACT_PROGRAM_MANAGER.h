//
//  CORE_ABSTRACT_PROGRAM_MANAGER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 8/11/14.
//  Copyright (c) 2014 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__CORE_ABSTRACT_PROGRAM_MANAGER__
#define __GAME_ENGINE_REBORN__CORE_ABSTRACT_PROGRAM_MANAGER__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_UNIQUE.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME_TYPE.h"
#include "CORE_ABSTRACT_PROGRAM_FACTORY.h"
#include "CORE_ABSTRACT_PROGRAM_RUNTIME.h"

XS_CLASS_BEGIN(CORE_ABSTRACT_PROGRAM_MANAGER)

XS_DEFINE_UNIQUE(CORE_ABSTRACT_PROGRAM_MANAGER)

    virtual    ~CORE_ABSTRACT_PROGRAM_MANAGER();

    CORE_ABSTRACT_PROGRAM_FACTORY * LoadProgram(
        const char *,
        const CORE_ABSTRACT_PROGRAM_RUNTIME_TYPE,
        CORE_ABSTRACT_BASE_PROGRAM_RUNTIME * customRuntime = NULL
        );

private :

    std::map< const char *, CORE_ABSTRACT_PROGRAM_FACTORY *> ProgramTable;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__CORE_ABSTRACT_PROGRAM_MANAGER__) */
