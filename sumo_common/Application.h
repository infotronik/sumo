/*
 * Application.h
 *
 *  Created on: 26.09.2014
 *      Author: marc
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Event.h"


void APP_Start(void);
static void APP_EventHandler(EVNT_Handle event);
#if PL_HAS_RTOS
void TaskLoop(void *pvParameters);
#else
static void APP_Loop(void);
#endif



#endif /* APPLICATION_H_ */
