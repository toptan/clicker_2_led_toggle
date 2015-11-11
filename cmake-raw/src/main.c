#include <main.h>
#include <stm32f407xx.h>


int main(void) {
    init_peripherals();
    LED_On(LED1);
    LED_Off(LED2);
    while (1) {
        for (int i = 0; i < 1000000; i++);
        LED_Toggle(LED1);
        LED_Toggle(LED2);
    }
}

void init_peripherals() {
    LED_Init(LED1);
    LED_Init(LED2);
}

void LED_Init(Led_TypeDef led) {
    /* Enable clock */
    LEDx_GPIO_CLK_ENABLE(led);
    /* Set pin as output */
    LED_PORT[led]->MODER |= (1 << (LED_PIN[led] << 1));
    /* Configure pin for maximum speed */
    LED_PORT[led]->OSPEEDR |= (3 << (LED_PIN[led] << 1));
}

void LED_On(Led_TypeDef led) {
    LED_PORT[led]->BSRR |= (1 << LED_PIN[led]);
}

void LED_Off(Led_TypeDef led) {
    LED_PORT[led]->BSRR &= ~(1 << LED_PIN[led]);
}

void LED_Toggle(Led_TypeDef led) {
    LED_PORT[led]->ODR ^= (1 << LED_PIN[led]);
}

void _init() { }


