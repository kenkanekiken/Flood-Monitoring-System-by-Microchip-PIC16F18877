/*
 * File:   isr.c
 * Author: kenneth.
 *
 * Created on July 17, 2025, 1:40 AM
 */


#include <xc.h>
#include "config.h"

#define SPKR PORTBbits.RB4

//Do re mi
//#define C6HALF_PERIOD 478
//#define D6HALF_PERIOD 426
//#define E6HALF_PERIOD 379

#define C6HALF_PERIOD 379
#define D6HALF_PERIOD 426

//#define E6HALF_PERIOD 714
//#define F6HALF_PERIOD 1667
//#define G6HALF_PERIOD 500

void dspTask_TimerLed(void);
void dspTask_TimerLcd(void);
void dspTask_TimerDanger(void);
void resetGate(void);
void dspTask_TimerMoist(void);

extern unsigned int tmr1_TotalReqCount; // extern to use timer1 variables
extern unsigned int tmr1_RunCount;
extern unsigned int tmr2_TotalReqCount;
extern unsigned int tmr2_RunCount;
extern unsigned int tmr3_TotalReqCount;
extern unsigned int tmr3_RunCount;
extern unsigned int tmr4_TotalReqCount;
extern unsigned int tmr4_RunCount;
extern unsigned int tmr5_TotalReqCount;
extern unsigned int tmr5_RunCount;
extern unsigned int tmr6_TotalReqCount;
extern unsigned int tmr6_RunCount;
extern unsigned int tmr7_TotalReqCount;
extern unsigned int tmr7_RunCount;
extern unsigned int tmr8_TotalReqCount;
extern unsigned int tmr8_RunCount;
extern unsigned int motorCount = 0;
unsigned int preload_value;
volatile uint8_t SleepDevice = 0; 

void __interrupt() isr(void) {
    // Timer 0 interrupt
    if (PIR0bits.TMR0IF == 1) {
        PIR0bits.TMR0IF = 0;
        dspTask_TimerLed();
        dspTask_TimerLcd();
        dspTask_TimerDanger();
        TMR0H = 0x48; // 3 second NPre 64
        TMR0L = 0xE5; // 3 second NPre 64
    }
    // Timer 1 interrupt
    if (PIR4bits.TMR1IF == 1) {
        PIR4bits.TMR1IF = 0;
        if (tmr1_RunCount < tmr1_TotalReqCount) {
            SPKR = ~SPKR;
            tmr1_RunCount++;
            preload_value = (65536 - C6HALF_PERIOD);
            TMR1H = (unsigned char)(preload_value >> 8);
            TMR1L = (unsigned char)preload_value;
        } else if (tmr2_RunCount < tmr2_TotalReqCount) {
            SPKR = ~SPKR;
            tmr2_RunCount++;
            preload_value = (65536 - D6HALF_PERIOD);
            TMR1H = (unsigned char)(preload_value >> 8);
            TMR1L = (unsigned char)preload_value;
        } else if (tmr3_RunCount < tmr3_TotalReqCount) {
            SPKR = ~SPKR;
            tmr3_RunCount++;
            preload_value = (65536 - C6HALF_PERIOD);
            TMR1H = (unsigned char)(preload_value >> 8);
            TMR1L = (unsigned char)preload_value;
        } else if (tmr4_RunCount < tmr4_TotalReqCount) {
            SPKR = ~SPKR;
            tmr4_RunCount++;
            preload_value = (65536 - D6HALF_PERIOD);
            TMR1H = (unsigned char)(preload_value >> 8);
            TMR1L = (unsigned char)preload_value;
        } else if (tmr5_RunCount < tmr5_TotalReqCount) {
            SPKR = ~SPKR;
            tmr5_RunCount++;
            preload_value = (65536 - C6HALF_PERIOD);
            TMR1H = (unsigned char)(preload_value >> 8);
            TMR1L = (unsigned char)preload_value;
        } else {
            T1CONbits.TMR1ON = 0;
        }
    }
    // Timer 3 interrupt
    if (PIR4bits.TMR3IF) {
        PIR4bits.TMR3IF = 0;
        dspTask_TimerMoist();
    }
    // Interrupt On Change DC MOTOR
    if (IOCBFbits.IOCBF0 == 1) {
        resetGate();
        IOCBFbits.IOCBF0 = 0;  
        PIR0bits.IOCIF = 0;
    }
    // Interrupt On Change LPM
    if (IOCBFbits.IOCBF2 == 1) {
        IOCBFbits.IOCBF2= 0;
        SleepDevice = 1;
        PIR0bits.IOCIF = 0;
 
    }
}
