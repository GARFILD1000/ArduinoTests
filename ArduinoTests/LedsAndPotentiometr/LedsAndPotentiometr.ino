#include <OLED_I2C.h>                               // Подключаем библиотеку OLED_I2C для работы со шрифтами и графикой
OLED  myOLED(A4, A5, A4);                           // Определяем пины I2C интерфейса: UNO и NANO -- SDA - пин A4, SCL - пин A5; MEGA -- SDA - пин 20, SCL - пин 21
extern uint8_t RusFont[];                           // Подключаем русский шрифт
extern uint8_t SmallFont[];   
int potentVal;
int numOfActiveLeds;
int displayBrightness;
void setup() {
  // put your setup code here, to run once:
  for(int i = 12; i >= 3; i--){
    pinMode(i, OUTPUT);
  }
  pinMode(A0, INPUT);
  myOLED.begin();
   myOLED.setFont(RusFont); 
}


void loop() {
  myOLED.clrScr();   
  potentVal = analogRead(0);
  numOfActiveLeds = map(potentVal, 0, 1023, 1, 10);
  numOfActiveLeds = constrain(numOfActiveLeds, 0, 10);
  displayBrightness = map(potentVal, 0, 1023, 1, 255);
  displayBrightness = constrain(displayBrightness, 0, 255);
  for (int i = 12, j = 1; i >= 3; i--, j++){
    if (j <= numOfActiveLeds) digitalWrite(i, HIGH);
    else digitalWrite(i, LOW);
  }
  
  myOLED.print("Gjkj;tybt gjntywbjv ",LEFT, 8);
  myOLED.print("Rjk-dj cdtnjlbjljd",LEFT, 24);
  myOLED.print("Zhrjcnm lbcgktz",LEFT,40);
  char buff[10];
  sprintf(buff,"%d",potentVal);
  myOLED.print(buff,CENTER, 16);
  sprintf(buff,"%d",numOfActiveLeds);
  myOLED.print(buff,CENTER, 32);
  sprintf(buff,"%d",displayBrightness);
  myOLED.print(buff,CENTER, 48);
  
  myOLED.setBrightness(displayBrightness);
  myOLED.update();
}
