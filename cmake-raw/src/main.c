#include <main.h>

int main(void) {
    init_peripherals();
    while (1) {
    }
}

void init_peripherals() {
    /* Enable system clock */
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    LED_Init(LED1);
    LED_Init(LED2);
    BTN_Init(BTN1, BTN_MODE_EXTI);
    BTN_Init(BTN2, BTN_MODE_EXTI);
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

void BTN_Init(Button_TypeDef button, ButtonMode_TypeDef mode) {
    /* Enable clock */
    BTNx_GPIO_CLK_ENABLE(button);

    if (mode == BTN_MODE_GPIO) {
        /* Set pin as input */
        BTN_PORT[button]->MODER &= ~(1 << (BTN_PIN[button] << 1));
        /* Configure pin for low speed. */
        BTN_PORT[button]->OSPEEDR |= (0 << (BTN_PIN[button] << 1));
        /* Configure pin for no-pull */
        BTN_PORT[button]->PUPDR &= ~(3 << (BTN_PIN[button] << 1));
    }

    if (mode == BTN_MODE_EXTI) {
        /* Set pin as input */
        BTN_PORT[button]->MODER &= ~(1 << (BTN_PIN[button] << 1));
        /* Configure pin for low speed. */
        BTN_PORT[button]->OSPEEDR |= (0 << (BTN_PIN[button] << 1));
        /* Configure pin for no-pull */
        BTN_PORT[button]->PUPDR &= ~(3 << (BTN_PIN[button] << 1));
        /* Configure external lines */
        SYSCFG->EXTICR[BTN_EXTICR[button]] |= BTN_EXTI_CONF[button];
        /* Set interrupt to trigger on the rising and failing edge */
        EXTI->RTSR |= (EXTI_RTSR_TR0 << BTN_PIN[button]);
        EXTI->RTSR |= (EXTI_RTSR_TR0 << BTN_PIN[button]);
        /* Unmask corresponding interrupt */
        EXTI->IMR |= BTN_INT_MASK[button];
        /* Enable IRQs */
        __enable_irq();
        /* Set interrupt priority */
        uint32_t priority_group = 0x00;
        priority_group = NVIC_GetPriorityGrouping();
        NVIC_SetPriority(BTN_EXTI[button], NVIC_EncodePriority(priority_group, 2, 0));
        NVIC_EnableIRQ(BTN_EXTI[button]);
    }
}

void EXTI0_IRQHandler(void) {
    __disable_irq();
    EXTI->PR |= EXTI_PR_PR0;
    if (button_is_pressed(BTN1)) {
        LED_Toggle(LED2);
    }
    __enable_irq();
}

void EXTI15_10_IRQHandler(void) {
    __disable_irq();
    EXTI->PR |= EXTI_PR_PR10;
    if (button_is_pressed(BTN2)) {
        LED_Toggle(LED1);
    }
    __enable_irq();
}

char read_the_button(Button_TypeDef button) {
    return (BTN_PORT[button]->IDR & BTN_PIN[button]) == 0;
}

char button_is_pressed(Button_TypeDef button) {
    for (int i = 0; i < 200; i++);
    return read_the_button(button);
}

void _init() { }

