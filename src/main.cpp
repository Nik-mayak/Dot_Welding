#include "my_variables.h"
#include "my_functions.h"
#include "oled.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Start setup");

  pinMode(LED_PIN, OUTPUT); // Настраиваем светодиод как выход
  digitalWrite(LED_PIN, LOW); // Выключаем светодиод
  pinMode(ENC_S1, INPUT); // Настраиваем S1 как вход
  pinMode(ENC_S2, INPUT); // Настраиваем S2 как вход
  pinMode(ENC_KEY, INPUT); // Настраиваем KEY как вход

  attachInterrupt(digitalPinToInterrupt(ENC_S1), int_S1, CHANGE); // Прерывание на любом изменении S1
  attachInterrupt(digitalPinToInterrupt(ENC_S2), int_S2, CHANGE); // Прерывание на любом изменении S2

  oledInit(); // Инициализация OLED дисплея
  //oledDisplay(); // Отображение заставки на дисплее
  //delay(2000); // Задержка для отображения заставки
  oledClearDisplay(); // Очистка дисплея
  oledMainScreen();

}

void loop() {
  //encFlag();
  controlImpulsTime(); // Управление временем импульса
  keyClickOrLong();
  if (keyLong) {
    Serial.print("keyLong = "); Serial.println (keyLong);
    keyLong = false; // сбрасываем флаг keyLong
  }
  if (keyClick) {
    //Serial.print("keyClick = "); Serial.println (keyClick);
    impulsGo(); // Выполняем действие при коротком нажатии
    keyClick = false; // сбрасываем флаг keyClick
  }
  if (newData) {
    oledMainScreen(); // Отображение главного экрана
    newData = false; // сбрасываем флаг encNewData
  }
  
}
