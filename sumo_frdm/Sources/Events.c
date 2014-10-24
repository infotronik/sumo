/* ###################################################################
**     Filename    : Events.c
**     Project     : sumo_frdm
**     Processor   : MKL25Z128VLK4
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2014-09-24, 16:01, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "Platform.h"

#if PL_HAS_TIMER
  #include "Timer.h"
#endif

#if PL_HAS_KBI
	#include "Keys.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  Cpu_OnNMIINT (module Events)
**
**     Component   :  Cpu [MKL25Z128LK4]
*/
/*!
**     @brief
**         This event is called when the Non maskable interrupt had
**         occurred. This event is automatically enabled when the [NMI
**         interrupt] property is set to 'Enabled'.
*/
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TI1_OnInterrupt(void)
{
#if PL_HAS_TIMER
	TMR_OnInterrupt();
#endif
}

/*
** ===================================================================
**     Event       :  SW_G_OnInterrupt (module Events)
**
**     Component   :  SW_G [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SW_G_OnInterrupt(void)
{
#if PL_HAS_KBI
	if(KEY7_Get()){
		KEY_OnInterrupt(KEY_BTN7);
	}
#endif
}

/*
** ===================================================================
**     Event       :  SW_D_OnInterrupt (module Events)
**
**     Component   :  SW_D [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SW_D_OnInterrupt(void)
{
#if PL_HAS_KBI
	if(KEY4_Get()){
		KEY_OnInterrupt(KEY_BTN4);
	}
#endif
}

/*
** ===================================================================
**     Event       :  SW_C_OnInterrupt (module Events)
**
**     Component   :  SW_C [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SW_C_OnInterrupt(void)
{
#if PL_HAS_KBI
	if(KEY3_Get()){
		KEY_OnInterrupt(KEY_BTN3);
	}
#endif
}

/*
** ===================================================================
**     Event       :  SW_B_OnInterrupt (module Events)
**
**     Component   :  SW_B [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SW_B_OnInterrupt(void)
{
#if PL_HAS_KBI
	if(KEY2_Get()){
		KEY_OnInterrupt(KEY_BTN2);
	}
#endif
}

/*
** ===================================================================
**     Event       :  SW_A_OnInterrupt (module Events)
**
**     Component   :  SW_A [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void SW_A_OnInterrupt(void)
{
#if PL_HAS_KBI
	if(KEY1_Get()){
		KEY_OnInterrupt(KEY_BTN1);
	}
#endif
}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.10]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
