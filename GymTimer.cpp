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

    if(modePress){
      nextMode();
    }else if(modeLongPress){
      Serial.println("Mode Long Pressed");
    }else if(modeRelease){
      //TODO anything that needs done on mode button release
    }

    switch(mode){
      case Mode::Up:
        matrix.blinkRate(HT16K33_BLINK_1HZ);
        matrix.writeDigitRaw(0, get_ascii('U'));
        matrix.writeDigitRaw(1, get_ascii('P'));
        break;
      case Mode::UpRnd:
        matrix.blinkRate(HT16K33_BLINK_1HZ);
        matrix.writeDigitRaw(0, get_ascii('U'));
        matrix.writeDigitRaw(1, get_ascii('R'));
        break;
      case Mode::Down:
        matrix.blinkRate(HT16K33_BLINK_1HZ);
        matrix.writeDigitRaw(0, get_ascii('D'));
        matrix.writeDigitRaw(1, get_ascii('N'));
        break;
      case Mode::DownRnd:
        matrix.blinkRate(HT16K33_BLINK_1HZ);
        matrix.writeDigitRaw(0, get_ascii('D'));
        matrix.writeDigitRaw(1, get_ascii('R'));
        break;
      case Mode::Interval:
        matrix.blinkRate(HT16K33_BLINK_1HZ);
        matrix.writeDigitRaw(0, get_ascii('I'));
        matrix.writeDigitRaw(1, get_ascii('N'));
        break;
      case Mode::Clock:
        matrix.blinkRate(HT16K33_BLINK_OFF);
        drawTime(); 
        break;
    }
    
    matrix.writeDisplay();
  }else{
    powerOff();
  }
}

void GymTimer::nextMode(){
  if(mode == Mode::Clock){
    mode = Mode::Up;
  }else{
    mode = mode + 1;
  }
  
}

Mode GymTimer::getMode(){
  return mode;
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
  }

  if(powerButtonShort->isReleased()){
    //Do quick press action 
    powerRelease = true;
  }
  
  if(powerButtonLong->isPressed()){
    poweredOn = !poweredOn; //Toggles the power, must wait 3s between power presses since that is the debounce time.
    powerLongPress = true;
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
  }

  if(playButtonShort->isReleased()){
    //Do quick press action 
    playRelease = true;
  }
  
  if(playButtonLong->isPressed()){
    //Do long press action
    playLongPress = true;
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
  }

  if(upButtonShort->isReleased()){
    //Do quick press action 
    upRelease = true;
  }
  
  if(upButtonLong->isPressed()){
    //Do long press action
    upLongPress = true;
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
  }

  if(downButtonShort->isReleased()){
    //Do quick press action 
    downRelease = true;
  }
  
  if(downButtonLong->isPressed()){
    //Do long press action
    downLongPress = true;
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
  }

  if(modeButtonShort->isReleased()){
    //Do quick press action 
    modeRelease = true;
  }
  
  if(modeButtonLong->isPressed()){
    //Do long press action
    modeLongPress = true;
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
void GymTimer::printName(String name){
  for(int i = 0; i <= name.length() + 3; i++){
    if(i > 14){
      matrix.writeDigitRaw(4, 0b00000000);
    }else{
      matrix.writeDigitRaw(4,  get_ascii(name.charAt(i) - ' '));
    }

    if(i-1 >= 0 && i-1 < name.length()){
      matrix.writeDigitRaw(3,  get_ascii(name.charAt(i-1) - ' '));
    }else{
      matrix.writeDigitRaw(3, 0b00000000);
    }

    if(i-2 >= 0 && i-2 < name.length()){
      matrix.writeDigitRaw(1,  get_ascii(name.charAt(i-2) - ' '));
    }else{
      matrix.writeDigitRaw(1, 0b00000000);
    }

    if(i-3 >= 0 && i-3 < name.length()){
      matrix.writeDigitRaw(0, get_ascii(name.charAt(i-3) - ' '));
    }else{
      matrix.writeDigitRaw(0, 0b00000000);
    }
    
    matrix.writeDisplay();
    delay(250);
  }
  delay(1000);
}
