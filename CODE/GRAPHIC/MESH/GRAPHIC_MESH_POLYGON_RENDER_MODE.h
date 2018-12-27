//
//  GRAPHIC_MESH_POLYGON_RENDER_MODE.h
//  GAME-ENGINE
//
//  Created by Christophe Bernard on 16/05/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef GAME_ENGINE_REBORN_GRAPHIC_MESH_POLYGON_RENDER_MODE_h
#define GAME_ENGINE_REBORN_GRAPHIC_MESH_POLYGON_RENDER_MODE_h

#include "GRAPHIC_SYSTEM_RUNTIME_ENVIRONMENT.h"

enum GRAPHIC_MESH_POLYGON_RENDER_MODE {
    GRAPHIC_MESH_POLYGON_RENDER_MODE_TriangleList = 0,
    GRAPHIC_MESH_POLYGON_RENDER_MODE_Line,
    GRAPHIC_MESH_POLYGON_RENDER_MODE_Point,
    GRAPHIC_MESH_POLYGON_RENDER_MODE_TriangleFan,
    GRAPHIC_MESH_POLYGON_RENDER_MODE_TriangleStrip,
    GRAPHIC_MESH_POLYGON_RENDER_MODE_TesselationPatches,
    GRAPHIC_MESH_POLYGON_RENDER_MODE_Count,
    GRAPHIC_MESH_POLYGON_RENDER_MODE_None
};

#if OPENGL4
    GLuint GRAPHIC_MESH_POLYGON_RENDER_MODE_GetForOpengl4( const GRAPHIC_MESH_POLYGON_RENDER_MODE mode );
#elif OPENGLES2
    GLuint GRAPHIC_MESH_POLYGON_RENDER_MODE_GetForOpenglES2( const GRAPHIC_MESH_POLYGON_RENDER_MODE mode );
#endif

#endif
