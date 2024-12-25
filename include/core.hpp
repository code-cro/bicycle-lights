#ifndef CORE_HPP
#define CORE_HPP

#include <Arduino.h>
#include <Bounce2.h>


// Pins for buttons
const int button1Pin = 2; // D2: Toggles Bank A ON/OFF
const int button2Pin = 3; // D3: Toggles Bank B ON/OFF
const int button3Pin = 4; // D4: Changes patterns

// Pins for LEDs (Bank A)
const int bankAPins[] = {5, 6, 7, 8}; // D5-D8: LED Bank A

// Pins for LEDs (Bank B)
const int bankBPins[] = {9, 10, 11, 12}; // D9-D12: LED Bank B

// State variables
bool bankAState = false; // State of Bank A (ON/OFF)
bool bankBState = false; // State of Bank B (ON/OFF)
int currentPattern = 0;  // Current blinking pattern (0-3)

// Debounced buttons
Bounce button1 = Bounce();
Bounce button2 = Bounce();
Bounce button3 = Bounce();



void setLEDs(const int pins[], bool state) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(pins[i], state ? HIGH : LOW); // Set LED state (ON/OFF)
  }
}

void executePattern(int pattern) {
  switch (pattern) {
    case 0: // All ON
      if (bankAState) setLEDs(bankAPins, true);
      if (bankBState) setLEDs(bankBPins, true);
      delay(100);
      break;
    case 1: // Blink Alternating
      if (bankAState) setLEDs(bankAPins, true);
      if (bankBState) setLEDs(bankBPins, false);
      delay(100);
      if (bankAState) setLEDs(bankAPins, false);
      if (bankBState) setLEDs(bankBPins, true);
      delay(100);
      break;
    case 2: // Chase
      for (int i = 0; i < 4; i++) {
        if (bankAState) digitalWrite(bankAPins[i], HIGH);
        if (bankBState) digitalWrite(bankBPins[i], HIGH);
        delay(100);
        if (bankAState) digitalWrite(bankAPins[i], LOW);
        if (bankBState) digitalWrite(bankBPins[i], LOW);
      }
      break;
    case 3: // All OFF
      if (bankAState) setLEDs(bankAPins, false);
      if (bankBState) setLEDs(bankBPins, false);
      delay(100);
      break;
  }
}

#endif
