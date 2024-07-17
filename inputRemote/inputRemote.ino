#include <IRremote.h>

const int RECV_PIN = 14;  // GPIO pin connected to the IR receiver

IRrecv irrecv(RECV_PIN);
decode_results results;

// Placeholder hex codes for remote buttons
const unsigned long BUTTON_0 = 0xFF6897;  // Replace with the actual hex code for button 0
const unsigned long BUTTON_1 = 0xFF30CF;  // Replace with the actual hex code for button 1
const unsigned long BUTTON_2 = 0xFF18E7;  // Replace with the actual hex code for button 2
const unsigned long BUTTON_3 = 0xFF7A85;  // Replace with the actual hex code for button 3
const unsigned long BUTTON_4 = 0xFF10EF;  // Replace with the actual hex code for button 4
const unsigned long BUTTON_5 = 0xFF38C7;  // Replace with the actual hex code for button 5
const unsigned long BUTTON_6 = 0xFF5AA5;  // Replace with the actual hex code for button 6
const unsigned long BUTTON_7 = 0xFF42BD;  // Replace with the actual hex code for button 7
const unsigned long BUTTON_8 = 0xFF4AB5;  // Replace with the actual hex code for button 8
const unsigned long BUTTON_9 = 0xFF52AD;  // Replace with the actual hex code for button 9

bool menuDisplayed = false;  // Track if the menu has been displayed
int firstDigit = -1;  // To store the first digit input
int secondDigit = -1; // To store the second digit input

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
    Serial.println("01. Choice 1");
    Serial.println("02. Choice 2");
    Serial.println("03. Choice 3");
    Serial.println("04. Choice 4");
    Serial.println("05. Choice 5");
    Serial.println("06. Choice 6");
    Serial.println("07. Choice 7");
    Serial.println("08. Choice 8");
    Serial.println("09. Choice 9");
    Serial.println("10. Choice 10");
    Serial.println("11. Choice 11");
    Serial.println("12. Choice 12");
    Serial.println("13. Choice 13");
    Serial.println("14. Choice 14");
    Serial.println("15. Choice 15");
    Serial.println("16. Choice 16");
    Serial.println("17. Choice 17");
    Serial.println("18. Choice 18");
    Serial.println("19. Choice 19");
    Serial.println("20. Choice 20");
    Serial.println("00. Exit");
    menuDisplayed = true;  // Mark the menu as displayed
}

void handleRemoteInput(unsigned long code) {
    if (!menuDisplayed) {
        displayMenu();
        return;
    }

    int digit = codeToDigit(code);
    if (digit == -1) {
        Serial.println("Unknown button pressed");
        return;
    }

    if (firstDigit == -1) {
        firstDigit = digit;
        Serial.print("First digit entered: ");
        Serial.println(firstDigit);
    } else {
        secondDigit = digit;
        Serial.print("Second digit entered: ");
        Serial.println(secondDigit);
        int choice = firstDigit * 10 + secondDigit;
        handleChoice(choice);
        firstDigit = -1;
        secondDigit = -1;
    }
}

int codeToDigit(unsigned long code) {
    switch (code) {
        case BUTTON_0: return 0;
        case BUTTON_1: return 1;
        case BUTTON_2: return 2;
        case BUTTON_3: return 3;
        case BUTTON_4: return 4;
        case BUTTON_5: return 5;
        case BUTTON_6: return 6;
        case BUTTON_7: return 7;
        case BUTTON_8: return 8;
        case BUTTON_9: return 9;
        default: return -1;
    }
}

void handleChoice(int choice) {
    switch (choice) {
        case 1: Serial.println("*** Choice 1 selected ***"); break;
        case 2: Serial.println("*** Choice 2 selected ***"); break;
        case 3: Serial.println("*** Choice 3 selected ***"); break;
        case 4: Serial.println("*** Choice 4 selected ***"); break;
        case 5: Serial.println("*** Choice 5 selected ***"); break;
        case 6: Serial.println("*** Choice 6 selected ***"); break;
        case 7: Serial.println("*** Choice 7 selected ***"); break;
        case 8: Serial.println("*** Choice 8 selected ***"); break;
        case 9: Serial.println("*** Choice 9 selected ***"); break;
        case 10: Serial.println("*** Choice 10 selected ***"); break;
        case 11: Serial.println("*** Choice 11 selected ***"); break;
        case 12: Serial.println("*** Choice 12 selected ***"); break;
        case 13: Serial.println("*** Choice 13 selected ***"); break;
        case 14: Serial.println("*** Choice 14 selected ***"); break;
        case 15: Serial.println("*** Choice 15 selected ***"); break;
        case 16: Serial.println("*** Choice 16 selected ***"); break;
        case 17: Serial.println("*** Choice 17 selected ***"); break;
        case 18: Serial.println("*** Choice 18 selected ***"); break;
        case 19: Serial.println("*** Choice 19 selected ***"); break;
        case 20: Serial.println("*** Choice 20 selected ***"); break;
        case 0: Serial.println("Exiting..."); menuDisplayed = false; break;
        default: Serial.println("Invalid choice"); break;
    }
    if (choice != 0) {
        displayMenu();
    }
}

