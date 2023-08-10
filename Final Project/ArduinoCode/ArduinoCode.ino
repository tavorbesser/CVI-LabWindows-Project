/*  Arduino Code
   Tavor Besser - 316475995
   Elinoy Rabian - 206841835
*/

#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x3F, 16 column and 2 rows
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  dht.begin();     // initialize the sensor
  lcd.init();      // initialize the lcd
  lcd.backlight(); // open the backlight 
  // Print On The Lcd : Tavor's And Elinoy's Project
  lcd.setCursor(2, 0);
  lcd.print("~~ Tavor's ~~");
  delay(1000); // wait a few seconds 
  lcd.clear();

  lcd.setCursor(4, 0);
  lcd.print("~~ And ~~");
  delay(1000); // wait a few seconds 
  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print("~~ Elinoy's ~~");
  delay(1000); // wait a few seconds
  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print("~~ Project ~~");
  delay(1000); // wait a few seconds  
  lcd.clear();
}
void loop()
{
  delay(2000); // wait a few seconds  

  float humidity  = dht.readHumidity();    // read humidity
  float temperature = dht.readTemperature(); // read temperature
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" Humidity: ");
    Serial.print(humidity);
    lcd.clear();
  // check if any reads failed
  if(isnan(humidity) || isnan(temperature)) {
    lcd.setCursor(0, 0);
    lcd.print("Failed");
  } else {
    
    lcd.setCursor(0, 0);  // start to print at the first row
    lcd.print("Temp: ");
    lcd.print(temperature);     // print the temperature
    lcd.print((char)223); // print ° character
    lcd.print("C");
   
    lcd.setCursor(0, 1);  // start to print at the second row
    lcd.print("Humi: ");
    lcd.print(humidity);      // print the humidity
    lcd.print("%");
  }
}
