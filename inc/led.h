#ifndef __LED_H__
#define __LED_H__
#include <stdint.h>

void delay_ms(uint32_t time);
void led_on(uint8_t led_no);
void led_off(uint8_t led_no);

#endif /* __LED_H__ */