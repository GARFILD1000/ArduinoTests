#define LOG_OUT 1 // use the log output function
#define FHT_N 64  // set to 256 point fht
#include <FHT.h>
#define LATCHPIN 10
#define CLOCKPIN 12
#define DATAPIN 11
#define CLOCK 9
#define RESET 8
#define AUDIOPIN A7       
#define INPUT_GAIN 1.5    // коэффициент усиления входного сигнала
#define LOW_PASS 35       // нижний порог чувствительности шумов (нет скачков при отсутствии звука)
#define MAX_COEF 1.1      // коэффициент, который делает "максимальные" пики чуть меньше максимума, для более приятного восприятия
#define NORMALIZE 0 

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

//
//int pictureSmile[10] = {
//  strtol("0111111110",NULL,2),
//  strtol("1000000001",NULL,2),
//  strtol("1011001101",NULL,2),
//  strtol("1011001101",NULL,2),
//  strtol("1000000001",NULL,2),
//  strtol("1000000001",NULL,2),
//  strtol("1010000101",NULL,2),
//  strtol("1001111001",NULL,2),
//  strtol("1000000001",NULL,2),
//  strtol("0111111110",NULL,2)
//};
//
//
//int pictureAll[10] = {
//  strtol("1111111111",NULL,2),
//  strtol("1111111111",NULL,2),
//  strtol("1111111111",NULL,2),
//  strtol("1111111111",NULL,2),
//  strtol("1111111111",NULL,2),
//  strtol("1111111111",NULL,2),
//  strtol("1111111111",NULL,2),
//  strtol("1111111111",NULL,2),
//  strtol("1111111111",NULL,2),
//  strtol("1111111111",NULL,2)
//};

int pictureEmpty[10] = {0,0,0,0,0,0,0,0,0,0};
unsigned char equalizerVolumes[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int volumesBitmap[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup(){
  pinMode(A7, INPUT);
  pinMode(DATAPIN,OUTPUT);
  pinMode(CLOCKPIN,OUTPUT);
  pinMode(LATCHPIN,OUTPUT);
  pinMode(CLOCK,OUTPUT);
  pinMode(RESET,OUTPUT);
  digitalWrite(RESET,HIGH);
  digitalWrite(RESET,LOW);   
  //analogReference(EXTERNAL);  
  Serial.begin(9600);

  sbi(ADCSRA, ADPS2);
  cbi(ADCSRA, ADPS1);
  sbi(ADCSRA, ADPS0);

  analogReference(EXTERNAL);
}

void tenBitsOut(int value){
  for(int i = 0; i < 10; i++){
    digitalWrite(DATAPIN, !((value >> i) & 0x1));
    digitalWrite(CLOCKPIN, HIGH);
    digitalWrite(CLOCKPIN, LOW);
    digitalWrite(DATAPIN, LOW);
  }
}

char im[64], data[64];
int  val;
byte h;
void loop() {

    for (int i = 0 ; i < FHT_N ; i++) {
    int sample = analogRead(AUDIOPIN);
    fht_input[i] = sample; // put real data into bins
  }
  fht_window();  // window the data for better frequency response
  fht_reorder(); // reorder the data before doing the fht
  fht_run();     // process the data in the fht
  fht_mag_log(); // take the output of the fht

  for (int curBin = 0; curBin < FHT_N / 2; ++curBin) {
    if (fht_log_out[curBin] < LOW_PASS) fht_log_out[curBin] = 0;
    //fht_log_out[curBin] = (float)fht_log_out[curBin] * INPUT_GAIN;

    //if (NORMALIZE) fht_log_out[curBin] = (float)fht_log_out[curBin] / ((float)1 + (float)curBin / 128);


  }

  for (int i=0; i<10; i++) {
    h = fht_log_out[i*3] + fht_log_out[i*3 + 1] + fht_log_out[i*3 + 2] + fht_log_out[i*3 + 3];   // вычисляем среднее 
    h = map(h, 0, 255, 0, 9);                              // делаем remap для LoL
    if (equalizerVolumes[i] < h){
      equalizerVolumes[i] = h;
    }
    else if (equalizerVolumes[i] > 0){
      equalizerVolumes[i]--;
    }
  }
  
   TIMSK0 = 1;
  volumesToBitmap();
  drawBitmap(volumesBitmap, 20);
   TIMSK0 = 0; 
}

void calculateEqualizer(){
  
}

void drawEqualizer(){
}

void volumesToBitmap(){
  for (int i = 0; i < 10; i++){
    volumesBitmap[i] = 0;
  }
  for (int i = 0; i < 10; i++){
    for(int j = 0; j < equalizerVolumes[9-i]; j++){
      volumesBitmap[9-j] |= 0x1 << i;
    }
  }
}

int drawBitmap(int *bitmap, int timeToDisplay){
  long timeMilliseconds = millis();  
  while(millis() - timeMilliseconds < timeToDisplay){
    digitalWrite(RESET,HIGH);
    digitalWrite(RESET,LOW);
    for(int i = 0; i < 10; i++){
      digitalWrite(LATCHPIN, LOW);
      tenBitsOut(bitmap[i]);
      digitalWrite(LATCHPIN, HIGH);    
      digitalWrite(CLOCK, HIGH);
      digitalWrite(CLOCK, LOW);
    }
  }
}
