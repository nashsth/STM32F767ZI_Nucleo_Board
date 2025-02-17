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

int RCC_Configure_Clock(Clock_Source clock);

int RCC_Configure_PLL();

int RCC_Clock_Is_Ready();

int RCC_Set_System_Clock();

int RCC_Enable_Peripheral_Clock();

int RCC_Measure_Clock_Frequency();

int RCC_Output_Clock_Signal();



