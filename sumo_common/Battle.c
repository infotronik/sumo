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
#include "FRTOS1.h"
#include "Battle.h"

#if PL_HAS_BATTLE

#define MAX_US_RANGE_CM 60

#define BACKWARDDISTANCE 500

static BattleStateType batstate = BATTLE_STATE_FIND;

static volatile BattleStateType battleState = BATTLE_STATE_INIT; /* state machine state */
static volatile BattleStateType battleStatePrev = BATTLE_STATE_INIT; /* previous state machine state */

static void BATTLE_changeState(BattleStateType state) {
    battleStatePrev = battleState;
    battleState = state;
}

static BattleStateType BATTLE_GetState(void) {
	return battleState;
}

static void changeState(void *state) {
    battleStatePrev = battleState;
    battleState = *((BattleStateType *) state);
}

bool BATTLE_EnemyInRange(){
      uint16_t cm;
      cm = US_usToCentimeters(US_Measure_us(), 22);
      return(cm <= MAX_US_RANGE_CM);
}

void BATTLE_Prove(void){
	if (battleState == BATTLE_STATE_FIND
	 || battleState == BATTLE_STATE_PUSH
	 || battleState == BATTLE_STATE_LINE
	 || battleState == BATTLE_STATE_LINE_LEFT
	 || battleState == BATTLE_STATE_LINE_RIGHT) {
        if (EVNT_EventIsSet(EVNT_LINE)) {
            EVNT_ClearEvent(EVNT_LINE);
            BATTLE_changeState(BATTLE_STATE_LINE);
	    } else if (EVNT_EventIsSet(EVNT_LINE_LEFT)) {
            EVNT_ClearEvent(EVNT_LINE_LEFT);
            BATTLE_changeState(BATTLE_STATE_LINE_LEFT);
	    } else if (EVNT_EventIsSet(EVNT_LINE_RIGHT)) {
            EVNT_ClearEvent(EVNT_LINE_RIGHT);
            BATTLE_changeState(BATTLE_STATE_LINE_RIGHT);
	    }
	} else if (battleState == BATTLE_STATE_REMOTE) {
	    if (EVNT_EventIsSet(EVNT_LINE)) {
            EVNT_ClearEvent(EVNT_LINE);
            BATTLE_changeState(BATTLE_STATE_REMOTE);
	    } else if (EVNT_EventIsSet(EVNT_LINE_LEFT)) {
            EVNT_ClearEvent(EVNT_LINE_LEFT);
            BATTLE_changeState(BATTLE_STATE_REMOTE_LINE_LEFT);
	    } else if (EVNT_EventIsSet(EVNT_LINE_RIGHT)) {
            EVNT_ClearEvent(EVNT_LINE_RIGHT);
            BATTLE_changeState(BATTLE_STATE_REMOTE_LINE_RIGHT);
	    }
	}
	if (battleState == BATTLE_STATE_FIND
	 || battleState == BATTLE_STATE_PUSH
	 || battleState == BATTLE_STATE_LINE
	 || battleState == BATTLE_STATE_LINE_LEFT
	 || battleState == BATTLE_STATE_LINE_RIGHT){
	    if (EVNT_EventIsSet(EVNT_ACCEL)) {
                EVNT_ClearEvent(EVNT_ACCEL);
                //BATTLE_changeState(BATTLE_STATE_FALLDOWN);
	    }
    }

}

void BATTLE_StateMachine(void) {
    BATTLE_Prove();
    switch (battleState) {
    case BATTLE_STATE_INIT:
        BATTLE_changeState(BATTLE_STATE_REMOTE);
        break;
    case BATTLE_STATE_NONE:
        DRV_EnableDisable(FALSE);
        DRV_SetSpeed(0,0);
        if (EVNT_EventIsSet(EVNT_SW_A_PRESSED)) {
            EVNT_ClearEvent(EVNT_SW_A_PRESSED);
            BATTLE_changeState(BATTLE_STATE_WAIT);
        }
        else {
            BATTLE_changeState(BATTLE_STATE_NONE);
        }
        break;
    case BATTLE_STATE_WAIT:
        if (battleStatePrev != BATTLE_STATE_WAIT) {
            TRG_SetTrigger(TRG_WAIT, 5000 / TRG_TICKS_MS, changeState, &batstate);
        }
        BATTLE_changeState(BATTLE_STATE_WAIT);
        break;
    case BATTLE_STATE_FIND:
        if(BATTLE_EnemyInRange()){
            BATTLE_changeState(BATTLE_STATE_PUSH);
        }
        else{
            DRV_EnableDisable(TRUE);
            DRV_SetSpeed(2000,-2000);
            BATTLE_changeState(BATTLE_STATE_FIND);
        }
        break;
    case BATTLE_STATE_PUSH:
        if(BATTLE_EnemyInRange()){
            DRV_EnableDisable(TRUE);
            DRV_SetSpeed(5000, 5000);
            BATTLE_changeState(BATTLE_STATE_PUSH);
        }
        else{
            BATTLE_changeState(BATTLE_STATE_FIND);
        }
        break;
    case BATTLE_STATE_LINE:
        if (battleStatePrev != BATTLE_STATE_LINE) {
            DRV_EnableDisable(TRUE);
            DRV_SetSpeed(-3000, -3000);
            // DRV_DriveDistance(-BACKWARDDISTANCE, -BACKWARDDISTANCE);
        }
        FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
        if (battleState == BATTLE_STATE_LINE) {
            BATTLE_changeState(BATTLE_STATE_FIND);
        }
        break;
    case BATTLE_STATE_LINE_LEFT:
        if (battleStatePrev != BATTLE_STATE_LINE_LEFT) {
            DRV_EnableDisable(TRUE);
            DRV_SetSpeed(-3000, -2000);
            // DRV_DriveDistance(-BACKWARDDISTANCE, -BACKWARDDISTANCE);
        }
        FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
        if (battleState == BATTLE_STATE_LINE_LEFT) {
            BATTLE_changeState(BATTLE_STATE_FIND);
        }
        break;
    case BATTLE_STATE_LINE_RIGHT:
        if (battleStatePrev != BATTLE_STATE_LINE_RIGHT) {
            DRV_EnableDisable(TRUE);
            DRV_SetSpeed(-2000, -3000);
            // DRV_DriveDistance(-BACKWARDDISTANCE, -BACKWARDDISTANCE);
        }
        FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
        if (battleState == BATTLE_STATE_LINE_RIGHT) {
            BATTLE_changeState(BATTLE_STATE_FIND);
        }
        break;
    case BATTLE_STATE_FALLDOWN:
        DRV_EnableDisable(FALSE);
        DRV_Pos_EnableDisable(FALSE);
        BATTLE_changeState(BATTLE_STATE_FALLDOWN);
        break;
    case BATTLE_STATE_REMOTE_NOLINE:
    	if (battleStatePrev != BATTLE_STATE_REMOTE_NOLINE) {
            DRV_EnableDisable(TRUE);
            DRV_SetSpeed(0,0);
    	}
        BATTLE_changeState(BATTLE_STATE_REMOTE_NOLINE);
        break;
    case BATTLE_STATE_REMOTE:
    	if (battleStatePrev != BATTLE_STATE_REMOTE) {
            DRV_EnableDisable(TRUE);
            DRV_SetSpeed(0,0);
    	}
        BATTLE_changeState(BATTLE_STATE_REMOTE);
        break;
    case BATTLE_STATE_REMOTE_LINE:
        if (battleStatePrev != BATTLE_STATE_REMOTE_LINE) {
            DRV_EnableDisable(TRUE);
            DRV_SetSpeed(-3000, -3000);
            // DRV_DriveDistance(-BACKWARDDISTANCE, -BACKWARDDISTANCE);
        }
        FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
        if (battleState == BATTLE_STATE_REMOTE_LINE) {
            BATTLE_changeState(BATTLE_STATE_REMOTE);
        }
        break;
    case BATTLE_STATE_REMOTE_LINE_LEFT:
        if (battleStatePrev != BATTLE_STATE_REMOTE_LINE_LEFT) {
            DRV_EnableDisable(TRUE);
            DRV_SetSpeed(-3000, -2000);
            // DRV_DriveDistance(-BACKWARDDISTANCE, -BACKWARDDISTANCE);
        }
        FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
        if (battleState == BATTLE_STATE_REMOTE_LINE_LEFT) {
            BATTLE_changeState(BATTLE_STATE_REMOTE);
        }
        break;
    case BATTLE_STATE_REMOTE_LINE_RIGHT:
        if (battleStatePrev != BATTLE_STATE_REMOTE_LINE_RIGHT) {
            DRV_EnableDisable(TRUE);
            DRV_SetSpeed(-2000, -3000);
            // DRV_DriveDistance(-BACKWARDDISTANCE, -BACKWARDDISTANCE);
        }
        FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
        if (battleState == BATTLE_STATE_REMOTE_LINE_RIGHT) {
            BATTLE_changeState(BATTLE_STATE_REMOTE);
        }
        break;
    default:

        break;
    }
}

#if PL_HAS_SHELL

#include "CLS1.h"
#include "UTIL1.h"
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
    case BATTLE_STATE_LINE_LEFT:
        CLS1_SendStr((unsigned char*) "  BATTLE_STATE_LINE_LEFT\r\n", io->stdOut);
        break;
    case BATTLE_STATE_LINE_RIGHT:
        CLS1_SendStr((unsigned char*) "  BATTLE_STATE_LINE_RIGHT\r\n", io->stdOut);
        break;
    case BATTLE_STATE_FALLDOWN:
        CLS1_SendStr((unsigned char*) "  BATTLE_STATE_FALLDOWN\r\n", io->stdOut);
        break;
    case BATTLE_STATE_REMOTE_NOLINE:
        CLS1_SendStr((unsigned char*) "  BATTLE_STATE_REMOTE_NOLINE\r\n", io->stdOut);
        break;
    case BATTLE_STATE_REMOTE:
        CLS1_SendStr((unsigned char*) "  BATTLE_STATE_REMOTE\r\n", io->stdOut);
        break;
    case BATTLE_STATE_REMOTE_LINE:
        CLS1_SendStr((unsigned char*) "  BATTLE_STATE_REMOTE_LINE\r\n", io->stdOut);
        break;
    case BATTLE_STATE_REMOTE_LINE_LEFT:
        CLS1_SendStr((unsigned char*) "  BATTLE_STATE_REMOTE_LINE_LEFT\r\n", io->stdOut);
        break;
    case BATTLE_STATE_REMOTE_LINE_RIGHT:
        CLS1_SendStr((unsigned char*) "  BATTLE_STATE_REMOTE_LINE_RIGHT\r\n", io->stdOut);
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
    CLS1_SendHelpStr((unsigned char*) "    wait",
            (unsigned char*) "BATTLE_STATE_WAIT\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "    find",
            (unsigned char*) "BATTLE_STATE_FIND\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "    push",
            (unsigned char*) "BATTLE_STATE_PUSH\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "    line",
            (unsigned char*) "BATTLE_STATE_LINE\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "    falldown",
            (unsigned char*) "BATTLE_STATE_FALLDOWN\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "    remote",
            (unsigned char*) "BATTLE_STATE_REMOTE\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "    remotenoline",
            (unsigned char*) "BATTLE_STATE_REMOTE_NOLINE\r\n", io->stdOut);
    BATTLE_PrintShortHelp(io);
}

static void BATTLE_PrintShortHelp(const CLS1_StdIOType *io) {
    CLS1_SendHelpStr((unsigned char*) "",
            (unsigned char*) "Short battle commands\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "  bh",
            (unsigned char*) "battle short help\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "  bs",
            (unsigned char*) "battle status\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "  bf",
            (unsigned char*) "Starts battle instantly\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "  bg",
            (unsigned char*) "Starts battle after waiting period\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "  bb",
            (unsigned char*) "Stops battle\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "  br",
            (unsigned char*) "remote control\r\n", io->stdOut);
    CLS1_SendHelpStr((unsigned char*) "  bR",
            (unsigned char*) "remote control without line sensor\r\n", io->stdOut);
}

uint8_t BATTLE_ParseCommand(const unsigned char *cmd, bool *handled,
        const CLS1_StdIOType *io) {
    if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP) == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle help") == 0) {
        BATTLE_PrintHelp(io);
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"bh") == 0) {
        BATTLE_PrintShortHelp(io);
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle status") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"bs") == 0) {
        BATTLE_PrintStatus(io);
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle on") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"bf") == 0) {
        BATTLE_changeState(BATTLE_STATE_FIND);
        BATTLE_StateMachine();
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle start") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"bg") == 0) {
        BATTLE_changeState(BATTLE_STATE_WAIT);
        BATTLE_StateMachine();
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle off") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"bb") == 0) {
        BATTLE_changeState(BATTLE_STATE_NONE);
        BATTLE_StateMachine();
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle remote") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"br") == 0) {
        BATTLE_changeState(BATTLE_STATE_REMOTE);
        BATTLE_StateMachine();
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle remote noline") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"bR") == 0) {
        BATTLE_changeState(BATTLE_STATE_REMOTE_NOLINE);
        BATTLE_StateMachine();
        *handled = TRUE;
    /* Commands for entering battle states manually */
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle state INIT") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle state init") == 0) {
        BATTLE_changeState(BATTLE_STATE_INIT);
        BATTLE_StateMachine();
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle state NONE") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle state none") == 0) {
        BATTLE_changeState(BATTLE_STATE_NONE);
        BATTLE_StateMachine();
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle state WAIT") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle state wait") == 0) {
        BATTLE_changeState(BATTLE_STATE_WAIT);
        BATTLE_StateMachine();
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle state FIND") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle state find") == 0) {
        BATTLE_changeState(BATTLE_STATE_FIND);
        BATTLE_StateMachine();
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle state PUSH") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle state push") == 0) {
        BATTLE_changeState(BATTLE_STATE_PUSH);
        BATTLE_StateMachine();
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle state LINE") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle state line") == 0) {
        BATTLE_changeState(BATTLE_STATE_LINE);
        BATTLE_StateMachine();
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle state FALLDOWN") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle state falldown") == 0) {
        BATTLE_changeState(BATTLE_STATE_FALLDOWN);
        BATTLE_StateMachine();
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle state REMOTE") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle state remote") == 0) {
        BATTLE_changeState(BATTLE_STATE_REMOTE);
        BATTLE_StateMachine();
        *handled = TRUE;
    } else if (UTIL1_strcmp((char*)cmd, (char*)"battle state REMOTENOLINE") == 0
            || UTIL1_strcmp((char*)cmd, (char*)"battle state remotenoline") == 0) {
        BATTLE_changeState(BATTLE_STATE_REMOTE_NOLINE);
        BATTLE_StateMachine();
        *handled = TRUE;
    }
    return ERR_OK;
}
#endif /* PL_HAS_SHELL */

static portTASK_FUNCTION(BattleTask, pvParameters) {
    (void) pvParameters; /* not used */
    for (;;) {
        BATTLE_StateMachine();
        FRTOS1_vTaskDelay(5/portTICK_RATE_MS);
    }
}

void BATTLE_Deinit(void) {
}

void BATTLE_Init(void) {
    BATTLE_changeState(BATTLE_STATE_INIT);
    if (FRTOS1_xTaskCreate(BattleTask, "Battle", configMINIMAL_STACK_SIZE, NULL,
            tskIDLE_PRIORITY, NULL) != pdPASS) {
        for (;;) {
        } /* error */
    }
}

#endif /* PL_HAS_BATTLE */
