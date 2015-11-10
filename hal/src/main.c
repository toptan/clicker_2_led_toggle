#include "main.h"

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

void _init() {
}

int main(void) {
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();
    /* Configure the system clock */
    SystemClock_Config();
    /* Initialize all configured peripherals */
    MX_GPIO_Init();

//    led_on(LED2);
    while (1) {
//        HAL_Delay(500);
        //      led_toggle(LED1);
        //      led_toggle(LED2);
    }
}

/*
 * System Clock Configuration
 */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct;
    __PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = 16;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
    /* GPIO Ports Clock Enable */
    __GPIOE_CLK_ENABLE();
    __GPIOA_CLK_ENABLE();
    /*Configure GPIO pins : LED1_Pin LED2_Pin */
    GPIO_InitStruct.Pin = LED1_Pin | LED2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    /*Configure GPIO pin : BTN2_Pin */
    GPIO_InitStruct.Pin = BTN2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(BTN2_GPIO_Port, &GPIO_InitStruct);
    /*Configure GPIO pin : BTN1_Pin */
    GPIO_InitStruct.Pin = BTN1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(BTN1_GPIO_Port, &GPIO_InitStruct);
    HAL_NVIC_SetPriority(EXTI0_IRQn, 2, 0);
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void led_on(Led_TypeDef Led) {
    HAL_GPIO_WritePin(GPIOE, (Led == LED1 ? LED1_Pin : LED2_Pin), GPIO_PIN_SET);
}

void led_off(Led_TypeDef Led) {
    HAL_GPIO_WritePin(GPIOE, (Led == LED1 ? LED1_Pin : LED2_Pin), GPIO_PIN_RESET);
}

void led_toggle(Led_TypeDef Led) {
    HAL_GPIO_TogglePin(GPIOE, (Led == LED1 ? LED1_Pin : LED2_Pin));
}

void EXTI0_IRQHandler(void) {
    /*if (__HAL_GPIO_EXTI_GET_FLAG(BTN1_Pin) != RESET) {*/
    /*if (HAL_GPIO_ReadPin(GPIOE, BTN1_Pin)) {*/
    /*HAL_GPIO_EXTI_IRQHandler(BTN1_Pin);*/
    /*}*/
    /*}*/
    if (button_is_pressed(BUTTON1)) {
        HAL_GPIO_EXTI_IRQHandler(BTN1_Pin);
    }
}

void EXTI15_10_IRQHandler(void) {
    /*if (__HAL_GPIO_EXTI_GET_FLAG(BTN2_Pin) != RESET) {*/
    /*if (HAL_GPIO_ReadPin(GPIOA, BTN2_Pin)) {*/
    /*HAL_GPIO_EXTI_IRQHandler(BTN2_Pin);*/
    /*}*/
    /*}*/
    if (button_is_pressed(BUTTON2)) {
        HAL_GPIO_EXTI_IRQHandler(BTN2_Pin);
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == BTN1_Pin) {
        led_toggle(LED2);
    } else if (GPIO_Pin == BTN2_Pin) {
        led_toggle(LED1);
    } else {
        led_on(LED1);
        led_on(LED2);
    }
}

GPIO_PinState read_the_button(Button_TypeDef button) {
    if (button == BUTTON1) {
        return HAL_GPIO_ReadPin(GPIOE, BTN1_Pin);
    } else if (button == BUTTON2) {
        return HAL_GPIO_ReadPin(GPIOA, BTN2_Pin);
    } else {
        return GPIO_PIN_RESET;
    }
}

char button_is_pressed(Button_TypeDef button) {
    unsigned int temp;
    /* button_bits[] is an array to hold the previous states of the port pin value
     * Each element holds the previous samples of teh button read.
     * We need as many elements as there are buttons.
     * Make this an integer array if more than 8 samples are needed for debounce determination.
     * if less samples are needed adjust the MAJORITY_VOTE and STABILITY_BITS to a smaller number
     */
    volatile static unsigned char button_bits[MAX_BUTTONS];
    /* Shift the latest read button status into the que
     * we should have the latest sample in LSB and older samples
     * higher up.
     */
    button_bits[button] = button_bits[button] << 1 | (read_the_button(button) & 0x01);
    temp = button_bits[button];

    /* Check if the input is stable in the last STABILITY_BITS samples */
    if ((temp & STABILITY_MASK) == STABILITY_MASK) {
        unsigned int bit_count = 0;

        /* Count the number of bits set in temp, we need more than the majority
         * straight out of the book of K&R, check it :-)*/
        while ((temp = (temp & (temp - 1)))) {
            bit_count++;
        }

        bit_count++; // we are off by one

        /*Check if the required number of samples were favourable */
        if (bit_count >= MAJORITY_VOTE) {
            button_bits[button] = 0;
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}
