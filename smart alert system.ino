#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int trigPin = 11;
const int echoPin = 12;
const int redLED = 8;
const int yellowLED = 9;
const int greenLED = 10;
const int buzzer = 7;
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Active");
  delay(1000);
}

void loop() {
  long duration;
  int distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print(" cm    ");

  if (distance > 100 || distance <= 0) {
    showSafe();
  } 
  else if (distance <= 100 && distance > 30) {
    showWarning();
  } 
  else if (distance <= 30) {
    showDanger();
  }

  delay(100); 
}

void showSafe() {
  digitalWrite(greenLED, HIGH);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);
  noTone(buzzer);
  lcd.setCursor(0, 1);
  lcd.print("SAFE Status     ");
}

void showWarning() {
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(redLED, LOW);
  noTone(buzzer);
  lcd.setCursor(0, 1);
  lcd.print("WARNING!!       ");
}

void showDanger() {
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, HIGH);
  lcd.setCursor(0, 1);
  lcd.print("DANGER!!        ");
  for (int hz = 600; hz < 1100; hz++) {
    tone(buzzer, hz);
    delay(2);
  }
  for (int hz = 1100; hz > 600; hz--) {
    tone(buzzer, hz);
    delay(2);
  }
}