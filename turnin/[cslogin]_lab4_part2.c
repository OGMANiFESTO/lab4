/*	Author: fbwog001
 *  Partner(s) Name: Linus Im
 *	Lab Section: 022
 *	Assignment: Lab #4 Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Init, Wait, Inc, Wait_Inc, Dec, Wait_Dec, Reset} State;

void Tick(){
	
    unsigned char tmpC = PORTC;
    switch(State){
	case Init:
		State = Wait;
		break;
        case Wait:
		if((PINA) && (tmpC != 9)){
			State = Inc;
		}
		else if((PINA == 2) && (tmpC > 0)){
			State = Dec;
		}
		else if(!PINA){
			State = Wait;
		}
		else if(PINA == 3){
			State = Reset;
		}
		break;
			
	case Inc:
		if(PINA){
			State = Wait_Inc;
		}
		else if(!PINA){
			State = Wait;
		}
		break;
			
	case Wait_Inc:
		if(!PINA){
			State = Wait;
		}
		else if(PINA){
			State = Wait_Inc;
		}
		else if(PINA == 3){
			State = Reset;
		}
		break;
			
	case Dec:
		if(PINA == 2){
			State = Wait_Dec;
		}
		else if(PINA == 3){
			State = Reset;
		}
		else if(!PINA){
			State = Wait;
		}
		break;
			
	case Wait_Dec:
		if(PINA == 2){
			State = Wait_Dec;
		}
		else if(PINA == 3){
			State = Reset;
		}
		else if(!PINA){
			State = Wait;
		}
		break;
			
	case Reset:
		if(!PINA){
			State = Wait;
		}
		else if(PINA){
			State = Inc;
		}
		else if(PINA == 3){
			State = Dec;
		}	
		break;
			
	default: 
		State = Init;
		break;
    }

    switch(State){
	case Wait:
		break;
		
	case Inc:
		PORTC = PORTC + 1;
		break;
			
	case Wait_Inc:
		break;
			
	case Dec:
		PORTC = PORTC - 1;
		break;
			
	case Wait_Dec:
		break;
			
	case Reset:
		PORTC = 0x00;
		break;
			
	default:
		break;	
    }
}		
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0x00;
    DDRC = 0xFF; PORTC = 0x07;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
