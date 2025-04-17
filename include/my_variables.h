#ifndef MY_VARIABLE_H
#define	MY_VARIABLE_H
#pragma once
#include <Arduino.h>

#define ENC_S1      PD2      // пин энкодера S1
#define ENC_S2      PD3      // пин энкодера S2
#define ENC_KEY     PD4      // пин энкодера KEY

#define SCL_PIN     A5
#define SDA_PIN     A4

#define DEBOUNCE_DELAY_MS  50
#define KEY_LONG_DELAY_MS 800

extern volatile int8_t  encData;
extern          uint8_t keyData;
extern          bool    keyClick;
extern          bool    keyPush;
extern          bool    keyLong;
extern volatile bool    encNewData;
extern volatile bool    encRstFlag;
extern volatile uint8_t encCurState;
extern volatile uint8_t encPrevState;
extern          uint32_t timeStartKey;
extern          uint32_t debounceTimeMs;
extern          uint8_t currentKeyState;
extern          uint8_t previousKeyState;  
extern          bool    isReady; // Признак готовности к работе
extern          uint16_t impulsTime; // Время импульса в мс
extern          bool    newData; // новые данные

#endif