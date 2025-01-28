#include Custom_GPIO_HAL.h 

int GPIO_Init(GPIO_TypeDef* GPIO_Port, GPIO_Config* Configurations)
{
  //Step 1: Wait for clock to be stable (for now, assume it to be the HSI clock)
  //Step 2: Enable clock to peripheral 
  //Step 3: Modify the appropriate registers by copying values from the Configurations struct 

  if(GPIO_Port < GPIOA || GPIO_Port > GPIOK)
  {
    return -1; //invalid port given -- STM32F767xx has ports A through K only.
  }
  //Step 1 
  uint32_t Timeout = 1000000;
  if(!((RCC -> CR) & RCC_CR_HSION))
  {
    (RCC -> CR) |= RCC_CR_HSION;
  }

  while(!((RCC -> CR) & RCC_CR_HSIRDY))
  {
    Timeout--;
    if(0 == Timeout)
    {
      return -2; //HSI Clock failed to stabilize
    }
  }
  
  //Step 2
  //To determine what value to put in the AHB1ENR register, use the memory map. Each GPIO port is 0x400
  //bytes away from each other: GPIOA_BASE is at 0x40020000, GPIOB_BASE at 0x40020400, etc.
  //Hence, we can calculate the offset that each GPIO port is from the base address of 0x4002 0000
  //and use that offset to set the correct bit in the register. The value for the GPIO base address is 
  //already defined in the stm32f767xx.h file, so you don't need to redefine it.
  
  uint32_t GPIO_Port_Offset = (GPIO_Port - GPIOA_BASE)/(GPIOB_BASE - GPIOA_BASE);
  (RCC -> AHB1ENR) |= (1 << GPIO_Port_Offset);

  //Step 3 
  (GPIO_Port -> MODER) &= ~(0b11 << ((Configurations -> Pin)*2)); //clear the MODER register's bits
  //corresponding to the Pin so that those bits have a well-defined starting value 

  (GPIO_Port -> MODER) |= (Configurations -> Mode) << ((Configurations -> Pin)*2);
}
