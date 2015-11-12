#ifndef __DEFINES_H_
#define __DEFINES_H_

#define LED1_Pin       GPIO_PIN_12
#define LED1_GPIO_Port GPIOE
#define LED2_Pin       GPIO_PIN_15
#define LED2_GPIO_Port GPIOE
#define BTN2_Pin       GPIO_PIN_10
#define BTN2_GPIO_Port GPIOA
#define BTN1_Pin       GPIO_PIN_0
#define BTN1_GPIO_Port GPIOE

/* Number of buttons we want to debounce */
#define MAX_BUTTONS    2

/* Number of samples for which the button has to be in pressed state to be considered as pressed */
#define MAJORITY_VOTE  5

/* The number of final samples after we which we consider that the input is stable */
#define STABILITY_BITS 2

/* Converting stability bits to a bit mask */
#define STABILITY_MASK ((1<<STABILITY_BITS) - 1)


#endif /* __DEFINES_H_ */
