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

//LDR
int ldr = A11;

//RELAY
int relay = 6;


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

    pinMode(buzzer, OUTPUT);
    pinMode(relay,OUTPUT);
    digitalWrite(relay, LOW);

    ledSetup();
    

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
    digitalWrite(aPin, LOW);
    digitalWrite(bPin, LOW);
    digitalWrite(cPin, LOW);
    digitalWrite(dPin, LOW);

    // e,f,g,h LCD ile ortak 

    digitalWrite(GND1, LOW);
    digitalWrite(GND2, LOW);
    digitalWrite(GND3, LOW);
    digitalWrite(GND4, LOW);
}

int tempReader(){
  int sensorValue = analogRead(lm35);

  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = voltage * 100.0;

  Serial.println(temperature);

  return (int)temperature;

}

int ldrReader(){
  int sensorValue = analogRead(ldr);
  return (int)sensorValue;
}

void relayOpener(){
  digitalWrite(relay , HIGH);
}

void relayCloser(){
  digitalWrite(relay , LOW);
}




int potReader(){
  int sensorValue = analogRead(A8);
  Serial.println(sensorValue);
  return sensorValue;

}

void buzzbuzzH(){
    digitalWrite(buzzer,HIGH);
}

void buzzbuzzL(){
    digitalWrite(buzzer,LOW);
}

void ledSetup(){

    pinMode(LcdRWPin , OUTPUT);
    digitalWrite(LcdRWPin,LOW);

    pinMode(BackLight , OUTPUT);
    digitalWrite(BackLight, HIGH); // LCD ışığı aç

    lcd.begin(16, 2);

}

void loop() {
   
    int potValue = potReader();
    int tempValue = tempReader();
    int ldrValue = ldrReader();

    if(ldrValue > 700){
      relayOpener();
    }else{
      relayCloser();
    }

    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(tempValue);
    lcd.print(" C");
    lcd.setCursor(0, 1);
    lcd.print("Dimness: ");
    lcd.print(ldrValue);
    lcd.setCursor(10, 0);
    lcd.print("P=");
    lcd.print(potValue);



    closeAll();

    if (tempValue > 20) {
        letterC();

        if (potValue > 600) {
    buzzbuzzH();

    for(int i=0; i<10; i++){
        closeAll();
        letterC();
        delay(10);
    }

    buzzbuzzL();
}

    } else {
        letterA();
    }
    delay(1000);
}

