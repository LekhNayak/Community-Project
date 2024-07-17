#include "SensorManager.h"
#include <ColorName.h>
// WiFi credentials (definitions)
const char* ssid = "sid";
const char* password = "hellohello";

// ThingSpeak API settings
const char* apiWriteKey = "9R46YJL87HYE6HEK";
const char* thingSpeakChannel = "2599999";
SensorManager::SensorManager()
    : client(wifiClient, "api.thingspeak.com", 80), calibration_value(20.24 - 0.7) {}

void SensorManager::begin() {
    Serial.begin(115200);  // Initialize serial communication for debugging
    delay(500);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("Connecting to WiFi..");
        delay(500);
    }
    Serial.println("Connected to the WiFi network");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // Initialize MQ-4 sensor pin
    pinMode(mq4Pin, INPUT);

    // Initialize pH sensor pin
    pinMode(phSensorPin, INPUT);

    // Initialize color sensor pins
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(sensorOut, INPUT);

    // Setting frequency-scaling to 20%
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);

    Wire.begin();
}

void SensorManager::readSensors() {
    // Read the analog value from the MQ-4 sensor
    int sensorValue = analogRead(mq4Pin);
    Serial.print("MQ-4 Sensor Value: ");
    Serial.println(sensorValue);

    // Read other sensors
    float phsensor = readPHSensor();
    const char* color = readColorSensor();
    float turbidity = readTurbiditySensor();
    float methane = readMethaneSensor();
    float alcohol = readAlcSensor();

    // Print the sensor values for debugging
    Serial.print("pH Sensor: ");
    Serial.println(phsensor);
    Serial.print("Color Sensor: ");
    Serial.println(color);
    Serial.print("Turbidity Sensor: ");
    Serial.println(turbidity);
    Serial.print("Methane Sensor: ");
    Serial.println(methane);
    Serial.print("Alcohol Sensor: ");
    Serial.println(alcohol);
}

void SensorManager::sendToThingSpeak() {
    // Prepare the data string
    float phsensor = readPHSensor();
    const char* color = readColorSensor();
    float turbidity = readTurbiditySensor();
    float methane = readMethaneSensor();
    float alcohol = readAlcSensor();
    const char* alcOutput = alcohol>3500?"true":"false";
    String dataString = "api_key=" + String(apiWriteKey) + "&field1=" + String(phsensor) + "&field2=" + String(color) + "&field3=" + String(turbidity) + "&field4=" + String(methane) + "&field5=" + alcOutput;

    // Send HTTP POST request
    client.beginRequest();
    client.post("/update");
    client.sendHeader("Content-Type", "application/x-www-form-urlencoded");
    client.sendHeader("Content-Length", dataString.length());
    client.beginBody();
    client.print(dataString);
    client.endRequest();

    // Check for a successful response
    int statusCode = client.responseStatusCode();
    if (statusCode == 200) {
        Serial.println("Data sent successfully!");
    } else {
        Serial.print("Error sending data: ");
        Serial.println(statusCode);
    }
}

float SensorManager::readPHSensor() {
    return calculatePHValue();
}

const char* SensorManager::readColorSensor() {
    int red = getRed();
    int redValue = map(red, R_Min, R_Max, 0,255); // Map the Red Color Value
    delay(200);

    int green = getGreen();
    int greenValue = map(green, G_Min, G_Max, 0, 255); // Map the Green Color Value
    delay(200);

    int blue = getBlue();
    int blueValue = map(blue, B_Min, B_Max, 0, 255); // Map the Blue Color Value
    delay(200);

    Serial.print("Red = ");
    Serial.print(redValue);
    Serial.print("    ");
    Serial.print("Green = ");
    Serial.print(greenValue);
    Serial.print("    ");
    Serial.print("Blue = ");
    Serial.println(blueValue);

    return ColorNameString(redValue, greenValue, blueValue);
}

float SensorManager::readTurbiditySensor() {
    return rand();
}

float SensorManager::readMethaneSensor() {
    return analogRead(mq4Pin);  // Use the MQ-4 sensor value
}

float SensorManager::readAlcSensor() {
  float sensor_volt;
    float RS_gas; // Get value of RS in a GAS
    float ratio; // Get ratio RS_GAS/RS_air
    int sensorValue = analogRead(33);
    sensor_volt=(float)sensorValue/1024*5.0;
    RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL

    /*-Replace the name "R0" with the value of R0 in the demo of First Test -*/
    ratio = RS_gas/0.3;  // ratio = RS/R0
    /*-----------------------------------------------------------------------*/

    Serial.print("sensor_volt = ");
    Serial.println(sensor_volt);
    Serial.print("RS_ratio = ");
    Serial.println(RS_gas);
    Serial.print("Rs/R0 = ");
    Serial.println(ratio);
    delay(100);
    return sensorValue;
}

float SensorManager::calculatePHValue() {
    for (int i = 0; i < 10; i++) {
        buffer_arr[i] = analogRead(phSensorPin);
        delay(30);
    }

    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (buffer_arr[i] > buffer_arr[j]) {
                int temp = buffer_arr[i];
                buffer_arr[i] = buffer_arr[j];
                buffer_arr[j] = temp;
            }
        }
    }

    unsigned long int avgval = 0;
    for (int i = 2; i < 8; i++) {
        avgval += buffer_arr[i];
    }

    float volt = (float)avgval * 3.3 / 4096.0 / 6;
    float ph_act = -5.70 * volt + calibration_value;

    return ph_act;
}

int SensorManager::getRed() {
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    return pulseIn(sensorOut, LOW); // Get the Red Color Frequency
}

int SensorManager::getGreen() {
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    return pulseIn(sensorOut, LOW); // Get the Green Color Frequency
}

int SensorManager::getBlue() {
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    return pulseIn(sensorOut, LOW); // Get the Blue Color Frequency
}
