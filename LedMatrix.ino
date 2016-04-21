#include "LedMatrix.h"
#include "TimerOne.h"
//#include "digitalWrite.h"
LedMatrix ledmatrix;
int i;
int j;

void setup() {
  Serial.begin(9600);


  Timer1.initialize(1000);
  Timer1.attachInterrupt(umschalten);
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
