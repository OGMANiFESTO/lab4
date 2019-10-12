/*	Author: fbwog001
 *	 *  Partner(s) Name: Linus Im
 *	  *	Lab Section: 022
 *	   *	Assignment: Lab #4 Exercise #2
 *	    *	Exercise Description: [optional - include for your own benefit]
 *	     *
 *	      *	I acknowledge all content contained herein, excluding template or example
 *	       *	code, is my own original work.
 *	        */
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
		if(PINA == 0x03){
                        State = Reset;
                }
		else if((PINA) && (tmpC != 0x09)){
			State = Inc;
		}
		else if((PINA == 0x02) && (tmpC > 0x00)){
			State = Dec;
		}
		else if(!PINA){
			State = Wait;
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
		else if(PINA == 0x03){
			State = Reset;
		}
		break;
			
	case Dec:
		if(PINA == 0x02){
			State = Wait_Dec;
		}
		else if(PINA == 0x03){
			State = Reset;
		}
		else if(!PINA){
			State = Wait;
		}
		break;
			
	case Wait_Dec:
		if(PINA == 0x02){
			State = Wait_Dec;
		}
		else if(PINA == 0x03){
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
		else if(PINA == 0x03){
			State = Reset;
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
		PORTC = PORTC + 0x01;
		break;
			
	case Wait_Inc:
		break;
			
	case Dec:
		PORTC = PORTC - 0x01;
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

}
