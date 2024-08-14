#define BLYNK_TEMPLATE_ID "TMPL3jf5PI-g7"
#define BLYNK_TEMPLATE_NAME "IOT WHETHER AND AIR MONITORING"
#define BLYNK_AUTH_TOKEN "eksEkugQ0uRcqd0tfMGCMZOw90BnRroO"

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "TP-Link_F5D8";
char pass[] = "61446861";


#include <DHT.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(D5, DHT11);


int gas = A0;
int sensorThreshold = 100;
int buz=D0;
void setup() {
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  dht.begin();
   pinMode(buz,OUTPUT);
   digitalWrite(buz,HIGH);
    delay(1000);
    digitalWrite(buz,LOW);

    lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();  // Turn on the backlight
  lcd.print("Air and whether");
  lcd.setCursor(0, 1);
  lcd.print(" Monitoring Sys ");
  delay(2000);
  lcd.clear();

}

void loop() {

  Blynk.run();

  
  int gasValue = analogRead(gas);
  Blynk.virtualWrite(V2, gasValue);
   
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // in Celsius

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
   
  Serial.println("temp: ");
  Serial.println(t);
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.setCursor(5,0);
  lcd.print(t);
  /*lcd.setCursor(6, 1);
  lcd.write(1); // Display degree symbol
  lcd.setCursor(7, 1);
  lcd.print("C");*/

  delay(1000);

  Serial.println("Humidity: ");
  Serial.println(h);

  lcd.setCursor(10,0);
  lcd.print("Hum:");
  lcd.setCursor(14,0);
  lcd.print(h);
  delay(1000);

  lcd.setCursor(0,1);
  lcd.print("Gas Value: ");
  lcd.print(gasValue);
  delay(1000);

  Serial.println("Gas Value: ");
  Serial.println(gasValue);

  if (gasValue <=1000)
  {
    lcd.setCursor(0,1);
    lcd.print("Fresh Air");
    Serial.println("Fresh Air");
  }
  else 
  {
    lcd.setCursor(0, 1);
    lcd.print("Bad Air  ");
    digitalWrite(buz,HIGH);
    delay(2000);
    digitalWrite(buz,LOW);
    Serial.println("Bad Air");
  }
  if(h>=70)
  {
    digitalWrite(buz,HIGH);
  }
  else
  {
    digitalWrite(buz,LOW);
  }

  if(t>=40)
  {
    digitalWrite(buz,HIGH);
  }
  else
  {
    digitalWrite(buz,LOW);
  }
}
