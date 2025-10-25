/*
 * File:   ioc.c
 * Author: kenneth.
 *
 * Created on July 17, 2025, 1:44 AM
 */


#include <xc.h>
#include "config.h"

void initMasterReset(void) {
    INTCONbits.GIE = 0;        // Disable global interrupts during config
    IOCBFbits.IOCBF0 = 0;      // Clear IOC flag for RB0
    IOCBPbits.IOCBP0 = 1;      // Enable rising edge trigger on RB0
    PIE0bits.IOCIE = 1;        // Enable IOC interrupt
    PIR0bits.IOCIF = 0;        // Clear IOC interrupt flag
    INTCONbits.GIE = 1;        // Enable global interrupts
}
void initIOCForSleep(void) {
    INTCONbits.GIE = 0;
    PIR0bits.IOCIF = 0;
    IOCBNbits.IOCBN2 = 1;    // RB3 negative edge interrupt
    IOCBPbits.IOCBP2 = 1;    // Disable positive edge (or set to 1 if you want both)
    PIE0bits.IOCIE = 1;
    INTCONbits.GIE = 1;
}
