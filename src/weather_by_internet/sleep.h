#include <sys/_stdint.h>
#include "core_esp8266_features.h"
#include "Esp.h"
#ifndef __SLEEP_H__
#define __SLEEP_H__

const uint64_t oneHour = 180E6;//3600E6;
const int arduinoWakeUpPin = 5;

void wakeUp() {
  //ISR
  //detachInterrupt(0);
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
  pinMode(LED_BUILTIN, INPUT);
  ESP.deepSleep( oneHour - micros());
}

#endif