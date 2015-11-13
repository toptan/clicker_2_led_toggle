#include <main.h>

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

    while (1) {
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
    /* No need to disable interrupts here as HAL does that for us. */
    if (button_is_pressed(BUTTON1)) {
        HAL_GPIO_EXTI_IRQHandler(BTN1_Pin);
    }
}

void EXTI15_10_IRQHandler(void) {
    /* No need to disable interrupts here as HAL does that for us. */
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
    HAL_Delay(200);
    return read_the_button(button);
}
