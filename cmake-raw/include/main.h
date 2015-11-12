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
 * Number of buttons on the board.
 */
#define BTNn                             2

/**
 * Button 1 definitions.
 */
#define BTN1_PIN                         0
#define BTN1_GPIO_PORT                   GPIOE
#define BTN1_GPIO_CLK_ENABLE()           RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN
#define BTN1_GPIO_CLK_DISABLE()          RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOEEN)
#define BTN1_EXTI_IRQn                   EXTI0_IRQn
#define BTN1_EXTICR                      0
#define BTN1_EXTI_CONF                   SYSCFG_EXTICR1_EXTI0_PE
#define BTN1_INT_MASK                    EXTI_IMR_MR0

/**
 * Button 2 definitions.
 */
#define BTN2_PIN                         10
#define BTN2_GPIO_PORT                   GPIOA
#define BTN2_GPIO_CLK_ENABLE()           RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN
#define BTN2_GPIO_CLK_DISABLE()          RCC->AHB1ENR &= ~(RCC_AHB1ENR_GPIOAEN)
#define BTN2_EXTI_IRQn                   EXTI15_10_IRQn
#define BTN2_EXTICR                      2
#define BTN2_EXTI_CONF                   SYSCFG_EXTICR3_EXTI10_PA
#define BTN2_INT_MASK                    EXTI_IMR_MR10

/**
 * Button helper macros.
 */
#define BTNx_GPIO_CLK_ENABLE(__INDEX__)  do{if((__INDEX__) == 0) BTN1_GPIO_CLK_ENABLE(); \
                                                 if((__INDEX__) == 1) BTN2_GPIO_CLK_ENABLE(); \
                                                }while(0)

#define BTNx_GPIO_CLK_DISABLE(__INDEX__) do{if((__INDEX__) == 0) BTN1_GPIO_CLK_DISABLE(); \
                                                  if((__INDEX__) == 1) BTN2_GPIO_CLK_DISABLE(); \
                                                 }while(0)

/**
 * LED variables.
 */

/**
 * GPIO port.
 */
GPIO_TypeDef *LED_PORT[LEDn] = {LED1_GPIO_PORT,
                                LED2_GPIO_PORT};

/**
 * Pin.
 */
const uint16_t LED_PIN[LEDn] = {LED1_PIN,
                                LED2_PIN};

/**
 * Button variables.
 */

/**
 * GPIO port.
 */
GPIO_TypeDef *BTN_PORT[BTNn] = {BTN1_GPIO_PORT,
                                BTN2_GPIO_PORT};

/**
 * Pin.
 */
const uint16_t BTN_PIN[BTNn] = {BTN1_PIN,
                                BTN2_PIN};

/**
 * Interrupt.
 */
const uint16_t BTN_EXTI[BTNn] = {BTN1_EXTI_IRQn,
                                 BTN2_EXTI_IRQn};

/**
 * External interrupt configuration register.
 */
const uint16_t BTN_EXTICR[BTNn] = {BTN1_EXTICR,
                                   BTN2_EXTICR};

/**
 * External interrupt line configuration.
 */
const uint32_t BTN_EXTI_CONF[BTNn] = {BTN1_EXTI_CONF,
                                      BTN2_EXTI_CONF};

/**
 * Interrupt masks.
 */
const uint32_t BTN_INT_MASK[BTNn] = {BTN1_INT_MASK,
                                     BTN2_INT_MASK};

/**
 * LED functions.
 */
void LED_Init(Led_TypeDef led);

void LED_On(Led_TypeDef led);

void LED_Off(Led_TypeDef led);

void LED_Toggle(Led_TypeDef led);

/**
 * Button functions.
 */
void BTN_Init(Button_TypeDef button, ButtonMode_TypeDef mode);

/**
 * Reads the pin state of the given button.
 */
char read_the_button(Button_TypeDef button);

/**
 * This function will return debounced state of the button.
 */
char button_is_pressed(Button_TypeDef button);

#endif /* __MAIN_H_ */
