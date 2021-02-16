#include "GymTimer.h"

GymTimer::GymTimer(int _playPin = 8, int _upPin = 7, int _downPin = 6, int _powerPin = 4, int _modePin = 2) {
  
  playPin = _playPin;
  upPin = _upPin;
  downPin = _downPin;
  powerPin = _powerPin;
  modePin = _modePin;

} //default constructor

void GymTimer::begin(){
  pinMode(playPin, INPUT_PULLUP);
  pinMode(upPin, INPUT_PULLUP);
  pinMode(downPin, INPUT_PULLUP);
  pinMode(powerPin, INPUT_PULLUP);
  pinMode(modePin, INPUT_PULLUP);
  //For some reason this can't be called in the constructor, so I created this begin function
  matrix = Adafruit_7segment();
  matrix.begin(0x70);
  //  //  matrix.drawColon(true);
  matrix.setBrightness(5);
  
  mode = Clock; //Default to clock mode
}

int GymTimer::getMode(){
  return mode;
}

void GymTimer::updateDisplay(){
  readPowerButton();
  
  if(poweredOn){
    int playButtonReading = digitalRead(playPin);
    int upButtonReading = digitalRead(upPin);
    int downButtonReading = digitalRead(downPin);
    int modeButtonReading = digitalRead(modePin);

    if(mode == Clock){
      drawTime(); 
    }
    matrix.writeDisplay();
  }else{
    Serial.println("Power Off");
    powerOff();
  }
}

void GymTimer::readPowerButton(){
  int powerButtonReading = digitalRead(powerPin);
  if (powerButtonReading != lastPowerButtonState) {
    // reset the debouncing timer
    lastPowerDebounce = millis();
  }
  
  if ((millis() - lastPowerDebounce) > debounceDelay) {
    if (powerButtonReading != powerButtonState) {
      powerButtonState = powerButtonReading;
      
      if (powerButtonState == LOW) {
        Serial.println("Press power");
        //Short press power button 
      }
    }
  }
  //TODO get this working, currently the timer resets when it hits the debounce time. need both.
  if ((millis() - lastPowerDebounce) > longPressDelay) {
    if (powerButtonReading != powerButtonState) {
      powerButtonState = powerButtonReading;
      
      if (powerButtonState == LOW) {
        Serial.println("POWER OFF");
        //Short press power button 
      }
    }
  }
  lastPowerButtonState = powerButtonReading;
}

void GymTimer::powerOff(){
  matrix.clear();
  matrix.writeDisplay();
}

void GymTimer::drawTime(){
  //This is not the right time obviously
  matrix.print(1234);
  matrix.drawColon(true);
}

void GymTimer::printName(){
  Serial.println("Printing Name:");
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
    
    matrix.writeDisplay();
    delay(250);
  }

  delay(1000);
}
