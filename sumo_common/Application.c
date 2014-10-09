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
#if PL_HAS_EVENTS
  #include "Event.h"
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
		LED2_Neg();
		break;
	default:
		break;
	  }
}

static void APP_Loop(){
	for(;;){
		#if PL_HAS_EVENTS
		  EVNT_HandleEvent(APP_EventHandler);
		#endif
		  WAIT1_Waitms(100);
	  }
}




