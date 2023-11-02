#include "led.h"
extern uint32_t *pRCC_AHB1ENR;
extern uint32_t *pGPIODModeReg;

extern uint32_t *pGPIODDataReg;
int main(void){
    /* enable clock RCC_AHB1ENR */

    *pRCC_AHB1ENR |= (1 << 3);
    delay_ms(100);
    /* cấu hình cho chân GPIOD là output */
    *pGPIODModeReg |= (1 << 30);
    delay_ms(100);
    /*tắt led*/
    led_off(15);


    while(1){
        led_on(15);
        delay_ms(1000);
        led_off(15);
        delay_ms(1000);
    }
    return 0;
}