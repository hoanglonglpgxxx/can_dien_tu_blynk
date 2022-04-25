#define BLYNK_TEMPLATE_ID "TMPLsLQ4UUMi"
#define BLYNK_DEVICE_NAME "Can Dien Tu"
#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <SimpleTimer.h>
 
WidgetLCD LCD(V2);
 
char auth[] = "QhFYuqC6nrZ32sSPw6IJwNCM6KEoHOZr"; //token ID Blynk
char ssid[] = "LongLe";
char pass[] = "Abc.2010@";
 
SimpleTimer timer;
 
String myString; // Dữ liệu hoàn chỉnh từ Arduino, bao gồm giá trị cảm biến
char rdata; // Các kí tự nhận được
String weight;
 
int firstVal;  
//Hàm này gửi … của Arduino(Arduino's up time) mỗi giây tới Virtual Pin(1)
//Ở trong phần mềm, đọc tần số của Widget(Widget's reading frequency) được set thành PUSH(cài đặt xem bao lâu thì //dữ liệu được gửi tới app Blynk)
void myTimerEvent()
{
  //Có thể gửi bất kì dữ liệu nào ở bất kì thời gian nào
  // Không thể gửi quá 10 giá trị mỗi giây
  Blynk.virtualWrite(V1, millis() / 1000);
}
 
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L,sensorvalue1); 
}
 
void loop()
{
   if (Serial.available() == 0 ) 
   {
  Blynk.run();
  timer.run(); // Khởi động Timer của Blynk
   }
  if (Serial.available() > 0 ) 
  {
    rdata = Serial.read(); 
    myString = myString+ rdata; 
   // Serial.print(rdata);
    if( rdata == '\n')
    {
Serial.println(myString);
weight = getValue(myString, ',', 0);
myString = "";
    }
  }
}
 
void sensorvalue1()
{
    LCD.clear();
    LCD.print(0,0,weight);
}
 
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
