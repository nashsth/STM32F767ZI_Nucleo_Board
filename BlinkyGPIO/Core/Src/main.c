#include "main.h"

#define DELAY (2000000)
#define HAL_DELAY (500000)

void Blink_Using_Registers(void)
{
	/*
	To make LED LD2 (connected to PB7) blink:
	1) Enable GPIOB clock
	2) Modify GPIOB_MODER, GPIOB_OTYPER, GPIOB_OSPEEDR, GPIOB_PUPDR
  */


	//step 1
	(RCC -> AHB1ENR) |= (RCC_AHB1ENR_GPIOBEN);

	//step 2: No need to modify OTYPER, OSPEEDR, PUPDR: default values will suffice
	(GPIOB -> MODER) &= ~(GPIO_MODER_MODER7); //Clear the bits to ensure a clean register
	(GPIOB -> MODER) |= (GPIO_MODER_MODER7_0);

	while(1)
	{
		(GPIOB -> BSRR) |= (GPIO_BSRR_BS7);
		for(volatile int i = 0; i <= DELAY; i++);

		(GPIOB -> BSRR) |= (GPIO_BSRR_BR7);
		for(volatile int i = 0; i <= DELAY; i++);
	}
}

void Blink_Using_Custom_HAL(void)
{
  /*
   To make LED LD2 blink using the custom HAL:
   1) Create a GPIO_Config struct and populate it with the configurations of your choice
   2) Call the GPIO_Init() function 
   3) Call the GPIO_Toggle() function 
   */

  GPIO_Config LED = 
    {
      .Pin = Pin_7,
      .Mode = Output,
      .Output_Mode = Push_Pull,
      .Output_Speed = Medium,
      .Pull = No_PullUp_PullDown,
      .Alternate_Function = Alternate_Function_0
    };

  GPIO_Init(GPIOB, &LED);

  while(1)
  {
    GPIO_Toggle(GPIOB, LED.Pin);
    for(volatile int i = 0; i <= HAL_DELAY; i++);
  }
}


int main(void)
{
  //Blink_Using_Registers();
  Blink_Using_Custom_HAL();
	return 0;
}

  /****************** Some Educational Notes *******************/
  /*
    * 1) How does the Peripheral Access Layer header file (stm32f767xx.h), included in main.h,
    * work?
    *
    * Answer: They declare a struct for each peripheral (e.g. the RCC_TypeDef struct for the Reset and
    * Clock Control peripheral). This struct contains all the registers pertaining to that peripheral.
    * Then, later in the file, they define the base address of the peripheral into a macro variable.
    * E.g. they define RCC_Base as the address of the RCC peripheral. They get this address from the
    * datasheet. Then, they define a pointer to the peripheral by type-casting the base address to the
    * struct type.
    *
    * E.g. #define RCC ((RCC_TypeDef *)(RCC_Base))
    *
    * With this, the pointer, RCC, now points to the RCC_TypeDef struct. Note that this is not the same 
    * thing as instantiating an instance of the struct. There is only one peripheral, hence only one
    * peripheral struct. RCC now modifies that struct directly.
    *
    * Then, further down the header file, they define positions and masks for all the bits of the
    * registers.
    *
    * 2) They don't define the address for each individual register. So then how can we manipulate
    * the registers at all? We only have a struct that represents a peripheral, and it contains the registers
    * for that peripheral, but it doens't contain the address offsets of those registers. I would have
    * expected something like #define RCC_CR_REGISTER (RCC_BASE + offset) where offset is the offset of the
    * CR register, which belongs to the RCC peripheral. However, there is no such definition, so how can 
    * it work? How can we access the individual registers? When I use the RCC pointer to modify the
    * RCC_TypeDef struct, how does the nucleo board know the appropriate register to modify?
    *
    * Answer: This is where struct padding comes into play. The peripheral struct is defined very
    * carefully. E.g. __IO uint32_t CR; __IO uint32_t PLLCFGR; etc.
    *
    * Recall that structs have fields which take up memory. Now the thing is, if you're not careful With
    * the padding, then the size of the struct can actually be larger than the sum of the sizes of the
    * fields. This is because the compiler can pad the struct wtih 0's so that the fields are aligned to 
    * some word boundaries. However, this would not work for embedded programming. This is because the
    * fields in the peripheral structs are carefully defined so that the fields appear in the same order
    * as they appear in the datasheet. For example, the CR register comes first (i.e. its offset is 0 from
    * the base address of the peripheral), then the PLLCFGR register, etc. 
    *
    * Now, each register of the STM32 is 32 bits large. This is why the registers are defined as uint32_t.
    * Next, by ensuring that there is no struct padding going on, all the fields in the struct will come
    * one after the other in memory. Hence, CR will have offset 0, then immediately afterwards in memory
    * will come PLLCFGR, etc. 
    *
    * Since we have defined a base address for the RCC_TypeDef peripheral, the STM32 will use that base
    * address, along with the compiler configuration of no structure padding, along with the careful
    * declaration/defintion of the peripheral struct, to know which register to modify. Notice the importance
    * of having no padding. If there were paddings, then the registers wouldn't be accessible, or would
    * be wrongly accessed, hence potentially crashing the system.
    *
    * This is how you are now able to use the RCC pointer to modify the various registers.
    *
    * Note that if we had defined a register address for every register, there would have been no point 
    * in defining the peripheral struct. This would make it more tedious to work with the registers:
    *
    * We would have had to do something like *((volatile uint32_t *)(RCC_BASE + offset)) if we 
    * wanted to access/write to a certain register, whose address is given by (RCC_BASE + offset).
    *
    * This instruction is first typecasting the register address to a uint32_t, and then dereferencing
    * that pointer. This is how you would have to modify every register if you had a register address,
    * rather than the peripheral struct.
    */


