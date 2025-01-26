/* This header file contains custom HAL functions related to the GPIO peripheral of the 
 * STM32F767ZI nucleo board.
 *
 *
 * Using this custom HAL, the use should be able to setup any GPIO pin to any 
 * acceptable/allowed configuration.
 * */

#pragma once 

/* Configuration struct deals with high-level concepts:
 * which pin do you want to configure? input or output? speed? etc.
 *
 * The GPIO_Port struct deals with modifying the registers so that your 
 * high-level concepts are realized.
 *
 * Configuration struct should be using enums for better readability.
 * An enum should be defined for every configuration option. Input/output, 
 * speed, pin, etc.
 *
 *
 *
 *
 *
 * */

typedef enum GPIO_Pins 
{
  Pin_1 = 0,
  Pin_2,
  Pin_3,
  Pin_4,
  Pin_5,
  Pin_6,
  Pin_7,
  Pin_8,
  Pin_9,
  Pin_10,
  Pin_11,
  Pin_12,
  Pin_13,
  Pin_14,
  Pin_15
} Pin;

typedef enum GPIO_Mode
{
  Input = 0,
  Output,
  Alternate_Function,
  Analog
} Mode;

typedef enum GPIO_Output_Mode
{
  Push_Pull = 0,
  Open_Drain
} Output_Mode;

typedef enum GPIO_Output_Speed 
{
  Low = 0,
  Medium,
  High,
  Very_High
} Output_Speed;

typedef enum GPIO_PullUp_PullDown 
{
  No_PullUp_PullDown = 0,
  PullUp,
  PullDown
} Output_PullUp_PullDown;



typedef struct GPIO_Configuration
{
  //pin 
  //mode 
  //speed 
  //pull-up/pull-down
  //alternate function 
} GPIO_Config; 

int GPIO_Init(GPIO_TypeDef* GPIO_Port, GPIO_Config* Configurations);

int GPIO_Read(GPIO_TypeDef* GPIO_Port, Pin pin);

int GPIO_Write(GPIO_TypeDef* GPIO_Port, Pin pin, uint8_t value);

int GPIO_Set(GPIO_TypeDef* GPIO_Port, Pin pin);

int GPIO_Reset(GPIO_TypeDef* GPIO_Port, Pin pin);

int GPIO_Init_Alternate_Function();
