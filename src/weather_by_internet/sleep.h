#ifndef __SLEEP_H__
#define __SLEEP_H__

const uint64_t oneHour = 3600E6;

void GoToSleep() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
 
  dbSerialPrintln("going to sleep");
  ESP.deepSleep( oneHour );
}

#endif
