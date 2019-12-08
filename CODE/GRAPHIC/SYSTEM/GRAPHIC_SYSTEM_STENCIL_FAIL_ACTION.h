//
//  , const GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION stencil_fail.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 10/11/2018.
//  Copyright © 2018 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_H
#define GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_H

enum GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION {
    GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Keep = 0,
    GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Zero,
    GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Replace,
    GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Increment,
    GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_IncrementWrap,
    GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Decrement,
    GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_DecrementWrap,
    GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_Invert,
    GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_None
};

#endif /* GRAPHIC_SYSTEM_STENCIL_FAIL_ACTION_H */