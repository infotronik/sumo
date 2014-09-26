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

void APP_Start(void) {
  PL_Init(); /* platform initialization */
  for(;;) {
    LED1_Neg();
    WAIT1_Waitms(300);
    LED2_Neg();
    WAIT1_Waitms(300);
    LED3_Neg();
    WAIT1_Waitms(300);
  }
}


