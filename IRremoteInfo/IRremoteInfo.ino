/* ***************************************************
IR Remote 
HX1838 remote controller and VS1838 sensor.
VS1838 sensor S -» Arduino PIN 12
VS1838 sensor - -» Arduino GND
VS1838 sensor + -» Arduino +3.3V

Version: 1.0.0
Date: 2025.03.09.
Author: Sümegi Zoltán Péter
Dependency: IRremote.h, ArduinoGraphics.h, Arduino_LED_Matrix.h

Based on: https://arduino-tutorials.net/tutorial/control-arduino-with-ir-receiver-and-remote but modernized.
Based on: Examples - LED_Matrix - TextWithArduinoGraphics
*************************************************** */
#include <IRremote.h>

// TextAnimation works only when ArduinoGraphics is installed and used.
// ArduinoGraphics is an external library and needs to be installed using
// Library Manager.
// To use ArduinoGraphics APIs, please include BEFORE Arduino_LED_Matrix
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

int IrReceiverPin = 12;
decode_results results;
IRrecv irrecv(IrReceiverPin);

void setup() {
   Serial.begin(9600);
   pinMode(LED_BUILTIN, OUTPUT);
   Serial.println("Starting IR-receiver...");
 
   irrecv.enableIRIn();
   Serial.println("IR-receiver active");
 
   digitalWrite(LED_BUILTIN, LOW);

   matrix.begin();
 }

void loop() {
  if (irrecv.decode()) {
 
    //Serial.println(irrecv.decodedIRData.decodedRawData, HEX);
    switch (irrecv.decodedIRData.decodedRawData) {
      case 0xBA45FF00:  // button 1
          Serial.println(1);
          show("1");
          break;

      case 0xB946FF00:  // button 2
          Serial.println(2);
          show("2");
          break;  

      case 0xB847FF00:  // button 3
          Serial.println(3);
          show("3");
          break;  

      case 0xBB44FF00:  // button 4
          Serial.println(4);
          show("4");
          break;  

      case 0xBF40FF00:  // button 5
          Serial.println(5);
          show("5");
          break;  

      case 0xBC43FF00:  // button 6
          Serial.println(6);
          show("6");
          break;  

      case 0xF807FF00:  // button 7
          Serial.println(7);
          show("7");
          break;  

      case 0xEA15FF00:  // button 8
          Serial.println(8);
          show("8");
          break;  

      case 0xF609FF00:  // button 9
          Serial.println(9);
          show("9");
          break;  

      case 0xE619FF00:  // button 0
          Serial.println(0);
          show("0");
          break;  

      case 0xE718FF00:  // button UP
          Serial.println("UP");
          showScroll("UP");
          break;  

      case 0xAD52FF00:  // button DOWN
          Serial.println("DOWN");
          showScroll("DOWN");
          break;  

      case 0xF708FF00:  // button LEFT
          Serial.println("LEFT");
          showScroll("LEFT");
          break;  

      case 0xA55AFF00:  // button RIGTH
          Serial.println("RIGTH");
          showScroll("RIGTH");
          break;  

      case 0xE31CFF00:  // button OK
          Serial.println("OK");
          showScroll("OK");
          break;  

      case 0xE916FF00:  // button *
          Serial.println("*");
          show("*");
          break;  

      case 0xF20DFF00:  // button #
          Serial.println("#");
          show("#");
          break;        
     }
     irrecv.resume();
 
     switch (irrecv.decodedIRData.decodedRawData) {
         case 0xE916FF00:  // button *
             digitalWrite(LED_BUILTIN, HIGH);
             break;
 
         case 0xF20DFF00:  // button #
             digitalWrite(LED_BUILTIN, LOW);
             break;        
     }
 
   }
 
   delay(100);         
}


void show(char text[]) {
  showScroll(text);
}

void showScroll(char text[]) {
  // Make it scroll!
  matrix.beginDraw();

  matrix.stroke(0xFFFFFFFF);
  matrix.textScrollSpeed(50);

  // add the text
  matrix.textFont(Font_5x7);
  matrix.beginText(10, 1, 0xFFFFFF);
  matrix.println(text);
  matrix.endText(SCROLL_LEFT);

  matrix.endDraw();
}