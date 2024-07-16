 //Define the analog pin for the MQ-4 sensor
const int mq4Pin = 34;  // GPIO 34 (Analog input pin)

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
 
  // Configure the analog input pin
  pinMode(mq4Pin, INPUT);
}

void loop() {
  // Read the analog value from the MQ-4 sensor
  int sensorValue = analogRead(mq4Pin);

  // Print the analog value to the Serial Monitor
  Serial.print("MQ-4 Sensor Value: ");
  Serial.println(sensorValue);
 
  // Wait for a second before reading again
  delay(1000);
}
