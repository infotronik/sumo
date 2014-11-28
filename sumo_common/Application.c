/*
 * Application.c
 *
 *  Created on: 26.09.2014
 *      Author: marc
 */

#include "Platform.h"
#include "Application.h"
#include "WAIT1.h"
#if PL_HAS_LED
    #include "LED.h"
#endif
#if PL_HAS_KEYS
    #include "Keys.h"
#endif
#if PL_HAS_KBI
    #include "Keys.h"
#endif
#if PL_HAS_JOYSTICK
    #include "Keys.h"
#endif
#if PL_HAS_EVENTS
    #include "Event.h"
#endif
#if PL_HAS_SHELL
    #include "CLS1.h"
	#include "Shell.h"
#endif
#if PL_HAS_BUZZER
    #include "Buzzer.h"
#endif
#if PL_HAS_TRIGGER
    #include "Trigger.h"
#endif
#if PL_HAS_RTOS
    #include "RTOS.h"
    #include "FRTOS1.h"
#endif
#if PL_HAS_SHELL_QUEUE
    #include "ShellQueue.h"
#endif
#if PL_HAS_LINE_SENSOR
    #include "Reflectance.h"
#endif
#if PL_HAS_ACCEL
    #include "Accel.h"
#endif

static LineStateType typ;

void APP_DebugPrint(unsigned char *str) {
#if PL_HAS_SHELL
  CLS1_SendStr(str, CLS1_GetStdio()->stdOut);
#endif
}

void APP_Start(void) {
    PL_Init(); /* platform initialization */

    EVNT_SetEvent(EVNT_INIT);
#if PL_HAS_RTOS
    RTOS_Run();
#else
    APP_Loop();
#endif

}

static void APP_EventHandler(EVNT_Handle event) {
	#if PL_HAS_LINE_SENSOR

	#endif
	static uint16_t buzzer = 1000;
	switch(event){
	case EVNT_INIT:
	    LED1_On();
	    WAIT1_Waitms(100);
	    LED1_Off();
	    break;
	case EVNT_HEARTBEAT:
		//LED1_Off();
		break;
	case EVNT_SW_A_RELEASED:
		//BUZ_Beep(2000,2000);
		break;
	case EVNT_SW_A_PRESSED:
		//LED1_Neg();
		LED3_Neg();
//		#if PL_HAS_SHELL
//			#if PL_HAS_SHELL_QUEUE
//				SQUEUE_SendString("SW A pressed\n");
//			#else
//				CLS1_SendStr("SW A pressed\n",CLS1_GetStdio()->stdOut);
//			#endif
//		#endif
		#if PL_HAS_LINE_SENSOR
			typ = Line_Detection();
			if(typ == LINE_STATE_AHEAD){
				SHELL_SendString("Line Ahead\n");
			}
			if(typ == LINE_STATE_RIGHT){
				SHELL_SendString("Line Right\n");
			}
			if(typ == LINE_STATE_LEFT){
				SHELL_SendString("Line Left\n");
			}
			if(typ == LINE_STATE_MIDDLE){
				SHELL_SendString("Line middle\n");
			}
			if(typ == LINE_STATE_NO_LINE){
				SHELL_SendString("no Line\n");
			}
			if(typ == LINE_STATE_ERR){
				SHELL_SendString("Line Error\n");
			}
			if(typ == LINE_STATE_LINE){
				SHELL_SendString("Line !!!\n");
			}
		#endif
		#if PL_HAS_BUZZER
			BUZ_Beep(1000,1000);
		#endif
		break;
	case EVNT_SW_A_LPRESSED:
		#if PL_HAS_LINE_SENSOR
			LED1_Neg();
			EVNT_SetEvent(EVNT_REF_START_STOP_CALIBRATION);
		#endif
		break;
	case EVNT_SW_B_PRESSED:
		LED2_Neg();
		LED3_Neg();
		#if PL_HAS_SHELL
			CLS1_SendStr("SW B pressed\n",CLS1_GetStdio()->stdOut);
		#endif
		break;
	case EVNT_SW_C_PRESSED:
		LED1_Neg();
		LED2_Neg();
		#if PL_HAS_SHELL
			CLS1_SendStr("SW C pressed\n",CLS1_GetStdio()->stdOut);
		#endif
		break;
	case EVNT_SW_D_PRESSED:
		LED1_Neg();
		#if PL_HAS_SHELL
			CLS1_SendStr("SW D pressed\n",CLS1_GetStdio()->stdOut);
		#endif
		break;
	case EVNT_SW_E_PRESSED:
		LED2_Neg();
		#if PL_HAS_SHELL
				CLS1_SendStr("SW E pressed\n",CLS1_GetStdio()->stdOut);
		#endif
		break;
	case EVNT_SW_F_PRESSED:
		LED3_Neg();
		#if PL_HAS_SHELL
			CLS1_SendStr("SW F pressed\n",CLS1_GetStdio()->stdOut);
		#endif
		break;
	case EVNT_SW_G_PRESSED:
		LED1_Neg();
		LED2_Neg();
		LED3_Neg();
		#if PL_HAS_SHELL
			CLS1_SendStr("SW g pressed\n",CLS1_GetStdio()->stdOut);
		#endif
		break;
	case EVNT_REF_START_STOP_CALIBRATION:

		break;
	default:
		break;
	}
}

#if PL_HAS_RTOS
void TaskLoop(void *pvParameters){
	#if PL_HAS_ACCEL
	ACCEL_LowLevelInit();
	#endif
	(void)pvParameters;
	for(;;){
		#if PL_HAS_KEYS
			KEY_Scan();
		#endif
		#if PL_HAS_LINE_SENSOR
			typ = Line_Detection();
			if(typ!=LINE_STATE_NO_LINE){
				EVNT_SetEvent(EVNT_LINE);
			}
		#endif
		#if PL_HAS_EVENTS
		  EVNT_HandleEvent(APP_EventHandler);
		#endif
		  FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
	  }
}
#else
static void APP_Loop(){
	for(;;){
		#if PL_HAS_KEYS
			KEY_Scan();
		#endif
		#if PL_HAS_EVENTS
		  EVNT_HandleEvent(APP_EventHandler);
		#endif
		  WAIT1_Waitms(50);
	  }
}
#endif



