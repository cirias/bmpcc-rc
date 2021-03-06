/*
   Send a Start/Sop Recording command to the LANC port of a video camera.
   Tested with a Canon XF300 camcorder
   This code requires a simple interface see http://micro.arocholl.com
   Feel free to use this code in any way you want.

   Comprehensive LANC info: www.boehmel.de/lanc.htm

   "LANC" is a registered trademark of SONY.
   CANON calls their LANC compatible port "REMOTE".

   2011, Martin Koch
http://controlyourcamera.blogspot.com/2011/02/arduino-controlled-video-recording-over.html
 */

#include <Arduino.h>

int outPin;
int inPin;

int cmdRepeatCount;
int bitDuration = 104; //Duration of one LANC bit in microseconds. 

void rec() {

  cmdRepeatCount = 0;

  while (cmdRepeatCount < 5) {  //repeat 5 times to make sure the camera accepts the command

    while (pulseIn(inPin, HIGH) < 5000) {   
      //"pulseIn, HIGH" catches any 0V TO +5V TRANSITION and waits until the LANC line goes back to 0V 
      //"pulseIn" also returns the pulse duration so we can check if the previous +5V duration was long enough (>5ms) to be the pause before a new 8 byte data packet
      //Loop till pulse duration is >5ms
    }

    //LOW after long pause means the START bit of Byte 0 is here
    delayMicroseconds(bitDuration);  //wait START bit duration

    //Write the 8 bits of byte 0 
    //"18hex" or “00011000”  tells the camera that there will be a normal command to camera in the next byte
    //Note that the command bits have to be put out in reverse order with the least significant, right-most bit (bit 0) first
    digitalWrite(outPin, LOW);  //Write bit 0. 
    delayMicroseconds(bitDuration); 
    digitalWrite(outPin, LOW);  //Write bit 1 
    delayMicroseconds(bitDuration);  
    digitalWrite(outPin, LOW);  //Write bit 2
    delayMicroseconds(bitDuration); 
    digitalWrite(outPin, HIGH);  //Write bit 3
    delayMicroseconds(bitDuration);  
    digitalWrite(outPin, HIGH);  //Write bit 4
    delayMicroseconds(bitDuration);
    digitalWrite(outPin, LOW);  //Write bit 5 
    delayMicroseconds(bitDuration);
    digitalWrite(outPin, LOW);  //Write bit 6
    delayMicroseconds(bitDuration); 
    digitalWrite(outPin, LOW);  //Write bit 7
    delayMicroseconds(bitDuration);
    //Byte 0 is written now put LANC line back to +5V
    digitalWrite(outPin, LOW);
    delayMicroseconds(10); //make sure to be in the stop bit before byte 1

    while (digitalRead(inPin)) { 
      //Loop as long as the LANC line is +5V during the stop bit
    }

    //0V after the previous stop bit means the START bit of Byte 1 is here
    delayMicroseconds(bitDuration);  //wait START bit duration

    //Write the 8 bits of Byte 1
    //"33hex" or “00110011” sends the  Record Start/Stop command
    //Note that the command bits have to be put out in reverse order with the least significant, right-most bit (bit 0) first
    digitalWrite(outPin, HIGH);  //Write bit 0 
    delayMicroseconds(bitDuration);
    digitalWrite(outPin, HIGH);  //Write bit 1 
    delayMicroseconds(bitDuration); 
    digitalWrite(outPin, LOW);  //Write bit 2
    delayMicroseconds(bitDuration); 
    digitalWrite(outPin, LOW);  //Write bit 3
    delayMicroseconds(bitDuration);
    digitalWrite(outPin, HIGH);  //Write bit 4 
    delayMicroseconds(bitDuration); 
    digitalWrite(outPin, HIGH);  //Write bit 5
    delayMicroseconds(bitDuration);
    digitalWrite(outPin, LOW);  //Write bit 6
    delayMicroseconds(bitDuration);
    digitalWrite(outPin, LOW);  //Write bit 7
    delayMicroseconds(bitDuration);
    //Byte 1 is written now put LANC line back to +5V
    digitalWrite(outPin, LOW); 

    cmdRepeatCount++;  //increase repeat count by 1

    /*Control bytes 0 and 1 are written, now don’t care what happens in Bytes 2 to 7
      and just wait for the next start bit after a long pause to send the first two command bytes again.*/


  }//While cmdRepeatCount < 5
}

void setupLANC(int _outPin, int _inPin) {
  outPin = _outPin;
  inPin = _inPin;

  pinMode(inPin, INPUT); //listens to the LANC line
  pinMode(outPin, OUTPUT); //writes to the LANC line
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(outPin, LOW); //set LANC line to +5V
  digitalWrite(LED_BUILTIN, LOW);

  // delay(5000); //Wait for camera to power up completly
  bitDuration = bitDuration - 8; //Writing to the digital port takes about 8 microseconds so only 96 microseconds are left till the end of each bit
}
