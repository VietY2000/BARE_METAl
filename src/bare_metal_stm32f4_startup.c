
#include <stdint.h>


#define SRAM_START  (0x20000000U)
#define SRAM_SIZE   (128U * 1024U)
#define STACK_START ((SRAM_START) + (SRAM_SIZE))
/* linker variable */

extern uint32_t _etext;
extern uint32_t _data;
extern uint32_t _edata;

extern uint32_t _bss;
extern uint32_t _ebss;

int main(void);

/* system interrupt */
void default_handler(void);
void reset_handler(void);


/* vector table xem trong reference manual */
uint32_t isr_vector[] __attribute__((section(".isr_vector"))) = {
    STACK_START,                        // con trỏ ngăn xếp ban đầu
    (uint32_t)reset_handler,                      // con trỏ hàm reset
    (uint32_t)default_handler,                    // The NMI handler
    (uint32_t)default_handler,                    // The HardFault handler
    (uint32_t)default_handler,                    // The MemManager handler 
    (uint32_t)default_handler,                    // The BusFault handler
    (uint32_t)default_handler,                    // The UnsageFault handler 
    0,                                  // Reserved
    0,                                  // Reserved,
    0,                                  // Reserved,
    0,                                  // Reserved,
    (uint32_t)default_handler,                    // The SVCall handler
    (uint32_t)default_handler,                    // The Debug Moniter handler 
    0,                                  // Reserved
    (uint32_t)default_handler,                    // The PendSV handler
    (uint32_t)default_handler,                    // The Systick handler  
    (uint32_t)default_handler,                    // The WWDG handler
    (uint32_t)default_handler,                    // The EXTI16 / PVD handler 
    (uint32_t)default_handler,                    // The EXTI21 / TAMP_STAMP handler 
    (uint32_t)default_handler,                    // The EXTI22 / RTC_WKUP handler
    (uint32_t)default_handler,                    // The FLASH 
    (uint32_t)default_handler,                    // The RCC  
    (uint32_t)default_handler,                    // The EXTI0 

    (uint32_t)default_handler,                    // The EXTI1 
    (uint32_t)default_handler,                    // The EXTI2 
    (uint32_t)default_handler,                    // The EXTI3

    (uint32_t)default_handler,                    // The EXTI4
    (uint32_t)default_handler,                    // The DMA1 Stream 0
    (uint32_t)default_handler,                    // The DMA1 Stream 1
    (uint32_t)default_handler,                    // The DMA1 Stream 2
    (uint32_t)default_handler,                    // The DMA1 Stream 3
    (uint32_t)default_handler,                    // The DMA1 Stream 4
    (uint32_t)default_handler,                    // The DMA1 Stream 5
    (uint32_t)default_handler,                    // The DMA1 Stream 6
    (uint32_t)default_handler,                    // The ADC
    (uint32_t)default_handler,                    // The EXTI9_5
    (uint32_t)default_handler,                    // The TIM9
    (uint32_t)default_handler,                    // The TIM10
    (uint32_t)default_handler,                    // The TIM11 
    (uint32_t)default_handler,                    // The TIM1_CC
    (uint32_t)default_handler,                    // The TIM2
    (uint32_t)default_handler,                    // The TIM3
    (uint32_t)default_handler,                    // The TIM4
    (uint32_t)default_handler,                    // The I2C1 Event
    (uint32_t)default_handler,                    // The I2C1 Error
    (uint32_t)default_handler,                    // The I2C2 Event
    (uint32_t)default_handler,                    // The I2C2 Error
    (uint32_t)default_handler,                    // The SPI1
    (uint32_t)default_handler,                    // The SPI2
    (uint32_t)default_handler,                    // The USART1
    (uint32_t)default_handler,                    // The USART2
    (uint32_t)default_handler,                    // The EXTI15_10 
    (uint32_t)default_handler,                    // The RTC Alarms through EXTI line
    (uint32_t)default_handler,                    // The USB On-The-Go FS Wakeup through EXTI line
    (uint32_t)default_handler,                    // The DMA1 Stream 7
    (uint32_t)default_handler,                    // The SDIO
    (uint32_t)default_handler,                    // The TIM5
    (uint32_t)default_handler,                    // The SPI3
    (uint32_t)default_handler,                    // The DMA2 Stream 0 
    (uint32_t)default_handler,                    // The DMA2 Stream 1
    (uint32_t)default_handler,                    // The DMA2 Stream 2
    (uint32_t)default_handler,                    // The DMA2 Stream 3
    (uint32_t)default_handler,                    // The DMA2 Stream 4
    (uint32_t)default_handler,                    // The USB OTG_FS
    (uint32_t)default_handler,                    // The DMA2 Stream 5
    (uint32_t)default_handler,                    // The DMA2 Stream 6
    (uint32_t)default_handler,                    // The DMA2 Stream 7
    (uint32_t)default_handler,                    // The USART6
    (uint32_t)default_handler,                    // The I2C3 Event
    (uint32_t)default_handler,                    // The I2C3 Error 
    (uint32_t)default_handler,                    // The I2C3 Error 
    (uint32_t)default_handler,                    // The FPU
    (uint32_t)default_handler,                    // The SPI4
    (uint32_t)default_handler                     // The SPI5

};

void default_handler(){
   while(1);
}

void reset_handler(){

    volatile uint32_t *pSrc = &_etext;
    volatile uint32_t *pDest = &_data;



    /* copy init data from FLASH to SRAM */
    while (pDest < &_edata){
        *pDest++ = *pSrc++;
    }

    /* zero bss */
    for(pDest = &_bss; pDest < &_ebss; ++pDest){

        *pDest = 0UL;
    }
    main();
}