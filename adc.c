/*
 * File:   adc.c
 * Author: kenneth.
 *
 * Created on July 17, 2025, 1:46 AM
 */


#include <xc.h>
#include "config.h"

void initSysADC(void) {
    ADREF = 0b00000000;
    ADCLK = 0b00000011;
    ADACQ = 0b00000000;
    ADCON0 = 0b10000100;
}

unsigned int dspTask_Moist(void) {
    unsigned int result;
    ADPCH = 0b00000000;
    __delay_us(2);
    ADCON0bits.ADGO = 1;
    while (ADCON0bits.ADGO == 1);
    result = (ADRESH * 256) + ADRESL; 
    return result;
}