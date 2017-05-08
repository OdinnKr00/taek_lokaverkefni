#include <Servo.h>

Servo myservo;

int pos = 0;
int pos_adur;
int snua = 0;
int xPin = A1;
int yPin = A0;
int led = 6;
int xPosition = 0;
int yPosition = 0;
int buttonState = 0;
int stadsetning = 0;
int takki = 5;
int takkiSW_stada_adur = LOW;
int takkiSW_stada;
int ljosSW_stada = HIGH;
const int TrigPin = 2;
const int EchoPin = 3;
float cm; 

void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  pinMode(TrigPin,OUTPUT);
  pinMode(EchoPin,INPUT);
  pinMode(led, OUTPUT);
  pinMode(takki, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  buttonState = digitalRead(takki);
  Serial.print("Y:");
  Serial.println(yPosition);
  Serial.print("X:");
  Serial.println(xPosition);
  
  Serial.println(buttonState);
  takkiSW_stada = digitalRead(takki);
  if(takkiSW_stada == HIGH && takkiSW_stada_adur == LOW) {
    if(ljosSW_stada == HIGH) {
      ljosSW_stada = LOW;
    } else {
      ljosSW_stada = HIGH;
    }
  }
  takkiSW_stada_adur = takkiSW_stada;

  if(ljosSW_stada == HIGH){
    if (pos>=180){
      snua = 1;
    } else if (pos == 0){
      snua = 0; 
    }
  
    if (snua <= 0){
      pos++;
    } else {
      pos--;
    }
  }else if(ljosSW_stada == LOW){
    xPosition = analogRead(xPin);
    yPosition = analogRead(yPin);
    if (xPosition <= 400){
      pos++;
    } else if(xPosition >= 600) {
      pos--;
    }
  }
  Serial.println(pos);
  myservo.write(pos);    
  digitalWrite(TrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigPin,LOW);
  
  cm = pulseIn(EchoPin,HIGH)/58.0;  
  cm = (int(cm * 100.0))/100.0;

  if(cm < 20){
    Serial.println("-----------------------------------");
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }
  Serial.println(cm);
  delay(15);                       
}

  
