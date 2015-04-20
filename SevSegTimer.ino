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
  if( state == "running" ) {
    unsigned long newCheck = millis();
    if( newCheck - lastCheck > 999 ) {
      counter++;
      lastCheck = newCheck;
      Serial.print("Time: ");
      Serial.println(millis());
      Serial.print("Counter: ");
      Serial.println(counter);
      display(counter);
      if( Serial.available() > 0 ) {
        String command = Serial.readString();
        if( command == "hide" ) {
          lc.shutdown(0, true);
        }
        else if( command == "show" ) {
          lc.shutdown(0, false);
        }
      }
    }
  }
}

