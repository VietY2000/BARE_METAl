#ifndef __LED_H__
#define __LED_H__
#include <stdint.h>

#include "register.h"
void delay_ms(uint32_t time);
void led_on(GPIO_Typedef *PORT, uint8_t led_no);
void led_off(GPIO_Typedef *PORT, uint8_t led_no);

#endif /* __LED_H__ */