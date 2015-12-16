// touch sensor to D3
// button to D4
const int pinTouch  = 3;
const int pinButton = 4;
const int pinLed    = 2;
const int potentiometer = A0;
const int pinLight = A1;
const int pinSound = A2;
int potValue = analogRead(potentiometer);
int lightValue = analogRead(pinLight);
int soundValue = analogRead(pinSound);
int counter = 0;
int delayCount = 5000;
unsigned long timerA;
unsigned long timerB;

#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;
int colorR = 255;
int colorG = 255;
int colorB = 255;

void setup() {
  Serial.begin(9600);
  pinMode(pinTouch, INPUT);
  pinMode(pinButton, INPUT);
  pinMode(potentiometer, INPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  initialize();
  delay(1000);
}
void initialize() {
        lcd.clear();
        lcd.print("Hold button to");
        lcd.setCursor(0,1);
        lcd.print("start game.");
        digitalWrite(13, LOW);
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);
        int counter = 0;
        int delayCount = 5000;
        return;
}

void gameOver() {
  lcd.clear();
  lcd.print("GAME OVER! ");
  lcd.print(counter);
  lcd.setCursor(0,1);
  lcd.print("turns completed");
  delay(3000);
  lcd.clear();
  lcd.print("Hold button to");
  lcd.setCursor(0,1);
  lcd.print("restart game.");
  counter = 0;
  delayCount = 5000;
  while (digitalRead(pinButton)) {
  loop();
  }
}
void loop() {
  // start countdown to start
  if (digitalRead(pinButton)) {
    digitalWrite(13, HIGH);
    delay(1000);
    if (digitalRead(pinButton)) {
      digitalWrite(12, HIGH);
      delay(1000);
      if (digitalRead(pinButton)) {
        digitalWrite(11, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);
        lcd.clear();
        lcd.print("Here We Go!");
        delay(1000);
        pickRandom();
      }
      else {
        digitalWrite(13, LOW);
        digitalWrite(12, LOW);
        digitalWrite(11, LOW);
      }
    }
    else {
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
    }
  }
  else {
    digitalWrite(13, LOW);
  }
}
void pickRandom() {
  int picker = random(5);
  if (picker == 0) {
    coverIt();
  }
  if (picker == 1) {
    turnIt();
  }
  if (picker == 2) {
    clapIt();
  }
  if (picker == 3) {
    pushIt();
  }
  if (picker == 4) {
    touchIt();
  }
}

void turnIt() {
  int potValue = analogRead(potentiometer);
  lcd.clear();
  lcd.print("Turn It!");
  delay(delayCount);
  if (abs(potValue - analogRead(potentiometer)) > 100) {
    counter = counter + 1;
    delayCount = delayCount - 250;
    digitalWrite(pinLed, HIGH);
    lcd.clear();
    lcd.print("Correct!");
    delay(500);
    digitalWrite(pinLed, LOW);
    pickRandom();
  }
  else {
    gameOver();
  }
}
void coverIt() {
  int lightValue = analogRead(pinLight);
  lcd.clear();
  lcd.print("Cover It!");
  timerA = millis();
  checkLight();
}
void clapIt() {
  int soundValue = analogRead(pinSound);
  lcd.clear();
  lcd.print("Clap It!");
  timerA = millis();
  checkSound();
}
void touchIt() {
  lcd.clear();
  lcd.print("Touch It!");
  timerA = millis();
  checkTouch();
}
void pushIt() {
  lcd.clear();
  lcd.print("Push It!");
  timerA = millis();
  checkPush();
}
void checkLight() {
  timerB = millis();
  if (timerB - timerA < delayCount) {
    if (analogRead(pinLight) < 400) {
      counter = counter + 1;
      delayCount = delayCount - 250;
      digitalWrite(pinLed, HIGH);
      lcd.clear();
      lcd.print("Correct!");
      delay(500);
      digitalWrite(pinLed, LOW);
      delay(2000);
      pickRandom();
    }
    else {
      checkLight();
    }
  }
  else { 
    gameOver();
   }
}
void checkSound() {
  timerB = millis();
//  Serial.println(analogRead(pinSound));
  if (timerB - timerA < delayCount) {
    if (analogRead(pinSound) > 900) {
      counter = counter + 1;
      delayCount = delayCount - 250;
      digitalWrite(pinLed, HIGH);
      lcd.clear();
      lcd.print("Correct!");
      delay(500);
      digitalWrite(pinLed, LOW);
      delay(2000);
      pickRandom();
    }
    else {
      checkSound();
    }
  }
  else { 
    gameOver();
   }
}
void checkTouch() {
  timerB = millis();
  if (timerB - timerA < delayCount) {
    if (digitalRead(pinTouch)) {
      counter = counter + 1;
      delayCount = delayCount - 250;
      digitalWrite(pinLed, HIGH);
      lcd.clear();
      lcd.print("Correct!");
      delay(500);
      digitalWrite(pinLed, LOW);
      delay(2000);
      pickRandom();
    }
    else {
      checkTouch();
    }
  }
  else { 
    gameOver();
   }
}
void checkPush() {
  timerB = millis();
  if (timerB - timerA < delayCount) {
    if (digitalRead(pinButton)) {
      counter = counter + 1;
      delayCount = delayCount - 250;
      digitalWrite(pinLed, HIGH);
      lcd.clear();
      lcd.print("Correct!");
      delay(500);
      digitalWrite(pinLed, LOW);
      delay(2000);
      pickRandom();
    }
    else {
      checkPush();
    }
  }
  else { 
    gameOver();
   }
}

