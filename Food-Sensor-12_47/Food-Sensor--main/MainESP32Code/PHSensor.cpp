#include "PHSensor.h"

PHSensor::PHSensor(int pin, float calibrationValue)
    : pin(pin), calibrationValue(calibrationValue) {}

void PHSensor::begin() {
    pinMode(pin, INPUT);
}

float PHSensor::readPH() {
    for (int i = 0; i < 10; i++) {
        bufferArr[i] = analogRead(pin);
        delay(30);
    }

    sortBuffer(bufferArr, 10);

    unsigned long int avgVal = 0;
    for (int i = 2; i < 8; i++)
        avgVal += bufferArr[i];

    float volt = (float)avgVal * 3.3 / 4096.0 / 6;
    return -5.70 * volt + calibrationValue;
}

void PHSensor::sortBuffer(int *bufferArr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (bufferArr[i] > bufferArr[j]) {
                int temp = bufferArr[i];
                bufferArr[i] = bufferArr[j];
                bufferArr[j] = temp;
            }
        }
    }
}
