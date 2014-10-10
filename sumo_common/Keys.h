/**
 * \file
 * \brief Key/switch driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic keyboard driver for up to 4 Keys.
 * It is using macros for maximum flexibility with minimal code overhead.
 */

#ifndef KEYS_H_
#define KEYS_H_

#include "Platform.h"

#if PL_HAS_KEYS

typedef enum {
  KEY_BTN1, /*!< button 1 */
  KEY_BTN2, /*!< button 2 */
  KEY_BTN3, /*!< button 3 */
  KEY_BTN4, /*!< button 4 */
  KEY_BTN5, /*!< button 5 */
  KEY_BTN6, /*!< button 6 */
  KEY_BTN7  /*!< button 7 */
} KEY_Buttons;

#if PL_NOF_KEYS>=1
  #include "SW_A.h"

  #define KEY1_Get()  (!(SW_A_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY1_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=2
  #include "SW_B.h"

  #define KEY2_Get()  (!(SW_B_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY2_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=3
  #include "SW_C.h"

  #define KEY3_Get()  (!(SW_C_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY3_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=4
  #include "SW_D.h"

  #define KEY4_Get()  (!(SW_D_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY4_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=5
  #include "SW_E.h"

  #define KEY5_Get()  (!(SW_E_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY5_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=6
  #include "SW_F.h"

  #define KEY6_Get()  (!(SW_F_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY6_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_NOF_KEYS>=7
  #include "SW_G.h"

  #define KEY7_Get()  (!(SW_G_GetVal()))
    /*!< Macro which returns TRUE if key is pressed */
#else
  #define KEY7_Get()  FALSE
    /*!< if we do not have a button, then return 'not pressed' */
#endif

#if PL_HAS_KBI
/*!
 * \brief Function called from a keyboard interrupt (if supported).
 * \param button Button for which interrupt has been generated.
 */
void KEY_OnInterrupt(KEY_Buttons button);
#endif

/*!
 * \brief Checks the key status and generates the events.
 */
void KEY_Scan(void);

/*! \brief Get access to key hardware. Use KEY_Close() afterwards. */
void KEY_Open(void);

/*! \brief Finish access to key hardware. Called after KEY_Open(). */
void KEY_Close(void);

/*! \brief Key driver initialization */
void KEY_Init(void);

/*! \brief Key driver de-initialization */
void KEY_Deinit(void);

#endif /* PL_HAS_KEYS */

#endif /* KEYS_H_ */
