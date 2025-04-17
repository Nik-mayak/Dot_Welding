#include "my_variables.h"

volatile    int8_t      encData = 0;
volatile    bool        encNewData = false;
volatile    bool        encRstFlag = false;
volatile    uint8_t     encCurState = 0;
volatile    uint8_t     encPrevState = 0;
            uint8_t     currentKeyState = HIGH;
            uint8_t     previousKeyState = HIGH;  
            uint8_t     finalKeyState = HIGH;
            uint8_t     keyData = 0;
            bool        keyClick = false;
            bool        keyPush = false;
            bool        keyLong = false;
            uint32_t    timeStartKey = 0;
            uint32_t    debounceTimeMs = 0;

            bool        isReady = true; // Признак готовности к работе
            uint16_t    impulsTime = 100; // Время импульса в мс
            bool        newData = false; // новые данные
