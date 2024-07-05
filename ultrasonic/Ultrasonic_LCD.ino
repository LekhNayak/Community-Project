  const int trig_pin = 5;
  const int echo_pin = 18;
  const int Led_red = 19;
  const int Led_green = 21;
  // include the library code:
  #include <LiquidCrystal.h>
  
  // initialize the library with the numbers of the interface pins
  LiquidCrystal lcd(15, 2, 23, 3, 1, 22);
  // Sound speed in air (cm/us)
  #define SOUND_SPEED 0.034
  #define TRIG_PULSE_DURATION_US 10

  long ultrason_duration;
  float distance_cm;

  void setup() {
    Serial.begin(9600);
    pinMode(trig_pin, OUTPUT); // We configure the trig as output
    pinMode(echo_pin, INPUT); // We configure the echo as input
    pinMode(Led_red, OUTPUT); // Configure the red LED as output
    pinMode(Led_green, OUTPUT); // Configure the green LED as output
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("yooo");
  }

  void loop() {
    // Set up the signal
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(2);
    // Create a 10 µs impulse
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(TRIG_PULSE_DURATION_US);
    digitalWrite(trig_pin, LOW);

    // Return the wave propagation time (in µs)
    ultrason_duration = pulseIn(echo_pin, HIGH);

    // Distance calculation
    distance_cm = (ultrason_duration * SOUND_SPEED) / 2;

    // Control LEDs based on distance
    if (distance_cm < 10) {
      digitalWrite(Led_red, HIGH);
      digitalWrite(Led_green, LOW);
    } else {
      digitalWrite(Led_green, HIGH);
      digitalWrite(Led_red, LOW);
    }

    // Print the distance on the serial port
    Serial.print("Distance (cm): ");
    Serial.println(distance_cm);

    delay(1000);
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(distance_cm);
  }
