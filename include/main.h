#ifndef _MAIN_H_
#define _MAIN_H_

typedef enum {
    LED1 = 0,
    LED2 = 1
} Led_TypeDef;

typedef enum {
    BUTTON1 = 0,
    BUTTON2 = 1
} Button_TypeDef;

void led_on(Led_TypeDef Led);
void led_off(Led_TypeDef Led);
void led_toggle(Led_TypeDef Led);

#endif /* _MAIN_H_ */
