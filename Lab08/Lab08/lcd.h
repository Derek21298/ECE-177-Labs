#ifndef __LCD_H__
#define __LCD_H__

// A. Sheaff 1/10/2008
// 4 bit LCD interface.

// Define LCD type. Choose one.
// #define LCD_1LINE
// #define LCD_2LINE
 #define LCD_4LINE
// End choice.

// Set line length
#define LCD_LINELEN 16
// Set New line address
#define LCD_LINE2A 0x40

// Register select, Read/Write, Clock
#define LCD_RS PIN4
#define LCD_RW PIN6
#define LCD_E  PIN7
// Code assumes lower 4 bits are for data.
#define LCD_DATW PORTB
#define LCD_DATR PINB

// LCD commands
#define LCD_CLR		0x01	// LCD Clear
#define LCD_HOME	0x02	// LCD Home
#define LCD_SETDD	0x80	// LCD Set Data Address
#define LCD_SHIFT	0x10	// Shift
#define LCD_SCURS	0x00	// Shift Cursor
#define LCD_SDISP	0x08	// Shift Dislay
#define LCD_SRGHT	0x04	// Shift Right
#define LCD_SLEFT	0x00	// Shift Left

// LCD initialization
void lcd_init(void);

// Wait for LCD to finish current operation.  Returnds DD RAM address.
unsigned char lcd_busy_wait(void);

// Write character data to LCD
void lcd_dwrite(unsigned char d);
int lcd_putc(char c, struct __file * f);

// Write instruction data to LCD
void lcd_iwrite(unsigned char d);

// Read data memory
unsigned char lcd_dread(void);
#endif // __LCD_H__
