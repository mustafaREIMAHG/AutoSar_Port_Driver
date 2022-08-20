/*
 * Port.c
 *
 *  Created on: Jul 22, 2022
 *      Author: mustafa
 */

#include "Port.h"
#include "MemMap.h"             // "Std_Types.h" included through "Port.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
#include <stdio.h>
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif

#define PORT_STATUS_INITIALIZED                 (STD_HIGH)
#define PORT_STATUS_NOT_INITIALIZED             (STD_LOW)

STATIC GPIO_TypeDef *GPIO_ptr[] = { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF };
STATIC uint8 Port_Init_Status = PORT_STATUS_NOT_INITIALIZED;

/* Port index, return port number */
#define PORT_PIN_TO_PORT_INDEX(__PORT_PIN__)   ((uint8)((__PORT_PIN__ < 32U) ? (__PORT_PIN__/8U):\
                                                    (((__PORT_PIN__- 32U)/5U) ? (5U):(4U))))
/* Pin index, return pin number */
#define PORT_PIN_TO_PIN_INDEX(__PORT_PIN__)    ((uint8)((__PORT_PIN__ < 32U) ? (__PORT_PIN__%8U):\
                                               (((__PORT_PIN__- 32U)/5U) ? (__PORT_PIN__ - 38U):(__PORT_PIN__ - 32U))))
/* Return pin mode position in PMC control register */
#define PORT_PIN_INDEX_TO_PMC_PIN_POS(__PIN_INDEX__)                ((uint32)(__PIN_INDEX__ << 2U))

/*==================================================================================
 * Service Name: Port_Init
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Non-reentrant
 * Parameters (in): ConfigPtr - Pointer to configuration set.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Initializes the Port Driver module.
 ==================================================================================*/
void Port_Init(const Port_ConfigType *ConfigPtr)
{
  uint8 pinIndex, portIndex;
  Port_PinType portPin;
  GPIO_TypeDef *GPIOx;

  const Port_ConfigType *portPinConfig; // used to optimize ConfigPtr call

#if (PORT_DEV_ERROR_DETECT == STD_ON)

  if (ConfigPtr == NULL_PTR)
  {
    /* Report DET error wrong configuration parameter */
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
                    PORT_E_PARAM_CONFIG);
    return;
  }
#endif
  /* Loop through each port pin*/
  for (portPin = 0; portPin < PORT_NUM_PORT_PIN; portPin++)
  {
    /* GPIO With special Considerations */
    if (
    // @formatter:off
        portPin == PORT_A_PIN_0 ||
        portPin == PORT_A_PIN_1 ||
        portPin == PORT_A_PIN_2 ||
        portPin == PORT_A_PIN_3 ||
        portPin == PORT_A_PIN_4 ||
        portPin == PORT_A_PIN_5 ||

        portPin == PORT_B_PIN_2 ||
        portPin == PORT_B_PIN_3 ||

        portPin == PORT_C_PIN_0 ||
        portPin == PORT_C_PIN_1 ||
        portPin == PORT_C_PIN_2 ||
        portPin == PORT_C_PIN_3 ||

        portPin == PORT_D_PIN_7 ||
        portPin == PORT_F_PIN_0
        // @formatter:on
    )

    {
      /* Nothing to do ----------------------*/
    }
    else
    {
      /* Load the port pin configuration */
      portPinConfig = &ConfigPtr[portPin];
      /* ----- Get pin index and port index of portPin number ---------------------------------------------*/
      pinIndex = PORT_PIN_TO_PIN_INDEX(portPin); /* 0 ~ 7 */
      portIndex = PORT_PIN_TO_PORT_INDEX(portPin); /* 0 ~ 5 */
      /* pointer to GPIO Base address */
      GPIOx = GPIO_ptr[portIndex];

      if (portPinConfig->mode == PORT_PIN_MODE_ADC)
      {
        /* --------------- Port Pin Analog Mode configuration: Pull-up, Pull-down resistors ---------------*/
        GPIOx->AMSEL |= (1 << pinIndex);
      }
      else if (portPinConfig->mode >= PORT_PIN_MODE_INVALID)
      {
        /* Error: Invalid Mode, Report DET Error */
      }
      else
      {
        /*========================================================
         *   Digital Function Configurations:
         *        - Alternate Function Select
         *        - GPIO
         *           - Input:
         *                * Pull-Up, Pull-Down, Pull-Off.
         *           - Output:
         *                * Open drain / Push Pull.
         *                * Pad Drive: 2-mA, 4-mA, 8-mA.
         *                * Slew-Rate : Enable / Disable.
         =========================================================*/
        /* Enable port pin digital function */
        GPIOx->DEN |= (1 << pinIndex);
        /* Port Pin Direction Configuration -----------------------------------------*/
        if ((portPinConfig->mode) > PORT_PIN_MODE_DIO)
        {
          /* Alternate function select */
          GPIOx->AFSEL |= (1 << pinIndex);
          /* Digital Function (GPIOPCTL PMCx Bit Field Encoding), See page 1351 */
          GPIOx->PCTL |= ((portPinConfig->mode)
              << PORT_PIN_INDEX_TO_PMC_PIN_POS(pinIndex));
        }
        else
        {
          /* Nothing to do -------*/
        }
        /* Port Pin Direction Configuration -----------------------------------------*/
        if (portPinConfig->direction == PORT_PIN_IN)
        {
          /* port pin in is input */
          GPIOx->DIR &= ~(1 << pinIndex);
          /* Pull-up, Pull-down configuration ---------------------------------------*/
          if (portPinConfig->pullResistor == PORT_PIN_PULL_UP)
          {
            GPIOx->PUR |= (1 << pinIndex);        // Enable Pull-Up.
          }
          else if (portPinConfig->pullResistor == PORT_PIN_PULL_DOWN)
          {
            GPIOx->PDR |= (1 << pinIndex);        // Enable Pull-Down.
          }
          else
          {
            /* PORT_PIN_PULL_OFF, floating : Unused port pin flow ends here --------*/
          }
        }
        else if (portPinConfig->direction == PORT_PIN_OUT)
        {
          /* Port Pin is output */
          GPIOx->DIR |= (1 << pinIndex);
          /* port pin open drain configuration */
          if (portPinConfig->openDrain == PORT_PIN_OPEN_DRAIN_ON)
          {
            GPIOx->ODR |= (1 << pinIndex);    // Enable Open-drain.
          }
          else
          {
            /* Port Pin output is Push/Pull, Nothing to do */
          }
          /* port pin drive strength and slew rate configuration -------------------*/
          switch (portPinConfig->padDrive)
          {
            case PORT_PIN_PAD_DRIVE_2_MA:
            {
              GPIOx->DR2R |= (1 << pinIndex);     // Enable 2-mA Drive strength.
              break;
            }

            case PORT_PIN_PAD_DRIVE_4_MA:
            {
              GPIOx->DR4R |= (1 << pinIndex);     // Enable 4-mA Drive strength.
              break;
            }
            case PORT_PIN_PAD_DRIVE_8_MA:
            {
              GPIOx->DR8R |= (1 << pinIndex);     // Enable 8-mA Drive strength.
              /* slew rate control only available in 8 mA drive mode*/
              if (portPinConfig->slewRate == PORT_PIN_SLEW_RATE_ON)
              {
                GPIOx->SLR |= (1 << pinIndex);
              }
              else
              {
                /* Nothing to do, -------------*/
              }
              break;
            }
            default:
              /* No drive strength Configuration */
              break;
          }
        }
        else
        {
          /* Wrong Configuration, Report DET Error */
        }
      }
    }
  }
  /* Control reached port initialization */
  Port_Init_Status = PORT_STATUS_INITIALIZED;
}

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/*==================================================================================
 * Service Name: Port_SetPinDirection
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): -Pin  -   Port Pin ID number
 *                  -Direction - Port Pin Direction
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the port pin direction.
 ==================================================================================*/
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* Invalid input parameter */
  if(Pin >= PORT_NUM_PORT_PIN)
  {
    /* Report DET error invalid pin parameter */
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                    PORT_E_PARAM_PIN);
    return;
  }
  /* port initialization */
  if(Port_Init_Status == PORT_STATUS_NOT_INITIALIZED)
  {
    /* Report DET error port module is not initialized */
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                    PORT_E_UNINIT);
    return;
  }

#endif

  uint8 pinIndex, portIndex;
  GPIO_TypeDef *GPIOx;
  const Port_ConfigType *portPinConfig; // used to optimize ConfigPtr call

  /* Load the port pin configuration */
  portPinConfig = &Port_Configuration[Pin];
  /* ----- Get pin index and port index of Pin number ---------------------------------------------*/
  pinIndex = PORT_PIN_TO_PIN_INDEX(Pin); /* 0 ~ 7 */
  portIndex = PORT_PIN_TO_PORT_INDEX(Pin); /* 0 ~ 5 */
  /* pointer to GPIO Base address */
  GPIOx = GPIO_ptr[portIndex];

#if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* pin changeable direction */
  if(portPinConfig->directionChangeable == STD_OFF)
  {
    /* Report DET error pin direction is not changeable */
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
                    PORT_E_DIRECTION_UNCHANGEABLE);
  }
  else
#endif
  {
    if(Direction == PORT_PIN_OUT)
    {
      /* Port Pin is output */
      GPIOx->DIR |= (1 << pinIndex);
    }
    else if(Direction == PORT_PIN_IN)
    {
      /* Port Pin is Input */
      GPIOx->DIR &=~(1 << pinIndex);
    }
  }
}
#endif

/*==================================================================================
 * Service Name: Port_RefreshPortDirection
 * Service ID[hex]: 0x02
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Refreshes port direction.
 ==================================================================================*/
void Port_RefreshPortDirection(void)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* port initialization */
  if(Port_Init_Status == PORT_STATUS_NOT_INITIALIZED)
  {
  /* Report DET error port module is not initialized */
  Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID,
                  PORT_E_UNINIT);
  return;
  }
#endif

  uint8 pinIndex, portIndex;
  Port_PinType portPin;
  GPIO_TypeDef *GPIOx;

  const Port_ConfigType *portPinConfig;

  /* Loop through each port pin*/
   for (portPin = 0; portPin < PORT_NUM_PORT_PIN; portPin++)
   {
     /* GPIO With special Considerations */
     if (
     // @formatter:off
         portPin == PORT_A_PIN_0 ||
         portPin == PORT_A_PIN_1 ||
         portPin == PORT_A_PIN_2 ||
         portPin == PORT_A_PIN_3 ||
         portPin == PORT_A_PIN_4 ||
         portPin == PORT_A_PIN_5 ||

         portPin == PORT_B_PIN_2 ||
         portPin == PORT_B_PIN_3 ||

         portPin == PORT_C_PIN_0 ||
         portPin == PORT_C_PIN_1 ||
         portPin == PORT_C_PIN_2 ||
         portPin == PORT_C_PIN_3 ||

         portPin == PORT_D_PIN_7 ||
         portPin == PORT_F_PIN_0
         // @formatter:on
     )

     {
       /* Nothing to do ----------------------*/
     }
     else
     {
       /* Load the port pin configuration */
       portPinConfig = &Port_Configuration[portPin];
       /* ----- Get pin index and port index of portPin number ---------------------------------------------*/
       pinIndex = PORT_PIN_TO_PIN_INDEX(portPin); /* 0 ~ 7 */
       portIndex = PORT_PIN_TO_PORT_INDEX(portPin); /* 0 ~ 5 */
       /* pointer to GPIO Base address */
       GPIOx = GPIO_ptr[portIndex];

       if(portPinConfig->mode < PORT_PIN_MODE_ADC &&     // Digital port pin
           portPinConfig->directionChangeable == STD_ON)        // Port pin is run-time changeable
       {
         if(portPinConfig->direction == PORT_PIN_OUT)
         {
           /* Set pin direction to output*/
           GPIOx->DIR |=(1<<pinIndex);
         }
         else if(portPinConfig->direction == PORT_PIN_IN)
         {
           /* Set pin direction to input */
           GPIOx->DIR &=~(1<<pinIndex);
         }
         else
         {
           /*--- Nothing to do --------------------*/

         }
       }
     }
   }
}

#if (PORT_VERSION_INFO_API == STD_ON)
/*==================================================================================
 * Service Name: Port_GetVersionInfo
 * Service ID[hex]: 0x03
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): versioninfo -   Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Returns the version information of this module.
 *==================================================================================*/
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if(PORT_DEV_ERROR_DETECT == STD_ON)
  if(Port_Init_Status == PORT_STATUS_NOT_INITIALIZED)
  {
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID,
                      PORT_E_UNINIT);
    return;
  }
#endif
  /* Return port version information */
  versioninfo->vendorID = PORT_VENDOR_ID;
  versioninfo->moduleID = PORT_MODULE_ID;
  versioninfo->sw_major_version = PORT_SW_MAJOR_VERSION;
  versioninfo->sw_minor_version = PORT_SW_MINOR_VERSION;
  versioninfo->sw_patch_version = PORT_SW_PATCH_VERSION;

}
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
/*==================================================================================
 * Service Name: Port_SetPinMode
 * Service ID[hex]: 0x04
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): -Pin     - Port Pin ID number
 *                  -Mode    - New Port Pin mode to be set on port pin
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Sets the port pin mode.
 *==================================================================================*/
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{

#if (PORT_DEV_ERROR_DETECT == STD_ON)

  /* module initialized */
  if(Port_Init_Status == PORT_STATUS_NOT_INITIALIZED)
  {
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                    PORT_E_UNINIT);
  }
  /* Invalid input parameter */
  if(Pin >= PORT_NUM_PORT_PIN)
  {
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                    PORT_E_PARAM_PIN);
    return;
  }

  if(Mode >= PORT_PIN_MODE_INVALID)
  {
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                    PORT_E_PARAM_INVALID_MODE);
    return;
  }
#endif

  /* GPIO With special Considerations */
  if (
  // @formatter:off
      Pin == PORT_A_PIN_0 ||
      Pin == PORT_A_PIN_1 ||
      Pin == PORT_A_PIN_2 ||
      Pin == PORT_A_PIN_3 ||
      Pin == PORT_A_PIN_4 ||
      Pin == PORT_A_PIN_5 ||

      Pin == PORT_B_PIN_2 ||
      Pin == PORT_B_PIN_3 ||

      Pin == PORT_C_PIN_0 ||
      Pin == PORT_C_PIN_1 ||
      Pin == PORT_C_PIN_2 ||
      Pin == PORT_C_PIN_3 ||

      Pin == PORT_D_PIN_7 ||
      Pin == PORT_F_PIN_0
      // @formatter:on
  )

  {
    /* Nothing to do ----------------------*/
  }
  else
  {
    uint8 pinIndex, portIndex;
    GPIO_TypeDef *GPIOx;
    const Port_ConfigType *portPinConfig; // used to optimize ConfigPtr call

    /* Load the port pin configuration */
    portPinConfig = &Port_Configuration[Pin];
    /* ----- Get pin index and port index of Pin number ---------------------------------------------*/
    pinIndex = PORT_PIN_TO_PIN_INDEX(Pin); /* 0 ~ 7 */
    portIndex = PORT_PIN_TO_PORT_INDEX(Pin); /* 0 ~ 5 */
    /* pointer to GPIO Base address */
    GPIOx = GPIO_ptr[portIndex];

#if (PORT_DEV_ERROR_DETECT == STD_ON)

    if (portPinConfig->modeChangeable == STD_OFF)
    {
      Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
                      PORT_E_MODE_UNCHANGEABLE);
      return;
    }
    else
    {

    }
#endif

    if (Mode == PORT_PIN_MODE_ADC)
    {
      /* --------------- Port Pin Analog Mode configuration: Pull-up, Pull-down resistors ---------------*/
      /* Disable port pin digital function */
      GPIOx->DEN &=~(1 << pinIndex);
      /*Disable Alternate function select */
      GPIOx->AFSEL &=~(1 << pinIndex);
      /* Analog port pin*/
      GPIOx->AMSEL |= (1 << pinIndex);
    }
    else if (Mode >= PORT_PIN_MODE_INVALID)
    {
      /* Error: Invalid Mode, Report DET Error */
    }
    else
    {
      /* Disable analog */
      GPIOx->AMSEL &=~(1 << pinIndex);
      /* Enable port pin digital function */
      GPIOx->DEN |= (1 << pinIndex);
      /* Port Pin Direction Configuration -----------------------------------------*/
      if (Mode > PORT_PIN_MODE_DIO)
      {
        /* Alternate function select */
        GPIOx->AFSEL |= (1 << pinIndex);
        /* Digital Function (GPIOPCTL PMCx Bit Field Encoding), See page 1351 */
        GPIOx->PCTL |= (Mode
            << PORT_PIN_INDEX_TO_PMC_PIN_POS(pinIndex));
      }
      else
      {
        /* Nothing to do -------*/
      }
    }
  }
}
#endif
