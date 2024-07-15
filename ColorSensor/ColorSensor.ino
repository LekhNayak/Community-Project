#include <ColorName.h>
/*
  ESP32 TCS3200 Color sensor
  http://www.electronicwings.com
*/

#define S0 19         /*Define S0 Pin Number of ESP32*/
#define S1 18         /*Define S1 Pin Number of ESP32*/
#define S2 5          /*Define S2 Pin Number of ESP32*/
#define S3 17         /*Define S3 Pin Number of ESP32*/
#define sensorOut 4   /*Define Sensor Output Pin Number of ESP32*/

/*Enter the Minimum and Maximum Values which getting from Calibration Code*/
int R_Min = 5;  /*Red minimum value*/
int R_Max = 38; /*Red maximum value*/
int G_Min = 4;  /*Green minimum value*/
int G_Max = 42; /*Green maximum value*/
int B_Min = 4;  /*Blue minimum value*/
int B_Max = 35; /*Blue maximum value*/

/*Define int variables*/
int Red = 0;
int Green = 0;
int Blue = 0;

int redValue;
int greenValue;
int blueValue;
int Frequency;

void setup() {
  pinMode(S0, OUTPUT);        /*Define S0 Pin as OUTPUT*/
  pinMode(S1, OUTPUT);        /*Define S1 Pin as OUTPUT*/
  pinMode(S2, OUTPUT);        /*Define S2 Pin as OUTPUT*/
  pinMode(S3, OUTPUT);        /*Define S3 Pin as OUTPUT*/
  pinMode(sensorOut, INPUT);  /*Define Sensor Output Pin as INPUT*/
  Serial.begin(9600);         /*Set the baudrate to 9600*/
  delay(1000);                /*Wait for 1000ms*/

  /* Setting frequency-scaling to 20% */
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
}

void loop() {
  Red = getRed();
  redValue = map(Red, R_Min, R_Max, 255, 0); /*Map the Red Color Value*/
  delay(200);
 
  Green = getGreen();
  greenValue = map(Green, G_Min, G_Max, 255, 0); /*Map the Green Color Value*/
  delay(200);
 
  Blue = getBlue();
  blueValue = map(Blue, B_Min, B_Max, 255, 0);   /*Map the Blue Color Value*/
  delay(200);

  Serial.print("Red = ");
  Serial.print(redValue);   /*Print Red Color Value on Serial Monitor*/
  Serial.print("    ");
  Serial.print("Green = ");
  Serial.print(greenValue); /*Print Green Color Value on Serial Monitor*/
  Serial.print("    ");
  Serial.print("Blue = ");
  Serial.println(blueValue);/*Print Blue Color Value on Serial Monitor*/
  delay(1000);              /*Wait a second*/

  const char* search_color = ColorNameString(redValue, greenValue, blueValue);
  Serial.print("Color Name: ");
  Serial.println(search_color);
}

int getRed() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  Frequency = pulseIn(sensorOut, LOW); /*Get the Red Color Frequency*/
  return Frequency;
}

int getGreen() {
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  Frequency = pulseIn(sensorOut, LOW); /*Get the Green Color Frequency*/
  return Frequency;
}

int getBlue() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  Frequency = pulseIn(sensorOut, LOW); /*Get the Blue Color Frequency*/
  return Frequency;
}
