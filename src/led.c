#include "led.h"

void delay_ms(uint32_t time){
    
    time = time*1250U;
    while(time){
        time--;
    }
}

void led_on(GPIO_Typedef *PORT, uint8_t led_no){
    PORT->ODR |= (1 << led_no);

}

void led_off(GPIO_Typedef *PORT, uint8_t led_no){
    PORT->ODR &= ~(1 << led_no);
}