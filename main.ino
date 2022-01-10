#include <Arduino.h>
#include <Wire.h>
#include <LIDARLite.h>

LIDARLite myLidarLite;

#define moteurD_Sens1 45
#define moteurD_Sens2 44

#define moteurG_Sens1 33
#define moteurG_Sens2 32

#define LedPIN 52

bool ledState = LOW;
unsigned long previousLedTimer = 0;
unsigned long ledInterval = 1000;


void forward(int timer){
  digitalWrite(moteurD_Sens2, HIGH);
  digitalWrite(moteurD_Sens1, LOW);
  digitalWrite(moteurG_Sens2, HIGH);
  digitalWrite(moteurG_Sens1, LOW);
  delay(timer);
}

void backwards(int timer){
  digitalWrite(moteurD_Sens2, LOW);
  digitalWrite(moteurD_Sens1, HIGH);
  digitalWrite(moteurG_Sens2, LOW);
  digitalWrite(moteurG_Sens1, HIGH);
  delay(timer);
}

void turnLeft(int timer){
  digitalWrite(moteurD_Sens2, HIGH);
  digitalWrite(moteurD_Sens1, LOW);
  digitalWrite(moteurG_Sens2, LOW);
  digitalWrite(moteurG_Sens1, HIGH);
  delay(timer);
}

void turnRight(int timer){
  digitalWrite(moteurD_Sens2, LOW);
  digitalWrite(moteurD_Sens1, HIGH);
  digitalWrite(moteurG_Sens2, HIGH);
  digitalWrite(moteurG_Sens1, LOW);
  delay(timer);
}

void stop(){
  digitalWrite(moteurD_Sens2, LOW);
  digitalWrite(moteurD_Sens1, LOW);
  digitalWrite(moteurG_Sens2, LOW);
  digitalWrite(moteurG_Sens1, LOW);
}

void runLed(){
 
  unsigned long ledTimer = millis();

  if (ledTimer - previousLedTimer >= ledInterval) {
    previousMillis = currentMillis;
    digitalWrite(LedPIN, !ledState);
  }
  
}

void setup() {
  pinMode(LedPIN, OUTPUT);
  pinMode(moteurD_Sens1, OUTPUT);
  pinMode(moteurD_Sens2, OUTPUT);
  Serial.begin(9600);
  myLidarLite.begin(0, true);
  myLidarLite.configure(0);
  stop();
  delay(100); 
}

void loop() {
  runLed();
  if(myLidarLite.distance() > 30  ){
    forward(250);
  } else {
    backwards(5);
    stop();
    delay(99999);
  }
}
