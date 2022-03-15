#include "NexConfig.h"
#ifndef __W_OTA_H__
#define __W_OTA_H__

#include <ArduinoOTA.h>

void otaUpdate() {
  ArduinoOTA.onStart([]() {
    String type;
      if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
      } else {  // U_FS
      type = "filesystem";
      }

      // NOTE: if updating FS this would be the place to unmount FS using FS.end()
      dbSerialPrintln("Start updating " + type);
  });

  ArduinoOTA.onEnd([]() {
    dbSerialPrintln("\nEnd");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    char str[20];
    sprintf(str, "Progress: %u%%\r", (progress / (total / 100)));
    dbSerialPrintln(str);
  });

  ArduinoOTA.onError([](ota_error_t error) {
    char str[20];
    sprintf(str, "Error[%u]: ", error);
    dbSerialPrintln(str);
    if (error == OTA_AUTH_ERROR) {
      dbSerialPrintln("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      dbSerialPrintln("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      dbSerialPrintln("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      dbSerialPrintln("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      dbSerialPrintln("End Failed");
    }
  });

  ArduinoOTA.begin();

  dbSerialPrintln("Ready");
  dbSerialPrint("IP address: ");
  dbSerialPrintln(WiFi.localIP());
}

#endif
