/*
 * Battle.h
 *
 *  Created on: 26.09.2014
 *      Author: marc
 */

#ifndef BATTLE_H_
#define BATTLE_H_

#include "Event.h"

#if PL_HAS_BATTLE

typedef enum {
    BATTLE_STATE_INIT,
    BATTLE_STATE_NONE,
    BATTLE_STATE_WAIT,
    BATTLE_STATE_FIND,
    BATTLE_STATE_PUSH,
    BATTLE_STATE_LINE,
    BATTLE_STATE_LINE_LEFT,
    BATTLE_STATE_LINE_RIGHT,
    BATTLE_STATE_FALLDOWN,
    BATTLE_STATE_REMOTE_NOLINE, /* Line sensor deactivated */
    BATTLE_STATE_REMOTE,
    BATTLE_STATE_REMOTE_LINE,
    BATTLE_STATE_REMOTE_LINE_LEFT,
    BATTLE_STATE_REMOTE_LINE_RIGHT,
    BATTLE_STATE_END /* not used state to mark end of states list */
} BattleStateType;

static void BATTLE_changeState(BattleStateType state);
static BattleStateType BATTLE_GetState(void);
void BATTLE_StateMachine(void);
bool BATTLE_EnemyInRange(void);

#if PL_HAS_SHELL
/*!
 * \brief Prints the system low power status
 * \param io I/O channel to use for printing status
 */
static void BATTLE_PrintStatus(const CLS1_StdIOType *io);
static void BATTLE_PrintHelp(const CLS1_StdIOType *io);
static void BATTLE_PrintShortHelp(const CLS1_StdIOType *io);
uint8_t BATTLE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif /* PL_HAS_SHELL */

void BATTLE_Deinit(void);
void BATTLE_Init(void);
#endif /* PL_HAS_BATTLE */

#endif /* BATTLE_H_ */
