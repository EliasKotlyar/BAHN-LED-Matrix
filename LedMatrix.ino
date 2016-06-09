#include "LedMatrix.h"
#include <Sprite.h>

extern "C" {
#include "user_interface.h"
}
//#include "digitalWrite.h"
LedMatrix ledmatrix;
int i = 0;
String LAUFSCHRIFT = "Munich Maker Lab";
byte speed = 1000;
byte stringLen;

os_timer_t myTimer;

void setup() {
  //Serial.begin(9600);


  os_timer_setfn(&myTimer, umschalten, NULL);
  os_timer_arm(&myTimer, 10, true);

  //ledmatrix.writeSprite(0, letter_L);
  stringLen = LAUFSCHRIFT.length();





}


void umschalten(void *pArg){
 
 for(byte c = 0; c < 8 ; c++){
    ledmatrix.update();
 }
  system_soft_wdt_feed();
}




void loop() {


  ledmatrix.clearMatrix();
  for(byte c = 0; c < stringLen ; c++){
      ledmatrix.writeFont(i+c*8,LAUFSCHRIFT[c]);
  }
  ledmatrix.send();
  delay(speed);
  //umschalten(0);
  
  
  i--;













}
