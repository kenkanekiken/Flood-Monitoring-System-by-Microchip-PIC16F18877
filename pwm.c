/*
 * File:   pwm.c
 * Author: kenneth.
 *
 * Created on July 17, 2025, 1:38 AM
 */


#include <xc.h>
#include "config.h"

extern unsigned int motorCount = 0;

void initSysPWM(void)
{
    CCPTMRS1 	= 0b00000100; // Select Timer2 as base timer for PWM6
    PWM6CON 	= 0b00000000; // Disable PWM first, set PWM to active high
    T2PR 		= 0x7C;         // Set the period with T2 period register
    PWM6DCH 	= 0b00000110; // Set the duty cycle high byte
    PWM6DCL 	= 0b01000000; // Set the duty cycle low byte
    T2CON 		= 0b11110000;// Enable Timer2, set prescaler, postscal-er 
    T2CLKCON 	= 0b00000001; // Select clock source for Timer2 as Fosc/4
	RD3PPS 		= 0x0E; // Route PWM6 waveform to RD3 
} 

void setPWMDuty(unsigned int duty)
{
    if (duty > 1023) duty = 1023;
    PWM6DCH = duty >> 2;
    PWM6DCL = (duty & 0x03) << 6;
}

void forward (void){
    PORTD = 0b00000010;
    setPWMDuty(500);
}

void backward (void){
    PORTD = 0b00000001;
    setPWMDuty(500);
}

void stop (void){
    PORTD = 0b00000000;
    setPWMDuty(0);
}

void resetGate(void) {
    backward();  
    __delay_ms(3000);
    stop();
    motorCount = 0;
}