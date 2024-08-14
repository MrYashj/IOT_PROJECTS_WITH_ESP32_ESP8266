#define BLYNK_TEMPLATE_ID "TMPL3DYpHqP6f"
#define BLYNK_TEMPLATE_NAME "IOT WATER PLANT MONITOR SYSTEM"
#define BLYNK_AUTH_TOKEN "18v1NkZ-LdeiZnzgMBUESXOLi7xnrFwL"
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "TP-Link_F5D8";
char pass[] = "61446861";

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int moistureSensorPin = A0;
const int relayPin = D5;
const int buzzer = D0;
const int moistureDryThreshold = 800;


void setup() 
{
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  pinMode(relayPin, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(relayPin, HIGH);
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.print("  WATER PLANT");
  lcd.setCursor(0, 1);
  lcd.print(" MONITORING SYS ");
  delay(2000);
  lcd.clear();
}


void loop() {
  int moistureLevel = analogRead(moistureSensorPin);
  Blynk.run();
  Blynk.virtualWrite(V0,moistureLevel);

  lcd.setCursor(0, 0);
  lcd.print("Mois level:");
  lcd.setCursor(11,0);
  lcd.print("      "); 
  lcd.setCursor(11, 0);
  lcd.print(moistureLevel);

  Serial.print("Moisture level:");
  Serial.println(moistureLevel);
  delay(1000);

  if (moistureLevel >= moistureDryThreshold)
  {
    digitalWrite(relayPin, LOW);
    digitalWrite(buzzer, HIGH);
    Serial.println("Relay ON");
     lcd.setCursor(0, 1);
    lcd.print("Motor ON  ");
  }
  else
  {
    digitalWrite(relayPin, HIGH);
    digitalWrite(buzzer, LOW);
    Serial.println("Relay OFF");
    lcd.setCursor(0, 1);
    lcd.print("Motor OFF");
  }

delay(1000);
}
