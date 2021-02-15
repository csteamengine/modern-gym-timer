#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "ascii.h"
#include "GymTimer.h"

Adafruit_7segment matrix = Adafruit_7segment();

#define REFRESH_INTERVAL 1000

#define PLAY_PIN 6 //Play button will be used to play/pause a running clock
#define UP_PIN 5 //Up button will be used to adjust the clock or the workout rounds/length up
#define DOWN_PIN 4 //Down button will be used the same as the up button
#define POWER_BUTTON 3 //Tap power button to enter clock mode, hold 3 seconds to power off
#define MODE_BUTTON 2 //Mode will select which workout type you want to do

//Up
//Up with Rounds
//Down
//Down with Rounds
//Intervals (e.g. 3min on, 1min off)

bool blinkColon = true;
unsigned long lastRefreshTime = millis(); 

GymTimer timer;


void setup() {
#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);
  
  pinMode(PLAY_PIN, INPUT_PULLUP);
  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(DOWN_PIN, INPUT_PULLUP);
  pinMode(POWER_BUTTON, INPUT_PULLUP);
  pinMode(MODE_BUTTON, INPUT_PULLUP);

//  matrix.drawColon(true);
  matrix.setBrightness(5);
  printName();
  updateDisplay();
  
  delay(1000);
  Serial.println(timer.getMode());
}

void loop() {

//  if(millis() - lastRefreshTime >= REFRESH_INTERVAL)
//  {
//    lastRefreshTime += REFRESH_INTERVAL;
//    blinkColon = !blinkColon;
//  }
//  
  if(digitalRead(PLAY_PIN) == LOW){
    matrix.print(0xBEEF, HEX);
  }else{
    matrix.writeDigitNum(0, 0);
    matrix.writeDigitNum(1, 0);
    matrix.writeDigitNum(3, 0);
    matrix.writeDigitNum(4, 0);
  }

  updateDisplay();
//  delay(50);
}

void updateDisplay(){
//  matrix.drawColon(blinkColon);
  matrix.writeDisplay();
}

void printName(){
  //Cycle the letters and print Modern Hobbyist
  uint8_t modern_hobbyist[] = {
    ASCII_CAPITAL_M,
    ASCII_CAPITAL_O,
    ASCII_CAPITAL_D,
    ASCII_CAPITAL_E,
    ASCII_CAPITAL_R,
    ASCII_CAPITAL_N,
    0b00000000,
    ASCII_CAPITAL_H,
    ASCII_CAPITAL_O,
    ASCII_CAPITAL_B,
    ASCII_CAPITAL_B,
    ASCII_CAPITAL_Y,
    ASCII_CAPITAL_I,
    ASCII_CAPITAL_S,
    ASCII_CAPITAL_T,
  };
  
  for(int i = 0; i <= 19; i++){
    if(i > 14){
      matrix.writeDigitRaw(4, 0b00000000);
    }else{
      matrix.writeDigitRaw(4, modern_hobbyist[i]);
    }

    if(i-1 >= 0 && i-1 <= 14){
      matrix.writeDigitRaw(3, modern_hobbyist[i-1]);
    }else{
      matrix.writeDigitRaw(3, 0b00000000);
    }

    if(i-2 >= 0 && i-2 <= 14){
      matrix.writeDigitRaw(1, modern_hobbyist[i-2]);
    }else{
      matrix.writeDigitRaw(1, 0b00000000);
    }

    if(i-3 >= 0 && i-3 <= 14){
      matrix.writeDigitRaw(0, modern_hobbyist[i-3]);
    }else{
      matrix.writeDigitRaw(0, 0b00000000);
    }
    
    updateDisplay();
    delay(250);
  }
}
