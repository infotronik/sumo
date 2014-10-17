
#include "Platform.h"
#if PL_HAS_LED
  #include "LED.h"
#endif
#if PL_HAS_TIMER
  #include "Timer.h"
#endif
#if PL_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_HAS_KEYS
  #include "Keys.h"
#endif



void PL_Init(void) {
#if PL_HAS_LED
  LED_Init();
#endif
#if PL_HAS_EVENTS
  EVNT_Init();
#endif  
#if PL_HAS_KEYS
  KEY_Init();
#endif
#if PL_HAS_TIMER
  TMR_Init();
#endif
}

void PL_Deinit(void) {
#if PL_HAS_LED
  LED_Deinit();
#endif
#if PL_HAS_EVENTS
  EVNT_Deinit();
#endif
#if PL_HAS_KEYS
  KEY_Deinit();
#endif
#if PL_HAS_TIMER
  TMR_Deinit();
#endif
}
