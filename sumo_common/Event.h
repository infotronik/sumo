/**
 * \file
 * \brief Event driver interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic event driver. We are using numbered events starting with zero.
 * EVNT_HandleEvent() can be used to process the pending events. Note that the event with the number zero
 * has the highest priority and will be handled first
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "Platform.h"

#if PL_HAS_EVENTS

    typedef enum EVNT_Handle {
        EVNT_INIT,            /*!< System Initialization Event */
        EVNT_HEARTBEAT,		/*!< Heartbeat Event */
        EVNT_SW_A_PRESSED,	/*!< Switch A Pressed Event */
        EVNT_SW_B_PRESSED,	/*!< Switch B Pressed Event */
        EVNT_SW_C_PRESSED,	/*!< Switch C Pressed Event */
        EVNT_SW_D_PRESSED,	/*!< Switch D Pressed Event */
        EVNT_SW_E_PRESSED,	/*!< Switch E Pressed Event */
        EVNT_SW_F_PRESSED,	/*!< Switch F Pressed Event */
        EVNT_SW_G_PRESSED,	/*!< Switch G Pressed Event */
        EVNT_SW_A_LPRESSED,	/*!< Switch A Long Pressed Event */
        EVNT_SW_B_LPRESSED,	/*!< Switch B Long Pressed Event */
        EVNT_SW_C_LPRESSED,	/*!< Switch C Long Pressed Event */
        EVNT_SW_D_LPRESSED,	/*!< Switch D Long Pressed Event */
        EVNT_SW_E_LPRESSED,	/*!< Switch E Long Pressed Event */
        EVNT_SW_F_LPRESSED,	/*!< Switch F Long Pressed Event */
        EVNT_SW_G_LPRESSED,	/*!< Switch G Long Pressed Event */
        EVNT_SW_A_RELEASED,	/*!< Switch A Released Event */
        EVNT_SW_B_RELEASED,	/*!< Switch B Released Event */
        EVNT_SW_C_RELEASED,	/*!< Switch C Released Event */
        EVNT_SW_D_RELEASED,	/*!< Switch D Released Event */
        EVNT_SW_E_RELEASED,	/*!< Switch E Released Event */
        EVNT_SW_F_RELEASED,	/*!< Switch F Released Event */
        EVNT_SW_G_RELEASED,	/*!< Switch G Released Event */
        EVNT_REF_START_STOP_CALIBRATION, /*!< Start Stopp Calibration Event */
        EVNT_LINE,/*!< Line Detected Event */
        EVNT_NOF_EVENTS       /*!< Must be last one! */
    } EVNT_Handle;
    
    /*!
     * \brief Sets an event.
     * \param[in] event The handle of the event to set.
     */
    void EVNT_SetEvent(EVNT_Handle event);
    
    /*!
     * \brief Clears an event.
     * \param[in] event The event handle of the event to clear.
     */
    void EVNT_ClearEvent(EVNT_Handle event);
    
    /*!
     * \brief Returns the status of an event.
     * \param[in] event The event handler of the event to check.
     * \return TRUE if the event is set, FALSE otherwise.
     */
    bool EVNT_EventIsSet(EVNT_Handle event);
    
    /*!
     * \brief Returns the status of an event. As a side effect, the event gets cleared.
     * \param[in] event The event handler of the event to check.
     * \return TRUE if the event is set, FALSE otherwise.
     */
    bool EVNT_EventIsSetAutoClear(EVNT_Handle event);
    
    /*!
     * \brief Routine to check if an event is pending. If an event is pending, the event is cleared and the provided callback is called.
     * \param[in] callback Callback routine to be called. The event handle is passed as argument to the callback.
     */
    void EVNT_HandleEvent(void (*callback)(EVNT_Handle));
    
    /*! \brief Event module initialization */
    void EVNT_Init(void);
    
    /*! \brief Event module de-initialization */
    void EVNT_Deinit(void);

#endif /* PL_HAS_EVENTS */

#endif /* EVENT_H_ */
