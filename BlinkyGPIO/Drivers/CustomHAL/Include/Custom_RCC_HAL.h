/*
 * This HAL deals with the "Reset and Clock Control" (RCC) peripheral of the STM32F767ZI nucleo board.
 *
 * By default, the HSI is used by the STM32 immediately upon power-up. You cannot change what clock 
 * the STM32 uses on power-up because there must be a default clock source already present for the CPU
 * to do anything useful. Only AFTER the CPU has performed some startup routines (setting up the stack 
 * pointer, moving data from flash to RAM, etc) can you choose what clock source to use to run your 
 * application.
 *
 * This HAL lets you perform operations related to the clock source. E.g. switching the clock source,
 * checking to see if a clock source is ready, configuring a clock source, etc.
 *
 *
 *
 */ 


/* Function prototypes to consider:
 * 
 * 1) Clock-out capability: allow pins PA8 and PC9 to output a clock signal.
 * MCO1 = PA8 clock signal = {HSI, LSE, HSE, PLL}
 * MCO2 = PC0 clock signal = {HSE, PLL, SYSCLK, PLLI2S}
 * => make {HSI, LSE, ...} an enum so that the user can select a clock source
 * => Function prototype: int Output_Clock(MCO1/MCO2, Clock source);
 * => This suggests making MCO1 and MCO2 as an enum as well
 *
 *
 * 2) Peripheral clock enabling. How would this interact with the GPIO HAL? Would the GPIO HAL include this
 * RCC HAL? 
 *
 * 3) Internal/external clock measuring using TIM5, channel 4 and TIM11, channel 1. Can be used to measure
 * and confirm clock frequencies. This will require the timer module to be set up so come back to this 
 * later.
 *
 * 4) Setting up a clock source with the appropriate parameters. 
 *
 * 5) Switching the system clock to use something other than the HSI. 
 *
 *
 *
 *
 *
 * */ 

#pragma once 

#include "stm32f767xx.h"
#include <stddef.h>

typedef enum
{
  HSI = 0,
  HSE,
  LSE,
  LSI,
  PLL 
} Clocks;

typedef enum 
{
  HSI = 0,
  HSE 
} PLL_Source;

typedef struct 
{
  Clocks clock;
  struct
  {
    PLL_Source Source;
    uint8_t M;
    uint16_t N;
    uint8_t P;
    uint8_t Q;
  } PLL_Config;

} Clock_Source;

typedef enum
{
  //AHB1 peripherals
  RCC_GPIOA = 0,
  RCC_GPIOB,
  RCC_GPIOC,
  RCC_GPIOD,
  RCC_GPIOE,
  RCC_GPIOF,
  RCC_GPIOG,
  RCC_GPIOH,
  RCC_GPIOI,
  RCC_GPIOJ,
  RCC_GPIOK,
  RCC_CRC,
  RCC_BKPSRAM,
  RCC_DTCMRAM,
  RCC_DMA1,
  RCC_DMA2,
  RCC_ETHMAC,
  RCC_ETHMACTX,
  RCC_ETHMACRX,
  RCC_ETHMACPTP,
  RCC_OTGHS,
  RCC_OTGHSULPI,

  //ABH2 Peripherals 
  RCC_DCMI,
  RCC_JPEG,
  RCC_RNG,
  RCC_OTGFS,

  //AHB3 Peripherals 
  RCC_FMC,
  RCC_QSPI,

  //APB1 Peripherals  
  RCC_TIM2,
  RCC_TIM3,
  RCC_TIM4,
  RCC_TIM5,
  RCC_TIM6,
  RCC_TIM7,
  RCC_TIM12,
  RCC_TIM13,
  RCC_TIM14,
  RCC_LPTIM1,
  RCC_WWDG,
  RCC_CAN3,
  RCC_SPI2,
  RCC_SPI3,
  RCC_SPDIFRX,
  RCC_USART2,
  RCC_USART3,
  RCC_UART4,
  RCC_UART5,
  RCC_I2C1,
  RCC_I2C2,
  RCC_I2C3,
  RCC_I2C4,
  RCC_CAN1,
  RCC_CAN2,
  RCC_CEC,
  RCC_PWR,
  RCC_DAC,
  RCC_UART7,
  RCC_UART8,

  //APB2 Peripherals  
  RCC_TIM1,
  RCC_TIM8,
  RCC_USART1,
  RCC_USART6,
  RCC_SDMMC2,
  RCC_ADC1,
  RCC_ADC2,
  RCC_ADC3,
  RCC_SDMMC1,
  RCC_SPI1,
  RCC_SPI4,
  RCC_SYSCFG,
  RCC_TIM9,
  RCC_TIM10,
  RCC_TIM11,
  RCC_SPI5,
  RCC_SPI6,
  RCC_SAI1,
  RCC_SAI2,
  RCC_LTDC,
  RCC_DSI,
  RCC_DFSDM1,
  RCC_MDIO,
  RCC_COUNT
} Peripherals;

typedef struct
{
  volatile uint32_t* Register, //must be a pointer because we deal with a register (i.e. an address in memory) here
  uint32_t Bit
} Peripheral_Clock_Enable_t;

extern const Peripheral_Clock_Enable_t RCC_Table[COUNT];

int RCC_Configure_Clock(Clock_Source clock);

int RCC_Configure_PLL();

int RCC_Clock_Is_Ready();

int RCC_Set_System_Clock();

//This one is the most important function. The question is, how do we implement this
//function in a nice way, without using a bunch of switch/if statements? The goal of
//this function is to enable the appropriate clock given a peripheral. There are 4
//of these peripheral-enable registers, and each peripheral's clock enable bit is in
//a different position in these registers. So if we're given some peripheral, then
//how can we correctly enable the correct register, and the correct bit in that register?
//At first, I was thinking about having a giant switch-case/if-else statements: if
//peripheral == GIPOA, enable bit Y in register X, and so forth. But this giant switch-case
//statement is a headache to maintain and is too amateur. So, my next thought was to use a
//hashmap, but the problem with that is that hashmaps are dynamic and shouldn't be used in an
//embedded context. However, even though I shouldn't use a hashmap, I can still use the
//underlying principle behind hashmaps -- a hashmap's key principle is that of associativity.
//So, I thought of creating a sort of "compile-time hashmap/associative map". 
//You have an array of structs, where each struct contains the perihepral name (which can 
//be collected in an enum), the corresponding peripheral-enable register, and the bit 
//position within that register. This isn't technically a hashmap because there's no hashing
//going on, however this method still uses the principle of associativty -- it associates the
//peripheral name with the register information for that peripheral.

int RCC_Enable_Peripheral_Clock();

int RCC_Measure_Clock_Frequency();

int RCC_Output_Clock_Signal();



