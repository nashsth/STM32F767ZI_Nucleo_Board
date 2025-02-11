#include Custom_GPIO_HAL.h 

int GPIO_Init(GPIO_TypeDef* GPIO_Port, GPIO_Config* Configurations)
{
  //Step 1: Wait for clock to be stable (for now, assume it to be the HSI clock)
  //Step 2: Enable clock to peripheral 
  //Step 3: Modify the appropriate registers by copying values from the Configurations struct 

  if(GPIO_Port == NULL || GPIO_Port < GPIOA || GPIO_Port > GPIOK)
  {
    return GPIO_ERROR_INVALID_PORT; //invalid port given -- STM32F767xx has ports A through K only.
  }

  if(Configurations == NULL)
  {
    return GPIO_ERROR_INVALID_CONFIG;
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
      return GPIO_ERROR_CLOCK_TIMEOUT; //HSI Clock failed to stabilize
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

  (GPIO_Port -> OTYPER) &= ~(0b1 << ((Configurations -> Pin)));
  (GPIO_Port -> OTYPER) |= (Configurations -> Output_Mode) << (Configurations -> Pin);
  

  (GPIO_Port -> OSPEEDR) &= ~(0b11 << ((Configurations -> Pin)*2));
  (GPIO_Port -> OSPEEDR) |= (Configurations -> Output_Speed) << ((Configurations -> Pin)*2);
  

  (GPIO_Port -> PUPDR) &= ~(0b11 << ((Configurations -> Pin)*2));
  (GPIO_Port -> PUPDR) |= (Configurations -> Output_Pull) << ((Configurations -> Pin)*2);
  
  if((Configurations -> Mode) ==  Alternate_Function)
  {
    if((Configurations -> Pin) <= Pin_7)
    {
      //modify the low register
      (GPIO_Port -> AFR[0]) &= ~(0b1111 << ((Configurations -> Pin)*4));
      (GPIO_Port -> AFR[0]) |= (Configurations -> Alternate_Function) << ((Configurations -> Pin)*4);

    }
    
    else if((Configurations -> Pin) <= Pin_15)
    {
      //modify the high register 
      (GPIO_Port -> AFR[1]) &= ~(0b1111 << ((Configurations -> Pin)*4));
      (GPIO_Port -> AFR[1]) |= (Configurations -> Alternate_Function) << ((Configurations -> Pin)*4);
    }

    else
    {
      return GPIO_ERROR_INVALID_PIN;
    }
  }

  return GPIO_OK;
}

int GPIO_Read(GPIO_TypeDef* GPIO_Port, Pin pin)
{
  //Step 1: Check for out-of-bounds port and pin parameters
  //Step 2: Read the pin and return the result

  //Step 1 
  if(GPIO_Port == NULL || GPIO_Port < GPIOA || GPIO_Port > GPIOK)
  {
    return GPIO_ERROR_INVALID_PORT;
  }

  if(pin < Pin_0 || pin > Pin_15)
  {
    return GPIO_ERROR_INVALID_PIN;
  }

  //Step 2 
  //Read the appropriate bit of IDR register (input data register) by bit shifting a 1 to the
  //proper location, and using the bitwise AND operator, then shift that result back to the right.
  //This is important because if you didn't bit shift the result back to the right, you'd be reading
  //the entire 32-bit value, rather than reading only the bit value of interest.
  return (((GPIO_Port -> IDR) & (0b1 << pin)) >> pin);
}

int GPIO_Write(GPIO_TypeDef* GPIO_Port, Pin pin, uint8_t value)
{
  //Step 1: Check for out-of-bounds port, pin and value parameters 
  //Write a 1 to the appropriate bit in the BSRR register. Remember that the BSRR register is a 
  //Write-Only register, so we only need to write a 1 to the proper location to either set or
  //reset the corresponding pin in the port. 

  //Step 1 
  if(GPIO_Port == NULL || GPIO_Port < GPIOA || GPIO_Port > GPIOK)
  {
    return GPIO_ERROR_INVALID_PORT;
  }

  if(pin < Pin_0 || pin > Pin_15)
  {
    return GPIO_ERROR_INVALID_PIN;
  }

  if(value > 1)
  {
    return GPIO_ERROR_INVALID_WRITE_VALUE;
  }
  
  //Step 2 
  if(value == 1)
  {
    (GPIO_Port -> BSRR) = (1 << pin);
  }
  else if(value == 0)
  {
    (GPIO_Port -> BSRR) = (1 << (pin + 16));
  }

  return GPIO_OK;
}

int GPIO_Set(GPIO_TypeDef* GPIO_Port, Pin pin)
{
  return (GPIO_Write(GPIO_Port, pin, 1));
}

int GPIO_Reset(GPIO_TypeDef* GPIO_Port, Pin pin)
{
  return (GPIO_Write(GPIO_Port, pin, 0));
}

int GPIO_Toggle(GPIO_TypeDef* GPIO_Port, Pin pin)
{
  if(GPIO_Port == NULL || GPIO_Port < GPIOA || GPIO_Port > GPIOK)
  {
    return GPIO_ERROR_INVALID_PORT;
  }

  if(pin < Pin_0 || pin > Pin_15)
  {
    return GPIO_ERROR_INVALID_PIN;
  }
  
  (GPIO_Port -> ODR) ^= (1 << pin);

  return GPIO_OK;
}
