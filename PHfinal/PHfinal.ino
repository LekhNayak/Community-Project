
#include <Wire.h>

// WiFi credentials are no longer needed since Blynk is removed

float calibration_value = 20.24 - 0.7; //21.34 - 0.7
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10], temp;

float ph_act;

void setup() 
{
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  for(int i = 0; i < 10; i++) 
  { 
    buffer_arr[i] = analogRead(35);
    delay(30);
  }
  for(int i = 0; i < 9; i++)
  {
    for(int j = i + 1; j < 10; j++)
    {
      if(buffer_arr[i] > buffer_arr[j])
      {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }
  avgval = 0;
  for(int i = 2; i < 8; i++)
    avgval += buffer_arr[i];
  float volt = (float)avgval * 3.3 / 4096.0 / 6;  
  ph_act = -5.70 * volt + calibration_value;

  Serial.print("pH Val: ");
  Serial.println(ph_act);
  delay(1000);
}
