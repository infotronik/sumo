/**
 * \file
 * \brief Timer driver
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for all our timers.
 */

#include "Platform.h"
#if PL_HAS_TIMER
    #include "Timer.h"
#endif
#if PL_HAS_EVENTS
    #include "Event.h"
#endif

static int cnt = 0;
static int cnt_pid = 0;

void TMR_OnInterrupt(void) {
    cnt++;
    if(cnt>1000){
        cnt = 0;
  	    EVNT_SetEvent(EVNT_HEARTBEAT);
    }
}

void TMR_Init(void) {
    /* nothing needed right now */
}

void TMR_Deinit(void) {
    /* nothing needed right now */
}
