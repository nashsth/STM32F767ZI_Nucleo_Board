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
  Pin_0 = 0,
  Pin_1,
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
} GPIO_Pin;

typedef enum GPIO_Mode
{
  Input = 0,
  Output,
  Alternate_Function,
  Analog
} GPIO_Mode;

typedef enum GPIO_Output_Mode
{
  Push_Pull = 0,
  Open_Drain
} GPIO_Output_Mode;

typedef enum GPIO_Output_Speed 
{
  Low = 0,
  Medium,
  High,
  Very_High
} GPIO_Output_Speed;

typedef enum GPIO_PullUp_PullDown 
{
  No_PullUp_PullDown = 0,
  PullUp,
  PullDown
} GPIO_Output_Pull;

typedef enum GPIO_Alternate_Functions
{
  Alternate_Function_0 = 0,
  Alternate_Function_1,
  Alternate_Function_2,
  Alternate_Function_3,
  Alternate_Function_4,
  Alternate_Function_5,
  Alternate_Function_6,
  Alternate_Function_7,
  Alternate_Function_8,
  Alternate_Function_9,
  Alternate_Function_10,
  Alternate_Function_11,
  Alternate_Function_12,
  Alternate_Function_13,
  Alternate_Function_14,
  Alternate_Function_15 
} GPIO_Alternate_Function;

typedef struct GPIO_Configuration
{
  GPIO_Pin Pin;
  GPIO_Mode Mode;
  GPIO_Output_Mode Output_Mode;
  GPIO_Output_Speed Output_Speed;
  GPIO_Output_Pull Pull;
  GPIO_Alternate_Function Alternate_Function;
} GPIO_Config; 

typedef enum GPIO_Status_Conditions
{
  GPIO_OK = 0,
  GPIO_ERROR_CLOCK_TIMEOUT = -1,
  GPIO_ERROR_INVALID_PORT = -2,
  GPIO_ERROR_INVALID_CONFIG = -3,
  GPIO_ERROR_INVALID_PIN = -4,
  GPIO_ERROR_INVALID_WRITE_VALUE = -5
} GPIO_Status;

int GPIO_Init(GPIO_TypeDef* GPIO_Port, GPIO_Config* Configurations);

int GPIO_Read(GPIO_TypeDef* GPIO_Port, Pin pin);

int GPIO_Write(GPIO_TypeDef* GPIO_Port, Pin pin, uint8_t value);

int GPIO_Set(GPIO_TypeDef* GPIO_Port, Pin pin);

int GPIO_Reset(GPIO_TypeDef* GPIO_Port, Pin pin);

int GPIO_Toggle(GPIO_TypeDef* GPIO_Port, Pin pin);
