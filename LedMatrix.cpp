
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
  //

  FuncDelegate f_delegate;
  f_delegate = MakeDelegate(this, &LedMatrix::switchLEDs);
  updateTimer.setInterval(2, f_delegate);


  clearMatrix();

}
void LedMatrix::clearMatrix(){
  memset( shadowMatrix,0,MAX_LEN);
}
void LedMatrix::setPixel(byte x,byte y,byte state){
  byte lednr = x / 8;
  if(lednr > MAX_X - 1){
      return;
  }
  x = x % 8;
  if(x > 7){
    return;
  }
  x = 7-x;
  setPixelOnLedMatrix(lednr,x,y,state);

}

void LedMatrix::writeFont(byte x,char c)
{

  for (uint8_t i = 0; i < 8; i++){
    byte charo = pgm_read_byte(&font_8x8_col[c][i]);
    for (uint8_t j = 0; j < 8; j++){
      byte bit = (charo >> j) & 1;
      setPixel(x + i,j,bit);
    }


  }

}

/**
http://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit-in-c-c
*/
void LedMatrix::setPixelOnLedMatrix(byte lednr,byte x,byte y,byte state){
  byte number = shadowMatrix[lednr][y];
  number ^= (-state ^ number) & (1 << x);
  shadowMatrix[lednr][y] = number;
}
void LedMatrix::send(){
  memcpy(  displayMatrix, shadowMatrix,MAX_LEN  );
}

void LedMatrix::update(void) {
  setRow(lineNr);

  SPI.begin();
  SPI.beginTransaction(settingsA);



  // Send Line:
  for (byte number = 0; number < 17; number++) {
    byte transferbuffer = displayMatrix[number][lineNr];
    //shiftOut(dataPin, clockPin, MSBFIRST, transferbuffer);
    SPI.transfer(transferbuffer);



  }



  digitalWrite(latchPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(latchPin, LOW);
  //delayMicroseconds(10000);
  //delayMicroseconds(400);
  for (byte number = 0; number < 17; number++) {
    SPI.transfer(0);
  }

  digitalWrite(latchPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(latchPin, LOW);

  SPI.end();


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

void LedMatrix::loopText(int con) {
  clearMatrix();
  for (byte c = 0; c < stringLen ; c++) {
    writeFont(strCounter + c * 8, scrollText[c]);
  }
  send();
  strCounter--;
}
void LedMatrix::switchLEDs(int c) {
  update();
}

void LedMatrix::loop(){
  updateTimer.run();
  loopTextTimer.run();
}
void LedMatrix::setScrollSpeed(byte speed){
  scrollSpeed = speed;
}
void LedMatrix::setText(String text){
  scrollText = text;
  stringLen = text.length();
  strCounter = 136 - stringLen * 8;
}
void LedMatrix::startScroll(){
  FuncDelegate f_delegate;
  f_delegate = MakeDelegate(this, &LedMatrix::loopText);
  loopTextTimer.setInterval(scrollSpeed, f_delegate);
}
