/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_HAS_RTOS
#include "Application.h"
#include "RTOS.h"
#include "FRTOS1.h"
#include "LED.h"

static portTASK_FUNCTION(T1, pvParameters) {
  for(;;) {
    LED1_Neg();
  }
}

void RTOS_Run(void) {
    if ( FRTOS1_xTaskCreate(
        TaskLoop,
        "TaskLoop",
        configMINIMAL_STACK_SIZE,
        (void*)NULL,
        tskIDLE_PRIORITY,
        (xTaskHandle*)NULL
    ) != pdPASS) {
        for(;;){};
	}
    FRTOS1_vTaskStartScheduler();
}

void RTOS_Init(void) {
  /*! \todo Add tasks here */
  if (FRTOS1_xTaskCreate(T1, (signed portCHAR *)"T1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

void RTOS_Deinit(void) {
}

#endif /* PL_HAS_RTOS */
