#include <OLED_I2C.h>     
#define SCR_WIDTH 128
#define SCR_HEIGHT 64                        
OLED  myOLED(A4, A5, A4); 
extern uint8_t SmallFont[];


void setup() {
  // put your setup code here, to run once:
  pinMode(A2, INPUT);
  myOLED.begin();
  myOLED.setFont(SmallFont);
  
}

void loop() {
  
  // put your main code here, to run repeatedly:
  float readed = ((float)analogRead(A2)) * 5.0 / 1024.0 / 10 * (10 + 10);
  char buf[100], temp[10];
  
  dtostrf(readed, 5, 2, temp);
  sprintf(buf,"Volt: %s", temp);
  myOLED.print(buf, CENTER, 40);
  myOLED.update();
  delay(1000);
  myOLED.clrScr();
}
