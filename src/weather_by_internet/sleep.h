#ifndef __SLEEP_H__
#define __SLEEP_H__

const uint64_t oneHour = 3600E6;
const int arduinoWakeUpPin = 5;

void GoToSleep() {
  //pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);                       
  digitalWrite(LED_BUILTIN, LOW);    
  delay(500); 
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);                      
  digitalWrite(LED_BUILTIN, LOW);
  //pinMode(LED_BUILTIN, INPUT);
  ESP.deepSleep( oneHour - micros());
}

void WakeUpArduino() {
  pinMode(arduinoWakeUpPin, OUTPUT);
  digitalWrite(arduinoWakeUpPin, HIGH);
  delay(500);
  digitalWrite(arduinoWakeUpPin, LOW);
}
#endif
