#include "my_functions.h"
#include "my_variables.h"

void int_S1() {
  encTick();
}
void int_S2() {
  encTick();
}
  
void encTick() {
  // Чтение состояния пинов энкодера
  encCurState = (bitRead(PIND, ENC_S1) << 1) | bitRead(PIND, ENC_S2); // Чтение состояния S1 (порт B) и S2 (порт D)
  if (encRstFlag && encCurState == 0b11) { // Если оба сигнала в HIGH
      if (encPrevState == 0b10) encData = -1; // Вращение по часовой стрелке
      if (encPrevState == 0b01) encData =  1; // Вращение против часовой стрелки
      encRstFlag = false;
      encNewData = true; // Устанавливаем флаг для обработки
  }
  if (encCurState == 0b00) encRstFlag = true; // Сброс флага при обоих LOW
  encPrevState = encCurState; // Сохраняем текущее состояние
}
 
void encFlag(){  
  if(encNewData) {
    Serial.print("encData = "); Serial.println (encData);
    encNewData = false;
  }
}

bool keyReady() {
  static bool fixedState = false; // Флаг фиксации состояния
  bool keyReady = false; // Флаг готовности данных от кнопки
  currentKeyState = bitRead(PIND, ENC_KEY); //digitalRead(ENC_KEY);
  // Если считанное значение отличается от сохраненного (состояние кнопки изменилось)
  if (currentKeyState != previousKeyState) {
    debounceTimeMs = millis();  // Сохраняем текущую временную отметку
    fixedState = false;
  } else if ((millis() - debounceTimeMs) >= DEBOUNCE_DELAY_MS && !fixedState) {
    keyData = bitRead(PIND, ENC_KEY); //digitalRead(ENC_KEY);
    fixedState = true;
    keyReady = true; // Устанавливаем флаг готовности к обработке нажатия кнопки
  }
  previousKeyState = currentKeyState;// Обновляем значение
  return keyReady; // Возвращаем флаг готовности к обработке нажатия кнопки
}

void keyClickOrLong() {
  if (keyReady()) {
    if (keyData == LOW) { // Если кнопка нажата
      timeStartKey = millis(); // Сохраняем время нажатия
      keyPush = true; // Устанавливаем флаг нажатия кнопки
    } else {
      if (!keyClick && keyPush) {
        if (millis() - timeStartKey < KEY_LONG_DELAY_MS) { // Если время удержания меньше 800 мс
          keyClick = true; // Устанавливаем флаг короткого нажатия
          keyPush = false; // Сбрасываем флаг нажатия кнопки
          keyLong = false; // Сбрасываем флаг длинного нажатия 
        } 
      }
    }
  } else if (keyPush && keyData == LOW) { // Если кнопка удерживается
    if (millis() - timeStartKey >= KEY_LONG_DELAY_MS) { // Если кнопка удерживается более 800 мс
      keyLong = true; // Устанавливаем флаг длинного нажатия
      keyClick = false; // Сбрасываем флаг короткого нажатия
      keyPush = false; // Сбрасываем флаг нажатия кнопки
    }
  }
}

void controlImpulsTime() {
  if(encNewData) {
    //Serial.print("encData = "); Serial.println (encData); // Отладочный вывод
    uint16_t oldImpulsTime = impulsTime; // Сохраняем старое значение времени импульса      
    if ((encData > 0 && impulsTime < 1000) || (encData < 0 && impulsTime >= 20)) { // Если вращение по часовой стрелке
      impulsTime += encData * 10; // Увеличиваем время импульса
    }
    if (oldImpulsTime != impulsTime) { // Если значение изменилось
      newData = true; // Устанавливаем флаг новых данных
      //Serial.print("impulsTime = "); Serial.println (impulsTime); // Отладочный выво
    }
    encNewData = false; // Сбрасываем флаг новых данных
  }
}

void impulsGo () {
  digitalWrite(LED_PIN, HIGH); // Устанавливаем HIGH на пине KEY
  delay(impulsTime); // Задержка на время импульса
  digitalWrite(LED_PIN, LOW); // Устанавливаем LOW на пине KEY
}

// Функция для запуска таймера:
void timer_start(Timer *timer, uint32_t delay_ms) {
  timer->start_time = millis(); // Получаем текущее время (F=27MHz = 108/4)
  timer->delay = delay_ms; //
  timer->active = true;
}

// Функция для проверки таймера:
uint8_t timer_state(Timer *timer) {
  if (!timer->active) {
      return NO_ACTIVE; // Таймер не запущен
  }
  uint64_t current_time = millis();
  if ((current_time - timer->start_time) >= timer->delay) {
      timer->active = false; // Таймер не активен
      return COMPLETED; // Таймер сработал
  }
  return RUNNING; // Таймер ещё работает
}
