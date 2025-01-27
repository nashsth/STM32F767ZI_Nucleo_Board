#include Custom_GPIO_HAL.h 

int GPIO_Init(GPIO_TypeDef* GPIO_Port, GPIO_Config* Configurations)
{
  //Step 1: Enable the clock and wait for it to be stable (for now, assume it to be the HSI clock)
  //Step 2: Modify the appropriate registers by copying values from the Configurations struct 

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
      return -1; //HSI Clock failed to stabilize
    }
  }

  (RCC -> AHB1ENR) |= 
}
