#include "LedMatrix.h"
LedMatrix ledmatrix;

void setup() {
  ledmatrix.setText("Munich Maker Lab");
  ledmatrix.startScroll();
}


void loop() {
  ledmatrix.loop();
}
