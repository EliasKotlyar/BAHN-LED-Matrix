int RCKPIN = D1;  // Rck Pin
int SERIN = D2;   // SERPin
int SRCK = D3;  // SerClk Pin
int A2PIN = D4;
int A1PIN = D5;
int A0PIN = D6;

void setRow(int rowNr){
  int A0Value;
int A1Value;
int A2Value;
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
    RCKPIN,
    SERIN,
    SRCK,   
    A0PIN,
    A1PIN,
    A2PIN
  };
  for (int i = 0; i < sizeof(pinArray); i++) {
    pinMode(pinArray[i], OUTPUT);
    digitalWrite(pinArray[i], LOW);
  }
  
}

void sendByte(int b) {
  shiftOut(SERIN, SRCK, MSBFIRST, b);
  // shift out the bits:

}


void sendLine(){
  for(int number = 0; number < 17; number ++){
      sendByte(number);
    }
    //delay(25);     
    digitalWrite(RCKPIN, HIGH);
    delayMicroseconds(50);
    digitalWrite(RCKPIN, LOW);   
}

void loop() {
for(byte i = 0; i < 8; i++){
  setRow(i);
  sendLine();
  delay(1000);
}

               
   

     


    


    


}



