#include <LiquidCrystal.h>
#include "DHT.h"
#define DHTTYPE DHT11
/*
Parameter
 */
int trig = 9, echo = 8;

char humid_str [16];
char temper_str [16];
char distance_str [16];

DHT dht(7, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  /*
  HC-Sr04
   */
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  /*
  DHT sensor init
   */
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
  /*
  LCD
   */
  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  lcd.print("hello  world!!");
  delay(3000);
  lcd.clear();
}

void loop() {
  delay(800);
  lcd.clear();
  //
  float duration, distance;
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = ((float)(duration * 340) / 10000) / 2; // calulate
  //
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  //Error
  if (isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
  }
  /*
  Show sensor's data to Lcd
   */
  lcd.setCursor(0, 0);
  sprintf(humid_str, "HUMI:%d",h);
  lcd.print(humid_str);
  sprintf(temper_str, "  TEMP:%d",t);
  lcd.print(temper_str);
  lcd.setCursor(2,1);
  sprintf(temper_str, "Distance: %d",(int)distance);
  lcd.print(temper_str);
}
