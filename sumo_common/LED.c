/*
 * LED.c
 *
 *  Created on: 26.09.2014
 *      Author: Mario
 */

#include "Platform.h"
#include "LED.h"

void LED_Deinit(void) {
    /* all LED's off by default */
    #if PL_NOF_LEDS>=1
        LED1_Off();
    #endif
    #if PL_NOF_LEDS>=2
        LED2_Off();
    #endif
    #if PL_NOF_LEDS>=3
        LED3_Off();
    #endif
        LED1_Deinit();
        LED2_Deinit();
        LED3_Deinit();
}

void LED_Init(void) {
    LED1_Init();
    LED2_Init();
    LED3_Init();
    /* all LED's off by default */
    #if PL_NOF_LEDS>=1
        LED1_Off();
    #endif
    #if PL_NOF_LEDS>=2
        LED2_Off();
    #endif
    #if PL_NOF_LEDS>=3
        LED3_Off();
    #endif
}

/*!
 * \brief LED test routine.
 * This routine tests if:
 * - we can turn the LEDs properly on and off
 * - if we can negate them
 * - if we can set an LED value
 * - if we can get the LED value
 * If the test fails, the program will hanging in an endless loop
 */
void LED_Test(void) {
    bool isOn = TRUE;

    LED1_On();
    LED2_On();
    LED3_On();

    LED1_Off();
    LED2_Off();
    LED3_Off();

    LED1_Neg();
    LED2_Neg();
    LED3_Neg();

    LED1_On();
    if (!LED1_Get()) {
        for(;;){} /*! \todo Need a dedicated error routine? */
    }
    LED1_Off();
    if (LED1_Get()) {
        for(;;){}; /* error */
    }
    LED1_Put(isOn);
    if (!LED1_Get()) {
        for(;;){}; /* error */
    }
}





