int latchPin = 10;  // Rck Pin
int dataPin = 9;   // SERPin
int clockPin = 8;  // SerClk Pin
int powerPin = 2;
int A2PIN = 7;
int A1PIN = 6;
int A0PIN = 5;
int A0Value;
int A1Value;
int A2Value;
int lineNr = 0;
#include "TimerOne.h"  

/**
 * Sets a Row According to the Set
 * http://stackoverflow.com/questions/8695945/c-get-a-bit-from-a-byte
 */
void setRow(int rowNr){
   // int A0Value = (rowNr >> 0)  & 0x01;
   // int A1Value = (rowNr >> 1)  & 0x01;
   // int A2Value = (rowNr >> 2)  & 0x01;
    
    

    //digitalWrite(A0PIN,A0Value);
    //digitalWrite(A1PIN, A1Value);
    //digitalWrite(A2PIN, A2Value);

    switch(rowNr){
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
    /*

    Serial.print("A0:");
    Serial.println(A0Value);
    Serial.print("A1:");
    Serial.println(A1Value);
    Serial.print("A2:");
    Serial.println(A2Value);
    */
}
void setup() {
   //Serial.begin(9600);
  byte pinArray[] = {
    latchPin,
    clockPin,
    dataPin,
    powerPin,
    A0PIN,
    A1PIN,
    A2PIN,3
  };
  for (int i = 0; i < sizeof(pinArray); i++) {
    //Serial.println(pinArray[i]);
    
    pinMode(pinArray[i], OUTPUT);
    digitalWrite(pinArray[i], LOW);
  }
  //digitalWrite(A2PIN,HIGH);
  //digitalWrite(A1PIN,HIGH);
  //digitalWrite(A0PIN,HIGH);
  digitalWrite(powerPin, HIGH);     
    delay(1000);
        Timer1.initialize(1000000);
    Timer1.attachInterrupt(umschalten);
}

void sendByte(int b) {
  shiftOut(dataPin, clockPin, MSBFIRST, b);
  // shift out the bits:

}


void sendLine(){
  for(int number = 0; number < 17; number ++){
      sendByte(number);
    }
    //delay(25);     
    digitalWrite(latchPin, HIGH);
    //delayMicroseconds(5);
    digitalWrite(latchPin, LOW);   
}
void umschalten(){
   
   setRow(lineNr);
   sendLine();
   lineNr++;
   if(lineNr == 8 ){
     lineNr = 0;
   }
}
void loop() {


               
   

     


    


    


}


