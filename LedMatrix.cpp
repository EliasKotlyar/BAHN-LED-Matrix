
#include "LedMatrix.h"

SPISettings settingsA(16000000, MSBFIRST, SPI_MODE0);

LedMatrix::LedMatrix(void)
{
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
}
void LedMatrix::setPixel(byte x,byte y,byte state){

}

void LedMatrix::writeSprite(byte ledMatrixNr,Sprite sprite)
{
  for (uint8_t i = 0; i < sprite.height(); i++){
    for (uint8_t j = 0; j < sprite.width(); j++){
      byte buffer = sprite.read(j, i);
      setPixelOnLedMatrix(ledMatrixNr,j,i,buffer);
    }
  }
}
void LedMatrix::writeFont(byte ledMatrixNr,char c)
{
  //Serial.println((byte)c);
  for (uint8_t i = 0; i < 8; i++){
    byte charo = pgm_read_byte(&font_8x8_col[c][i]);
    //Serial.println(charo, HEX);

    for (uint8_t j = 0; j < 8; j++){
      byte bit = (charo >> j) & 1;
      //Serial.print(bit);
      setPixelOnLedMatrix(ledMatrixNr,7-i,j,bit);
    }
    //Serial.println();

  }

}

/**
http://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit-in-c-c
*/
void LedMatrix::setPixelOnLedMatrix(byte lednr,byte x,byte y,byte state){
  byte number = displayMatrix[lednr][y];
  number ^= (-state ^ number) & (1 << x);
  displayMatrix[lednr][y] = number;
}

void LedMatrix::update(void) {

  setRow(lineNr);
  SPI.begin();
  SPI.beginTransaction(settingsA);

  // Send Line:
  for (byte number = 0; number < 17; number++) {
    byte transferbuffer = displayMatrix[number][lineNr];
    //transferbuffer = 255;
    //transferbuffer = 0;
    SPI.transfer(transferbuffer);

    /*
    Serial.print("LEDNR:");
    Serial.print(number);
    Serial.print(" LineNR");
    Serial.print(lineNr);
    Serial.println();
    */

    //Serial.println(transferbuffer);
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
/**
   Sets a Row According to the Set
   http://stackoverflow.com/questions/8695945/c-get-a-bit-from-a-byte
*/

void LedMatrix::setRow(byte rowNr) {
  byte A0Value;
  byte A1Value;
  byte A2Value;
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
