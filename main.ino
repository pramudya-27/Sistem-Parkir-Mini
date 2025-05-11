#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo gateServo;

const int irSensorPin = 2;
const int closeAngle = 0;
const int openAngle = 90;
bool gateOpen = false;

void setup() {
  Serial.begin(9600);
  pinMode(irSensorPin, INPUT);
  gateServo.attach(9);
  lcd.init();
  lcd.backlight();
  gateServo.write(closeAngle);
  lcd.setCursor(0, 0);
  lcd.print("Parkir Penuh");
}

void loop() {
  int sensorValue = digitalRead(irSensorPin);

  if (sensorValue == LOW && !gateOpen) {
    Serial.println("Mobil Terdeteksi - Membuka Gate");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Silahkan Masuk");
    gateServo.write(openAngle);
    gateOpen = true;
    delay(5000);
  }
  else if (sensorValue == HIGH && gateOpen) {
    Serial.println("Menutup Gate");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Parkir Penuh");
    gateServo.write(closeAngle);
    gateOpen = false;
  }

  delay(100);
}
