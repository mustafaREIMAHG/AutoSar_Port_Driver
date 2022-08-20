/*
 * Port.h
 *
 *  Created on: Jul 22, 2022
 *      Author: mustafa
 */

#ifndef PORT_H_
#define PORT_H_

/*
 * AUTOSAR Vendor ID
 */
#define PORT_VENDOR_ID                     (1000U)

/*
 *  Port Module ID
 */
#define PORT_MODULE_ID                     (124U)

/*
 * Port Instance ID
 */
#define PORT_INSTANCE_ID                   (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION              (1U)
#define PORT_SW_MINOR_VERSION              (0U)
#define PORT_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION      (4U)
#define PORT_AR_RELEASE_MINOR_VERSION      (0U)
#define PORT_AR_RELEASE_PATCH_VERSION      (3U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Dio Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Dio.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Dio.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/*==================================================================================
 *                            Module Type definitions
 *==================================================================================*/
/* Port_PinType: Data type for the symbolic name of a port pin. */
typedef  uint8   Port_PinType;

/*  Port_PinDirectionType: Possible directions of a port pin.*/
typedef enum{PORT_PIN_IN, PORT_PIN_OUT}  Port_PinDirectionType;

/* Port_PinModeType: Different port pin modes */
typedef  uint8       Port_PinModeType;

/* Port_ConfigType: Type of the external data structure containing the initialization data for this module. */
typedef struct
{
  Port_PinDirectionType     direction;              // port pin direction @ref Port_PinDirectionType.
  uint8                     directionChangeable;    // port pin direction changeable at run-time (STD_ON, STD_OFF).
  uint8                     initialValue;           // port pin initial value.(STD_HIGH, STD_LOW)
  uint8                     pullResistor;           // port pin pull-up, pull-down resistor.
  uint8                     openDrain;              // port pin open drain configuratio.
  uint8                     slewRate;               // port pin slew rate configuration (STD_ON, STD_OFF).
  uint8                     padDrive;               // port pin pad current drive.
  Port_PinModeType          mode;                   // port pin mode.
  uint8                     modeChangeable;         // port pin mode changeable at run-time (STD_ON, STD_OFF).

}Port_ConfigType;


extern const Port_ConfigType Port_Configuration [PORT_NUM_PORT_PIN];

/*==================================================================================
 *                             API Service Id Macros
 *==================================================================================*/
/* Service ID for Port_Init */
#define PORT_INIT_SID                       (0x00U)

/* Service ID for Port_SetPinDirection */
#define PORT_SET_PIN_DIRECTION_SID          (0x01U)

/* Service ID for Port_RefreshPortDirection */
#define PORT_REFRESH_PORT_DIRECTION_SID     (0x02U)

/* Service ID for Port_GetVersionInfo */
#define PORT_GET_VERSION_INFO_SID           (0x03U)

/* Service ID for Port_SetPinMode     */
#define PORT_SET_PIN_MODE_SID               (0x04U)

/*==================================================================================
 *                             DET Error Codes
 *==================================================================================*/

/* Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                    ((uint8)0x0A)
/* Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE       ((uint8)0x0B)
/* API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG                 ((uint8)0x0C)
/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_PARAM_INVALID_MODE           ((uint8)0x0D)
/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE            ((uint8)0x0E)
/* API service called with module initialization */
#define PORT_E_UNINIT                       ((uint8)0x0F)
/* API service called with a NULL pointer */
#define PORT_E_PARAM_POINTER                ((uint8)0x10)
/* API service called when trying to commit/ change mode of pins of specific consideration */
#define PORT_E_COMMIT_UNCHANGABLE           ((uint8)0x20)

/*==================================================================================
 *                        Function Prototypes
 *==================================================================================*/

/*Initializes the Port Driver module.*/
void Port_Init(const Port_ConfigType* ConfigPtr);

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/* Set the port pin direction */
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
#endif

/* Refreshes port direction. */
void Port_RefreshPortDirection(void);

#if (PORT_VERSION_INFO_API == STD_ON)
/*Returns the version information of this module.*/
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
/*Sets the port pin mode.*/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
#endif

#endif /* PORT_H_ */
