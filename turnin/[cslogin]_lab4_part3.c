/*	Author: fbwog001
 *  Partner(s) Name: Linus Im
 *	Lab Section: 022
 *	Assignment: Lab #4 Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Init = 0x00, Wait = 0x01, Right = 0x02, Unlock = 0x03, Lock = 0x04} State;

void Tick(){
	
    unsigned char tmpC = PORTC;
    switch(State){
	case Init:
		State = Wait;
		break;

	case Wait:
		if(PINA == 4){
			State = Right;
		}
		else {
			State = Wait;
		}
		break;

	case Right:
		if(PINA == 2){
			State = Unlock;
		}
		else if(PINA == 4){
			State = Right;
		}
		else {
			State = Wait;
		}
		break;

	case Unlock:
		if(PINA == 128){
			State = Lock;
		}
		else{
			State = Unlock;
		}
		break;
			
	case Lock:
		State = Wait;
 
    }

    switch(State){
	case Init:
		PORTC = Init; //might not work
		break;

	case Wait:
		PORTC = Wait;
		break;

	case Right:
		PORTC = Right;
		break;

	case Unlock:
		PORTC = Unlock;
		PORTB = 0x01;
		break;

	case Lock:
		PORTC = Lock;
		PORTB = 0x00;
		break;
    }
}		
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0x00;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
