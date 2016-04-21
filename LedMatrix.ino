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



void setup() {
  Serial.begin(9600);


  Timer1.initialize(1000);
  Timer1.attachInterrupt(umschalten);

  //ledmatrix.writeSprite(0, letter_L);

  String myStr = "BBBBBBBBBBBBBBBBBBB";

  for(byte c = 0; c < 10 ; c++){
      ledmatrix.writeFont(2 + c ,myStr[c]);
  }





  i = 0;
  j = 0;

}


void umschalten(){
 ledmatrix.update();
}




void loop() {


  delay(1000);
  ledmatrix.setPixelOnLedMatrix(0,j,i,1);
  //ledmatrix.setPixelOnLedMatrix(0,1,0,1);
  //ledmatrix.setPixelOnLedMatrix(0,0,1,1);
  i++;
  if (i == 8 ) {
    i = 0;
    j++;
  }
  //displayMatrix[number][lineNr]
  //umschalten();
  //  delay(500);

  //delayMicroseconds(500);













}
