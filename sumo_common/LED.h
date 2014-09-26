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
  #include "LedBit1.h"
  #define LED1_On()     LedBit1_ClrVal()
    /*!< Turn LED 1 on */
  #define LED1_Off()    LedBit1_SetVal()
    /*!< Turn LED 1 off */
  #define LED1_Neg()    LedBit1_NegVal()
    /*!< Toggle LED 1 */
  #define LED1_Get()    LedBit1_GetVal()
    /*!< Return TRUE if LED is on, FALSE otherwise */
  #define LED1_Put(val) LedBit1_PutVal(val)
    /*!< Turn LED on or off */
  #define LED1_Init()   /* do nothing */
    /*!< Initialize LED */
  #define LED1_Deinit() /* do nothing */
    /*!< De-Initialize LED */
#else
  #define LED1_On()     /* do nothing */
    /*!< Turn LED 1 on */
  #define LED1_Off()    /* do nothing */
    /*!< Turn LED 1 off */
  #define LED1_Neg()    /* do nothing */
    /*!< Toggle LED 1 */
  #define LED1_Get()  0 /* do nothing */
    /*!< Return TRUE if LED is on, FALSE otherwise */
  #define LED1_Put(val) /* do nothing */
    /*!< Turn LED 1 on or off */
  #define LED1_Init()   /* do nothing */
    /*!< Initialize LED 1 */
  #define LED1_Deinit() /* do nothing */
    /*!< De-Initialize LED 1 */
#endif

#if PL_NOF_LEDS >= 2
  #include "LedBit2.h"
  #define LED2_On()     LedBit2_ClrVal()
    /*!< Turn LED 1 on */
  #define LED2_Off()    LedBit2_SetVal()
    /*!< Turn LED 1 off */
  #define LED2_Neg()    LedBit2_NegVal()
    /*!< Toggle LED 1 */
  #define LED2_Get()    LedBit2_GetVal()
    /*!< Return TRUE if LED is on, FALSE otherwise */
  #define LED2_Put(val) LedBit2_PutVal(val)
    /*!< Turn LED on or off */
  #define LED2_Init()   /* do nothing */
    /*!< Initialize LED */
  #define LED2_Deinit() /* do nothing */
    /*!< De-Initialize LED */
#else
  #define LED2_On()     /* do nothing */
    /*!< Turn LED 2 on */
  #define LED2_Off()    /* do nothing */
    /*!< Turn LED 2 off */
  #define LED2_Neg()    /* do nothing */
    /*!< Toggle LED 2 */
  #define LED2_Get()  0 /* do nothing */
    /*!< Return TRUE if LED is on, FALSE otherwise */
  #define LED2_Put(val) /* do nothing */
    /*!< Turn LED 2 on or off */
  #define LED2_Init()   /* do nothing */
    /*!< Initialize LED 2 */
  #define LED2_Deinit() /* do nothing */
    /*!< De-Initialize LED 2 */
#endif

#if PL_NOF_LEDS >= 3
  #include "LedBit3.h"
  #define LED3_On()     LedBit3_ClrVal()
    /*!< Turn LED 1 on */
  #define LED3_Off()    LedBit3_SetVal()
    /*!< Turn LED 1 off */
  #define LED3_Neg()    LedBit3_NegVal()
    /*!< Toggle LED 1 */
  #define LED3_Get()    LedBit3_GetVal()
    /*!< Return TRUE if LED is on, FALSE otherwise */
  #define LED3_Put(val) LedBit3_PutVal(val)
    /*!< Turn LED on or off */
  #define LED3_Init()   /* do nothing */
    /*!< Initialize LED */
  #define LED3_Deinit() /* do nothing */
    /*!< De-Initialize LED */
#else
  #define LED3_On()     /* do nothing */
    /*!< Turn LED 3 on */
  #define LED3_Off()    /* do nothing */
    /*!< Turn LED 3 off */
  #define LED3_Neg()    /* do nothing */
    /*!< Toggle LED 3 */
  #define LED3_Get()  0 /* do nothing */
    /*!< Return TRUE if LED is on, FALSE otherwise */
  #define LED3_Put(val) /* do nothing */
    /*!< Turn LED 3 on or off */
  #define LED3_Init()   /* do nothing */
    /*!< Initialize LED 3 */
  #define LED3_Deinit() /* do nothing */
    /*!< De-Initialize LED 3 */
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
