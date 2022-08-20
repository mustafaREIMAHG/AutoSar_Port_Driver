/*
 *  Dio_Regs.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Dio Driver Registers
 *
 * Created on: Jul 22, 2022
 *      Author: mustafa
 */
 

#ifndef _MEM_MAP_H
#define _MEM_MAP_H

/* ------------------------  TM4C123GH6PM registers used in Dio.c -----------------------*/
#define GPIO_PORTA_DATA_REG       (*((volatile uint32 *)0x400043FC))
#define GPIO_PORTB_DATA_REG       (*((volatile uint32 *)0x400053FC))
#define GPIO_PORTC_DATA_REG       (*((volatile uint32 *)0x400063FC))
#define GPIO_PORTD_DATA_REG       (*((volatile uint32 *)0x400073FC))
#define GPIO_PORTE_DATA_REG       (*((volatile uint32 *)0x400243FC))
#define GPIO_PORTF_DATA_REG       (*((volatile uint32 *)0x400253FC))
/* --------------------------------------------------------------------------------------*/


/* Exported Types -----------------------------------------------------------------------*/
/*
 * @brief GPIO_Type
 */
typedef struct
{
  volatile uint32_t DATA[256];                          /* GPIO Data bit-banding aliases */
  volatile uint32_t DIR;                                /* GPIO Direction */
  volatile uint32_t IS;                                 /* GPIO Interrupt Sense */
  volatile uint32_t IBE;                                /* GPIO Interrupt Both Edges */
  volatile uint32_t IEV;                                /* GPIO Interrupt Event */
  volatile uint32_t IM;                                 /* GPIO Interrupt Mask */
  volatile uint32_t RIS;                                /* GPIO Raw Interrupt Status */
  volatile uint32_t MIS;                                /* GPIO Masked Interrupt Status */
  volatile uint32_t ICR;                                /* GPIO Interrupt Clear */
  volatile uint32_t AFSEL;                              /* GPIO Alternate Function Select */
  volatile uint32_t RESERVED0[55];                      /* RESERVED*/
  volatile uint32_t DR2R;                               /* GPIO 2-mA Drive Select */
  volatile uint32_t DR4R;                               /* GPIO 4-mA Drive Select */
  volatile uint32_t DR8R;                               /* GPIO 8-mA Drive Select */
  volatile uint32_t ODR;                                /* GPIO Open Drain Select */
  volatile uint32_t PUR;                                /* GPIO Pull-Up Select */
  volatile uint32_t PDR;                                /* GPIO Pull-Down Select */
  volatile uint32_t SLR;                                /* GPIO Slew Rate Control Select */
  volatile uint32_t DEN;                                /* GPIO Digital Enable */
  volatile uint32_t LOCK;                               /* GPIO Lock */
  volatile uint32_t CR;                                 /* GPIO Commit */
  volatile uint32_t AMSEL;                              /* GPIO Analog Mode Select */
  volatile uint32_t PCTL;                               /* GPIO Port Control */
  volatile uint32_t ADCCTL;                             /* GPIO ADC Control */
  volatile uint32_t DMACTL;                             /* GPIO DMA Control */
  volatile uint32_t RESERVED1[678];                     /* RESERVED */
  volatile uint32_t PERIPHID4;                          /* GPIO Peripheral Identification 4 */
  volatile uint32_t PERIPHID5;                          /* GPIO Peripheral Identification 5 */
  volatile uint32_t PERIPHID6;                          /* GPIO Peripheral Identification 6 */
  volatile uint32_t PERIPHID7;                          /* GPIO Peripheral Identification 7 */
  volatile uint32_t PERIPHID0;                          /* GPIO Peripheral Identification 0 */
  volatile uint32_t PERIPHID1;                          /* GPIO Peripheral Identification 1 */
  volatile uint32_t PERIPHID2;                          /* GPIO Peripheral Identification 2 */
  volatile uint32_t PERIPHID3;                          /* GPIO Peripheral Identification 3 */
}GPIO_TypeDef;

/*
 * @ref GPIOPCTL  PMC field
 */

/*
 *  Constant Macros
 */
#define GPIO_PORT_DATA                  (0xFF)      // Index of all port data


 /* GPIO peripheral MemoryMap ----------- APB aperture  -------------------*/

#ifndef  GPIO_AHB_APERTURE

#define GPIOA_BASE          (0x40004000UL)
#define GPIOB_BASE          (0x40005000UL)
#define GPIOC_BASE          (0x40006000UL)
#define GPIOD_BASE          (0x40007000UL)
#define GPIOE_BASE          (0x40024000UL)
#define GPIOF_BASE          (0x40025000UL)

#else
/* GPIO peripheral MemoryMap ----------- AHB Bus  -------------------------*/
#define GPIOA_BASE          (0x40058000UL)
#define GPIOB_BASE          (0x40059000UL)
#define GPIOC_BASE          (0x4005A000UL)
#define GPIOD_BASE          (0x4005B000UL)
#define GPIOE_BASE          (0x4005C000UL)
#define GPIOF_BASE          (0x4005D000UL)

#endif
/* GPIO definition ----------------------------------------------------------*/
#define GPIOA               ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *)GPIOE_BASE)
#define GPIOF               ((GPIO_TypeDef *)GPIOF_BASE)



#endif /* DIO_REGS_H */
