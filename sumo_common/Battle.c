/*
 * Battle.c
 *
 *  Created on: 26.09.2014
 *      Author: marc
 */

#include "Platform.h"
#include "Application.h"
#include "Trigger.h"
#include "Drive.h"
#include "Ultrasonic.h"

#if PL_HAS_BATTLE

#define MAX_US_RANGE_CM 100

typedef enum {
    BATTLE_STATE_INIT,
    BATTLE_STATE_NONE,
    BATTLE_STATE_REMOTE,
    BATTLE_STATE_WAIT,
    BATTLE_STATE_FIND,
    BATTLE_STATE_PUSH,
    BATTLE_STATE_LINE,
    BATTLE_STATE_FALLDOWN
} BattleStateType;

#define BACKWARDDISTANCE 500

static BattleStateType batstate = BATTLE_STATE_FIND;

static volatile BattleStateType battleState = BATTLE_STATE_INIT; /* state machine state */

static void changeState(void *state) {
    battleState = *((BattleStateType *) state);
}

bool BATTLE_EnemyInRange(){
      uint16_t cm;
      cm = US_usToCentimeters(US_Measure_us(), 22);
      return(cm <= MAX_US_RANGE_CM);
}

void BATTLE_Prove(void){
	if (EVNT_EventIsSet(EVNT_LINE)) {
            EVNT_ClearEvent(EVNT_LINE);
            battleState = BATTLE_STATE_LINE;
	}
	if (EVNT_EventIsSet(EVNT_ACCEL)) {
            EVNT_ClearEvent(EVNT_ACCEL);
            battleState = BATTLE_STATE_FALLDOWN;
	}


}

void BATTLE_StateMachine(void) {
    switch (battleState) {
    case BATTLE_STATE_INIT:
        battleState = BATTLE_STATE_NONE;
        break;
    case BATTLE_STATE_NONE:
        if (EVNT_EventIsSet(EVNT_SW_A_PRESSED)) {
            EVNT_ClearEvent(EVNT_SW_A_PRESSED);
            battleState = BATTLE_STATE_WAIT;
        }
        break;
    case BATTLE_STATE_REMOTE:

        break;
    case BATTLE_STATE_WAIT:
        TRG_SetTrigger(TRG_WAIT, 5000 / TRG_TICKS_MS, changeState, &batstate);
        break;
    case BATTLE_STATE_FIND:
    	BATTLE_Prove();
        if(BATTLE_EnemyInRange()){
            battleState = BATTLE_STATE_PUSH;
        }
        else{
            DRV_DriveDistance(100,-100);
        }
        break;
    case BATTLE_STATE_PUSH:
    	BATTLE_Prove();
        if(BATTLE_EnemyInRange()){
            DRV_DriveDistance(1000,1000);
        }
        else{
            battleState = BATTLE_STATE_FIND;
        }
        break;
    case BATTLE_STATE_LINE:
        DRV_DriveDistance(-BACKWARDDISTANCE, -BACKWARDDISTANCE);
        break;
    case BATTLE_STATE_FALLDOWN:
        DRV_EnableDisable(FALSE);
        DRV_Pos_EnableDisable(FALSE);
        break;
    default:

        break;
    }
}

#if PL_HAS_SHELL

#include "CLS1.h"
#include "UTIL1.h"
#include "FRTOS1.h"
/*!
 * \brief Prints the system low power status
 * \param io I/O channel to use for printing status
 */
static void BATTLE_PrintStatus(const CLS1_StdIOType *io) {
    //TACHO_CalcSpeed(); /* only temporary until this is done periodically */
    CLS1_SendStatusStr((unsigned char*) "battle", (unsigned char*) "\r\n",
            io->stdOut);
    CLS1_SendStatusStr((unsigned char*) "  state", (unsigned char*) "",
            io->stdOut);
    switch (battleState) {
    case BATTLE_STATE_INIT:
        CLS1_SendStr((unsigned char*) "  BATTLE_STATE_INIT\r\n", io->stdOut);
        break;
    case BATTLE_STATE_NONE:
        CLS1_SendStr((unsigned char*) "  BATTLE_STATE_NONE\r\n", io->stdOut);
        break;
    case BATTLE_STATE_REMOTE:
        CLS1_SendStr((unsigned char*) "  BATTLE_STATE_REMOTE\r\n", io->stdOut);
        break;
    case BATTLE_STATE_WAIT:
        CLS1_SendStr((unsigned char*) "  BATTLE_STATE_WAIT\r\n", io->stdOut);
        break;
    case BATTLE_STATE_FIND:
        CLS1_SendStr((unsigned char*) "  BATTLE_STATE_FIND\r\n", io->stdOut);
        break;
    case BATTLE_STATE_PUSH:
        CLS1_SendStr((unsigned char*) "  BATTLE_STATE_PUSH\r\n", io->stdOut);
        break;
    case BATTLE_STATE_LINE:
        CLS1_SendStr((unsigned char*) "  BATTLE_STATE_LINE\r\n", io->stdOut);
        break;
    default:
        CLS1_SendStr((unsigned char*) "  Invalid State\r\n", io->stdOut);
        break;
    }
}

/*!
 * \brief Prints the help text to the console
 * \param io I/O channel to be used
 */
static void BATTLE_PrintHelp(const CLS1_StdIOType *io) {
    CLS1_SendHelpStr((unsigned char*) "battle",
            (unsigned char*) "Group of battle commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "  help|status",
            (unsigned char*) "Shows battle help or status\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "  on",
            (unsigned char*) "Starts battle\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "  start",
            (unsigned char*) "Starts battle after waiting period\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "  off",
            (unsigned char*) "Stops battle\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "  remote",
            (unsigned char*) "Starts battle with remote control\r\n", io->stdOut);
    /* Commands for setting battle states manually */
    CLS1_SendHelpStr((unsigned char*) "  state",
            (unsigned char*) "Commands for setting battle states manually\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "    init",
            (unsigned char*) "BATTLE_STATE_INIT\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "    none",
            (unsigned char*) "BATTLE_STATE_NONE\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "    remote",
            (unsigned char*) "BATTLE_STATE_REMOTE\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "    wait",
            (unsigned char*) "BATTLE_STATE_WAIT\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "    find",
            (unsigned char*) "BATTLE_STATE_FIND\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "    push",
            (unsigned char*) "BATTLE_STATE_PUSH\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "    line",
            (unsigned char*) "BATTLE_STATE_LINE\r\n", io->stdOut);
}

uint8_t BATTLE_ParseCommand(const unsigned char *cmd, bool *handled,
        const CLS1_StdIOType *io) {
    if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP) == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle help") == 0) {
        BATTLE_PrintHelp(io);
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle status") == 0) {
        BATTLE_PrintStatus(io);
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle on") == 0) {
        battleState = BATTLE_STATE_FIND;
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle start") == 0) {
        battleState = BATTLE_STATE_WAIT;
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle off") == 0) {
        battleState = BATTLE_STATE_NONE;
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle remote") == 0) {
        battleState = BATTLE_STATE_REMOTE;
        *handled = TRUE;
    /* Commands for entering battle states manually */
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle state INIT") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle state init") == 0) {
        battleState = BATTLE_STATE_INIT;
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle state NONE") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle state none") == 0) {
        battleState = BATTLE_STATE_NONE;
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle state REMOTE") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle state remote") == 0) {
        battleState = BATTLE_STATE_REMOTE;
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle state WAIT") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle state wait") == 0) {
        battleState = BATTLE_STATE_WAIT;
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle state FIND") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle state find") == 0) {
        battleState = BATTLE_STATE_FIND;
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle state PUSH") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle state push") == 0) {
        battleState = BATTLE_STATE_PUSH;
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle state LINE") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle state line") == 0) {
        battleState = BATTLE_STATE_LINE;
        *handled = TRUE;
    }
    return ERR_OK;
}
#endif /* PL_HAS_SHELL */

static portTASK_FUNCTION(BattleTask, pvParameters) {
    (void) pvParameters; /* not used */
    for (;;) {
        BATTLE_StateMachine();
        FRTOS1_vTaskDelay(2/portTICK_RATE_MS);
    }
}

void BATTLE_Deinit(void) {
}

void BATTLE_Init(void) {
    battleState = BATTLE_STATE_INIT;
    if (FRTOS1_xTaskCreate(BattleTask, "Battle", configMINIMAL_STACK_SIZE, NULL,
            tskIDLE_PRIORITY, NULL) != pdPASS) {
        for (;;) {
        } /* error */
    }
}

#endif /* PL_HAS_BATTLE */
