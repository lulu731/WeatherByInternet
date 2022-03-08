#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "secrets.h"
#include "json_ops.h"
#include "w_OTA.h"
#include "sleep.h"

#include "Nextion.h"
#include "hmi_ops.h"

void setup() {
  nexInit();
  dbSerialPrintln("Serial OK");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
    delay(500);
  }

  otaUpdate();
  //wait for about 25 sec to update sketch
  for (byte i; i < 250; i++) {
    ArduinoOTA.handle();
    delay(100);
  }
  
}

void loop() {
  byte cnt = 0;
  DynamicJsonDocument doc(12288);
  while (!RequestJson(doc) && cnt < 5) {
    UpdateHmi(doc);
    cnt++;
  };
  GoToSleep();
}