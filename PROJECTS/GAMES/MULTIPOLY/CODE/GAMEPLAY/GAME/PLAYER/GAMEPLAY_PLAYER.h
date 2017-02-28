//
//  GAMEPLAY_PLAYER.hpp
//  MULTIPOLY
//
//  Created by Christophe Bernard on 20/02/17.
//  Copyright © 2017 cbe. All rights reserved.
//

#ifndef GAMEPLAY_PLAYER_hpp
#define GAMEPLAY_PLAYER_hpp

#include "CORE_HELPERS_CLASS.h"
#include "GAMEPLAY_COMPONENT_ENTITY.h"
#include "CORE_MATH_QUATERNION.h"
#include "GAMEPLAY_COMPONENT_POSITION.h"
#include "GAMEPLAY_SCENE.h"
#include "GRAPHIC_MESH.h"
#include "GRAPHIC_OBJECT_RESOURCE_LOADER.h"
#include "GRAPHIC_SHADER_EFFECT_LOADER.h"
#include "GRAPHIC_SHADER_EFFECT.h"
#include "GRAPHIC_OBJECT_SHAPE_PLAN.h"
#include "GRAPHIC_TEXTURE_BLOCK.h"
#include "CORE_FIXED_STATE_MACHINE.h"
#include "CORE_HELPERS_COLOR.h"
#include "GAMEPLAY_DICE_ROLL_RESULT.h"
#include "GAME_HUD_PRESENTER.h"
#include "CORE_DATA_MODEL.h"

class GAMEPLAY_GAME_CARD;

XS_CLASS_BEGIN_WITH_ANCESTOR(GAMEPLAY_PLAYER, GAMEPLAY_COMPONENT_ENTITY)

    CORE_FIXED_STATE_MACHINE_DefineEvent( UPDATE_EVENT, const float )

    CORE_FIXED_STATE_MACHINE_DeclareBaseState(PLAYER_BASE_STATE, GAMEPLAY_PLAYER)
        CORE_FIXED_STATE_MACHINE_DeclareHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_End()

    CORE_FIXED_STATE_MACHINE_DefineState( PLAYER_BASE_STATE, IDLE_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( IDLE_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( PLAYER_BASE_STATE, LAUNCH_DICE_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( LAUNCH_DICE_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( PLAYER_BASE_STATE, PLAYER_MOVE_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( PLAYER_MOVE_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( PLAYER_BASE_STATE, PLAYER_FORCED_ADVANCE_MOVE_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( PLAYER_FORCED_ADVANCE_MOVE_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( PLAYER_BASE_STATE, PLAYER_SPECIAL_MOVE_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( PLAYER_SPECIAL_MOVE_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( PLAYER_BASE_STATE, ACTION_CHOICE_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( ACTION_CHOICE_STATE )

    CORE_FIXED_STATE_MACHINE_DefineState( PLAYER_BASE_STATE, PLAYER_DISPLAY_CARD_STATE )
        CORE_FIXED_STATE_MACHINE_DefineHandleEvent( UPDATE_EVENT )
    CORE_FIXED_STATE_MACHINE_EndDefineState( PLAYER_DISPLAY_CARD_STATE )


    GAMEPLAY_PLAYER( std::string & name );
    ~GAMEPLAY_PLAYER();

    void Initialize( CORE_HELPERS_COLOR & player_color, GAMEPLAY_COMPONENT_POSITION * component, GAMEPLAY_SCENE * scene, bool is_human, int money_amount, int index );
    void Update(const float);

    void SetupTurn( GAME_HUD_PRESENTER * presenter );
    void RollDice();
    GAMEPLAY_DICE_ROLL_RESULT ComputeRollResult();
    void SetTurnIsOver() { ItIsDone = true; }

    inline int GetPlayerIndex() { return PlayerIndex; }
    inline void AddMoney( int amount ) { Money += amount;OnChangedCallback( this ); }
    inline void RemoveMoney( int amount ) { Money -= amount;OnChangedCallback( this ); }
    inline bool IsHuman() { return ItIsHuman; }
    inline bool IsDone() { return ItIsDone; }
    inline int GetMoney() { return Money; }
    inline void SetOnChangedCallback(CORE_HELPERS_CALLBACK_1< GAMEPLAY_PLAYER * > & callback ) { OnChangedCallback = callback; }
    inline GAMEPLAY_DICE_ROLL_RESULT & GetRollResult() {return RollResult; }
    inline int GetCurrentCellIndex() { return CurrentCellIndex; }
    int AttemptPay( int amount );

    void JumpTo( int cell_index );
    void ForceAdvanceTo( int cell_index );

    void ShowActiveGameplayCard( GAMEPLAY_GAME_CARD * card );

private :

    GAMEPLAY_COMPONENT_ENTITY * CreateThisComponent(
        GRAPHIC_OBJECT::PTR object,
        GRAPHIC_SHADER_PROGRAM_DATA_PROXY::PTR program,
        const CORE_MATH_VECTOR & position,
        const CORE_MATH_QUATERNION & orientation,
        const CORE_MATH_VECTOR & size,
        GAMEPLAY_SCENE * scene,
        CORE_HELPERS_COLOR & player_color );

    int
        Money,
        CellAdvance,
        CurrentCellIndex,
        SpecialDestination,
        PlayerIndex;
    float
        TurnTime,
        DiceRollTime,
        PlayerMoveAnimationTime;
    bool
        ItIsHuman,
        ItIsDone,
        HasLost,
        DiceIsRolling;
    CORE_HELPERS_CALLBACK_1< GAMEPLAY_PLAYER * >
        OnChangedCallback;
    std::string
        Name;
    GAMEPLAY_DICE_ROLL_RESULT
        DiceRollResult;
    CORE_FIXED_STATE_MACHINE<PLAYER_BASE_STATE, GAMEPLAY_PLAYER>
        StateMachine;
    GAMEPLAY_DICE_ROLL_RESULT
        RollResult;
    GAMEPLAY_GAME_CARD
        * ActiveCard;

XS_CLASS_END

#endif /* GAMEPLAY_PLAYER_hpp */
