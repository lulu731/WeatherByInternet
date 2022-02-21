#ifndef __SLEEP_H__
#define __SLEEP_H__

#include <LowPower.h>

//ISR
void wakeUp() {
  detachInterrupt(2);
}

void goToSleep() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);                       
  digitalWrite(LED_BUILTIN, LOW);    
  delay(500); 
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);                      
  digitalWrite(LED_BUILTIN, LOW);
  delay(500); 
  pinMode(LED_BUILTIN, INPUT);
  attachInterrupt(2, wakeUp, LOW);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
}

#endif
