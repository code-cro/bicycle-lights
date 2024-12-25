#include <Arduino.h>
#include "core.hpp"



void setup() {
  // Initialize LED pins
  for (int i = 0; i < 4; i++) {
    pinMode(bankAPins[i], OUTPUT); // Set Bank A LED pins as OUTPUT
    pinMode(bankBPins[i], OUTPUT); // Set Bank B LED pins as OUTPUT
  }

  // Initialize button pins
  pinMode(button1Pin, INPUT_PULLUP); // Button 1: Toggle Bank A LEDs
  pinMode(button2Pin, INPUT_PULLUP); // Button 2: Toggle Bank B LEDs
  pinMode(button3Pin, INPUT_PULLUP); // Button 3: Change patterns

  // Attach debouncers
  button1.attach(button1Pin);
  button1.interval(50);

  button2.attach(button2Pin);
  button2.interval(50);

  button3.attach(button3Pin);
  button3.interval(50);
}

void loop() {
  // Update button states
  button1.update();
  button2.update();
  button3.update();

  // Handle button 1: Toggle Bank A LEDs
  if (button1.fell()) {
    bankAState = !bankAState;
    if (bankAState) { // If Bank A is enabled, disable Bank B
      bankBState = false;
      setLEDs(bankBPins, false);
    }
    setLEDs(bankAPins, bankAState);
  }

  // Handle button 2: Toggle Bank B LEDs
  if (button2.fell()) {
    bankBState = !bankBState;
    if (bankBState) { // If Bank B is enabled, disable Bank A
      bankAState = false;
      setLEDs(bankAPins, false);
    }
    setLEDs(bankBPins, bankBState);
  }

  // Handle button 3: Change patterns
  if (button3.fell()) {
    currentPattern = (currentPattern + 1) % 4; // Cycle through 4 patterns
  }

  // Execute current pattern (if any LEDs are ON)
  if (bankAState || bankBState) {
    executePattern(currentPattern);
  }
}
