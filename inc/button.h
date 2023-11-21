#ifndef __BUTTON_H__
#define __BUTTON_H__
#include <stdint.h>

#include "register.h"

int button_read(GPIO_Typedef *PORT, uint8_t button_no);
#endif /* __BUTTON_H__ */