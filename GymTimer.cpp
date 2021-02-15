#include "GymTimer.h"

GymTimer::GymTimer() {
  mode = Clock; //Default to clock mode
} //default constructor

int GymTimer::getMode(){
  return mode;
}
