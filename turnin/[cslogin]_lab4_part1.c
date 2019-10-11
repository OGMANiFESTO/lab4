/*	Author: fbwog001
 *  Partner(s) Name: Linus Im
 *	Lab Section: 022
 *	Assignment: Lab #4 Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{START, LED1, LED2, WAIT1, WAIT2}  state;

void Tick(){
	switch(state) { // Transition Actions
		case START:
			state = LED1;
			break;
		case LED1:
			if( (PINA & 0x01) == 0x01) {
				state = WAIT1;
			} else {
				state = LED1;
			}
			break;
		case LED2:
			if( (PINA & 0x01) == 0x01) {
				state = WAIT2;
			} else {
				state = LED2;
			}
			break;
		case WAIT1:
			if( (PINA & 0x01) == 0x01) {
				state = WAIT1;
			} else {
				state = LED2;
			}
			break;
		case WAIT2:
			if( (PINA & 0x01) == 0x01) {
				state = WAIT2;
			} else {
				state = LED1;
			}
	}
	
	switch(state) { // State Actions
		case START:
			PORTB = 0x01;
			break;
		case LED1:
			PORTB = 0x01;
			break;
		case LED2:
			PORTB = 0x02;
			break;
		case WAIT1:
			break;
		case WAIT2:
			break;
		default:
			break;
	}
}		
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0x00;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
}
