/*
 * File:   buzzer.c
 * Author: kenneth.
 *
 * Created on July 17, 2025, 1:36 AM
 */


#include <xc.h>
#include "config.h"   

#define C6HALF_PERIOD 379
#define D6HALF_PERIOD 426 

unsigned int tmr1_TotalReqCount;
unsigned int tmr1_RunCount;
unsigned int tmr2_TotalReqCount;
unsigned int tmr2_RunCount;
unsigned int tmr3_TotalReqCount;
unsigned int tmr3_RunCount;
unsigned int tmr4_TotalReqCount;
unsigned int tmr4_RunCount;
unsigned int tmr5_TotalReqCount;
unsigned int tmr5_RunCount;
void tmr1_StartTone(void);
void tmr2_StartTone(void);
void tmr3_StartTone(void);
void tmr4_StartTone(void); // 2000
void tmr5_StartTone(void);

void buzzTone(void) {
    tmr1_StartTone();
    tmr2_StartTone();   
    tmr3_StartTone();
    tmr4_StartTone();
    tmr5_StartTone();
}
void tmr1_StartTone(void) {
    unsigned int preload_value;
    preload_value = (65536 - C6HALF_PERIOD);
    TMR1H = (unsigned char)(preload_value >> 8);
    TMR1L = (unsigned char)preload_value;
    tmr1_TotalReqCount = 1319; // 1000 , 2000
    tmr1_RunCount = 0;
    T1CONbits.TMR1ON = 1;
}
void tmr2_StartTone(void) {
    unsigned int preload_value;
    preload_value = (65536 - D6HALF_PERIOD);
    TMR1H = (unsigned char)(preload_value >> 8);
    TMR1L = (unsigned char)preload_value;
    tmr2_TotalReqCount = 1175; // 1100, 1600
    tmr2_RunCount = 0;
    T1CONbits.TMR1ON = 1;
}
void tmr3_StartTone(void) {
    unsigned int preload_value;
    preload_value = (65536 - C6HALF_PERIOD);
    TMR1H = (unsigned char)(preload_value >> 8);
    TMR1L = (unsigned char)preload_value;
    tmr3_TotalReqCount = 1319; //  1319, 800
    tmr3_RunCount = 0;
    T1CONbits.TMR1ON = 1;
}
void tmr4_StartTone(void) {
    unsigned int preload_value;
    preload_value = (65536 - D6HALF_PERIOD);
    TMR1H = (unsigned char)(preload_value >> 8);
    TMR1L = (unsigned char)preload_value;
    tmr4_TotalReqCount = 1175; //  1319, 800
    tmr4_RunCount = 0;
    T1CONbits.TMR1ON = 1;
}
void tmr5_StartTone(void) {
    unsigned int preload_value;
    preload_value = (65536 - C6HALF_PERIOD);
    TMR1H = (unsigned char)(preload_value >> 8);
    TMR1L = (unsigned char)preload_value;
    tmr5_TotalReqCount = 1319; //  1319, 800
    tmr5_RunCount = 0;
    T1CONbits.TMR1ON = 1;
}