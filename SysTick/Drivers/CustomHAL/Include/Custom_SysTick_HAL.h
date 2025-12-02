//APIs for the SysTick timer

#pragma once


#include <stddef.h>
#include "stm32f767xx.h"
#include <stdint.h>
#include "Custom_RCC_HAL.h" //the RCC HAL is central to all other peripheral HALs because the RCC
                            //HAL is the one that enables the clock to all peripherals. It might
                            //not be important for the SysTick HAL because SysTick is a ARM-core
                            //peripheral rather than an STM32 peripheral, but get in the habit of
                            //including the RCC HAL in all other HALs.

/* Initialize the SysTIck peripheral. Need to:
 * 1) Select the clock source that will drive the SysTick peripheral (in Hz),
 * 2) Determine how frequently you want the interrupts to occur (also in Hz e.g. 1000 Hz = 1 ms)
 *
 * This function needs to modify the SysTick registers:
 * - SYST_CSR
 * - SYST_RVR
 * - SYST_CVR
 */
void SysTick_Init_ms(uint32_t clk_hz, tick_hz);


/* Return how many tick periods/counts has been obtained since SysTick peripheral was initialized
 *
 */
uint32_t SysTick_Get_Ticks(void);


/* Busy-wait for a given number of tick periods. By busy-wait, I mean that it prevents other tasks
 * from running (i.e. it just loops and polls until the timer is up). This isn't good for RTOS, though,
 * so I shouldn't use this function in that context.
 */
void SysTick_Delay(uint32_t ticks);

