#include "GymTimer.h"

GymTimer timer = GymTimer();
Adafruit_7segment matrix;

void setup() {
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  Serial.println("Here");
  timer.begin();
//  timer.printName();
}

void loop() {
//  Serial.println("Herre");
  timer.updateDisplay();
}
