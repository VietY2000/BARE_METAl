#include "button.h"

int button_read(GPIO_Typedef *PORT, uint8_t button_no){
    
    return ((PORT->IDR >> button_no) & 0x1);
}