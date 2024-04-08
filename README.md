# Weight Scaling with Arduino Pro Micro and Load Cell

This project demonstrates weight scaling using an Arduino Pro Micro and a load cell (HX711). It allows you to measure weight and display it on an LCD screen, with options to increment or decrement the displayed value.

## Hardware Setup

1. Connect your load cell to the Arduino Pro Micro:
   - Load cell pins to Arduino Pro Micro pins: 
     - Data pin to pin 4
     - Clock pin to pin 5

2. Connect the LCD screen to the Arduino Pro Micro using the I2C interface.

## Dependencies

- [HX711_ADC Library](https://github.com/olkal/HX711_ADC) - Library for interfacing the HX711 load cell amplifier with Arduino.
- [LiquidCrystal_I2C Library](https://github.com/johnrickman/LiquidCrystal_I2C) - Library for controlling LCD screens using the I2C bus.

Ensure you have both libraries installed in your Arduino IDE.

## Usage

1. Include the required libraries and define necessary variables:

```cpp
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

Initialize the hardware and libraries in the setup() function:

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

Continuously read data from the load cell and update the LCD display in the loop() function:

void loop() {
  LoadCell.update();
  float i = LoadCell.getData();

  // Increment or decrement the displayed value based on button presses
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

  // Update LCD display with weight and other information
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

Contributing
Contributions are welcome! If you have suggestions, feature requests, or find any issues, feel free to open an issue or pull request.

License
This project is licensed under the MIT License.


Make sure to replace "link-to-library" with the actual links to the HX711_ADC and LiquidCrystal_I2C libraries. Also, ensure you have a LICENSE file in your repository with the appropriate license text.
