#ifndef SENSOR_H
#define SENSOR_H
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#endif // SENSOR_H
extern DHT dht;
const int moisture_pin = A0;
const int LDR_pin = A1;
int soil_moisture;
float mois;
float temp;
int LDR;
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
void updateMoisture(){
    unsigned long currentMillis1 = millis();
    if (currentMillis1 - previousMillis1 >= 1000)
    {   
        previousMillis1 = currentMillis1;
        soil_moisture = analogRead(moisture_pin);
        mois = map(soil_moisture, 0, 1023, 0, 100);
    }
}
void updateTemp(){
    unsigned long currentMillis2 = millis();
    if (currentMillis2 - previousMillis2 >= 1000)
    {
        previousMillis2 = currentMillis2;
        temp = dht.readTemperature();
    }
}
void updateLDR(){
    unsigned long currentMillis3 = millis();
    if (currentMillis3 - previousMillis3 >= 1000)
    {
        previousMillis3 = currentMillis3;
        LDR = analogRead(LDR_pin);
    }
}