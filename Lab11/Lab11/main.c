/*
 * Lab11.c
 *
 * Created: 4/24/2017 10:08:31 AM
 * Author : Derek
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>		// Always include this
#include <stdio.h>		// If you want to use printf
#include <util/delay.h>		// for delays
#include "lcd.h"

#define MAGIC 30

static FILE lcd_stdout=FDEV_SETUP_STREAM(lcd_putc,NULL,_FDEV_SETUP_WRITE);

// The following defines are for the serial port (F_CPU, above, is also needed)
#define BAUD 9600
#define UBRR_SET (F_CPU / 8 / BAUD -1) // page 174


struct note {
	unsigned char notenum;		// index into array of frequencies for this note
	unsigned char duration;		// duration of note in 1/8ths of a second
};

struct song {
	unsigned char numnotes;		// Number of notes in this song
	const struct note thenotes[100];	// Array of the notes (max 30)
};

const struct song mario = {
	97,
	{
		{23, 1},
		{23, 1},
		{0, 1},
		{23, 1},
		{0, 1},
		{21, 1},
		{23, 1},
		{0, 1},
		{25, 1},
		{0, 3},
		{17, 1},
		{0, 3},
		{21, 1},
		{0, 2},
		{17, 1},
		{0, 2},
		{16, 1},
		{0, 2},
		{18, 1},
		{0, 1},
		{20, 1},
		{0, 1},
		{19, 1},
		{18, 1},
		{0, 1},
		{17, 1},
		{23, 1},
		{25, 1},
		{26, 1},
		{0, 1},
		{24, 1},
		{25, 1},
		{0, 1},
		{23, 1},
		{0, 1},
		{21, 1},
		{22, 1},
		{20, 1},
		{0, 2},
		{21, 1},
		{0, 2},
		{17, 1},
		{0, 2},
		{16, 1},
		{0, 2},
		{18, 1},
		{0, 1},
		{20, 1},
		{0, 1},
		{19, 1},
		{18, 1},
		{0, 1},
		{17, 1},
		{23, 1},
		{25, 1},
		{26, 1},
		{0, 1},
		{24, 1},
		{25, 1},
		{0, 1},
		{23, 1},
		{0, 1},
		{21, 1},
		{22, 1},
		{20, 1},
		{0, 2},
	}
};

const struct song steinsong = {
	14,
	{
		{3,12},	//	 First line of "Maine Stein Song"
		{5,1},	//	 Data is note number and duration (1/8 ths second)
		{3,3},
		{2,1},
		{3,3},
		{8,4},
		{12,8},
		{15,4},
		{8,2},
		{8,2},
		{10,4},
		{8,4},
		{7,8},
		{5,8}
	}
};

const struct song marylamb = {
	26,
	{
		{5,3},	//	 First line of "Mary Had a Little Lamb"
		{3,1},	//	 Data is note number and duration (1/8 ths second)
		{1,2},
		{3,2},
		{5,2},
		{5,2},
		{5,4},
		{3,2},
		{3,2},
		{3,4},
		{5,2},
		{8,2},
		{8,4},
		{5,3},
		{3,1},
		{1,2},
		{3,2},
		{5,2},
		{5,2},
		{5,2},
		{5,2},
		{3,2},
		{3,2},
		{5,2},
		{3,2},
		{1,8}
	}
};

const unsigned int frequency[] = {        // note number & note
	0,		  // 0 rest
	523,      // 1  C5
	554,      // 2  C#5
	587,      // 3  D5
	622,      // 4  D#5
	659,      // 5  E5
	698,      // 6  F5
	740,      // 7  F#5
	784,      // 8  G5
	831,      // 9  G#5
	880,      // 10  A5
	932,      // 11 A#5
	988,      // 12 B5
	1047,     // 13 C6
	1109,     // 14 C#6
	1175,	  // 15 D6
	1319,	  // 16 E6
	1568,	  // 17 G6
	1760,	  // 18 A6
	1865,	  // 19 A#6
	1976,	  // 20 B6
	2093,	  // 21 C7
	2349,	  // 22 D7
	2637,	  // 23 E7
	2794,	  // 24 F7
	3136,	  // 25 G7
	3520	  // 26 A7
};

signed char getkey();
signed char mapkey(signed char key);
void delaycycles(unsigned int cycles);
void mydelayms(unsigned int ms);
void playnote(struct note n);
void playsong(const struct song* s);
void serialInit(void);
unsigned char serialRead(void);
void serialWrite(unsigned char sendByte);
void playANote(const unsigned int f);


int main(void) {
	
	DDRD |= 0b00000100;
	DDRD &= 0b11111100;
	DDRC &= 0b11111100;
	TCCR1B = 0x01;
	
	serialInit();
	 
	lcd_init();
	stdout=&lcd_stdout;
	lcd_iwrite(LCD_CLR);
    
    while (1) {
		//volatile unsigned char input;
		
		
		//input = serialRead();
		
		while(mapkey(getkey()) != -1);
		while(mapkey(getkey()) == -1);
		
		if(mapkey(getkey()) == 1) {
			playsong(&steinsong);
		}
		if(mapkey(getkey()) == 2){
			playsong(&marylamb);
		}
		if(mapkey(getkey()) == 3){
			playsong(&mario);
		}
		
		
		//if(input == '1') {
			//playANote(frequency[0]);
			//playsong(&steinsong);
			//playANote(frequency[4]);
		//}
		//if(input == '2') {
			//playsong(&marylamb);
		//}
		//if(input == 'z') {
			
		
			//while(1) {
				//input = serialRead();
				//if(input == 'z') break;
				//if(input == 'q') playANote(frequency[0]);
				//if(input == 'w') playANote(frequency[2]);
				//if(input == 'e') playANote(frequency[4]);
				//if(input == 'r') playANote(frequency[5]);
				//if(input == 't') playANote(frequency[7]);
				//if(input == 'y') playANote(frequency[9]);
				//if(input == 'u') playANote(frequency[11]);
				//if(input == 'i') playANote(frequency[12]);
				//if(input == 'o') playANote(frequency[14]);
				//if(input == '2') playANote(frequency[1]);
				//if(input == '3') playANote(frequency[3]);
				//if(input == '5') playANote(frequency[6]);
				//if(input == '6') playANote(frequency[8]);
				//if(input == '7') playANote(frequency[10]);
				//if(input == '9') playANote(frequency[13]);
				
			//}
		//}
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
void serialInit(void) {
	// set BAUD rate to 9600
	UCSR0A |= 1<<U2X0; 		// Set transmission speed
	UBRR0H = UBRR_SET>>8;	// load the upper UBRR bits
	UBRR0L = UBRR_SET;		// load lower bits. set the things in accordance with page 194

	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);	// set 8-bit data
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);	// enable rx and tx
}

unsigned char serialRead(void) {
	
	UCSR0A &= ~(1 << RXC0);
	while((UCSR0A & (1 << RXC0)) != (1 << RXC0));
	
	return UDR0;
}

void serialWrite(unsigned char sendByte) {
	
	UCSR0A &= ~(1 << UDRE0);
	while((UCSR0A & (1 << UDRE0)) != (1 << UDRE0));
	UDR0 = sendByte;
	
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
void playnote(struct note n){
	long int speakerToggle;
	long int toggleTime;
	long int i;
	
	speakerToggle = (frequency[n.notenum] * n.duration) / 8;
	toggleTime = 500000 / frequency[n.notenum];
	
	if(frequency[n.notenum] == 0) {
		mydelayms(125);
	}
	
	for(i = 0; i < speakerToggle; i++) {
		PORTD |= 0b00000100;
		delaycycles(toggleTime);
		PORTD &= ~0b0000100;
		delaycycles(toggleTime);
	}
	mydelayms(10);
}
void playsong(const struct song* s) {
	int i;
	
	for(i = 0; i < s->numnotes; i++) {
		playnote(s->thenotes[i]);
	}
}
void playANote(const unsigned int f) {
	long int loopduration, fq, i;
	
	fq = 1000000 / f;
	loopduration = 125000;
	loopduration /= fq;
	
	for(i = 0; i < loopduration; i++){
		delaycycles(fq/2);
		PORTD |= 0x04;
		delaycycles(fq/2);
		PORTD &= ~0x04;
	}
} 

