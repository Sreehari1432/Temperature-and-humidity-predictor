#define BLYNK_TEMPLATE_ID "TMscvPLq3vziMRnadw"
#define BLYNK_TEMPLATE_NAME "Temperature And Humidity esp32"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

// WiFi Credentials
const char* ssid = "Praveen's S23";
const char* password = "123";

// Blynk Authentication Token
char auth[] = "145tyudQggeArC1Dd-Wl_YEvFihMWFxzq";


#define DHTPIN 27
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_PCF8574 lcd(0x27);

BlynkTimer timer;

// Read DHT11 and send data to Blynk
void sendSensorData() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (!isnan(temperature) && !isnan(humidity)) {
        Blynk.virtualWrite(V0, temperature);  // Send temperature to V0
        Blynk.virtualWrite(V1, humidity);  // Send humidity to V1
        Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
        Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Temp: "); lcd.print(temperature); lcd.print(" C");
        lcd.setCursor(0, 1);
        lcd.print("Humidity: "); lcd.print(humidity); lcd.print(" %");

    } else {
        Serial.println("Failed to read from DHT sensor!");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("DHT Read Error");
    }
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Wire.begin(21, 22);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");

    Blynk.begin(auth, ssid, password);
    dht.begin();

    lcd.begin(16, 2);
    lcd.setBacklight(255);
    lcd.print("Initializing...");

    timer.setInterval(5000L, sendSensorData);  // Send data every 5 seconds
}

void loop() {
    Blynk.run();
    timer.run();
}
