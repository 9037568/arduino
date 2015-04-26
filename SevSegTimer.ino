#include <LedControl.h>

#include "LedControl.h"

/* data,clock,load,numDevices */
LedControl lc=LedControl(5,3,4,1);
String state;
unsigned long runTime;
unsigned long counter;
unsigned long lastCheck;

void setup()
{
  Serial.begin(9600);
  pinMode(8, INPUT_PULLUP);
  runTime = 0;
  lc.shutdown(0, false);
  lc.setIntensity(0,15);
  lc.clearDisplay(0);
  state = "running";
}

void display(unsigned long count)
{
  unsigned long temp = count;
  int digitValue;
  int cursor = 0;
  digitValue = temp%10;
  temp = temp/10;
  lc.setDigit(0, cursor, digitValue, false);
  while( temp != 0 ) {
    cursor++;
    digitValue = temp%10;
    temp = temp/10;
    lc.setDigit(0, cursor, digitValue, false);
  }
}

void loop()
{
  unsigned long newCheck = millis();
  int latchState;
  
  if( newCheck - lastCheck > 999 ) {
    latchState = digitalRead(8);
    if( latchState == HIGH ) { //door is open
      state = "stopped";
    }
    else { //door is closed
      state = "running";
    }
    
    if( Serial.available() > 0 ) {
      String command = Serial.readString();
      if( command == "hide" ) {
        lc.shutdown(0, true);
      }
      else if( command == "show" ) {
        lc.shutdown(0, false);
      }
      else if( command == "reset" ) {
        counter = 0;
      }
      else if( command == "stop" ) {
        state = "stopped";
      }
      else if( command == "start" ) {
        state = "running";
      }
    }
  }

  if( state == "running" ) {
    if( newCheck - lastCheck > 999 ) {
      counter++;
      lastCheck = newCheck;
      display(counter);
    }
  }
}

