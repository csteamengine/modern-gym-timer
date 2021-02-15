#include "ascii.h"

uint8_t get_ascii(int input){
  return ascii_lookup[input - 32];
}
