
#include "led.h"


/* thanh ghi clock các ngoại vi gpio */
uint32_t *pRCC_AHB1ENR = (uint32_t*)0x40023830;

/* thanh ghi cấu hình chân GPIOD */
uint32_t *pGPIODModeReg = (uint32_t*)0x40020C00;

/* thanh ghi data chân GPIOD */
uint32_t *pGPIODDataReg = (uint32_t*)0x40020C14;

void delay_ms(uint32_t time){
    
    time = time*1250U;
    while(time){
        time--;
    }
}

void led_on(uint8_t led_no){
    *pGPIODDataReg |= (1 << led_no);

}

void led_off(uint8_t led_no){
    *pGPIODDataReg &= ~(1 << led_no);
}