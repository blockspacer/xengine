//
//  GRAPHIC_MESH_ANIMATION_JOINT.h
//  GAME-ENGINE-REBORN
//
//  Created by Christophe Bernard on 26/01/15.
//  Copyright (c) 2015 Christophe Bernard. All rights reserved.
//

#ifndef __GAME_ENGINE_REBORN__GRAPHIC_MESH_ANIMATION_JOINT__
#define __GAME_ENGINE_REBORN__GRAPHIC_MESH_ANIMATION_JOINT__

#include "CORE_HELPERS_CLASS.h"
#include "CORE_HELPERS_IDENTIFIER.h"
#include "CORE_DATA_BUFFER.h"
#include "CORE_HELPERS_SCALAR.h"
#include "CORE_MATH_POSE.h"
#include "CORE_MEMORY.h"

XS_CLASS_BEGIN_WITH_COPY( GRAPHIC_MESH_ANIMATION_JOINT )

    XS_DEFINE_SERIALIZABLE

    GRAPHIC_MESH_ANIMATION_JOINT();
    ~GRAPHIC_MESH_ANIMATION_JOINT();

    void Initialize( int matrix_size, int count );

    inline float * GetMatrixBuffer() { return (float *) FloatMatrixBuffer.getpointerAtIndex( 0, 0 ); }
    inline CORE_MATH_POSE * GetPoseBuffer() { return (CORE_MATH_POSE *) PoseBuffer.getpointerAtIndex( 0, 0 ); }

    inline void SetJointName( const char * name ) { strcpy(JointName, name); }

    inline void * GetFloatMatrixBuffer( int offset = 0 ) { return FloatMatrixBuffer.getpointerAtIndex( offset, 0); }
    inline CORE_DATA_BUFFER &  GetTimeTableBuffer() { return TimeTableBuffer; }

    inline void * GetInterPolatedMatrix() { return &InterPolatedMatrix; };
    inline const CORE_MATH_POSE & GetInterPolatedPose() { return InterpolatedPose; };

    void SetWorldMatrix( float * world_matrix ) { memcpy( (void *) WorldMatrix.Value.FloatMatrix4x4, (void*) world_matrix, 16*sizeof(float) ); }
    void SetSkinningMatrix( float * skinning_matrix ) { memcpy( (void *) &InterPolatedMatrix, (void*) skinning_matrix, 16*sizeof(float)); }

    void SetWorldPose( CORE_MATH_POSE & pose ) { WorldPose.CopyFrom( pose ); }
    void SetSkinningPose( CORE_MATH_POSE & skinning_pose ) { InterpolatedPose.CopyFrom( skinning_pose ); }

    void * YieldFloatMatrixBufferForTime( const float time );
    void YieldPoseForTime( const float time, CORE_MATH_POSE & pose );
    char * GetJointName() { return JointName; }

    float GetDuration();

private:

    CORE_DATA_BUFFER
        FloatMatrixBuffer;
    CORE_DATA_BUFFER
        PoseBuffer;
    CORE_MATH_MATRIX
        InterPolatedMatrix;
    CORE_MATH_POSE
        InterpolatedPose;
    CORE_SCALAR
        WorldMatrix;
    CORE_MATH_POSE
        WorldPose;
    CORE_DATA_BUFFER
        TimeTableBuffer;
    char
        JointName[256];
    CORE_SCALAR
        BindShapeMatrix;

XS_CLASS_END

#endif /* defined(__GAME_ENGINE_REBORN__GRAPHIC_MESH_ANIMATION_JOINT__) */
