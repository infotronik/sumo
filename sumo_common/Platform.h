#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "PE_Types.h" /* for common Processor Expert types used throughout the project, e.g. 'bool' */
#include "PE_Error.h" /* global error constants */
#include <stddef.h>   /* for NULL */

/* List of supported platforms. The PL_BOARD_IS_xxx is defined in the compiler command line settings.  */
#define PL_IS_FRDM  (defined(PL_BOARD_IS_FRDM))
    /*!< Macro is defined through compiler option for the FRDM board */
#define PL_IS_ROBO  (defined(PL_BOARD_IS_ROBO))
    /*!< Macro is defined through compiler option for the Robot board */

#define PL_IS_INTRO_ZUMO_K22_V2 (1)


#if PL_IS_FRDM
    #define PL_HAS_KEYS  (1)
        /*!< Set to 1 to enable KEYS support, 0 otherwise */
    #define PL_HAS_KBI  (1)
        /*!< Set to 1 to enable KBI support, 0 otherwise */
	#define PL_NOF_KEYS       (7)
        /*!< FRDM board has up to 7 KEYs */
    #define PL_KEY_POLLED_KEY_A  (0)
    #define PL_KEY_POLLED_KEY_B  (0)
    #define PL_KEY_POLLED_KEY_C  (0)
    #define PL_KEY_POLLED_KEY_D  (0)
    #define PL_KEY_POLLED_KEY_E  (1)
    #define PL_KEY_POLLED_KEY_F  (1)
    #define PL_KEY_POLLED_KEY_G  (0)
    #define PL_HAS_DEBOUNCE (1)
        /*!< Set to 1 to enable Debounce support, 0 otherwise */

    #define PL_HAS_LED  (1)
        /*!< Set to 1 to enable LED support, 0 otherwise */
    #define PL_NOF_LEDS       (2)
        /*!< FRDM board has up to 3 LEDs (RGB) */

    #define PL_HAS_JOYSTICK  (1)
    #define PL_APP_ACCEL_CONTROL_SENDER (1)
        /*!< Set to 1 to enable JOYSTICK support, 0 otherwise */
    #define PL_HAS_EVENTS  (1)
        /*!< Set to 1 to enable EVENTS support, 0 otherwise */

    #define PL_HAS_TIMER  (1)
        /*!< Set to 1 to enable TIMER support, 0 otherwise */

    #define PL_HAS_TRIGGER  (1)
        /*!< Set to 1 to enable Trigger support, 0 otherwise */

    #define PL_HAS_RTOS (1)
        /*!< Set to 1 to enable RTOS support, 0 otherwise */

    #define PL_HAS_SHELL  (1)
        /*!< Set to 1 to enable Shell support, 0 otherwise */

    #define PL_HAS_SHELL_QUEUE (0)
        /*!< Set to 1 to enable Shell-Queue support, 0 otherwise */

    #define PL_HAS_BLUETOOTH (0)
        /*!< Set to 1 to enable Bluetooth support, 0 otherwise */

    #define PL_HAS_USB_CDC (1)
        /*!< Set to 1 to enable USB CDC support, 0 otherwise */

    #define PL_HAS_SEMAPHORE (0)
        /*!< Set to 1 to enable Semaphore support, 0 otherwise */

    #define PL_HAS_ACCEL (1)
        /*!< Set to 1 to enable Acceleration support, 0 otherwise */

	#define PL_HAS_RADIO (1)
        /*!< Set to 1 to enable Radio support, 0 otherwise */

    #define PL_HAS_REMOTE (1)
        /*!< Set to 1 to enable Remote support, 0 otherwise */

#elif PL_IS_ROBO
    #define PL_HAS_KEYS  (1)
        /*!< Set to 1 to enable KEYS support, 0 otherwise */
    #define PL_HAS_KBI  (1)
        /*!< Set to 1 to enable KBI support, 0 otherwise */
    #define PL_NOF_KEYS       (1)
        /*!< FRDM board has up to 2 KEYs */
    #define PL_HAS_DEBOUNCE (1)
        /*!< Set to 1 to enable Debounce support, 0 otherwise */

    #define PL_HAS_LED  (1)
        /*!< Set to 1 to enable LED support, 0 otherwise */
    #define PL_NOF_LEDS       (1)
        /*!< We have up to 2 LED's on the robo board */
    #define PL_HAS_BUZZER  (1)
        /*!< Set to 1 to enable Buzzer support, 0 otherwise */
	#define PL_HAS_LINE_SENSOR  (1)
        /*!< Set to 1 to enable Line Sensor support, 0 otherwise */
	#define PL_HAS_MOTOR  (1)
        /*!< Set to 1 to enable Line Sensor support, 0 otherwise */

    #define PL_HAS_EVENTS  (1)
        /*!< Set to 1 to enable EVENTS support, 0 otherwise */

    #define PL_HAS_TIMER  (1)
        /*!< Set to 1 to enable TIMER support, 0 otherwise */

    #define PL_HAS_TRIGGER  (1)
        /*!< Set to 1 to enable Trigger support, 0 otherwise */

    #define PL_HAS_RTOS (1)
        /*!< Set to 1 to enable RTOS support, 0 otherwise */

    #define PL_HAS_SHELL  (1)
        /*!< Set to 1 to enable Shell support, 0 otherwise */

    #define PL_HAS_SHELL_QUEUE (1)
    /*!< Set to 1 to enable Shell-Queue support, 0 otherwise */

    #define PL_HAS_BLUETOOTH (1)
        /*!< Set to 1 to enable Bluetooth support, 0 otherwise */

    #define PL_HAS_USB_CDC (1)
    /*!< Set to 1 to enable USB CDC support, 0 otherwise */

    #define PL_HAS_SEMAPHORE (0)
    /*!< Set to 1 to enable Semaphore support, 0 otherwise */

    #define PL_HAS_QUAD_CALIBRATION (1)
    /*!< Set to 1 to enable QUAD_CALIBRATION support, 0 otherwise */
    #define PL_HAS_MCP4728 (1)
    /*!< Set to 1 to enable MCP4728 support, 0 otherwise */

    #define PL_HAS_MOTOR_TACHO (1)
        /*!< Set to 1 to enable Motor Tacho support, 0 otherwise */

    #define PL_HAS_DRIVE (1)
        /*!< Set to 1 to enable Drive support, 0 otherwise */

    #define PL_HAS_PID (1)
        /*!< Set to 1 to enable PID support, 0 otherwise */

    #define PL_HAS_ULTRASONIC (1)
        /*!< Set to 1 to enable Ultrasonic support, 0 otherwise */

    #define PL_NOF_ULTRASONIC (2)
        /*!< Number of ultrasonic sensors */

    #define PL_HAS_ACCEL (1)
        /*!< Set to 1 to enable Acceleration support, 0 otherwise */

	#define PL_HAS_RADIO (1)
        /*!< Set to 1 to enable Radio support, 0 otherwise */

    #define PL_HAS_REMOTE (1)
        /*!< Set to 1 to enable Remote support, 0 otherwise */

	#define PL_HAS_BATTLE (1)
        /*!< Set to 1 to enable Battle support, 0 otherwise */

	#define PL_HAS_CONFIG_NVM (1)
        /*!< Set to 1 to enable Battle support, 0 otherwise */

	#define PL_HAS_SERVO (1)
        /*!< Set to 1 to enable Servo support, 0 otherwise */

#else
    //#error "unknown configuration?"
#endif

/*!
 * \brief Platform initialization
 */
void PL_Init(void);

/*!
 * \brief Platform de-initialization
 */
void PL_Deinit(void);

#endif /* PLATFORM_H_ */
