#include "GymTimer.h"

GymTimer::GymTimer(int _playPin = 8, int _upPin = 7, int _downPin = 6, int _powerPin = 4, int _modePin = 2) {
  powerButtonShort = new ezButton(_powerPin);
  powerButtonLong = new ezButton(_powerPin);
  playButtonShort = new ezButton(_playPin);
  playButtonLong = new ezButton(_playPin);
  upButtonShort = new ezButton(_upPin);
  upButtonLong = new ezButton(_upPin);
  downButtonShort = new ezButton(_downPin);
  downButtonLong = new ezButton(_downPin);
  modeButtonShort = new ezButton(_modePin);
  modeButtonLong = new ezButton(_modePin);
} //default constructor

void GymTimer::begin(){
  powerButtonShort->setDebounceTime(50);
  powerButtonLong->setDebounceTime(3000);
  playButtonShort->setDebounceTime(50);
  playButtonLong->setDebounceTime(3000);
  upButtonShort->setDebounceTime(50);
  upButtonLong->setDebounceTime(3000);
  downButtonShort->setDebounceTime(50);
  downButtonLong->setDebounceTime(3000);
  modeButtonShort->setDebounceTime(50);
  modeButtonLong->setDebounceTime(3000);
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
    if(setting){ //Going to use this so the display blinks while you are setting times -- do individual digits?
      matrix.blinkRate(HT16K33_BLINK_1HZ);
    }
    readPlayButton();
    readUpButton();
    readDownButton();
    readModeButton();
    if(playPress){
      Serial.println("Here1");
    }else if(playRelease){
      Serial.println("Here 2");
    }

    if(mode == Clock){
      drawTime(); 
      //Handle mode change
    }
    matrix.writeDisplay();
  }else{
    powerOff();
  }
}

void GymTimer::readPowerButton(){
  //Detect if power button has been pressed down, and then released again for a short press
  powerButtonShort->loop();
  powerButtonLong->loop();
  powerPress = false;
  powerRelease = false;
  powerLongPress = false;
  
  if(powerButtonShort->isPressed()){
    powerPress = true;
    Serial.println("Power -- Short");
  }

  if(powerButtonShort->isReleased()){
    //Do quick press action 
    powerRelease = true;
    Serial.println("Power -- Release");
  }
  
  if(powerButtonLong->isPressed()){
    poweredOn = !poweredOn; //Toggles the power, must wait 3s between power presses since that is the debounce time.
    powerLongPress = true;
    Serial.println("Power -- Long");
  }
}

void GymTimer::readPlayButton(){
  playButtonShort->loop();
  playButtonLong->loop();
  playPress = false;
  playRelease = false;
  playLongPress = false;
  
  if(playButtonShort->isPressed()){
    playPress = true;
    Serial.println("Play -- Short");
  }

  if(playButtonShort->isReleased()){
    //Do quick press action 
    playRelease = true;
    Serial.println("Play -- Release");
  }
  
  if(playButtonLong->isPressed()){
    //Do long press action
    playLongPress = true;
    Serial.println("Play -- Long");
  }
}

void GymTimer::readUpButton(){
  upButtonShort->loop();
  upButtonLong->loop();
  upPress = false;
  upRelease = false;
  upLongPress = false;
  
  if(upButtonShort->isPressed()){
    upPress = true;
    Serial.println("Up -- Short");
  }

  if(upButtonShort->isReleased()){
    //Do quick press action 
    upRelease = true;
    Serial.println("Up -- Release");
  }
  
  if(upButtonLong->isPressed()){
    //Do long press action
    upLongPress = true;
    Serial.println("Up -- Long");
  }
}

void GymTimer::readDownButton(){
  downButtonShort->loop();
  downButtonLong->loop();
  downPress = false;
  downRelease = false;
  downLongPress = false;
  
  if(downButtonShort->isPressed()){
    downPress = true;
    Serial.println("Down -- Short");
  }

  if(downButtonShort->isReleased()){
    //Do quick press action 
    downRelease = true;
    Serial.println("Down -- Release");
  }
  
  if(downButtonLong->isPressed()){
    //Do long press action
    downLongPress = true;
    Serial.println("Down -- Long");
  }
}

void GymTimer::readModeButton(){
  modeButtonShort->loop();
  modeButtonLong->loop();
  modePress = false;
  modeRelease = false;
  modeLongPress = false;
  
  if(modeButtonShort->isPressed()){
    modePress = true;
    Serial.println("Mode -- Short");
  }

  if(modeButtonShort->isReleased()){
    //Do quick press action 
    modeRelease = true;
    Serial.println("Mode -- Release");
  }
  
  if(modeButtonLong->isPressed()){
    //Do long press action
    modeLongPress = true;
    Serial.println("Mode -- Long");
  }
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
