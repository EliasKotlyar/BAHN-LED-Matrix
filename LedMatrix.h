#include <SPI.h>
#include "Arduino.h"
#include "SimpleTimerDelegate.h"
#include "font_8x8_col.h"
#include "FastDelegate.h"
using namespace fastdelegate;

extern "C" {
  #include "user_interface.h"
}

typedef FastDelegate1<int> FuncDelegate;

class LedMatrix
{
  public:

    LedMatrix(void);
    void setPixel(byte x,byte y,byte state);
    void update(void);
    void setRow(byte rowNr);
    void setPixelOnLedMatrix(byte lednr,byte x,byte y,byte state);
    void writeFont(byte ledMatrixNr,char c);
    void clearMatrix();
    void send();
    void loop();
    void setScrollSpeed(byte speed);
    void setText(String text);
    void switchLEDs(int c);
    void loopText(int con);
    void startScroll();
    void toggleWC(byte state);
  private:
    int latchPin = D8;  // Rck Pin / pin 12
    int dataPin = D7;   // SERPin / pin 11 (MOSI pin)
    int clockPin = D5;  // SerClk Pin / pin 13 (SCK pin)
    int A2PIN = D3;
    int A1PIN = D2;
    int A0PIN = D1;
    int WCPIN = D4;
    byte lineNr = 0;

    #define MAX_X 17
    #define MAX_Y 8
    #define MAX_LEN 136

    byte displayMatrix[MAX_X][MAX_Y];
    byte shadowMatrix[MAX_X][MAX_Y];

    // Loop Text Functions:
    SimpleTimerDelegate updateTimer;
    SimpleTimerDelegate loopTextTimer;
    String scrollText;
    int strCounter = 0;
    byte stringLen;
    byte scrollSpeed = 100;
};
