#include <DHT11.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial sim800l(0, 1);
#define DHT11_PIN A1

DHT11 dht11(A1);
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  sim800l.begin(9600);   //Module baude rate, this is on max, it depends on the version
  Serial.begin(9600);  
}

void loop() {
  int ldr = analogRead(A0);
  int temperature = 0;
  int humidity = 0;
  int result = dht11.readTemperatureHumidity(temperature, humidity);

  // Print the LDR value to the LCD.
  lcd.setCursor(0, 0);
  //lcd.print("LDR: ");
  //lcd.print(ldr);
  lcd.print("Temperature: ");
  lcd.print(temperature);

  // Print the humidity value to the LCD.
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);

  // Delay for a short period to avoid flickering
  delay(500);
  //SendSMS();       
  Serial.println("Sending SMS...");               //Show this message on serial monitor
       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  delay(100);
  sim800l.print("AT+CMGS=\"+919080659745\"\r");  //Your phone number don't forget to include your country code, example +212123456789"
  delay(500);
  sim800l.print("SIM800l is working");       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  delay(500);
  sim800l.print((char)26);// (required according to the datasheet)
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
  if (sim800l.available()){            //Displays on the serial monitor if there's a communication from the module
    Serial.write(sim800l.read()); 
  }                   //And this function is called

}

void SendSMS()
{
  

}
/* Code for the voltage readings or smth
#include <LiquidCrystal.h>
#include <DHT.h>
#include <SoftwareSerial.h>

// Initialize the LCD with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Define the pin for the DHT11 sensor
#define DHTPIN A1
#define DHTTYPE DHT11

// Define the pins for the GSM module
#define RX 10
#define TX 11

// Create a DHT object
DHT dht(DHTPIN, DHTTYPE);

// Create a SoftwareSerial object for the GSM module
SoftwareSerial gsmSerial(RX, TX);

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);

  // Initialize the serial communication
  Serial.begin(9600);
  delay(500);
  Serial.println("Welcome to Microdigisoft");
  delay(500);
  Serial.println("DHT Humidity & Temperature Sensor");
  delay(1000); // Wait before accessing sensor

  // Initialize the DHT sensor
  dht.begin();

  // Initialize the GSM module
  gsmSerial.begin(9600);
  delay(1000);

  // Test the GSM module
  gsmSerial.println("AT");
  delay(1000);
  gsmSerial.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);
  gsmSerial.println("AT+CNMI=1,2,0,0,0"); // Configure the module to show SMS through the serial port
  delay(1000);
}

void loop() {
  // Read values from the LDR and DHT11 sensor
  int ldr = analogRead(A0);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the LDR value to the LCD
  lcd.setCursor(0, 0);
  lcd.print("LDR: ");
  lcd.print(ldr);

  // Print the humidity value to the LCD
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");

  // Prepare the message to be sent
  String message = "Temp: " + String(temperature) + "C\n";
  message += "Humidity: " + String(humidity) + "%\n";
  message += "Light: " + String(ldr);

  // Print the message to the serial monitor for debugging
  Serial.println(message);

  // Send the message via GSM module
  sendSMS("RECIPIENT_PHONE_NUMBER", message);

  // Delay for a short period
  delay(60000); // Delay for 1 minute before sending the next message
}

void sendSMS(String number, String message) {
  gsmSerial.println("AT+CMGS=\"" + number + "\"");
  delay(100);
  gsmSerial.println(message);
  delay(100);
  gsmSerial.write(26); // ASCII code of CTRL+Z to send the message
  delay(1000);
}

Code for gsm*/

