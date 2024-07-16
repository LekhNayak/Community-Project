#include <IRremote.h>

const int RECV_PIN = 14;  // GPIO pin connected to the IR receiver

IRrecv irrecv(RECV_PIN);
decode_results results;

// Placeholder hex codes for remote buttons
const unsigned long BUTTON_1 = 0xFF30CF;  // Replace with the actual hex code for button 1
const unsigned long BUTTON_2 = 0xFF18E7;  // Replace with the actual hex code for button 2
const unsigned long BUTTON_3 = 0xFF7A85;  // Replace with the actual hex code for button 3
const unsigned long BUTTON_4 = 0xFF10EF;  // Replace with the actual hex code for button 4
const unsigned long BUTTON_5 = 0xFF38C7;  // Replace with the actual hex code for button 5

bool menuDisplayed = false;  // Track if the menu has been displayed

void setup() {
    Serial.begin(115200);
    Serial.println("Initializing IR Receiver...");
    irrecv.enableIRIn();  // Start the IR receiver
    delay(100);  // Allow time for the IR receiver to stabilize
    Serial.println("IR Receiver Initialized");
    displayMenu();
}

void loop() {
    if (irrecv.decode(&results)) {
        handleRemoteInput(results.value);  // Handle the received IR code
        irrecv.resume();  // Receive the next value
    }
    delay(100);  // Small delay to prevent continuous polling
}

void displayMenu() {
    Serial.println("\n\nSelect an option using the remote:");
    Serial.println("1. MQ3");
    Serial.println("2. MQ4");
    Serial.println("3. Color");
    Serial.println("4. pH");
    Serial.println("5. Turbidity");
    menuDisplayed = true;  // Mark the menu as displayed
}

void handleRemoteInput(unsigned long code) {
    if (!menuDisplayed) {
        displayMenu();
        return;
    }

    switch (code) {
        case BUTTON_1:
            Serial.println("*** MQ3 sensor selected ***");
            // Add code to handle MQ3 sensor
            break;
        case BUTTON_2:
            Serial.println("*** MQ4 sensor selected ***");
            // Add code to handle MQ4 sensor
            break;
        case BUTTON_3:
            Serial.println("*** Color sensor selected ***");
            // Add code to handle Color sensor
            break;
        case BUTTON_4:
            Serial.println("*** pH sensor selected ***");
            // Add code to handle pH sensor
            break;
        case BUTTON_5:
            Serial.println("*** Turbidity sensor selected ***");
            // Add code to handle Turbidity sensor
            break;
        default:
            Serial.println("Unknown button pressed");
            break;
    }

    menuDisplayed = false;  // Reset the flag to display the menu again after handling input
}
