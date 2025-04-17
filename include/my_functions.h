#ifndef MY_FUNCTIONS_H
#define	MY_FUNCTIONS_H
#pragma once
#include <Arduino.h>
#include "my_variables.h"

void int_S1();    // необходимо объявление функ. обраб. прерывания в памяти
void int_S2();
void int_Falling_KEY();
void int_Rising_KEY();
void encTick();
bool keyLongOK();
void encFlag();
bool keyReady();
void keyClickOrLong();
void controlImpulsTime();
void impulsGo ();
void    timer_start(Timer *timer, uint32_t delay_ms);
uint8_t timer_state(Timer *timer);

#endif