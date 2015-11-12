#ifndef __MAIN_H_
#define __MAIN_H_
#include <stm32f4xx_hal.h>

typedef enum {
    LED1 = 0,
    LED2 = 1
} Led_TypeDef;

typedef enum {
    BUTTON1 = 0,
    BUTTON2 = 1
} Button_TypeDef;


/* Debounced statuses of all buttons at any time */
volatile unsigned int debounced_buttons;

/* Reads the pin state of the given button. */
GPIO_PinState read_the_button(Button_TypeDef button);

/* This function will return debounced state of the button. The algorithm is The Majority Vote. */
char button_is_pressed(Button_TypeDef button);

void led_on(Led_TypeDef Led);
void led_off(Led_TypeDef Led);
void led_toggle(Led_TypeDef Led);

#endif /* __MAIN_H_ */
