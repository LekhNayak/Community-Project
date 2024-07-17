#include <EEPROM.h> // to store last calibration value (blank, Vclear)

int sensor = 0; // variable for averaging
int n = 25; // number of samples to average
int sensorValue = 0;
float voltage = 0.00;
float turbidity = 0.00;
float Vclear = 3.3; // Output voltage to calibrate (with clear water).

void setup()
{
  Serial.begin(115200);
  EEPROM.get(0, Vclear); // recovers the last Vclear calibration value stored in ROM.
  delay(3000); // Pause for 3 seconds
}

void loop()
{
  // Sensing routine:
  for (int i = 0; i < n; i++) {
    sensor += analogRead(35); // read the input on analog pin 3 (turbidity sensor analog output)
    delay(10);
  }
  sensorValue = sensor / n; // average the n values
  voltage = sensorValue * (3.300 / 4095.000); // Convert analog (0-4095) to voltage (0 - 3.3V)

  turbidity = 20.00 * (100.00 - (voltage / Vclear) * 100.00); // as relative percentage of 2000 NTU; 0% = clear water; // Factor 20 at the front instead of 100 to limit the result to 2000

  // Serial display
  Serial.print("Raw voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V, Turbidity: ");
  Serial.print(turbidity, 3);
  Serial.println(" NTU");
  Serial.println(sensorValue);

  sensor = 0; // resets for averaging
  delay(1000); // Pause for 1 seconds. // sampling rate
}
