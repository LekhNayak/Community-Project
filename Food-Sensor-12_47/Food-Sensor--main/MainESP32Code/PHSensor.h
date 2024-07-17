#ifndef PHSENSOR_H
#define PHSENSOR_H

#include <Arduino.h>

class PHSensor {
public:
    PHSensor(int pin, float calibrationValue);
    void begin();
    float readPH();

private:
    int pin;
    float calibrationValue;
    int bufferArr[10];
    float calculatePH(int *bufferArr);

    void sortBuffer(int *bufferArr, int size);
};

#endif // PHSENSOR_H
