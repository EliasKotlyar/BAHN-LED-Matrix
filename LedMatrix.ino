#include "LedMatrix.h"
#include "TimerOne.h"
#include <Sprite.h>
//#include "digitalWrite.h"
LedMatrix ledmatrix;
int i;
int j;

Sprite letter_L = Sprite(5, 8,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11111,
  B11111
);

bool state;

void setup() {
  Serial.begin(9600);


  Timer1.initialize(1000);
  Timer1.attachInterrupt(umschalten);

  //ledmatrix.writeSprite(0, letter_L);

  String myStr = "BBBBBBBBBBBBBBBBBBB";

  for(byte c = 0; c < 8 ; c++){
      //ledmatrix.writeFont(2 + c ,myStr[c]);
      //ledmatrix.setPixelOnLedMatrix(0,c,1,1);
  }





  i = 0;
  j = 0;
  //ledmatrix.update();
  state = true;

}


void umschalten(){
 ledmatrix.update();
}




void loop() {

  ledmatrix.setPixel(i,1,state);
  delay(100);
  i++;
  if (i == 136 ) {
    i = 0;
    state = !state;
  }
  //delayMicroseconds(1000);
  /*


  ledmatrix.setPixelOnLedMatrix(0,j,i,1);
  //ledmatrix.setPixelOnLedMatrix(0,1,0,1);
  //ledmatrix.setPixelOnLedMatrix(0,0,1,1);
  j++;


  */

  //displayMatrix[number][lineNr]
  //umschalten();
  //  delay(500);

  //delayMicroseconds(500);













}
