//Пин подключен к ST_CP входу 74HC595
int latchPin = 8;
//Пин подключен к SH_CP входу 74HC595
int clockPin = 12;
//Пин подключен к DS входу 74HC595
int dataPin = 11;
 
 
 
void setup() {
  //устанавливаем режим OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
 
void loop() {
  // отсчитываем от 0 до 255  и отображаем значение на светодиоде
  for (int numberToDisplay = 255; numberToDisplay >= 0; numberToDisplay--) {
    // устанавливаем синхронизацию "защелки" на LOW
    digitalWrite(latchPin, LOW);
    // передаем последовательно на dataPin
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay); 
 
    //"защелкиваем" регистр, тем самым устанавливая значения на выходах
    digitalWrite(latchPin, HIGH);
    // пауза перед следующей итерацией
    delay(100);
  }
}
