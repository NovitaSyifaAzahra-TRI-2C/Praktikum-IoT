#include "DHT.h"

const byte ldrPin = 34;       
const byte dhtPin = 14;
const byte relayPin = 12;     
const byte ledPin = 5;        

#define DHTTYPE DHT22 
DHT dht(dhtPin, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(relayPin, LOW);
  digitalWrite(ledPin, LOW);
  
  Serial.println("Sistem Smart Warehouse Siap...");
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  float suhu = dht.readTemperature();

  if (isnan(suhu)) {
    Serial.println("Peringatan: Sensor DHT belum siap / Error!");
    delay(2000);
    return;
  }

  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print(" C | LDR ADC: ");
  Serial.println(ldrValue);

  if (suhu > 34.0 || ldrValue < 300) {
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, HIGH);
    Serial.println("-> Peringatan: Aktuator Aktif! (Kondisi Buruk)");
  } else {
    digitalWrite(relayPin, LOW);
    digitalWrite(ledPin, LOW);
    Serial.println("-> Kondisi Aman");
  }

  delay(2000);
}