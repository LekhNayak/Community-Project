#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <Arduino.h>
#include <ArduinoHttpClient.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>


// WiFi credentials (extern declarations)
extern const char* ssid;
extern const char* password;

// ThingSpeak API settings
extern const char* apiWriteKey;
extern const char* thingSpeakChannel;

// Define the analog pin for the MQ-4 sensor
const int mq4Pin = 34;  // GPIO 34 (Analog input pin)

// Define the analog pin for the pH sensor
const int phSensorPin = 35;  // GPIO 35 (Analog input pin)

// Define pins for the color sensor
#define S0 19
#define S1 18
#define S2 5
#define S3 17
#define sensorOut 4

// Calibration values for the color sensor
const int R_Min = 5;
const int R_Max = 255;
const int G_Min = 4;
const int G_Max = 255;
const int B_Min = 4;
const int B_Max = 255;

class SensorManager {
public:
    SensorManager();
    void begin();
    void readSensors();
    void sendToThingSpeak();

private:
    WiFiClient wifiClient;
    HttpClient client;
    float calibration_value;
    int buffer_arr[10];
    float readPHSensor();
    const char* readColorSensor();
    float readTurbiditySensor();
    float readMethaneSensor();
    float readAlcSensor();
    float calculatePHValue();
    int getRed();
    int getGreen();
    int getBlue();
};

#endif // SENSORMANAGER_H
