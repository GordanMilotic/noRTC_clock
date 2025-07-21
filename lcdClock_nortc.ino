#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int btnSat = 2;
const int btnMin = 3;
const int btnSec = 4;
const int btnPause = 5;
bool paused = false;
unsigned long previousMillis = 0;
const long interval = 1000;
int sekunde = 0;
int minute = 0;
int sati = 0;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(btnSat, INPUT_PULLUP);
  pinMode(btnMin, INPUT_PULLUP);
  pinMode(btnSec, INPUT_PULLUP);
  pinMode(btnPause, INPUT_PULLUP);

  lcd.setCursor(0, 0);
  delay(2000);
  lcd.clear();
}

void loop() {
  if (digitalRead(btnSat) == LOW) {
    sati++;
    if (sati >= 24) sati = 0;
    delay(200);
  }

  if (digitalRead(btnMin) == LOW) {
    minute++;
    if (minute >= 60) minute = 0;
    delay(200);
  }

  if (digitalRead(btnSec) == LOW) {
    sekunde++;
    if (sekunde >= 60) sekunde = 0;
    delay(200);
  }

  if (digitalRead(btnPause) == LOW) {
    paused = !paused;
    delay(300);
  }

  unsigned long currentMillis = millis();
  if (!paused && (currentMillis - previousMillis >= interval)) {
    previousMillis = currentMillis;
    sekunde++;

    if (sekunde >= 60) {
      sekunde = 0;
      minute++;
    }

    if (minute >= 60) {
      minute = 0;
      sati++;
    }
    if (sati >= 24) {
      sati = 0;
    }
  }
  lcd.setCursor(3, 0);
  lcd.print("Che ore sono?");

  lcd.setCursor(6, 1);
  if (sati < 10) lcd.print("0");
  lcd.print(sati);
  lcd.print(":");
  if (minute < 10) lcd.print("0");
  lcd.print(minute);
  lcd.print(":");
  if (sekunde < 10) lcd.print("0");
  lcd.print(sekunde);
}
