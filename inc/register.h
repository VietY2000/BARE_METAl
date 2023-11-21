#ifndef __REGISTER_H__
#define __REGISTER_H__
#include <stdint.h>

#define RCC_BASE        ((uint32_t*)0x40023800)
#define GPIOA_BASE      ((uint32_t*)0x40020000)
#define GPIOD_BASE      ((uint32_t*)0x40020C00)
#define EXTI_BASE       ((uint32_t*)0x40013C00)

typedef struct{
    uint32_t MODER;
    uint32_t OTYPER;
    uint32_t OSPEEDR;
    uint32_t PUPDR;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t LCKR;
    uint32_t AFRL;
    uint32_t AFRH;
} GPIO_Typedef;

typedef struct{
    uint32_t CR;
    uint32_t PLLCFGR;
    uint32_t CFGR;
    uint32_t CIR;
    uint32_t AHB1RSTR;
    uint32_t AHB2RSTR;
    uint32_t RESERVED0[2];
    uint32_t APB1RSTR;
    uint32_t APB2RSTR;
    uint32_t RESERVED1[2];
    uint32_t AHB1ENR;
    uint32_t AHB2ENR;
    uint32_t RESERVED2[2];
    uint32_t APB1ENR;
    uint32_t APB2ENR;
    uint32_t RESERVED3[2];
    uint32_t AHB1LPENR;
    uint32_t AHB2LPENR;
    uint32_t RESERVED4[2];
    uint32_t APB1LPENR;
    uint32_t APB2LPENR;
    uint32_t RESERVED5[2];
    uint32_t BDCR;
    uint32_t CSR;

    uint32_t RESERVED6[2];
    uint32_t SSCGR;
    uint32_t PLLI2SCFGR;

    uint32_t RESERVED7;
    uint32_t DCKCFGR;
} RCC_Typedef;

typedef struct{
    uint32_t IMR;
    uint32_t EMR;
    uint32_t RTSR;
    uint32_t FTSR;
    uint32_t SWIER;
    uint32_t PR;
} EXTI_Typedef;

#define GPIOA   ((GPIO_Typedef*)GPIOA_BASE)
#define GPIOD   ((GPIO_Typedef*)GPIOD_BASE)
#define RCC     ((RCC_Typedef*)RCC_BASE)
#define EXTI    ((EXTI_Typedef*)EXTI_BASE)

#endif /* __REGISTER_H__ */