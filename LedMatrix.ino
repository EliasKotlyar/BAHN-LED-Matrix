#include "LedMatrix.h"
#include <Sprite.h>
extern "C" {
#include "user_interface.h"
}
//#include "digitalWrite.h"
LedMatrix ledmatrix;
int i;
String LAUFSCHRIFT = "Munich Maker Lab";
byte speed = 100000;
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
 ledmatrix.update();
}




void loop() {


  ledmatrix.clearMatrix();

  for(byte c = 0; c < stringLen ; c++){
      ledmatrix.writeFont(i+c*8,LAUFSCHRIFT[c]);
  }
  ledmatrix.send();
  delay(speed);
  //i--;













}
