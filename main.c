/*
 * File:   main.c
 * Author: kenneth.
 *
 * Created on July 17, 2025, 1:34 AM
 */


#include <xc.h>
#include "config.h"

void initSysPins(void);
void initSysTimer0(void);
void initSysTimer1(void);
void initSysADC(void);
void initLCD(void);
void initMasterReset();
void initSysPWM();
void initIOCForSleep(void);
void dspTask_OnSevSeg(void);
void initSysTimer3(void);
void lcdCtrl_SetPos(unsigned char row, unsigned char col);
void lcdDspAllData(char *msg);

extern unsigned int moist;
extern volatile uint8_t SleepDevice; 

void main(void) {
    initSysPins();
    initSysADC();
    initLCD();
    initMasterReset();
    initSysPWM();
    initSysTimer0();
    initSysTimer1();
    initSysTimer3();
    initIOCForSleep();
    PWM6CONbits.EN = 1;
   
    char messageClear[] = "                 ";
    while(1) {
        dspTask_OnSevSeg();      
        if (SleepDevice == 1) {
            CPUDOZEbits.IDLEN = 0; 
            lcdCtrl_SetPos(1, 1);
            lcdDspAllData(messageClear);
            SLEEP();
            NOP();
        } 
        SleepDevice = 0;
    }
}

void initSysPins(void) {
    ANSELA = 0b00000001;
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;
    ANSELE = 0;
    TRISA = 0b11000011;
    TRISB = 0b11101111;
    TRISC = 0b10000000;
    TRISD = 0b00000100;
    TRISE = 0b11111100;
}
