
#include "Platform.h"
#if PL_HAS_LED
  #include "LED.h"
#endif
#if PL_HAS_TIMER
  #include "Timer.h"
#endif


void PL_Init(void) {
#if PL_HAS_LED
  LED_Init();
#endif
#if PL_HAS_EVENTS
  EVNT_Init();
#endif  
}

void PL_Deinit(void) {
#if PL_HAS_LED
  LED_Deinit();
#endif
#if PL_HAS_EVENTS
  EVNT_Deinit();
#endif
}
