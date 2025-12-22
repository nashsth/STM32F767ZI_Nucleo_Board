#include "Custom_RCC_HAL.h"

const Peripheral_Clock_Enable_t RCC_Table[RCC_COUNT] = 
{
  //AHB1 peripherals
  [RCC_GPIOA] = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_GPIOAEN},
  [RCC_GPIOB] = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_GPIOBEN},
  [RCC_GPIOC] = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_GPIOCEN},
  [RCC_GPIOD] = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_GPIODEN},
  [RCC_GPIOE] = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_GPIOEEN},
  [RCC_GPIOF] = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_GPIOFEN},
  [RCC_GPIOG] = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_GPIOGEN},
  [RCC_GPIOH] = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_GPIOHEN},
  [RCC_GPIOI] = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_GPIOIEN},
  [RCC_GPIOJ] = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_GPIOJEN},
  [RCC_GPIOK] = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_GPIOKEN},
  [RCC_CRC]     = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_CRCEN},
  [RCC_BKPSRAM] = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_BKPSRAMEN},
  [RCC_DTCMRAM] = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_DTCMRAMEN},
  [RCC_DMA1]    = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_DMA1EN},
  [RCC_DMA2]    = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_DMA2EN},
  [RCC_DMA2D]   = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_DMA2DEN},
  [RCC_ETHMAC]   = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_ETHMACEN},
  [RCC_ETHMACTX]   = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_ETHMACTXEN}, 
  [RCC_ETHMACRX]   = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_ETHMACRXEN},
  [RCC_ETHMACPTP]   = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_ETHMACPTPEN},
  [RCC_OTGHS]   = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_OTGHSEN},
  [RCC_OTGHSULPI]   = {.Register = (&RCC->AHB1ENR), .Bit = RCC_AHB1ENR_OTGHSULPIEN},

  //AHB2 Peripherals
  [RCC_DCMI]   = {.Register = (&RCC->AHB2ENR), .Bit = RCC_AHB2ENR_DCMIEN},
  [RCC_JPEG]   = {.Register = (&RCC->AHB2ENR), .Bit = RCC_AHB2ENR_JPEGEN},
  [RCC_RNG]   = {.Register = (&RCC->AHB2ENR), .Bit = RCC_AHB2ENR_RNGEN},
  [RCC_OTGFS]   = {.Register = (&RCC->AHB2ENR), .Bit = RCC_AHB2ENR_OTGFSEN},

  //AHB3 Peripherals
  [RCC_FMC]   = {.Register = (&RCC->AHB3ENR), .Bit = RCC_AHB3ENR_FMCEN},
  [RCC_QSPI]   = {.Register = (&RCC->AHB3ENR), .Bit = RCC_AHB3ENR_QSPIEN},

  //APB1 Peripherals

  [RCC_TIM2]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_TIM2EN},
  [RCC_TIM3]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_TIM3EN},
  [RCC_TIM4]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_TIM4EN},
  [RCC_TIM5]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_TIM5EN},
  [RCC_TIM6]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_TIM6EN},
  [RCC_TIM7]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_TIM7EN},
  [RCC_TIM12]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_TIM12EN},
  [RCC_TIM13]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_TIM13EN},
  [RCC_TIM14]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_TIM14EN},
  [RCC_LPTIM1]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_LPTIM1EN},
  [RCC_WWDG]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_WWDGEN},
  [RCC_CAN3]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_CAN3EN},
  [RCC_SPI2]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_SPI2EN},
  [RCC_SPI3]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_SPI3EN},
  [RCC_SPDIFRX]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_SPDIFRXEN},
  [RCC_USART2]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_USART2EN},
  [RCC_USART3]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_USART3EN},
  [RCC_UART4]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_UART4EN},
  [RCC_UART5]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_UART5EN},
  [RCC_I2C1]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_I2C1EN},
  [RCC_I2C2]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_I2C2EN},
  [RCC_I2C3]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_I2C3EN},
  [RCC_I2C4]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_I2C4EN},
  [RCC_CAN1]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_CAN1EN},
  [RCC_CAN2]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_CAN2EN},
  [RCC_CEC]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_CECEN},
  [RCC_PWR]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_PWREN},
  [RCC_DAC]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_DACEN},
  [RCC_UART7]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_UART7EN},
  [RCC_UART8]   = {.Register = (&RCC->APB1ENR), .Bit = RCC_APB1ENR_UART8EN},

  //APB2 Peripherals

  [RCC_TIM1]     = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_TIM1EN},
  [RCC_TIM8]     = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_TIM8EN},
  [RCC_USART1]   = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_USART1EN},
  [RCC_USART6]   = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_USART6EN},
  [RCC_SDMMC2]   = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_SDMMC2EN},
  [RCC_ADC1]     = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_ADC1EN},
  [RCC_ADC2]     = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_ADC2EN},
  [RCC_ADC3]     = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_ADC3EN},
  [RCC_SDMMC1]   = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_SDMMC1EN},
  [RCC_SPI1]     = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_SPI1EN},
  [RCC_SPI4]     = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_SPI4EN},
  [RCC_SYSCFG]   = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_SYSCFGEN},
  [RCC_TIM9]     = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_TIM9EN},
  [RCC_TIM10]    = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_TIM10EN},
  [RCC_TIM11]    = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_TIM11EN},
  [RCC_SPI5]     = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_SPI5EN},
  [RCC_SPI6]     = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_SPI6EN},
  [RCC_SAI1]     = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_SAI1EN},
  [RCC_SAI2]     = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_SAI2EN},
  [RCC_LTDC]     = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_LTDCEN},
  // [RCC_DSI]      = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_DSIEN}, //This peripheral apparently isn't defined in the stm32f767xx.h file.
  [RCC_DFSDM1]   = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_DFSDM1EN},
  [RCC_MDIO]     = {.Register = (&RCC->APB2ENR), .Bit = RCC_APB2ENR_MDIOEN},
};

int RCC_Enable_Peripheral_Clock(Peripherals peripheral)
{
  *RCC_Table[peripheral].Register |= (RCC_Table[peripheral].Bit);
  return 0;
}

int RCC_Disable_Peripheral_Clock(Peripherals peripheral)
{
  *RCC_Table[peripheral].Register &= ~(RCC_Table[peripheral].Bit);
  return 0;
}

int RCC_Configure_Clock(Clock_Source_Config* clock_config)
{
  uint32_t Timeout = 1000000;
  if(clock_config->clock == CLOCK_HSI)
  {
    if(clock_config->Configure_PLL != NULL)
    {
      return -1; //you can't have PLL configurations if you're not using PLL
    }

    if(!((RCC->CR) & RCC_CR_HSION))
    {
      (RCC->CR) |= RCC_CR_HSION;
    }

    while(!((RCC->CR) & RCC_CR_HSIRDY))
    {
      Timeout--;
      if(Timeout == 0)
      {
        return -1;
      }
    }

    return 0;
  }

  else if(clock_config->clock == CLOCK_HSE)
  {
    if(clock_config->Configure_PLL != NULL)
    {
      return -1; //you can't have PLL configurations if you're not using PLL
    }
    return 0;
    //do nothing because I don't have an external oscillator so I'm not going to implement the logic for this
  }

  else if(clock_config->clock == CLOCK_LSE)
  {
    if(clock_config->Configure_PLL != NULL)
    {
      return -1; //you can't have PLL configurations if you're not using PLL
    }
    return 0;
    //do nothing because I don't have an external oscillator
  }
  
  else if(clock_config->clock == CLOCK_LSI)
  {
    if(clock_config->Configure_PLL != NULL)
    {
      return -1; //you can't have PLL configurations if you're not using PLL
    }

    (RCC->CSR) |= RCC_CSR_LSION;
    while(!((RCC->CSR) & RCC_CSR_LSIRDY))
    {
      Timeout--;
      if(Timeout==0)
      {
        return -1; //oscillator couldn't stabilize so no point in being stuck in an infinite loop
      }
      // With RTOS's you'd want to yield instead of busy-waiting so that you're not wasting CPU time
    }

    return 0;
  }

  else if (clock_config->clock == CLOCK_PLL)
  {
    if((clock_config->Configure_PLL) == NULL)
    {
      return -1; //If you're using PLL, then you have to have a valid PLL configuration
    }
    
    //Set PLLSRC as either HSI (0) or HSE (1); since HSE won't be implemented, set to 0.
    if(((clock_config->Configure_PLL)->Source) == PLL_HSI)
    {
      (RCC->PLLCFGR) &= ~(RCC_PLLCFGR_PLLSRC); //Remember that the HSI has a frequency of 16 MHz.
    }
    
    else if(((clock_config->Configure_PLL)->Source) == PLL_HSE)
    {
      //(RCC->PLLCFGR) |= (RCC_PLLCFGR_PLLSRC); //If you want to use HSE
      (RCC->PLLCFGR) &= ~(RCC_PLLCFGR_PLLSRC);
    }
    
    //M = division factor for main PLL input clock
    //N = multiplication factor for VCO (VCO = Voltage Controlled Oscillator)
    //P = division factor for main system clock
    //Q = division factor USB, SDMMC, and RNG clock
    //R = division factor for DSI clock
    //Therefore, if you only want to set PLL as system clock, you only need to worry about M, N, and P.
    //Q and R are for peripherals that we don't care about right now.
    
    //Since it's impossible to check all possible combinations of M,N,P, Q, etc, we'll only 
    //go with one combination for now.

    Pll_Config PLL_216Mhz_From_HSI = 
    {
      .Source = PLL_HSI,
      .M = 16, //010000 in binary
      .N = 432, //110110000 in binary
      .P = 2, //10. However, the reference manual says that if you want P = 2, then you set PLLP to 00
      .Q = 9 //1001
    };

    //Clear the contents of PLLCFGR before modifying it as per the config struct
    (RCC->PLLCFGR) &= ~(RCC_PLLCFGR_PLLM_Msk |
                  RCC_PLLCFGR_PLLN_Msk |
                  RCC_PLLCFGR_PLLP_Msk |
                  RCC_PLLCFGR_PLLQ_Msk);

    //Configure the PLLCFGR register appropriately, based on the values of the config struct.
    (RCC->PLLCFGR) |= (RCC_PLLCFGR_PLLM_4); //Set the M value
    (RCC->PLLCFGR) |= (RCC_PLLCFGR_PLLN_8 | RCC_PLLCFGR_PLLN_7 | RCC_PLLCFGR_PLLN_5 | RCC_PLLCFGR_PLLN_4); //Set the N value
    //Since P = 2 <=> PLLP = 00, no need to use any bit-twidling
    (RCC->PLLCFGR) |= (RCC_PLLCFGR_PLLQ_3 | RCC_PLLCFGR_PLLQ_0); //Set the Q value


    //enable PLL
    (RCC->CR) |= (RCC_CR_PLLON);

    //Wait for PLL to be ready
    while(!((RCC->CR) & RCC_CR_PLLRDY))
    {
      Timeout--;
      if(Timeout ==0)
      {
        return -1; //PLL couldn't stabilitize so no point in being stuck in an infinite loop
      }
    }

    return 0;
  }
  return -1; //one clock MUST be selected. If code reaches this point, return an error
}

int RCC_Set_System_Clock(Clock_Source_Config* clock_config)
{
  uint32_t Timeout = 1000000;

  if(clock_config == NULL)
  {
    return -1;
  }

  switch(clock_config->clock)
  {
    case CLOCK_HSI:
      if(RCC_Configure_Clock(clock_config) !=0)
      {
        return -1;
      }
      (RCC->CFGR) &= ~(RCC_CFGR_SW); //Clear SW fields before modifiyng it
      (RCC->CFGR) |= (RCC_CFGR_SW_HSI); //Put 00 to SW field of CFGR register to set HSI as system clock
      while(((RCC->CFGR) & (RCC_CFGR_SWS)) != RCC_CFGR_SWS_HSI) //Check if the system clock really is HSI
      {
        Timeout--;
        if(Timeout == 0)
        {
          return -1;
        }
      }
      return 0;

    case CLOCK_PLL:
      if(RCC_Configure_Clock(clock_config) != 0)
      {
        return -1;
      }
      (RCC->CFGR) &= ~(RCC_CFGR_SW); //Clear SW fields before modifying it
      (RCC->CFGR) |= (RCC_CFGR_SW_PLL); //Put 10 to SW field of CFGR register to set PLL as system clock
      while(((RCC->CFGR) & (RCC_CFGR_SWS)) != RCC_CFGR_SWS_PLL) //Check if the system clock really is PLL
      {
        Timeout--;
        if(Timeout == 0)
        {
          return -1;
        }
      }
      return 0;
  
    default: //LSI, LSE can't be used as system clock and HSE isn't implemented so do nothing
      return -1;
  }

  return 0;
}
