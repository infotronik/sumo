
#include "Platform.h"
#if PL_HAS_LED
  #include "LED.h"
#endif

void PL_Init(void) {
#if PL_HAS_LED
  LED_Init();
#endif  
}

void PL_Deinit(void) {
#if PL_HAS_LED
  LED_Deinit();
#endif
}
