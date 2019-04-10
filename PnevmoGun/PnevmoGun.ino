#define relayPin 2
int delayTime = 100;
int openTime = 18;
bool shooting = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(relayPin, OUTPUT);
  pinMode(A0, INPUT);
  digitalWrite(relayPin, LOW);
  pinMode(3, INPUT);
}

void loop() {
  if(digitalRead(3) == HIGH){
    int shootingSpeed = analogRead(A0);
    if (shootingSpeed > 100 || !shooting){
      shooting = true;
      delayTime = map(shootingSpeed, 0, 1024, 150, 50);
      
      digitalWrite(relayPin, HIGH);
      delay(openTime);
      digitalWrite(relayPin, LOW);
      analogWrite(A5, map(shootingSpeed, 0, 1024, 0, 255));
      delay(delayTime);
      analogWrite(A5, 0);
    }
  }
  else{
    shooting = false;
  }
}
