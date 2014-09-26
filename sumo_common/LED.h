/*
 * LED.h
 *
 *  Created on: 26.09.2014
 *      Author: Mario
 */

#ifndef LED_H_
#define LED_H_

#include "Platform.h"

#if PL_NOF_LEDS >= 1
  #include "LED1.h"
  #define LED1_On()     LED1_ClrVal()
    /*!< Turn LED 1 on */
  #define LED1_Off()    LED1_SetVal()
    /*!< Turn LED 1 off */
  #define LED1_Neg()    LED1_NegVal()
    /*!< Toggle LED 1 */
  #define LED1_Get()    LED1_GetVal()
    /*!< Return TRUE if LED is on, FALSE otherwise */
  #define LED1_Put(val) LED1_PutVal(val)
    /*!< Turn LED on or off */
  #define LED1_Init()   /* do nothing */
    /*!< Initialize LED */
  #define LED1_Deinit() /* do nothing */
    /*!< De-Initialize LED */
#else
  /*!< Not needed because no LEDs are available */
#endif

#if PL_NOF_LEDS >= 2
  #include "LED2.h"
  #define LED2_On()     LED2_ClrVal()
    /*!< Turn LED 1 on */
  #define LED2_Off()    LED2_SetVal()
    /*!< Turn LED 1 off */
  #define LED2_Neg()    LED2_NegVal()
    /*!< Toggle LED 1 */
  #define LED2_Get()    LED2_GetVal()
    /*!< Return TRUE if LED is on, FALSE otherwise */
  #define LED2_Put(val) LED2_PutVal(val)
    /*!< Turn LED on or off */
  #define LED2_Init()   /* do nothing */
    /*!< Initialize LED */
  #define LED2_Deinit() /* do nothing */
    /*!< De-Initialize LED */
#else
  /*!< Not needed because no LEDs are available */
#endif

#if PL_NOF_LEDS >= 3
  #include "LED3.h"
  #define LED3_On()     LED3_ClrVal()
    /*!< Turn LED 1 on */
  #define LED3_Off()    LED3_SetVal()
    /*!< Turn LED 1 off */
  #define LED3_Neg()    LED3_NegVal()
    /*!< Toggle LED 1 */
  #define LED3_Get()    LED3_GetVal()
    /*!< Return TRUE if LED is on, FALSE otherwise */
  #define LED3_Put(val) LED3_PutVal(val)
    /*!< Turn LED on or off */
  #define LED3_Init()   /* do nothing */
    /*!< Initialize LED */
  #define LED3_Deinit() /* do nothing */
    /*!< De-Initialize LED */
#else
  /*!< Not needed because no LEDs are available */
#endif

/*!
 * \brief LED test routine.
 * This routine tests if:
 * - we can turn the LEDs properly on and off
 * - if we can negate them
 * - if we can set an LED value
 * - if we can get the LED value
 * If the test fails, the program will hanging in an endless loop
 */
void LED_Test(void);

/*!
 * \brief LED Driver Intialization.
 */
void LED_Init(void);

/*!
 * \brief LED Driver De-Initialization.
 */
void LED_Deinit(void);




#endif /* LED_H_ */
