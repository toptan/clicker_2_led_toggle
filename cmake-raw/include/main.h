/**
 * Created by Toplica Tanasković on 11.11.2015.
 */
#ifndef __MAIN_H_
#define __MAIN_H_

#include <stm32f4xx.h>

typedef enum {
    LED1 = 0,
    LED2 = 1
} Led_TypeDef;

typedef enum {
    BTN1 = 0,
    BTN2 = 1
} Button_TypeDef;

typedef enum {
    BTN_MODE_GPIO = 0,
    BTN_MODE_EXTI = 1,
} ButtonMode_TypeDef;

/**
 * Function that initializes all peripherals.
 */
void init_peripherals();

/**
 * Number of LEDs on the board.
 */
#define LEDn                             2

/**
 * LED 1 definitions.
 */
#define LED1_PIN                         12
#define LED1_GPIO_PORT                   GPIOE
#define LED1_GPIO_CLK_ENABLE()           RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN
#define LED1_GPIO_CLK_DISABLE()          RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOEEN)

/**
 * LED 2 definitions.
 */
#define LED2_PIN                         15
#define LED2_GPIO_PORT                   GPIOE
#define LED2_GPIO_CLK_ENABLE()           RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN
#define LED2_GPIO_CLK_DISABLE()          RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOEEN)

/**
 * LED helper macros.
 */
#define LEDx_GPIO_CLK_ENABLE(__INDEX__)  do{if((__INDEX__) == 0) LED1_GPIO_CLK_ENABLE(); else \
                                           if((__INDEX__) == 1) LED2_GPIO_CLK_ENABLE(); \
                                           }while(0)

#define LEDx_GPIO_CLK_DISABLE(__INDEX__) do{if((__INDEX__) == 0) LED1_GPIO_CLK_DISABLE(); else \
                                            if((__INDEX__) == 1) LED2_GPIO_CLK_DISABLE(); \
                                            }while(0)

/**
 * LED variables
 */
GPIO_TypeDef *LED_PORT[LEDn] = {LED1_GPIO_PORT,
                                LED2_GPIO_PORT};

const uint16_t LED_PIN[LEDn] = {LED1_PIN,
                                LED2_PIN};

/**
 * LED functions.
 */
void LED_Init(Led_TypeDef led);
void LED_On(Led_TypeDef led);
void LED_Off(Led_TypeDef led);
void LED_Toggle(Led_TypeDef led);

#endif /* __MAIN_H_ */
