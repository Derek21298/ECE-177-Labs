/*
 * Lab07.c
 *
 * Created: 3/28/2017 1:57:17 PM
 * Author : Derek
 */ 

#include <stdio.h>
#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>

#define PUSHED 1
#define RIGHT_BUTTON ((PINA&_BV(PIN0)) >> 0)
#define LEFT_BUTTON ((PINA&_BV(PIN3)) >> 3)
#define RESET_BUTTON ((PINA&_BV(PIN1)) >> 1)
#define LEFTMOST 0b1000000000
#define RIGHTMOST 0b00000001

static FILE lcd_stdout=FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);

int main(void) {
    
	enum state {left_serve, right_serve, moving_left, moving_right};
	
	char state;
	int leds = LEFTMOST;
	int leftScore = 0;
	int rightScore = 0;
	
	lcd_init();
	stdout = &lcd_stdout;
	
	
	DDRD = 0xFF;		
	DDRA = 0x10;		
	PORTA |= 0x10;
	DDRC |= 0x03;
	
	state = left_serve;
	
    while (1) {
		
		if (LEFT_BUTTON == PUSHED) {
			if(leds == LEFTMOST) {
				state = moving_right;
			}
			else {
				state = right_serve;
				rightScore++;
			}
		}
		
		else if (RIGHT_BUTTON == PUSHED) {
			if(leds == RIGHTMOST) {
				state = moving_left;
			}
			else {
				state = left_serve;
				leftScore++;
			}
		}
		
		else if (leds == 0x00) {
			if (state == moving_right) {
				state = left_serve;
			}
			else state = right_serve;
		}
		switch (state) {
			case moving_left:
			leds = leds << 1;
			break;
			
			case moving_right:
			leds = leds >> 1;
			break;
			
			case left_serve:
			leds = LEFTMOST;
			break;
			
			case right_serve:
			leds = RIGHTMOST;
			break;
		}
		
		PORTD = ~leds;
		PORTD = (PORTD & 0xFF00) | ((~leds) & 0x00FF);
		PORTC = (PORTC & 0xFFFC) | (((~leds) & 0x0300) >> 8 );
		
		_delay_ms(500);
		lcd_iwrite(LCD_CLR);
		if((leftScore == 15) || (rightScore == 15) || (RESET_BUTTON == PUSHED)) {
			leftScore = 0;
			rightScore = 0;
		}
		
		printf("Left Score: %d\n" , leftScore);
		printf("Right Score: %d\n", rightScore);
		
		
		
		
    }
}

