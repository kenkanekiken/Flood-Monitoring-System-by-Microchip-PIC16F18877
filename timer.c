/*
 * File:   timer.c
 * Author: kenneth.
 *
 * Created on July 17, 2025, 1:35 AM
 */


#include <xc.h>
#include "config.h"

void initSysTimer0(void) {
    INTCONbits.GIE = 0;
    T0CON0 = 0b10010000;
    T0CON1 = 0b01000110;
    TMR0H = 0x48; 
    TMR0L = 0xE5;
    PIR0bits.TMR0IF = 0;
    PIE0bits.TMR0IE = 1;
    INTCONbits.GIE = 1;
}
void initSysTimer1(void) {
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 1;
    T1CON = 0b00000010;
    T1CLK = 0b00000001;
    PIE4bits.TMR1IE = 1;
    PIR4bits.TMR1IF = 0;
    INTCONbits.GIE = 1;
}
void initSysTimer3(void) {
    INTCONbits.GIE = 0;
    T3CON = 0b00000010;       
    T3CLK = 0b00000001;      
    TMR3H = 0x0B;
    TMR3L = 0xDC;
    PIR4bits.TMR3IF = 0;
    PIE4bits.TMR3IE = 1;
    T3CONbits.TMR3ON = 1;     
    INTCONbits.GIE = 1;
}
