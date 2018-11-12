#include <OLED_I2C.h>       
#define SCR_WIDTH 128
#define SCR_HEIGHT 64                        
OLED  myOLED(A4, A5, A4);                           // Определяем пины I2C интерфейса: UNO и NANO -- SDA - пин A4, SCL - пин A5; MEGA -- SDA - пин 20, SCL - пин 21
//extern uint8_t RusFont[];                           // Подключаем русский шрифт
extern uint8_t SmallFont[]; 
extern uint8_t Arconoid1[];
extern uint8_t Arconoid2[];
extern uint8_t ArconoidLevel0[];
extern uint8_t ArconoidLevel1[];
extern uint8_t ArconoidLevel2[];

short int potentVal;
unsigned short int platformLength;
short int platformPositionY;
short int platformPositionX;
float ballAccelerationX;
float ballAccelerationY;
float ballPositionX;
float ballPositionY; 
short int ballSize;
unsigned short int cellsNumber;
unsigned short int brokenCellsNumber;
unsigned short int cellSizeX;
unsigned short int cellSizeY;
unsigned short int cellsPerLine;
unsigned short int bonusesNumber;
float stepLength;
int level;
bool ballMoving;
bool autopilot;
bool bigger;
bool smaller;
bool destroyer;
long autopilotTimer;
long destroyerTimer;
 

typedef struct cell{
  unsigned short int leftUpX;
  unsigned short int leftUpY;
  unsigned short int rightDownX;
  unsigned short int rightDownY;
  unsigned short int health;
  bool isBroken;
};
cell *cells;
typedef struct bonus{
  unsigned short int positionX;
  float positionY;
  char symbol[2];
  bool isCatched;
  bonus *next;
};
bonus *bonuses;

void gameStartAnimation(){
  for(int i = 0; i < 10; i++){
    myOLED.drawBitmap(0, 0, Arconoid1, 128, 64); 
    myOLED.update();
    delay(100);
    myOLED.drawBitmap(0, 0, Arconoid2, 128, 64); 
    myOLED.update();
    delay(100);
  }
}

void levelCnangeAnimation(){
    char buf[30]; 
    sprintf(buf,"Level %d completed!",level);
    myOLED.drawBitmap(0, 0, ArconoidLevel0, 128, 40);
    
    myOLED.print(buf,CENTER,45);
    //myOLED.clrScr();
    myOLED.update();
    delay(300);
    myOLED.drawBitmap(0, 0, ArconoidLevel1, 128, 40);
    myOLED.print(buf,CENTER,45);
    //myOLED.clrScr();
    myOLED.update();
    delay(300);
    myOLED.drawBitmap(0, 0, ArconoidLevel2, 128, 40);
    myOLED.print(buf,CENTER,45);
    //myOLED.clrScr();
    myOLED.update();
    delay(300);
    myOLED.drawBitmap(0, 0, ArconoidLevel1, 128, 40);
    myOLED.print(buf,CENTER,45);
    //myOLED.clrScr();
    myOLED.update();
    delay(300);
    myOLED.drawBitmap(0, 0, ArconoidLevel0, 128, 40);
    myOLED.print(buf,CENTER,45);
    //myOLED.clrScr();
    myOLED.update();
    delay(1000);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(A0, INPUT);
  randomSeed(analogRead(0));
  myOLED.begin();
  myOLED.setFont(SmallFont);
  myOLED.clrScr();
  cells = new cell[cellsNumber];
  bonuses = NULL;
  gameStartAnimation();
  platformLength = 15;
  platformPositionY = SCR_HEIGHT - 5;
  platformPositionX = SCR_WIDTH / 2  - platformLength / 2;
  cellsNumber = 10;
  bonusesNumber;
  level = 1;
  autopilotTimer = 0;
  autopilot = false;
  bigger = false;
  smaller = false;
  destroyer = false;
  ballMoving = true;
  brokenCellsNumber = 0;
  cellsPerLine = 10;
  cellSizeX = SCR_WIDTH / cellsPerLine;
  cellSizeY = SCR_HEIGHT / 10;
  ballSize = 2;
  stepLength = 1.5;
  setCells();
  setBall();
  
}

void setBall(){
  ballPositionX = SCR_WIDTH / 2;
  ballPositionY = platformPositionY - ballSize - 5;
  ballAccelerationX = stepLength;
  ballAccelerationY = -stepLength;
}

void setCells(){
  int rows = 0;
  for(int i = 0; i < cellsNumber; i++){
    delete(cells);
    cells = new cell[cellsNumber];
    if ((i - (rows * cellsPerLine)) * cellSizeX + cellSizeX < SCR_WIDTH){
      cells[i].leftUpX = (i - (rows * cellsPerLine)) * cellSizeX;
      cells[i].leftUpY = rows * cellSizeY;
      cells[i].rightDownX = (i - (rows * cellsPerLine)) * cellSizeX + cellSizeX;
      cells[i].rightDownY = rows * cellSizeY + cellSizeY;
      cells[i].health = ((level-1) % 3) + 1;
      cells[i].isBroken = false;
    }
    else {
      i--;
      rows++;
    }
  }
}

void createNewBonus(int destroyedCellNumber){
  bonus *lastBonus = bonuses, *newBonus;
  if(lastBonus != NULL){
    while(lastBonus->next != NULL){
      lastBonus = lastBonus->next; 
    }
    newBonus = new bonus();
    lastBonus->next = newBonus;
  }
  else{
    bonuses = new bonus();
    newBonus = bonuses;
  }
  newBonus->positionX = cells[destroyedCellNumber].rightDownX;
  newBonus->positionY = cells[destroyedCellNumber].rightDownY;
  newBonus->isCatched = false;
  newBonus->symbol[1] = 0; 
  bonusesNumber++;
  switch(random(7)){
    case 0: newBonus->symbol[0] = 'B'; break;
    case 1: newBonus->symbol[0] = 'S'; break;
    case 2: newBonus->symbol[0] = 'D'; break;
    default: newBonus->symbol[0] = 'A'; break;
  }     
}

void deleteBonus(bonus *previous, bonus *iterator){
  bonus *deletedElement;
  if (previous == NULL){
    deletedElement = iterator;
    iterator = iterator->next;
    bonuses = iterator; 
    delete(deletedElement);
   }
   else{
     previous->next = iterator->next;
     delete(iterator);
     iterator = previous->next;
   }
}

void collisions(){
  float partOfPlatform;
  if (ballPositionX + ballSize > SCR_WIDTH - 1){ 
    if(ballAccelerationX > 0)
      ballAccelerationX = -ballAccelerationX;
  }
  else if(ballPositionX - ballSize < 0){
    if(ballAccelerationX < 0){
      ballAccelerationX = -ballAccelerationX;
    }
  }
  if (ballPositionY + ballSize > SCR_HEIGHT - 1){
    setCells();
    brokenCellsNumber = 0;
    if(ballAccelerationY > 0)
      ballAccelerationY = - ballAccelerationY;
  }
  else if(ballPositionY - ballSize < 0) {
    if (ballAccelerationY < 0)
      ballAccelerationY = -ballAccelerationY;
  }
  if (ballPositionY > (platformPositionY - ballSize - stepLength) && ballPositionY < (platformPositionY - ballSize + stepLength)){
    if((ballPositionX + ballSize >= platformPositionX)&&(ballPositionX - ballSize <= platformPositionX + platformLength)){
      partOfPlatform = ((float)abs(ballPositionX - platformPositionX) / platformLength) - 0.5;
      ballAccelerationX = partOfPlatform * stepLength * 2; 
      ballAccelerationY = -ballAccelerationY;
    }
  } 
  for(int i = 0; i < cellsNumber; i++){
     if(!cells[i].isBroken){
        if((ballPositionY + ballSize + stepLength <= cells[i].rightDownY) && (ballPositionY + ballSize + stepLength >= cells[i].leftUpY) || (ballPositionY - ballSize - stepLength <= cells[i].rightDownY)&&(ballPositionY - ballSize - stepLength >= cells[i].leftUpY)){
         if((ballPositionX + ballSize + stepLength >= cells[i].leftUpX)&&(ballPositionX + ballSize + stepLength <= cells[i].rightDownX) || (ballPositionX - ballSize - stepLength >= cells[i].leftUpX)&&(ballPositionX - ballSize - stepLength <= cells[i].rightDownX)){
            cells[i].health--;
            if (cells[i].health == 0){
              cells[i].isBroken = true;
              brokenCellsNumber++;
              if (random(9) == 1){
                createNewBonus(i);
              }
            }
            if ((ballPositionY + stepLength >= cells[i].leftUpY)&&(ballPositionY - stepLength <= cells[i].rightDownY) && !destroyer) ballAccelerationX = -ballAccelerationX;
            else if(!destroyer) ballAccelerationY = -ballAccelerationY;
            break;
         }
       }
     }
   }
}

void moveBonuses(){
  if (bonuses != NULL){
    bonus *iterator = bonuses; 
    bonus *previous = NULL;
    while(iterator != NULL){
      if (iterator->positionY > SCR_HEIGHT){
        bonus *deletedElement;
  if (previous == NULL){
    deletedElement = iterator;
    iterator = iterator->next;
    bonuses = iterator; 
    delete(deletedElement);
   }
   else{
     previous->next = iterator->next;
     delete(iterator);
     iterator = previous->next;
    }
        bonusesNumber--;
        continue;
      }
      if(iterator->positionY > (platformPositionY - 3) && iterator->positionY < (platformPositionY + 3)){
        if((iterator->positionX + 2 >= platformPositionX)&&(iterator->positionX - 2 <= platformPositionX + platformLength)){
          switch(iterator->symbol[0]){
            case 'A': autopilot = true; autopilotTimer = millis(); break;
            case 'B': bigger = true; break;
            case 'S': smaller = true; break;
            case 'D': destroyer = true; destroyerTimer = millis(); break;
          }
          deleteBonus(previous, iterator);
          bonusesNumber--;
        }
      }
      iterator->positionY += 0.8;
      myOLED.print(iterator->symbol,iterator->positionX,iterator->positionY);
      previous = iterator;
      iterator = iterator->next;
    }
  }
}

void moveBall(){
  collisions();
  if (ballMoving){
    ballPositionX += ballAccelerationX;
    ballPositionY += ballAccelerationY;
  }
  if(destroyer){
    myOLED.setPixel(ballPositionX, ballPositionY);
    myOLED.setPixel(ballPositionX+1, ballPositionY+1);
    myOLED.setPixel(ballPositionX-1, ballPositionY+1);
    myOLED.setPixel(ballPositionX+1, ballPositionY-1);
    myOLED.setPixel(ballPositionX-1, ballPositionY-1); 
  }
  else{
    myOLED.drawCircle(ballPositionX, ballPositionY, ballSize); 
  }
}

void drawCells(){
  for(int i = 0; i < cellsNumber; i++){
    if (!cells[i].isBroken){ 
      myOLED.drawRect(cells[i].leftUpX, cells[i].leftUpY, cells[i].rightDownX, cells[i].rightDownY);
      if (cells[i].health == 2)  
        myOLED.drawRect(cells[i].leftUpX+1, cells[i].leftUpY+1, cells[i].rightDownX-1, cells[i].rightDownY-1);
      if (cells[i].health == 3)
        myOLED.drawRect(cells[i].leftUpX+2, cells[i].leftUpY+2, cells[i].rightDownX-2, cells[i].rightDownY-2);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //potentVal = analogRead(0);
  //platformPositionX = map(potentVal, 0, 1023, 1, SCR_WIDTH - platformLength);
  
  if (destroyer){
    if(millis() - destroyerTimer > 1000) destroyer = false;
  }
  if (smaller){
    if(platformLength > 10) platformLength -= 5;
    smaller = false;
  }
  if (bigger){
    if(platformLength < 40) platformLength += 5;
    bigger = false;
  }
  
  if (autopilot){
    platformPositionX = ballPositionX - random(platformLength);
    if (platformPositionX < 0 || platformPositionX + platformLength > SCR_WIDTH){  
      if (platformPositionX < 0) platformPositionX = 0;
      else platformPositionX = SCR_WIDTH - platformLength;
    }
    if(millis() - autopilotTimer > 3000){ 
      autopilotTimer = 0;
      ballMoving = true;
      autopilotTimer = millis();
      autopilot = false;
    }
  }
  else{
    if(autopilotTimer != 0){
      ballMoving = false;
      if(millis() - autopilotTimer < 400){
        if(millis() - autopilotTimer > 300) myOLED.print("AUTOPILOT OFF", CENTER, 40);
        else if(millis() - autopilotTimer > 200) myOLED.print("1", CENTER, 40);
        else if(millis() - autopilotTimer > 100) myOLED.print("2", CENTER, 40);
        else myOLED.print("3", CENTER, 40);
      }
      else{
        ballMoving = true;
        autopilotTimer = 0;
      }
    }
    potentVal = analogRead(0);
    platformPositionX = map(potentVal, 0, 1023, 1, SCR_WIDTH - platformLength);
  }
  myOLED.drawLine(platformPositionX, platformPositionY, platformPositionX + platformLength, platformPositionY);
  drawCells();
  moveBall(); 
  moveBonuses();
    myOLED.update();
    myOLED.clrScr();
  
  if (brokenCellsNumber == cellsNumber){
      levelCnangeAnimation();
      level++;
      if (level > 18) {
        level = 1;
        cellsNumber = 10;
      }
      if (level %3 == 1) cellsNumber += 10;  
      setCells();
      setBall();
      brokenCellsNumber = 0;
  }
}
