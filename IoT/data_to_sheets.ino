#include "WiFi.h"
#include <HTTPClient.h>
#include "DHT.h"
//----------------------------------------

// Defining LED PINs on the ESP32 Board.
#define On_Board_LED_PIN  2

// Defines the DHT11 PIN and DHT sensor type.
#define DHTPIN  27
#define DHTTYPE DHT11

const char* ssid = "Praveen's S23";  //--> Your wifi's ssid
const char* password = "hellothere"; //--> Your wifi password

// Google script Web_App_URL.
String Web_App_URL = "https://script.google.com/macros/s/Agsggsgseere3qwgswjTMYtfAJ_8XmJdxnSMrPXPdWlZVNV8ieZST5xeqzHZsrKNJwyLf-HPA/exec";

String Status_Read_Sensor = "";
float Temp;
int Humd;

// Initialize DHT as dht11.
DHT dht11(DHTPIN, DHTTYPE);

void Getting_DHT11_Sensor_Data() {

  Humd = dht11.readHumidity();
  // Read temperature as Celsius (the default)
  Temp = dht11.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(Humd) || isnan(Temp)) {
    Serial.println();
    Serial.println(F("Failed to read from DHT sensor!"));
    Serial.println();

    Status_Read_Sensor = "Failed";
    Temp = 0.00;
    Humd = 0;
  } else {
    Status_Read_Sensor = "Success";
  }

  Serial.println();
  Serial.println("-------------");
  Serial.print(F("Status_Read_Sensor : "));
  Serial.print(Status_Read_Sensor);
  Serial.print(F(" | Humidity : "));
  Serial.print(Humd);
  Serial.print(F("% | Temperature : "));
  Serial.print(Temp);
  Serial.println(F("°C"));
  Serial.println("-------------");
}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println();
  delay(1000);

  pinMode(On_Board_LED_PIN, OUTPUT);

  Serial.println();
  Serial.println("-------------");
  Serial.println("WIFI mode : STA");
  WiFi.mode(WIFI_STA);
  Serial.println("-------------");

  Serial.println();
  Serial.println("------------");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  int connecting_process_timed_out = 20;
  connecting_process_timed_out = connecting_process_timed_out * 2;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(On_Board_LED_PIN, HIGH);
    delay(250);
    digitalWrite(On_Board_LED_PIN, LOW);
    delay(250);
    if (connecting_process_timed_out > 0) connecting_process_timed_out--;
    if (connecting_process_timed_out == 0) {
      delay(1000);
      ESP.restart();
    }
  }

  digitalWrite(On_Board_LED_PIN, LOW);
  
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("------------");

  delay(100);

  Serial.println();
  Serial.println("DHT11 Begin");
  Serial.println();
  delay(1000);
  
  dht11.begin();

  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:

  Getting_DHT11_Sensor_Data();
  
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(On_Board_LED_PIN, HIGH);

    // Create a URL for sending or writing data to Google Sheets.
    String Send_Data_URL = Web_App_URL + "?sts=write";
    Send_Data_URL += "&srs=" + Status_Read_Sensor;
    Send_Data_URL += "&temp=" + String(Temp);
    Send_Data_URL += "&humd=" + String(Humd);

    Serial.println();
    Serial.println("-------------");
    Serial.println("Send data to Google Spreadsheet...");
    Serial.print("URL : ");
    Serial.println(Send_Data_URL);


      HTTPClient http;

      http.begin(Send_Data_URL.c_str());
      http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

      int httpCode = http.GET(); 
      Serial.print("HTTP Status Code : ");
      Serial.println(httpCode);

      String payload;
      if (httpCode > 0) {
        payload = http.getString();
        Serial.println("Payload : " + payload);    
      }
      
      http.end();
    
    digitalWrite(On_Board_LED_PIN, LOW);
    Serial.println("-------------");
  }

  delay(10000);
}
