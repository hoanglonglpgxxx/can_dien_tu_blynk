#include <SoftwareSerial.h> 
#include <LiquidCrystal_I2C.h> 
#include <HX711_ADC.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2); 
HX711_ADC LoadCell (3,2); 
SoftwareSerial nodemcu(7, 8); 
void setup() { 
nodemcu.begin(9600); 
LoadCell.begin(); 
LoadCell.start(2000); 
LoadCell.setCalFactor (999.0); 
lcd.init(); 
lcd.backlight(); 
} void loop() { 
LoadCell.update (); 
float i = LoadCell.getData();
 if (i<=1000) { 
lcd.setCursor(0, 0); 
lcd.print(" DO AN 2 "); 
lcd.setCursor(0, 1); 
lcd.print ("WEIGHT:"); 
lcd.print(i); lcd.print(" G "); 
nodemcu.println(i); 
delay(100); 
} if (i>1000) { 
lcd.setCursor(1, 0);
 lcd.print("can qua tai "); 
lcd.setCursor(0, 1); 
lcd.print ("WEIGHT:"); 
lcd.print(i); 
nodemcu.print("can qua tai "); 
nodemcu.println(i); delay(100); 
}
 }
