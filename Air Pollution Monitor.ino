#include<ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(D5, D4, D3, D2, D1, D0);
const int aqsensor = A0;

WiFiClient client;
long myChannelNumber = 1933420;
const char myWriteAPIKey[] = "VYJRSAWOA5RQFKD5";
void setup()
{
  pinMode(D8, OUTPUT);
  pinMode (aqsensor, INPUT); // MQ135 is connected as INPUT to ESP-8266
  Serial.begin (115200);
  lcd.clear();              // clear lcd
  lcd.begin (16, 2);
  WiFi.begin("Chauhan", "sudheer7");
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected");
  ThingSpeak.begin(client);
}
void loop() {
  int ppm = analogRead(aqsensor); //read MQ135 analog outputs at A0 and store it in ppm

  Serial.print("Air Quality:");  //print message in serail monitor
  Serial.println(ppm);            //print value of ppm in serial monitor
  lcd.setCursor(0, 0);            // set cursor of lcd to 1st row and 1st column
  lcd.print("Air Quality : ");    // print message on lcd
  lcd.print(ppm); // print value of MQ135
  lcd.setCursor(0, 1);
  if (ppm < 180)
  {
    lcd.print("Safe Zone");
    digitalWrite(D8, LOW);
  }
  else
  {
    lcd.print("Danger Zone");
    digitalWrite(D8, HIGH);
  }
  delay(1000);
  ThingSpeak.writeField(myChannelNumber, 1, ppm, myWriteAPIKey);
  delay(100);
}
