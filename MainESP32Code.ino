#include "SensorManager.h"

SensorManager sensorManager;

void setup() {
    sensorManager.begin();
}

void loop() {
    sensorManager.readSensors();
    sensorManager.sendToThingSpeak();
    delay(5000);  // Delay between uploads (adjust as needed)
}
