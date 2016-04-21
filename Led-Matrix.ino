int latchPin = 12;  // Rck Pin / pin 12
int dataPin = 11;   // SERPin / pin 11 (MOSI pin)
int clockPin = 13;  // SerClk Pin / pin 13 (SCK pin)
int A2PIN = 7;
int A1PIN = 6;
int A0PIN = 5;
int A0Value;
int A1Value;
int A2Value;
byte lineNr = 0;
#include "TimerOne.h"
//#include "digitalWrite.h"
#include <SPI.h>
byte displayMatrix[17][7];

SPISettings settingsA(16000000, MSBFIRST, SPI_MODE0);
/**
   Sets a Row According to the Set
   http://stackoverflow.com/questions/8695945/c-get-a-bit-from-a-byte
*/
void setRow(int rowNr) {
  switch (rowNr) {
    case 0:
      A0Value = 0;
      A1Value = 0;
      A2Value = 0;
      break;
    case 1:
      A0Value = 0;
      A1Value = 1;
      A2Value = 0;
      break;
    case 2:
      A0Value = 0;
      A1Value = 0;
      A2Value = 1;
      break;
    case 3:
      A0Value = 1;
      A1Value = 1;
      A2Value = 0;
      break;
    case 4:
      A0Value = 0;
      A1Value = 1;
      A2Value = 1;
      break;
    case 5:
      A0Value = 1;
      A1Value = 0;
      A2Value = 1;
      break;
    case 6:
      A0Value = 1;
      A1Value = 1;
      A2Value = 1;
      break;
    case 7:
      A0Value = 1;
      A1Value = 0;
      A2Value = 0;
      break;
  }
  digitalWrite(A0PIN, A0Value);
  digitalWrite(A1PIN, A1Value);
  digitalWrite(A2PIN, A2Value);

}
void setup() {
  Serial.begin(9600);
  byte pinArray[] = {
    latchPin,
    clockPin,
    dataPin,
    A0PIN,
    A1PIN,
    A2PIN
  };
  for (int i = 0; i < sizeof(pinArray); i++) {
    //Serial.println(pinArray[i]);

    pinMode(pinArray[i], OUTPUT);
    digitalWrite(pinArray[i], LOW);
  }
  
  



  for (byte number = 0; number < 17; number ++) {
    for(byte line = 0; line < 8; line ++){
      displayMatrix[number][line] = 0;
    }
    
  }

  Timer1.initialize(500);
  Timer1.attachInterrupt(umschalten);


}






void umschalten() {

  setRow(lineNr);
  SPI.begin();
  SPI.beginTransaction(settingsA);

  // Send Line:
  for (byte number = 0; number < 17; number++) {
    byte transferbuffer = displayMatrix[number][lineNr];
    //transferbuffer = 255;
    //transferbuffer = 0;
    SPI.transfer(transferbuffer);
   
    Serial.print("LEDNR:");
    Serial.print(number);
    Serial.print(" LineNR");
    Serial.print(lineNr);
    Serial.println();

    Serial.println(transferbuffer);
    //delay(10000);

  }
  SPI.endTransaction();
  SPI.end();

  digitalWrite(latchPin, HIGH);
  delayMicroseconds(300);
  digitalWrite(latchPin, LOW);
  
  //SPI.endTransaction();
  // Increase Line Number


  lineNr++;
  if (lineNr == 8 ) {
    lineNr = 0;
  }
}
void loop() {
  
  delay(1000);
  //displayMatrix[number][lineNr]
  //umschalten();
  //  delay(500);

  //delayMicroseconds(500);













}



