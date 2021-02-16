#include <stdint.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "ascii.h"

#ifndef gymTimer
#define gymTimer 

enum Mode : int{
      Up,
      UpRnd,
      Down,
      DownRnd,
      Interval,
      Clock
    };
class GymTimer{
  private:
    bool poweredOn = true;
    unsigned long lastRefreshTime = millis(); 
    char* name;
    Mode mode;
    Adafruit_7segment matrix;
    int debounceDelay = 50;
    int longPressDelay = 3000;

    int playPin;
    int upPin;
    int downPin;
    int powerPin;
    int modePin;
    
    int playButtonState = HIGH;
    int upButtonState = HIGH;
    int downButtonState = HIGH;
    int powerButtonState = HIGH;
    int modeButtonState = HIGH;

    int lastPlayButtonState = HIGH;
    int lastUpButtonState = HIGH;
    int lastDownButtonState = HIGH;
    int lastPowerButtonState = HIGH;
    int lastModeButtonState = HIGH;

    bool playPress = false;
    bool upPress = false;
    bool downPress = false;
    bool powerPress = false;
    bool modePress = false;

    bool playLongPress = false;
    bool upLongPress = false;
    bool downLongPress = false;
    bool powerLongPress = false;
    bool modeLongPress = false;
    
    unsigned long lastPlayDebounce = 0;
    unsigned long lastUpDebounce = 0;
    unsigned long lastDownDebounce = 0;
    unsigned long lastPowerDebounce = 0;
    unsigned long lastModeDebounce = 0;
  public:
    GymTimer(int _playPin = 8, int _upPin = 7, int _downPin = 6, int _powerPin = 4, int _modePin = 2);
    void begin();
    int getMode();
    char* getName();
    void printName();
    void updateDisplay();
    void powerOff();
    void readPowerButton();
    void drawTime();
    Adafruit_7segment getMatrix() { return matrix; };

  
};


#endif
