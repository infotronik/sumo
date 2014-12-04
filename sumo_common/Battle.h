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

#if PL_HAS_SHELL
/*!
 * \brief Prints the system low power status
 * \param io I/O channel to use for printing status
 */
void BATTLE_StateMachine(void);
static void BATTLE_PrintStatus(const CLS1_StdIOType *io);
static void BATTLE_PrintHelp(const CLS1_StdIOType *io);
uint8_t BATTLE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif /* PL_HAS_SHELL */

void BATTLE_Deinit(void);
void BATTLE_Init(void);
#endif /* PL_HAS_BATTLE */

#endif /* BATTLE_H_ */
