#include <stdint.h>

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
    char* name;
    Mode mode;
  public:
    GymTimer();
    int getMode();
    char* getName();

  
};


#endif
