#include "LedMatrix.h"
#include "TimerOne.h"
#include <Sprite.h>
//#include "digitalWrite.h"
LedMatrix ledmatrix;
int i;
String LAUFSCHRIFT = "MUNICHMAKERLAB";
byte speed = 0;
byte stringLen;


void setup() {
  Serial.begin(9600);


  Timer1.initialize(1000);
  Timer1.attachInterrupt(umschalten);

  //ledmatrix.writeSprite(0, letter_L);
  stringLen = LAUFSCHRIFT.length();
  




}


void umschalten(){
 ledmatrix.update();
}




void loop() {

  ledmatrix.clearMatrix();
  for(byte c = 0; c < stringLen ; c++){
      ledmatrix.writeFont(i+c*8,LAUFSCHRIFT[c]);
  }
  ledmatrix.send();

  delay(speed);

  i++;













}
