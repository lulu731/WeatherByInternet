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
  WakeUpArduino();
  
  Serial.begin(115200);
  while (!Serial) {
    ;
  }

  nexInit();
  dbSerialPrintln("Serial OK");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
    delay(500);
  }

  otaUpdate();
}

void loop() {
  ArduinoOTA.handle();



  if (jsonToRequest) {
    Serial3.print("REQJSO\n");
    jsonToRequest = false;
  }
  
  //update screen when JSON doc is updated
  if (docUpdated) {
    //Serial.println("update HMI");
    HMIUpdated = UpdateHmi(doc);
    docUpdated = false;
  }  

  //send go to sleep signal to ESP and board sleeps if HMI is updated
  if (HMIUpdated) {
    HMIUpdated = false;
    Serial3.print("SLEEP\n"); 
    //Serial.println("");
    dbSerialPrintln("go to sleep");
    goToSleep();
    //Serial.println("woke up");
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
  }


}
