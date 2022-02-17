#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
//#include "secrets.h"

#include <ArduinoJson.h>
#include <SerialCmd.h>
#include "json_ops.h"
#include "w_OTA.h"
#include "sleep.h"

SerialCmd serCmd(Serial, SERIALCMD_LF);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(300);                       
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(300); 
  digitalWrite(LED_BUILTIN, HIGH);
  delay(300);                       
  digitalWrite(LED_BUILTIN, LOW);
  delay(300); 
  digitalWrite(LED_BUILTIN, HIGH);
  delay(300);                       
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(LED_BUILTIN, INPUT);
  
  //wake-up arduino
  pinMode(arduinoWakeUpPin, OUTPUT);
  digitalWrite(arduinoWakeUpPin, LOW);
  delay(100);
  digitalWrite(arduinoWakeUpPin, HIGH);
  
  Serial.begin(115200);
  while (!Serial) {
    ;
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
    delay(500);
  }

  otaUpdate();
  serCmd.AddCmd("REQJSO", SERIALCMD_FROMSERIAL, requestJson);
  serCmd.AddCmd("SLEEP", SERIALCMD_FROMSERIAL, goToSleep);

  Serial.print("SEROK\n");
}

void loop() {
  ArduinoOTA.handle();
  serCmd.ReadSer();
}
