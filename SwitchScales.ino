#include <HX711_ADC.h> 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

HX711_ADC LoadCell(4, 5);
LiquidCrystal_I2C lcd(0x27, 20, 2);

int led = 11;
int taree = 10;
int incrementPin = 6;
int decrementPin = 7;
int Number = 0;
float b = 0;
int c = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(taree, INPUT_PULLUP);
  pinMode(incrementPin, INPUT_PULLUP);
  pinMode(decrementPin, INPUT_PULLUP);
  LoadCell.begin();
  LoadCell.start(1000);
  LoadCell.setCalFactor(103);
  lcd.init();
  lcd.backlight();
}

void loop() {
  LoadCell.update();
  float i = LoadCell.getData();

  if (digitalRead(incrementPin) == LOW) {
    Number++;
    delay(200);
  }

  if (digitalRead(decrementPin) == LOW) {
    if (Number > 0) {
      Number--;
    }
    delay(200);
  }

  lcd.setCursor(3, 0);
  lcd.print(Number);
  delay(1);
  lcd.setCursor(8, 0);
  lcd.print("T=");
  b = ((i/1000)*Number); 
  if(b < 0) {
    b = 0; 
  }
  lcd.setCursor(11, 0);
  lcd.print(b, 2);
  lcd.print("   ");
  lcd.setCursor(0, 0);
  lcd.print("P=");
  float k = i / 1000;
  lcd.setCursor(8, 1);
  lcd.print(k , 2);
  lcd.print("KG ");
  lcd.setCursor(0, 1);
  lcd.print("Weight= ");
}
