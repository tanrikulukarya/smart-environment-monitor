#include <LiquidCrystal.h>

// 7 SEGMENT PINS
int aPin = 22;
int bPin = 23;
int cPin = 24;
int dPin = 25; 
int ePin = 26; 
int fPin = 27; 
int gPin = 28; 
int hPin = 29;
int GND1 = 33; 
int GND2 = 34; 
int GND3 = 35; 
int GND4 = 36;

// TEMP SENSOR
int lm35 = A4;

//BUZZER SENSOR
int buzzer = 5;

//POTENTIOMETER SENSOR  min 0 , max 1023
int pot = A8;

// LCD 
LiquidCrystal lcd(36, 37, 26, 27, 28, 29);
#define LcdRWPin 35
#define BackLight 31




void setup() {
    Serial.begin(9600);
    pinMode(aPin ,OUTPUT);
    pinMode(bPin ,OUTPUT);
    pinMode(cPin ,OUTPUT);
    pinMode(dPin ,OUTPUT);
    pinMode(ePin ,OUTPUT);
    pinMode(fPin ,OUTPUT);
    pinMode(gPin ,OUTPUT);
    pinMode(hPin ,OUTPUT);
    pinMode(GND1 ,OUTPUT);
    pinMode(GND2 ,OUTPUT);
    pinMode(GND3 ,OUTPUT);
    pinMode(GND4 ,OUTPUT);
    digitalWrite(aPin ,HIGH);
    digitalWrite(bPin ,HIGH);
    digitalWrite(cPin ,HIGH);
    digitalWrite(dPin ,HIGH);
    digitalWrite(ePin ,HIGH);
    digitalWrite(fPin ,HIGH);
    digitalWrite(gPin ,HIGH);
    digitalWrite(hPin ,HIGH);
    digitalWrite(GND1,HIGH);
    digitalWrite(GND2 ,HIGH);
    digitalWrite(GND3 ,HIGH);
    digitalWrite(GND4 ,HIGH);

}

void letterA(){
    digitalWrite(aPin ,HIGH);
    digitalWrite(bPin ,HIGH);
    digitalWrite(cPin ,HIGH);
    digitalWrite(fPin ,HIGH);
    digitalWrite(ePin ,HIGH);
    digitalWrite(gPin ,HIGH);
    digitalWrite(GND1 ,HIGH);
}

void letterC(){
    digitalWrite(aPin ,HIGH);
    digitalWrite(fPin ,HIGH);
    digitalWrite(ePin ,HIGH);
    digitalWrite(dPin ,HIGH);
    digitalWrite(GND1 ,HIGH);
}

void closeAll(){
    digitalWrite(aPin ,LOW);
    digitalWrite(bPin ,LOW);
    digitalWrite(cPin ,LOW);
    digitalWrite(dPin ,LOW);
    digitalWrite(ePin ,LOW);
    digitalWrite(fPin ,LOW);
    digitalWrite(gPin ,LOW);
    digitalWrite(hPin ,LOW);
    digitalWrite(GND1,LOW);
    digitalWrite(GND2 ,LOW);
    digitalWrite(GND3 ,LOW);
    digitalWrite(GND4 ,LOW);
}

int tempReader(){
  int sensorValue = analogRead(lm35);

  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = voltage * 100.0;

  Serial.println(temperature);

  return temperature;

  delay(1000);


}


int potReader(){
  int sensorValue = analogRead(A8);
  Serial.println(sensorValue);
  return sensorValue;

}

void buzzbuzzH(){
    digitalWrite(5,HIGH);
}

void buzzbuzzL(){
    digitalWrite(5,LOW);
}

void ledOn(){

  //#define LcdRWPin 35
  //#define BackLight 31
pinMode(LcdRWPin , OUTPUT);
digitalWrite(LcdRWPin,LOW);

pinMode(BackLight , OUTPUT);
digitalWrite(BackLight, HIGH); // LCD ışığı aç

lcd.begin(16, 2);


}

void loop() {
    closeAll();
    delay(1000);
    int potValue = potReader();
    int tempValue = tempReader();
    ledOn();

    if (tempValue > 20) {
        letterC();
        delay(1000);

        if (potValue > 600) {
            buzzbuzzH();
            delay(100);
            buzzbuzzL();
        }

    } else {
        letterA();
        delay(1000);
    }
}

