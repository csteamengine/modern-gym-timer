#include <stdint.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "ascii.h"
#include <ezButton.h>

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
    bool modeSelect = false;
    bool timeSelect = false;
    bool roundSelect = false;
    unsigned long lastRefreshTime = millis(); 
    char* name;
    Mode mode;
    Adafruit_7segment matrix;
    int debounceDelay = 50;
    int longPressDelay = 3000;

    ezButton* powerButtonShort;
    ezButton* powerButtonLong;
    ezButton* playButtonShort;
    ezButton* playButtonLong;
    ezButton* upButtonShort;
    ezButton* upButtonLong;
    ezButton* downButtonShort;
    ezButton* downButtonLong;
    ezButton* modeButtonShort;
    ezButton* modeButtonLong;

    bool setting = false;

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

    bool playRelease = false;
    bool upRelease = false;
    bool downRelease = false;
    bool powerRelease = false;
    bool modeRelease = false;
    
  public:
    GymTimer(int _playPin = 8, int _upPin = 7, int _downPin = 6, int _powerPin = 4, int _modePin = 2);
    void begin();
    Mode getMode();
    void nextMode();
    char* getName();
    void printName(String name);
    void updateDisplay();
    void powerOff();
    void readPowerButton();
    void readPlayButton();
    void readUpButton();
    void readDownButton();
    void readModeButton();
    void drawTime();
    Adafruit_7segment getMatrix() { return matrix; };

  
};


#endif
