/*
 * File:   dspTask.c
 * Author: kenneth.
 *
 * Created on July 17, 2025, 1:44 AM
 */


#include <xc.h>
#include "config.h"

#define detectMotion PORTDbits.RD2

void lcdCtrl_SetPos(unsigned char row, unsigned char col);
void lcdDspAllData(char *msg);
void buzzTone(void);
void backward (void);
void forward (void);
void stop(void);
void dspTask_ForwardMotor(void);
void seg_DispAll(unsigned int result);
void dspTask_Led(void);
void dspTask_Lcd(void);
void dspTask_Danger(void);
unsigned int dspTask_Moist(void);

unsigned int moist;
unsigned char led_state = 0;
unsigned char lcd_state = 0;
unsigned char updateADC = 0;
unsigned char hour = 0, min = 0, sec = 0;
static uint8_t motorTimer = 0; 
static uint8_t motorTriggered = 0;
extern unsigned int motorCount = 0;
char det = 0;
char messageLow[] = "Water Lvl:Low  ";
char messageMed[] = "Water Lvl:Med  ";
char messageHigh[] = "Water Lvl:High  ";
char messageVHigh[] = "Water Lvl:VHigh ";
char messageDanger[] = "RETURN TO UNIT";
char messageBlank[] = "              ";


void dspTask_TimerMoist(void) {
    sec++;
    if (sec>59) {
        sec = 0;
        min++;
        if (min>59) {
            min = 0;
            hour++;
            if (hour>23) {
                hour = 0;
            }
        } 
    }
    // Upon every 2 seconds, set the updateADC flag to 1.
    if ((sec == 0) || (sec % 2 == 0)) {
        updateADC = 1; 
    }
}
void dspTask_OnSevSeg(void) {
    if (updateADC == 1) {
        moist = 1023 - dspTask_Moist();
        updateADC = 0; 
    }
    seg_DispAll(moist);
}
void dspTask_TimerLed(void) {
    if (moist <= 400) {
        led_state = 0;  
    } else if (moist <= 500) {
        led_state = 1;
    } else if (moist <= 600) {
        led_state = 2; 
        motorTriggered = 1;
        dspTask_ForwardMotor();
        buzzTone();
    } else {
        led_state = 3;
        motorTriggered = 1;
        dspTask_ForwardMotor();
        buzzTone();
    }
    dspTask_Led();
}
void dspTask_TimerLcd(void) {
    if (moist <= 400) {
        lcd_state = 0;
    } else if (moist <= 500) {
        lcd_state = 1;
    } else if (moist <= 600) {
        lcd_state = 2;
    } else {
        lcd_state = 3;
    }
    dspTask_Lcd();
}
void dspTask_TimerDanger(void) {
    if (detectMotion) {
        det = 1;
    }
    dspTask_Danger();
}
void dspTask_Lcd(void) {
    switch(lcd_state) {
        case 0:
            lcdCtrl_SetPos(1, 1);
            lcdDspAllData(messageLow);
            break;
        case 1: 
            lcdCtrl_SetPos(1, 1);
            lcdDspAllData(messageMed);
            break;
        case 2:
            lcdCtrl_SetPos(1, 1);
            lcdDspAllData(messageHigh);
            break;
        case 3:
            lcdCtrl_SetPos(1, 1);
            lcdDspAllData(messageVHigh);
            break;
    }
}
void dspTask_Led(void) {
    switch(led_state) {
        case 0:  // No LEDs
            PORTAbits.RA2 = 0;
            PORTAbits.RA3 = 0;
            break;
        case 1:  // RA2 on (medium moisture)
            PORTAbits.RA2 = 1;
            PORTAbits.RA3 = 0;
            break;
        case 2:  // RA3 on (high moisture)
            PORTAbits.RA2 = 0;
            PORTAbits.RA3 = 1;
            break;
        case 3:  // Both on (very high moisture)
            PORTAbits.RA2 = 1;
            PORTAbits.RA3 = 1;
            break;
    }
}
void dspTask_ForwardMotor(void) {
    if (motorCount == 0) {
        motorCount++;
        if (motorTriggered == 1 && motorTimer < 1) {
        forward();
        motorTimer++;
        } else if (motorTriggered == 1 && motorTimer >= 1) {
        stop();          
        motorTriggered = 0;
        motorTimer = 0;  
        }
    } else {
        stop();       
        motorTriggered = 0;
        motorTimer = 0;
    }
}
void dspTask_Danger(void) {
    if (det && moist >= 500) {
           lcdCtrl_SetPos(2, 1);
           lcdDspAllData(messageDanger);
           det = 0;
           __delay_ms(1000);
    } else {
           lcdCtrl_SetPos(2, 1);
           lcdDspAllData(messageBlank);
    }
} 
