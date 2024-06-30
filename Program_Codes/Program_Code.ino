#include <DHT11.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial sim800l(0, 1);
#define DHT11_PIN A1

DHT11 dht11(A1);
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
SoftwareSerial gsmSerial(10, 11);
void setup() {
  gsmSerial.begin(9600);
  lcd.begin(16, 2);
  sim800l.begin(9600);   
  Serial.begin(9600);  
}

void loop() {
  int ldr = analogRead(A0);
  int temperature = 0;
  int humidity = 0;
  int result = dht11.readTemperatureHumidity(temperature, humidity);

  lcd.setCursor(0, 0);
  lcd.print("VeraWeather");
  lcd.setCursor(0, 1);
  lcd.print("Light: ");
  lcd.print(ldr);
  lcd.print("     "); 
  delay(1000);

  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.print(temperature);

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);

  delay(500);
  Serial.println("Sending SMS...");              
  sim800l.print("AT+CMGF=1\r");                  
  delay(100);
  sim800l.print("AT+CMGS=\"+254759626842\"\r");  //Your phone number 
  delay(500);
  sim800l.print("SIM800l is working");       
  delay(500);
  sim800l.print((char)26);
  delay(500);
  sim800l.println();
  String temp = "Temperature: " + String(temperature);
  delay(500);
  Serial.println(temp);
  String lig = "Light: " + String(ldr);
  delay(500);
  Serial.println(lig);
  String hum = "Humidity: " + String(humidity);
  delay(500);
  Serial.println(hum);
  Serial.println("Text Sent.");
  delay(500);
  if (sim800l.available()){            
    Serial.write(sim800l.read()); 
  }                   
  String message = "Temp: " + String(temp) + "C, Humidity: " + String(humidity) + "%, Light: " + String(lig);
  
  // Send SMS
  gsmSerial.println("AT+CMGF=1"); 
  delay(1000);
  gsmSerial.println("AT+CMGS=\"+254759626842\""); 
  delay(1000);
  gsmSerial.println(message);
  delay(1000);
}



