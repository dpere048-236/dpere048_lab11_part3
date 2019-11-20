/*	Author:David Perez dpere048
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include <avr/interrupt.h>
#include "bit.h"
#include "timer.h"
#include "io.c"
#include "io.h"
#include "keypad.h"
#include "scheduler.h"
#include <stdio.h>
enum displayStates{display};
unsigned char tmpA = 0x00;
int displaySMTick(int state){
	unsigned char output;
	output = GetKeypadKey();
	switch(state){
		case display:
			switch(output){
				case '\0': tmpA = 0x1F; break;
				case '1': tmpA = 0x01;
				LCD_Cursor(1); LCD_WriteData(tmpA + '0'); break;
				case '2': tmpA = 0x02;
                                LCD_Cursor(1); LCD_WriteData(tmpA + '0'); break;
				case '3': tmpA = 0x03;
                                LCD_Cursor(1); LCD_WriteData(tmpA + '0'); break;
				case '4': tmpA = 0x04;
                                LCD_Cursor(1); LCD_WriteData(tmpA + '0'); break;
				case '5': tmpA = 0x05;
                                LCD_Cursor(1); LCD_WriteData(tmpA + '0'); break;
				case '6': tmpA = 0x06;
                                LCD_Cursor(1); LCD_WriteData(tmpA + '0'); break;
				case '7': tmpA = 0x07;
                                LCD_Cursor(1); LCD_WriteData(tmpA + '0'); break;
				case '8': tmpA = 0x08;
                                LCD_Cursor(1); LCD_WriteData(tmpA + '0'); break;
				case '9': tmpA = 0x09;
                                LCD_Cursor(1); LCD_WriteData(tmpA + '0'); break;
				case 'A': tmpA = 0x0A;
                                LCD_Cursor(1); LCD_WriteData(tmpA + 0x37); break;
				case 'B': tmpA = 0x0B;
                                LCD_Cursor(1); LCD_WriteData(tmpA + 0x37); break;
				case 'C': tmpA = 0x0C;
                                LCD_Cursor(1); LCD_WriteData(tmpA + 0x37); break;
				case 'D': tmpA = 0x0D;
                                LCD_Cursor(1); LCD_WriteData(tmpA + 0x37); break;
				case '*': tmpA = 0x0E;
                                LCD_Cursor(1); LCD_WriteData(tmpA + 0x1C); break;
				case '0': tmpA = 0x00;
                                LCD_Cursor(1); LCD_WriteData(tmpA + '0'); break;
				case '#': tmpA = 0x0F;
                                LCD_Cursor(1); LCD_WriteData(tmpA + 0x14); break;
			default: tmpA = 0x1B; break; //middle led off, never happens
		}
	state = display;
	PORTB = tmpA;
		break;
		}
return state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
DDRA = 0xFF; PORTA = 0x00; //inputs
DDRB = 0x00; PORTB = 0xFF; //outputs
DDRC = 0xF0; PORTC = 0x0F; //pins pc7-4 are inputs while pinsc3-0 are outputs
DDRD = 0xFF; PORTD = 0x00; //port d is outputs
unsigned long int displaySMTick_calc = 50;
unsigned long int tmpGCD = 1;
unsigned long int GCD = tmpGCD;
unsigned long int displaySMTick_period = displaySMTick_calc;
static _task task1;
_task *tasks[] = {&task1};
const unsigned short numTasks = sizeof(tasks)/sizeof(task*);
//task1
task1.state = 0;
task1.period = displaySMTick_period;
task1.elapsedTime = displaySMTick_period;
task1.TickFct = &displaySMTick; //pointer for the tick
///TIMER
TimerSet(GCD);
TimerOn();
LCD_init();
unsigned short i;
    /* Insert your solution below */

    while (1) {
	for(i = 0; i < numTasks; i++ ) {
		if( tasks[i]->elapsedTime >= tasks[i]->period){
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 0;
}
