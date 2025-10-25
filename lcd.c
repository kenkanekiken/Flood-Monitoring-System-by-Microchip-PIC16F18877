/*
 * File:   lcd.c
 * Author: kenneth.
 *
 * Created on July 17, 2025, 1:38 AM
 */


#include <xc.h>
#include "config.h"

#define LCD_DATA_D7 PORTDbits.RD7
#define LCD_DATA_D6 PORTDbits.RD6
#define LCD_DATA_D5 PORTDbits.RD5
#define LCD_DATA_D4 PORTDbits.RD4
#define LCD_RS PORTEbits.RE1
#define LCD_E PORTEbits.RE0

void lcdWriteCtrlWord(char x);
void lcdWriteDspData(char x);
void lcdWriteNibble(char nibble);
void lcdCtrl_SetPos(unsigned char row, unsigned char col);
void lcdCtrl_FunctionSet(void);
void lcdCtrl_OnOffDisplay(char display_state, char cursor_state);
void lcdCtrl_SetEntryMode(void);
void lcdCtrl_ClearDisplay(void);
void lcdDspAllData(char *msg);


void initLCD() {
    __delay_ms(15);
    lcdWriteCtrlWord(0b00000011); // Set (DB4 - DB7: 8 bit interface)
    __delay_ms(5);
    lcdWriteCtrlWord(0b00000010); // Set (DB4 - DB7: 4 bit interface)
    
    lcdCtrl_FunctionSet(); // Set (4-bit, 2 line, 5x7)
    lcdCtrl_OnOffDisplay(1,0); // Display on, Cursor off
    lcdCtrl_SetEntryMode();
    lcdCtrl_ClearDisplay();
}

void lcdWriteCtrlWord(char x) { // Control for LCD 
    char upper_nibble, lower_nibble;
    
    upper_nibble = (x & 0b11110000) >> 4;
    lower_nibble = x & 0b00001111;
    
    LCD_RS = 0;
    lcdWriteNibble(upper_nibble);
    lcdWriteNibble(lower_nibble);
}
void lcdWriteDspData(char x) { // Display Text on LCD
    char upper_nibble, lower_nibble;
    
    upper_nibble = (x & 0b11110000) >> 4;
    lower_nibble = x & 0b00001111;
    
    LCD_RS = 1;
    lcdWriteNibble(upper_nibble);
    lcdWriteNibble(lower_nibble);
}
void lcdDspAllData(char *msg) { 
    while (*msg) { 
        lcdWriteDspData(*msg);
        msg++;
    }
}
void lcdWriteNibble(char nibble) {
    LCD_DATA_D7 = (nibble & 0b00001000) >> 3;
    LCD_DATA_D6 = (nibble & 0b00000100) >> 2;
    LCD_DATA_D5 = (nibble & 0b00000010) >> 1;
    LCD_DATA_D4 = (nibble & 0b00000001);
    
    LCD_E = 1;
    __delay_ms(1);
    LCD_E = 0;
    __delay_ms(1);
}
void lcdCtrl_SetPos(unsigned char row, unsigned char col) {
    // row values are 1 to 2
    // col values are 1 to 16
    unsigned char ramAddr;
    if (row == 1) {
        ramAddr = col - 1;
    } else {
        ramAddr = 0x40 + col - 1;
    }
    lcdWriteCtrlWord(0x80 + ramAddr);
}
void lcdCtrl_FunctionSet(void) {
    lcdWriteCtrlWord(0b00101000);
}
void lcdCtrl_OnOffDisplay(char display_state, char cursor_state) {
    char pattern = 0b00001000;
    
    if (display_state == 1) {
        pattern |= 0b00000100;
    } else if (cursor_state == 1) {
        pattern |= 0b00000011;
    }
    lcdWriteCtrlWord(pattern);
}
void lcdCtrl_SetEntryMode(void) {
    lcdWriteCtrlWord(0b00000110);
}
void lcdCtrl_ClearDisplay(void) {
    lcdWriteCtrlWord(0b00000001); // Clear display & home position
}
