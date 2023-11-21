#include "led.h"
#include "button.h"
#include "register.h"

#define LED_NO 15
#define BUTTON_NO 0
#define IRQ_EXTI0_NO 6

int main(void){
    
    RCC_Typedef *rcc = RCC;    
    rcc->AHB1ENR |= (1 << 3);
    rcc->AHB1ENR |= (1 << 0);
    GPIO_Typedef *LED_PORT = GPIOD;
    LED_PORT->MODER |= (1 << 30);

    GPIO_Typedef *BUTTON_PORT = GPIOA;
    BUTTON_PORT->MODER |= (0 << 0);
    BUTTON_PORT->PUPDR |= (2 << 0);

    led_on(LED_PORT, LED_NO);
    delay_ms(500);
    led_off(LED_PORT, LED_NO);

    while(1){   
        if(button_read(BUTTON_PORT,BUTTON_NO) == 1){
            led_on(LED_PORT, LED_NO);
        }
        else{
            led_off(LED_PORT, LED_NO);
        }
    }
    return 0;
}