// индикатор
#include "Arduino.h"
#include <avr/pgmspace.h>
#include <avr/io.h>
#include "stdlib.h"
#include <string.h>
#include "my_variables.h"
#include "font.h"
//#include "user_config.h"

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif
#define TW_MT_SLA_ACK       0x18
#define i2c_addr            0x78
#define BLACK               0
#define WHITE               1
#define SSD_LCDWIDTH		128
#define SSD_LCDHEIGHT		64
#define SSD_SETPAGESTART	0xB0
#ifdef OLED_096
#define SSD_SHIFT           0x00
#else
#define SSD_SHIFT			0x02
#endif
#define TWI_FREQ            800000L // частоьа шины I2C

void oledInit();
void oledClearDisplay();
void oledDisplay();
void setTextColor(uint8_t color);
void oledDrawPixel(uint8_t x, uint8_t y, uint8_t color);
void oledVLine(uint8_t x, uint8_t y, uint8_t h, uint8_t color);
void oledHLine(uint8_t x, uint8_t y, uint8_t w, uint8_t color);
void oledDrawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
void oledFillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
void oledSetTextSize(uint8_t s);
void oledSetCursor(uint8_t x, uint8_t y);
void oledSetFont(const GFXfont *f);
void drawChar(uint8_t x, uint8_t y, uint8_t c, uint8_t color, uint8_t bg, uint8_t size);
void charWrite(uint8_t c);
void oledPrint(char* str);

void oledMainScreen();
//extern void startScreen();
//extern void powerStabScreen();
//extern void powerSetScreen();
