#include "DHT.h"
#define DHTTYPE DHT11
#define dht_pin D1
#define pinDO D2
#define pinAO A0

int DataDigital, DataAnalog;
DHT dht(dht_pin,DHTTYPE);

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

//INFORMASI JARINGAN DAN THINGSPEAK
char ssid[] = "BEBAS TETRING";
char pass[] = "12345678";
const char* apikey = "U424HS9PYIUB9TIP"; //write key
const long channelID = 1619227;
WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode (pinDO, INPUT);
  pinMode (pinAO, INPUT);
  dht.begin();
  delay (10);
  Serial.println("connected");
  WiFi.begin(ssid,pass);
  ThingSpeak.begin(client);
}

void loop() {
  DataDigital = digitalRead(pinDO);
  DataAnalog = analogRead(pinAO);
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  //PEMBUATAN FIELD
  ThingSpeak.writeField(channelID, 1, t, apikey);
  ThingSpeak.writeField(channelID, 2, h, apikey);
  ThingSpeak.writeField(channelID, 3, DataAnalog, apikey);
  delay(10);
}
