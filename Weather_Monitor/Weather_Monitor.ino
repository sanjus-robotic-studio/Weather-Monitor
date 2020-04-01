#include <DHT.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
 #include <ESP8266HTTPClient.h>
// Set these to run example.
#define DHTPIN 2
#define FIREBASE_HOST "<your project id>.firebaseio.com" //paste your project id in the place of <your project id>
#define FIREBASE_AUTH "........" //paste your secret here
#define WIFI_SSID "....."
#define WIFI_PASSWORD "......"
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);

void setup()
{
  // Debug console
  Serial.begin(115200);
  dht.begin();
  pinMode(D0,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
      {
    Serial.print(".");
    delay(500);
      }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

   }

void loop()
{
float humidityData = dht.readHumidity();
float celData = dht.readTemperature();
if (isnan(humidityData) || isnan(celData))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
Firebase.setFloat("Moisture",humidityData);
Firebase.setFloat("Temperature",celData);
delay(1000);            
}
