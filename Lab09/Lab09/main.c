/*
 * Lab09.c
 *
 * Created: 4/11/2017 1:54:03 PM
 * Author : Derek
 */ 

#include <avr/io.h>

#define F_CPU 1000000UL
#include <avr/io.h>		// Always include this
#include <stdio.h>		// If you want to use printf
#include <util/delay.h>		// for delays
#include "lcd.h"

static FILE lcd_stdout=FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);


#define BUFFSIZE 16

signed char getkey(void);			// forward declarations
signed char mapkey(signed char key);
char getpw(char maxsize, char pw[]); 	// Input keys into the array
char compareArrays(char size, const char a1[], const char a2[]);
void mydelayms(unsigned int ms);

void main(void) {
	    char passwd[] = {10,2,13,4};			// Set the password in your function
	    char pwsize = 4;
	    char pwbuff[BUFFSIZE];
		int k;
		int usersize;

	    //	DDRA = 0xF0; // While running the lower 4 bits of PORTA will be inputs and the
	    // upper 4 bits will be outputs, but we'll make them outputs one at
	    // a time, so we'll actually control the data direction in getkey(),
	    // the keypad scanning routine.

	    lcd_init();		// Init the LCD display
	    stdout=&lcd_stdout;
    while (1) {
		lcd_iwrite(LCD_CLR);
		usersize = getpw(BUFFSIZE, pwbuff);
		lcd_iwrite(LCD_CLR);
		if(usersize == pwsize) {
			if (compareArrays(pwsize, passwd, pwbuff) == 1) {
				printf("Open Lock");
				mydelayms(2000);
				lcd_iwrite(LCD_CLR);
			}
			else {
				for(k = 0; k < 4; k++) {
					printf("Error");
					mydelayms(250);
					lcd_iwrite(LCD_CLR);
					mydelayms(250);
				}
			}
		}
		else {
			for(k = 0; k < 4; k++) {
				printf("Error");
				mydelayms(250);
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

char getpw(char maxsize, char pw[]) {
	
	char size = 0;
	int i;
	
	
	while(1) {
		
		while(getkey() != -1);
		while(getkey() == -1);
		
		
		if(size < maxsize) {
			if(mapkey(getkey()) <= 13) {
				pw[size] = mapkey(getkey());
				size++;
			}
		}
		
		if((mapkey(getkey()) == '*') && (size > 0)) {
			size -= 1;
		}
		
		if(mapkey(getkey()) == '#') {
			return size;
		}
		lcd_iwrite(LCD_CLR);
		for(i = 0; i < size; i++) {
			printf("*");
		}
	}
}

char compareArrays(char SIZE, const char a1[], const char a2[]) {
	
	char i;
	
	for(i = 0; i < SIZE; i++) {
		if(a1[i] != a2[i]) {
			return 0;
		}
	}
	return 1;
}

void mydelayms(unsigned int ms) {
	
	volatile int i;
	volatile long long int j;
	
	for(i = 0; i < ms; i++) {
		 for(j = 0; j < 12; j++){};
	}
}


