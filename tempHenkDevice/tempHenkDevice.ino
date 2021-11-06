#include <ESP8266WiFi.h>

#define SendKey 0  //Button to send data Flash BTN on NodeMCU

int port = 8888;  //Port number
WiFiServer server(port);

#include "MySSIDAndPassword"

const char* ssid  = STASSID;
const char* password = STAPSK;

#include "DHT.h"
#define DHTPIN D1

int count=0;

DHT dht(DHTPIN, DHT22); //Инициация датчика
//DHT dht(DHTPIN, DHT11);

void setup() {
  Serial.begin(9600);
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting server");
  server.begin();
  Serial.println("Starting DHT");
  dht.begin();
}
void loop() {
  WiFiClient client = server.available();

    if(client)
    {
      if(client.connected())
      {
        Serial.println("Client Connected");
        float h = dht.readHumidity(); 
       float t = dht.readTemperature(); 
       if (isnan(h) || isnan(t)) {
         Serial.println("Ошибка считывания");
         return;
       }
       client.print(t);
       Serial.print("Влажность: ");
       Serial.print(h);
       Serial.print(" %\t");
       Serial.print("Температура: ");
       Serial.print(t);
       Serial.println(" *C ");
      }
    client.stop();
    Serial.println("Client disconnected"); 
    }   
}
