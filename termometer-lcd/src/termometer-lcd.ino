#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);   // byt till 0x3F om skarmen ar tom

OneWire oneWire(2);                    // DS18B20 signal pa pin 2
DallasTemperature sensors(&oneWire);

void setup() {
  lcd.init();
  lcd.backlight();
  sensors.begin();
  lcd.print("Temperatur:");
}

void loop() {
  sensors.requestTemperatures();              // be sensorn mata
  float tempC = sensors.getTempCByIndex(0);   // las forsta sensorn

  lcd.setCursor(0, 1);                         // rad 2
  lcd.print(tempC, 1);                         // en decimal
  lcd.print((char)223);                        // grad-tecken
  lcd.print("C   ");                           // extra mellanslag rensar gamla siffror

  delay(1000);                                 // uppdatera varje sekund
}
