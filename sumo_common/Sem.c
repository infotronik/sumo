/**
 * \file
 * \brief Semaphore usage
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * Module demonstrating semaphores.
 */

#include "Platform.h" /* interface to the platform */
#if PL_HAS_SEMAPHORE
#include "FRTOS1.h"
#include "Sem.h"
#include "LED.h"
#if PL_HAS_RTOS_TRACE
  #include "RTOSTRC1.h"
#endif

static portTASK_FUNCTION(vSlaveTask, pvParameters) {
  for(;;) {
    /*! \todo implement functionality */
  }
}

static portTASK_FUNCTION(vMasterTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    /*! \todo implement functionality */
  }
}
#endif /* USE_SEMAPHORES */

void SEM_Deinit(void) {
  /* nothing */
}

/*! \brief Initializes module */
void SEM_Init(void) {
  if (FRTOS1_xTaskCreate(vMasterTask, "Master", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  if (FRTOS1_xTaskCreate(vSlaveTask, "Slave", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL) != pdPASS) {
    for(;;){} /* error */
  }

}
