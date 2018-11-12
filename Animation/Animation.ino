#include <OLED_I2C.h> 
#include "graphics.cpp"      
#define SCR_WIDTH 128
#define SCR_HEIGHT 64                        
OLED  myOLED(A4, A5, A4); 
extern uint8_t SmallFont[];

const class RabbitRun rabbitRun PROGMEM;
const class RabbitWait rabbitWait PROGMEM;


void setup() {
  // put your setup code here, to run once:
  myOLED.begin();
  myOLED.setFont(SmallFont);
  myOLED.clrScr();
}

void loop() {
  // put your main code here, to run repeatedly:
  /*myOLED.drawBitmap(0, 0, rabbitRun.frame1, 128, 64);
  
  delay(50);
  myOLED.drawBitmap(0, 0, rabbitRun.frame2, 128, 64);
  myOLED.update();
  
  myOLED.drawBitmap(0, 0, rabbitRun.frame3, 128, 64);
  myOLED.update();
  delay(50);
  myOLED.drawBitmap(0, 0, rabbitRun.frame4, 128, 64);
  myOLED.update();
  delay(50);
*/
 for(int i = 0; i < rabbitWait.framesNumber; i++){
   myOLED.drawBitmap(0, 0, rabbitWait.frames[i], 128, 64);
   myOLED.update();
   delay(50);
 }
}
