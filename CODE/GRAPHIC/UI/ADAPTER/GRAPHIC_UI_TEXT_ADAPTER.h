//
//  GRAPHIC_UI_TEXT_ADAPTER.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 6/02/16.
//  Copyright © 2016 Christophe Bernard. All rights reserved.
//

#ifndef GRAPHIC_UI_TEXT_ADAPTER_h
#define GRAPHIC_UI_TEXT_ADAPTER_h

#include "CORE_HELPERS_CLASS.h"
#include "GRAPHIC_UI_BASE_ADAPTER.h"

XS_CLASS_BEGIN_WITH_ANCESTOR( GRAPHIC_UI_TEXT_ADAPTER, GRAPHIC_UI_BASE_ADAPTER )

GRAPHIC_UI_TEXT_ADAPTER();

virtual void OnTextPropertyChanged( GRAPHIC_UI_ELEMENT * element, const char * text );
virtual void OnResize( GRAPHIC_UI_ELEMENT * );

XS_CLASS_END

#endif /* GRAPHIC_UI_TEXT_ADAPTER_h */
