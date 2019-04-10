
#include <OLED_I2C.h>                               
OLED  myOLED(A4, A5, A4);                         
extern uint8_t SmallFont[];  
boolean buttons[9];
boolean phone, startPhone; 
boolean clicks, previousClicks;
unsigned short int phoneDigit;
unsigned long time;


void setup() {
  // put your setup code here, to run once:
  time = 0;
  phone = false;
  clicks = false;
  myOLED.begin(); 
   myOLED.setFont(SmallFont);
   myOLED.print("HI!",LEFT,12);
   myOLED.update();
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(A1, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
    /*
    for (int i = 0; i < 9; i++){
        buttons[i] = !digitalRead(i+2); 
        if (buttons[i]){
            showButtonNumber(i+1);
            break;
        }
    }
    */
   // myOLED.clrScr();   
    startPhone = phone;
    readPhone();
    if (phone){
        myOLED.print("Reading phone",LEFT,24);
    }
     digitalWrite(A1, LOW);
    if(!digitalRead(12)){
      digitalWrite(A1, HIGH);
    }
    static int number = -1;
    if (!phone && startPhone){
        number = phoneDigit;    
    }
    showButtonNumber(phoneDigit);
    
    myOLED.update();
    myOLED.clrScr();
}

void showButtonNumber(int i){
    char buf[3];
    sprintf(buf,"%d",i);
    myOLED.print(buf,LEFT,12);
    myOLED.update();
}

boolean readPhone(){
    boolean read = !digitalRead(11);
    previousClicks = clicks;
    if (!phone){
        if (startPhone){
          clicks = digitalRead(12);
            if(previousClicks) return true;
            if(clicks){
                phoneDigit++;
            }  
        }
        if (read){
            phone = true;
            phoneDigit = 0;
        }
    }
    
    if (phone){
        if (read){    
            clicks = digitalRead(12);
            if(previousClicks) return true;
            if(clicks){
                phoneDigit++;
            }  
            return true;
        } 
        else{
            phone = false;
            clicks = false;
        }
    }
    return false;
}
