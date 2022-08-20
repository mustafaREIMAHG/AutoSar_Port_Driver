/*
 * Port_Cfg.h
 *
 *  Created on: Jul 22, 2022
 *      Author: mustafa
 */

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

#include "Std_Types.h"

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION            (1U)
#define PORT_CFG_SW_MINOR_VERSION            (0U)
#define PORT_CFG_SW_PATCH_VERSION            (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION      (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION      (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION      (3U)

/*=================================================================================
 * Symbolic names for the individual port pins defined in the configuration tool
 *              for TM4C123GH6PH  MCU
 *=================================================================================*/
/* (8) GPIO for port A ----------------------- */
#define PORT_A_PIN_0                                    (0U)
#define PORT_A_PIN_1                                    (1U)
#define PORT_A_PIN_2                                    (2U)
#define PORT_A_PIN_3                                    (3U)
#define PORT_A_PIN_4                                    (4U)
#define PORT_A_PIN_5                                    (5U)
#define PORT_A_PIN_6                                    (6U)
#define PORT_A_PIN_7                                    (7U)
/* (8) GPIO for port B ----------------------- */
#define PORT_B_PIN_0                                    (8U)
#define PORT_B_PIN_1                                    (9U)
#define PORT_B_PIN_2                                    (10U)
#define PORT_B_PIN_3                                    (11U)
#define PORT_B_PIN_4                                    (12U)
#define PORT_B_PIN_5                                    (13U)
#define PORT_B_PIN_6                                    (14U)
#define PORT_B_PIN_7                                    (15U)
/* (8) GPIO for port C ----------------------- */
#define PORT_C_PIN_0                                    (16U)
#define PORT_C_PIN_1                                    (17U)
#define PORT_C_PIN_2                                    (18U)
#define PORT_C_PIN_3                                    (19U)
#define PORT_C_PIN_4                                    (20U)
#define PORT_C_PIN_5                                    (21U)
#define PORT_C_PIN_6                                    (22U)
#define PORT_C_PIN_7                                    (23U)
/* (8) GPIO for port D ----------------------- */
#define PORT_D_PIN_0                                    (24U)
#define PORT_D_PIN_1                                    (25U)
#define PORT_D_PIN_2                                    (26U)
#define PORT_D_PIN_3                                    (27U)
#define PORT_D_PIN_4                                    (28U)
#define PORT_D_PIN_5                                    (29U)
#define PORT_D_PIN_6                                    (30U)
#define PORT_D_PIN_7                                    (31U)
/* (6) GPIO for port E ----------------------- */
#define PORT_E_PIN_0                                    (32U)
#define PORT_E_PIN_1                                    (33U)
#define PORT_E_PIN_2                                    (34U)
#define PORT_E_PIN_3                                    (35U)
#define PORT_E_PIN_4                                    (36U)
#define PORT_E_PIN_5                                    (37U)
/* (5) GPIO for port F ----------------------- */
#define PORT_F_PIN_0                                    (38U)
#define PORT_F_PIN_1                                    (39U)
#define PORT_F_PIN_2                                    (40U)
#define PORT_F_PIN_3                                    (41U)
#define PORT_F_PIN_4                                    (42U)

/*=================================================================================
 *                          Port Pin Mode Configuration
 *================================================================================*/
#define PORT_PIN_MODE_INVALID                               (16U)

#define PORT_PIN_MODE_DIO                                   (0U)
#define PORT_PIN_MODE_CAN_AF_PMC_3                          (3U)
#define PORT_PIN_MODE_CAN_AF_PMC_8                          (8U)
#define PORT_PIN_MODE_ICU_AF_PMC_7                          (7U)
#define PORT_PIN_MODE_SPI_AF_PMC_1                          (1U)
#define PORT_PIN_MODE_SPI_AF_PMC_2                          (2U)
#define PORT_PIN_MODE_PWM_AF_PMC_4                          (4U)
#define PORT_PIN_MODE_PWM_AF_PMC_5                          (5U)
#define PORT_PIN_MODE_ADC                                   (15U)

#define PORT_PIN_MODE_LIN                               (PORT_PIN_MODE_INVALID)     /* Not supported in this module */
#define PORT_PIN_MODE_MEM                               (PORT_PIN_MODE_INVALID)     /* Not supported in this module */
#define PORT_PIN_MODE_FLEXRAY                           (PORT_PIN_MODE_INVALID)     /* Not supported in this module */
#define PORT_PIN_MODE_DIO_GPT                           (PORT_PIN_MODE_INVALID)     /* Not supported in this module */
#define PORT_PIN_MODE_DIO_WDG                           (PORT_PIN_MODE_INVALID)     /* Not supported in this module */


/*=================================================================================
 *                          Port Pin Pull-Up / Pull-Down Configuration
 *================================================================================*/
#define PORT_PIN_PULL_OFF                (0x00U)
#define PORT_PIN_PULL_UP                 (0x01U)
#define PORT_PIN_PULL_DOWN               (0x02U)

/*=================================================================================
 *                          Pad Drive Configuration
 *================================================================================*/
#define PORT_PIN_PAD_DRIVE_2_MA          (0x01U)
#define PORT_PIN_PAD_DRIVE_4_MA          (0x02U)
#define PORT_PIN_PAD_DRIVE_8_MA          (0x03U)

/*=================================================================================
 *                          Open drain push/pull configuration
 *================================================================================*/
#define PORT_PIN_OPEN_DRAIN_OFF          (0x00U)            /* Port pin configured as open drain */
#define PORT_PIN_OPEN_DRAIN_ON           (0x01U)            /* Port pin configured as Push/Pull */

/*=================================================================================
 *                          slew rate control configuration
 *================================================================================*/
#define PORT_PIN_SLEW_RATE_OFF          (0x01U)
#define PORT_PIN_SLEW_RATE_ON           (0x01U)

/*=================================================================================
 *                          General port configuration
 *================================================================================*/

/* The number of specified PortPins, 43 for TM4C123 */
#define PORT_NUM_PORT_PIN                       (43U)
/* Pre-compile configuration for development code detection */
#define PORT_DEV_ERROR_DETECT                   (STD_ON)
/* Pre-processor switch to enable / disable the use of the function Poer_SetPinDirection() */
#define PORT_SET_PIN_DIRECTION_API              (STD_ON)
/* Pre-processor switch to enable / disable the use of the function Port_SetPinMode(). */
#define PORT_SET_PIN_MODE_API                   (STD_ON)
/* Pre-processor switch to enable / disable the API to read out the modules version information.*/
#define PORT_VERSION_INFO_API                   (STD_ON)

/*=================================================================================
 *                          Port Pin default configuration
 *================================================================================*/
/*
 * Default configuration for the configuration struct, each port pin is configured as the following
 *
 *      direction:                    - PORT_PIN_IN
 *      directionChangeable:          - STD_OFF
 *      initialValue:                 - STD_LOW
 *      pullResistor:                 - PORT_PIN_PULL_OFF
 *      slewRate:                     - STD_OFF
 *      padDrive:                     - STD_OFF
 *      mode:                         - PORT_PIN_MODE_DIO
 *      modeChangeable:               - STD_OFF
 */

#define PORT_PIN_DEFAULT_CONFIG                 {PORT_PIN_IN, STD_OFF, STD_LOW, PORT_PIN_PULL_OFF,  \
                                                   PORT_PIN_OPEN_DRAIN_OFF, STD_OFF, STD_OFF, PORT_PIN_MODE_DIO, STD_OFF}

/*=================================================================================
 *                          Port Pin Numeric Constants Configuration
 *================================================================================*/
/* Input Numeric Constants Mapping -------------------*/
#define PORT_PIN_SW1_NUM                (PORT_F_PIN_4)
#define PORT_PIN_SW2_NUM                (PORT_F_PIN_0)
/* Output Numeric Constants Mapping ------------------*/
#define PORT_PIN_LED_RED_NUM            (PORT_F_PIN_1)
#define PORT_PIN_LED_GREEN_NUM          (PORT_F_PIN_2)
#define PORT_PIN_LED_BLUE_NUM           (PORT_F_PIN_3)

#define PORT_PIN_SW1_CONFIG             {PORT_PIN_IN, STD_OFF, STD_LOW, PORT_PIN_PULL_UP, \
                                         PORT_PIN_OPEN_DRAIN_OFF, STD_OFF, STD_OFF,  PORT_PIN_MODE_DIO, STD_OFF}

#define PORT_PIN_SW2_CONFIG             PORT_PIN_DEFAULT_CONFIG

#define PORT_PIN_LED_RED_CONFIG         {PORT_PIN_OUT, STD_OFF, STD_LOW, PORT_PIN_PULL_OFF, \
                                         PORT_PIN_OPEN_DRAIN_OFF, STD_OFF, STD_OFF,  PORT_PIN_MODE_DIO, STD_OFF}

#define PORT_PIN_LED_GREEN_CONFIG         {PORT_PIN_OUT, STD_OFF, STD_LOW, PORT_PIN_PULL_OFF, \
                                         PORT_PIN_OPEN_DRAIN_OFF, STD_OFF, STD_OFF,  PORT_PIN_MODE_DIO, STD_OFF}

#define PORT_PIN_LED_BLUE_CONFIG         {PORT_PIN_OUT, STD_OFF, STD_LOW, PORT_PIN_PULL_OFF, \
                                         PORT_PIN_OPEN_DRAIN_OFF, STD_OFF, STD_OFF,  PORT_PIN_MODE_DIO, STD_OFF}



#endif /* PORT_CFG_H_ */
