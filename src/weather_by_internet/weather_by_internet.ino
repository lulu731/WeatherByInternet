#include <ArduinoHttpClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "Nextion.h"
#include "secrets.h"
#include "json_ops.h"
#include "w_OTA.h"
#include "sleep.h"
#include "hmi_ops.h"

void setup() {
  nexInit();
  dbSerialPrintln("Serial OK");

  WiFi.begin(ssid, password);
  dbSerialPrintln("connecting");
  dbSerialPrint("ssid : ");
  dbSerialPrintln(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    dbSerialPrint(".");
    delay(500);
  }

  otaUpdate();
  //wait for about 25 sec to update sketch
  dbSerialPrintln("ReadyOTA");
  pinMode(0, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  for (byte i; i < 250; i++) {
    ArduinoOTA.handle();
    delay(100);
  };
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(0, INPUT);
  dbSerialPrintln("setup done");
}

void loop() {
  byte cnt = 0;
  DynamicJsonDocument doc(12288);
  while (!RequestJson(doc) && cnt < 5) {
    dbSerialPrintln(cnt);
    cnt++;
  };
  if (cnt < 5) {
    UpdateHmi(doc);
    GoToSleep();  
  } else {
    dbSerialPrintln("HMI not updated");
  };
}
