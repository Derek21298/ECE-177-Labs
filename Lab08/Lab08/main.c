/*
 * Lab08.c
 *
 * Created: 4/4/2017 2:01:03 PM
 * Author : Derek
 */ 

#include <avr/io.h>
#include <stdio.h>		// If you want to use printf
#include <util/delay.h>		// for delays
#include "lcd.h"

static FILE lcd_stdout=FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);

signed char getkey(void);			
signed char mapkey(signed char key);
signed int getnum(void);

int main(void){
	
	int num = 0;

    DDRA = 0xF0;
	
	lcd_init();		
	stdout=&lcd_stdout;
	
	
    while (1) {
		
		num = getnum();
		lcd_iwrite(LCD_CLR);
		
		printf("%d -> 0x%X", num, num);
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

signed int getnum() {
	
	int result = 0;
	int count = 0;
	
	while(1) {
		
		while(getkey() != -1);
		while(getkey() == -1);
		
		if(mapkey(getkey()) == '#') {
			break;
		}
		
		if(mapkey(getkey()) <= 9) {
			result = (result * 10) + mapkey(getkey());
		}
		
		if(mapkey(getkey()) == '*') {
			result /= 10;
		}
		if(mapkey(getkey()) == 10){
			count++;
		}
	}
	if((count % 2) == 1){
		result *= -1;
	}
	
	return result;
}



