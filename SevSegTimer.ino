#include <LedControl.h>

#include "LedControl.h"

/* data,clock,load,numDevices */
LedControl lc=LedControl(5,3,4,1);
unsigned long runTime;
unsigned long counter;

void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(0);
  runTime = 0;
  lc.shutdown(0, false);
  lc.setIntensity(0,15);
  lc.clearDisplay(0);
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
  delay(1000);
  counter++;
  Serial.print("Time: ");
  Serial.println(millis());
  Serial.print("Counter: ");
  Serial.println(counter);
  display(counter);
  String command = Serial.readString();
  if( command == "hide" ) {
    lc.shutdown(0, true);
  }
  else if( command == "show" ) {
    lc.shutdown(0, false);
  }
}

