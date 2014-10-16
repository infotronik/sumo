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
#if PL_HAS_CONSOLE
  #include "CLS1.h"
#endif

void APP_Start(void) {
  PL_Init(); /* platform initialization */

  EVNT_SetEvent(EVNT_INIT);
  APP_Loop();

}

static void APP_EventHandler(EVNT_Handle event) {
	switch(event){
	case EVNT_INIT:
	    LED1_On();
	    WAIT1_Waitms(100);
	    LED1_Off();
	    break;
	case EVNT_HEARTBEAT:
		//LED1_Neg();
		break;
	case EVNT_SW_A_PRESSED:
		LED1_Neg();
		LED3_Neg();
		CLS1_SendStr("SW A pressed\n",CLS1_GetStdio()->stdOut);
		break;
	case EVNT_SW_B_PRESSED:
		LED2_Neg();
		LED3_Neg();
		CLS1_SendStr("SW B pressed\n",CLS1_GetStdio()->stdOut);
		break;
	case EVNT_SW_C_PRESSED:
		LED1_Neg();
		LED2_Neg();
		CLS1_SendStr("SW C pressed\n",CLS1_GetStdio()->stdOut);
		break;
	case EVNT_SW_D_PRESSED:
		LED1_Neg();
		CLS1_SendStr("SW D pressed\n",CLS1_GetStdio()->stdOut);
		break;
	case EVNT_SW_E_PRESSED:
		LED2_Neg();
		CLS1_SendStr("SW E pressed\n",CLS1_GetStdio()->stdOut);
		break;
	case EVNT_SW_F_PRESSED:
		LED3_Neg();
		CLS1_SendStr("SW F pressed\n",CLS1_GetStdio()->stdOut);
		break;
	case EVNT_SW_G_PRESSED:
		LED1_Neg();
		LED2_Neg();
		LED3_Neg();
		CLS1_SendStr("SW G pressed\n",CLS1_GetStdio()->stdOut);
		break;
	default:
		break;
	  }
}

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




