#include <ArduinoJson.h>
#include "DHT.h"

int luminosity = 0;
int temperature = 0;
int humidity = 0;

int luminosityPin = A0;
int pinBtn = 7;

DHT dht(2, DHT11);

int getLuminosity() {
  pinMode(luminosityPin, INPUT);
  
  return analogRead(luminosityPin);
}

int getTemperature() {
  return dht.readTemperature();
}

int getHumidity() {
  return dht.readHumidity();
}

void setup() {
  Serial.begin(9600);
  pinMode(pinBtn, INPUT_PULLUP);
  dht.begin();
}

void loop() {
  luminosity = getLuminosity();
  temperature = getTemperature();
  humidity = getHumidity();
  int estadoBtn = digitalRead(pinBtn);

  StaticJsonDocument<200> doc;
  doc["luminosity"] = luminosity;
  doc["temperature"] = temperature;
  doc["humidity"] = humidity;
  if (estadoBtn != 1){
      doc["chamado"] = "Chamado: Leito 01";
    }else{
      doc["chamado"] = " ";
    }

  serializeJson(doc, Serial);
  Serial.println();
  
  delay(4000);
}
