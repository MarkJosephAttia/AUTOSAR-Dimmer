#ifndef STD_TYPES_H
#define STD_TYPES_H

#define NULL                            ((void*)0)

typedef unsigned char                   u8;
typedef unsigned char                   uint8_t;
typedef signed char                     s8;
typedef signed char                     sint8_t;
typedef unsigned       int              u16;
typedef unsigned       int              uint16_t;
typedef signed short int                s16;
typedef signed short int                sint16_t;
typedef unsigned long int               u32;
typedef unsigned long int               uint32_t;
typedef signed long int                 s32;
typedef signed long int                 sint32_t;
typedef unsigned long long int          u64;
typedef unsigned long long int          uint64_t;
typedef signed long long int            s64;
typedef signed long long int            sint64_t;

typedef float                           f32;
typedef double                          f64;

typedef void (*callback_t)(void);

typedef uint8_t Std_ReturnType;

#define DELAY_US(tmp)    do{                            \
            asm volatile("mov r5, %0" :"r+" (tmp));     \
            asm("mov r4, #0");                          \
            asm("newlabel:");                           \
            asm("nop");                                 \
            asm("nop");                                 \
            asm("nop");                                 \
            asm("nop");                                 \
            asm("nop");                                 \
            asm("adds r4, #1");                         \
            asm("cmp r4, r5");                          \
            asm("bne newlabel");                        \
}while(0);

#define E_OK                            (0)
#define E_NOT_OK                        (1)

#define STD_LOW                         (0)
#define STD_HIGH                        (1)

#define STD_IDLE                        (0)
#define STD_ACTIVE                      (1)

#define STD_OFF                         (0)
#define STD_ON                          (1)

#endif