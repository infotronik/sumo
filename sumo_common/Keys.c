/**
 * \file
 * \brief Key/Switch driver implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic keyboard driver for up to 7 Keys.
 * It is using macros for maximum flexibility with minimal code overhead.
 */

#include "Platform.h"
#if PL_HAS_KEYS
  #include "Keys.h"
#if PL_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_HAS_DEBOUNCE
  #include "KeyDebounce.h"
#endif

void KEY_Scan(void) {
#if (PL_HAS_DEBOUNCE)
    KEYDBNC_Process();
#else
    #if (PL_NOF_KEYS >= 1) & (PL_KEY_POLLED_KEY1)
        if (KEY1_Get()) { /* key pressed */
            EVNT_SetEvent(EVNT_SW_A_PRESSED);
        }
    #endif
    #if (PL_NOF_KEYS >= 2) & (PL_KEY_POLLED_KEY2)
        if (KEY2_Get()) { /* key pressed */
            EVNT_SetEvent(EVNT_SW_B_PRESSED);
        }
    #endif
    #if (PL_NOF_KEYS >= 3) & (PL_KEY_POLLED_KEY3)
        if (KEY3_Get()) { /* key pressed */
            EVNT_SetEvent(EVNT_SW_C_PRESSED);
        }
    #endif
    #if (PL_NOF_KEYS >= 4) & (PL_KEY_POLLED_KEY4)
        if (KEY4_Get()) { /* key pressed */
            EVNT_SetEvent(EVNT_SW_D_PRESSED);
        }
    #endif
    #if (PL_NOF_KEYS >= 5) & (PL_KEY_POLLED_KEY5)
        if (KEY5_Get()) { /* key pressed */
            EVNT_SetEvent(EVNT_SW_E_PRESSED);
        }
    #endif
    #if (PL_NOF_KEYS >= 6) & (PL_KEY_POLLED_KEY6)
        if (KEY6_Get()) { /* key pressed */
            EVNT_SetEvent(EVNT_SW_F_PRESSED);
        }
    #endif
    #if (PL_NOF_KEYS >= 7) & (PL_KEY_POLLED_KEY7)
        if (KEY7_Get()) { /* key pressed */
            EVNT_SetEvent(EVNT_SW_G_PRESSED);
        }
    #endif
#endif
}

#if PL_HAS_KBI
void KEY_OnInterrupt(KEY_Buttons button) {
#if (PL_HAS_DEBOUNCE)
  KEYDBNC_Process();
#else
    switch(button){
    case KEY_BTN1: EVNT_SetEvent(EVNT_SW_A_PRESSED);
        break;
    case KEY_BTN2: EVNT_SetEvent(EVNT_SW_B_PRESSED);
        break;
    case KEY_BTN3: EVNT_SetEvent(EVNT_SW_C_PRESSED);
        break;
    case KEY_BTN4: EVNT_SetEvent(EVNT_SW_D_PRESSED);
        break;
    case KEY_BTN5: EVNT_SetEvent(EVNT_SW_E_PRESSED);
        break;
    case KEY_BTN6: EVNT_SetEvent(EVNT_SW_F_PRESSED);
        break;
    case KEY_BTN7: EVNT_SetEvent(EVNT_SW_G_PRESSED);
        break;
    default:
        break;
    }
#endif
}
#endif

/*! \brief Key driver initialization */
void KEY_Init(void) {
    /* nothing needed for now */
}

/*! \brief Key driver de-initialization */
void KEY_Deinit(void) {
    /* nothing needed for now */
}

/*! \brief Key interrupts enable */
void KEY_EnableInterrupts(void) {
    #if PL_NOF_KEYS >= 1 && !PL_KEY_POLLED_KEY_A
        SW_A_Enable();
    #endif
    #if PL_NOF_KEYS >= 2 && !PL_KEY_POLLED_KEY_B
        SW_B_Enable();
    #endif
    #if PL_NOF_KEYS >= 3 && !PL_KEY_POLLED_KEY_C
        SW_C_Enable();
    #endif
    #if PL_NOF_KEYS >= 4 && !PL_KEY_POLLED_KEY_D
        SW_D_Enable();
    #endif
    #if PL_NOF_KEYS >= 5 && !PL_KEY_POLLED_KEY_E
        SW_E_Enable();
    #endif
    #if PL_NOF_KEYS >= 6 && !PL_KEY_POLLED_KEY_F
        SW_F_Enable();
    #endif
    #if PL_NOF_KEYS >= 7 && !PL_KEY_POLLED_KEY_G
        SW_G_Enable();
    #endif
}

/*! \brief Key interrupts disable */
void KEY_DisableInterrupts(void) {
    #if PL_NOF_KEYS >= 1 && !PL_KEY_POLLED_KEY_A
        SW_A_Disable();
    #endif
    #if PL_NOF_KEYS >= 2 && !PL_KEY_POLLED_KEY_B
        SW_B_Disable();
    #endif
    #if PL_NOF_KEYS >= 3 && !PL_KEY_POLLED_KEY_C
        SW_C_Disable();
    #endif
    #if PL_NOF_KEYS >= 4 && !PL_KEY_POLLED_KEY_D
        SW_D_Disable();
    #endif
    #if PL_NOF_KEYS >= 5 && !PL_KEY_POLLED_KEY_E
        SW_E_Disable();
    #endif
    #if PL_NOF_KEYS >= 6 && !PL_KEY_POLLED_KEY_F
        SW_F_Disable();
    #endif
    #if PL_NOF_KEYS >= 7 && !PL_KEY_POLLED_KEY_G
        SW_G_Disable();
    #endif
}



#endif /* PL_HAS_KEYS */
