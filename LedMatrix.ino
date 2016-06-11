#include "LedMatrix.h"
#include <Sprite.h>

extern "C" {
#include "user_interface.h"
}
#include "SimpleTimer.h"

//#include "digitalWrite.h"
LedMatrix ledmatrix;
int i = 0;
String LAUFSCHRIFT = "Munich Maker Lab";
byte speed = 100;
byte stringLen;

SimpleTimer updateTimer;
SimpleTimer loopTextTimer;


void setup() {
  //Serial.begin(9600);
  updateTimer.setInterval(2, umschalten);
  loopTextTimer.setInterval(speed, loopText);



  //ledmatrix.writeSprite(0, letter_L);
  stringLen = LAUFSCHRIFT.length();





}


void umschalten() {

  for (byte c = 0; c < 8 ; c++) {

  }
  ledmatrix.update();

  system_soft_wdt_feed();
}

void loopText() {
  ledmatrix.clearMatrix();
  for (byte c = 0; c < stringLen ; c++) {
    ledmatrix.writeFont(i + c * 8, LAUFSCHRIFT[c]);
  }
  ledmatrix.send();
  i--;
}



void loop() {
  updateTimer.run();
  loopTextTimer.run();
}
