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
static void APP_Loop(void);



#endif /* APPLICATION_H_ */
