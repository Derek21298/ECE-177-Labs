/*
 * Lab10.c
 *
 * Created: 4/18/2017 1:48:45 PM
 * Author : Derek
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>		// Always include this
#include <stdio.h>		// If you want to use printf
#include <util/delay.h>		// for delays (but you'll write your own)
#include "lcd.h"

static FILE lcd_stdout=FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);


#define BUFFSIZE 16
#define MAGIC 30

// the following is provided in case it is needed in "getkey()" -- see class notes
//#define nop() asm volatile("nop")


signed char getkey(void);			// forward declarations
signed char mapkey(signed char key);
char getpw(char maxsize, char *pw); 	// Input keys into the array
char compareArrays(char SIZE, const char *px, const char *py);
void delaycycles(unsigned int cycles);
void mydelayms(unsigned int ms);



int main(void) {
	char passwd[] = {1,1,1,1};			// Hardcode the password here
	char pwsize = 4;
	char pwbuff[BUFFSIZE];
	char usersize;
	int k;


	//	DDRA = 0xF0; // While running the lower 4 bits of PORTA will be inputs and the
	// upper 4 bits will be outputs, but we'll make them outputs one at
	// a time, so we'll actually control the data direction in getkey(),
	// the keypad scanning routine.
	
	TCCR1B  = 0x01;		// Enable Timer 1 to count normally using the internal clock
	DDRD |= 0x01;

	lcd_init();		// Init the LCD display
	stdout=&lcd_stdout;
    
    while (1) {
		
		//while(1){
			
			//PORTD--;
			//for(int w = 0; w < 20000; w++) {
				//delaycycles(50);
			//}
		//}
		
		lcd_iwrite(LCD_CLR);
		usersize = getpw(BUFFSIZE, pwbuff);
		lcd_iwrite(LCD_CLR);
		if(usersize == pwsize) {
			if (compareArrays(pwsize, passwd, pwbuff) == 1) {
				printf("Open Lock");
				for(int s = 0; s < 880; s++) {
					PORTD = 1;
					delaycycles(1136);
					PORTD = 0;
					delaycycles(1136);
					
				}
				lcd_iwrite(LCD_CLR);
			}
			else {
				for(k = 0; k < 4; k++) {
					printf("Error");
					for(int s = 0; s < 56; s++) {
						PORTD = 1;
						delaycycles(2203);
						PORTD = 0;
						delaycycles(2203);
						
					}
					lcd_iwrite(LCD_CLR);
					mydelayms(250);
				}
			}
		}
		else {
			for(k = 0; k < 4; k++) {
				printf("Error");
				for(int s = 0; s < 56; s++) {
					PORTD = 1;
					delaycycles(2203);
					PORTD = 0;
					delaycycles(2203);
					
				}
				lcd_iwrite(LCD_CLR);
				mydelayms(250);
			}
		}
		
    }
}
signed char getkey() {
	
	int key = -1;
	int i, j;
	int row = 0;
	int col = 0;
	int maskRow = 0b00010000;
	int maskCol = 0b00000001;
	
	for(i = 4; i < 8; i++) {
		DDRA = maskRow << (i -4);
		PORTA = maskRow << (i - 4);
		row = (i - 4);
		
		for(j = 0; j < 4; j++) {
			if((PINA & (maskCol << j)) == (maskCol << j)) {
				col = j;
				
				key = 4 * row + col;
			}
		}
	}
	return key;
}
signed char mapkey(signed char key) {
	
	if((key < 0) || (key > 15)) {
		return key = -1;
	}
	
	signed char numkey[16] = {1, 2, 3, 10, 4, 5, 6, 11, 7, 8, 9, 12, '*', 0, '#', 13};
	
	key = numkey[key];
	
	return key;
}
char getpw(char maxsize, char *pw) {
	
	char *element = pw;
	int i;
	
	while(1) {
		
		while(getkey() != -1);
		while(getkey() == -1);
		
		
		if(element-pw < maxsize) {
			if(mapkey(getkey()) <= 13) {
				*element = mapkey(getkey());
				element++;
			}
		}
		
		if((mapkey(getkey()) == '*') && (element-pw > 0)) {
			element--;
		}
		
		if(mapkey(getkey()) == '#') {
			return (element-pw);
		}
		lcd_iwrite(LCD_CLR);
		for(i = 0; i < (element-pw); i++) {
			printf("*");
		}
	}
}
char compareArrays(char SIZE, const char *px, const char *py) {
	
	char *checkX = 0;
	char *checkY = 0;
	
	for(checkX = px, checkY = py; checkX-px < SIZE; checkX++, checkY++) {
		
		if(*checkX != *checkY) {
			return 0;
		}
	}
	return 1;
}
void mydelayms(unsigned int ms) {
	for(int i = 0; i < ms; i++) {
		delaycycles(1000);
	}
}

void delaycycles(unsigned int cycles) {
	TCNT1 = -(cycles - MAGIC);
	TIFR1 = (1 << TOV1);
	while((TIFR1 & (1 << TOV1)) != (1 << TOV1));
}

