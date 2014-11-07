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
#if PL_HAS_RTOS
	#include "RTOS.h"
#endif
#if PL_HAS_SHELL
	#include "Shell.h"
#endif
#if PL_HAS_SHELL_QUEUE
	#include "ShellQueue.h"
#endif
#if PL_HAS_SEMAPHORE
	#include "Sem.h"
#endif
#if PL_HAS_LINE_SENSOR
	#include "Reflectance.h"
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
#if PL_HAS_RTOS
    RTOS_Init();
#endif
#if PL_HAS_SHELL
    SHELL_Init();
#endif
#if PL_HAS_SHELL_QUEUE
    SQUEUE_Init();
#endif
#if PL_HAS_SEMAPHORE
	SEM_Init();
#endif
#if PL_HAS_LINE_SENSOR
	REF_Init();
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
#if PL_HAS_RTOS
    RTOS_Deinit();
#endif
#if PL_HAS_SHELL
    SHELL_Deinit();
#endif
#if PL_HAS_SHELL_QUEUE
    SQUEUE_Deinit();
#endif
#if PL_HAS_SEMAPHORE
	SEM_Deinit();
#endif
#if PL_HAS_LINE_SENSOR
	REF_Deinit();
#endif
}
