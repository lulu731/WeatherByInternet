#include <Nextion.h>
#include <ArduinoJson.h>
#include "hmi_ops.h"

NexPicture weatherIcon = NexPicture(0, 1, "weather_icon");
NexText city = NexText(0, 2, "city");
NexText temp = NexText(0, 3, "temp");
NexText feelTemp = NexText(0, 4, "feel_temp");
NexText pressure = NexText(0, 5, "pressure");
NexText humidity = NexText(0, 6, "humidity");

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial3.begin(115200);
  while (!Serial3) {
    ;
  }
}

void loop() {
  while (Serial3.available()){
    char buff[256];
    memset(buff, "\0", 256);
    int nbrBytes = Serial3.readBytesUntil("\n", buff, 256);
    Serial.println(buff);
    
    if (nbrBytes >= 8) {
      char* readyJson = buff + (nbrBytes - 8);//get last 8 chars then compare with "readyJson"
      if (strcmp(readyJson, "readyJson") == 0) {
        StaticJsonDocument<1024> doc;
        DeserializationError error = deserializeJson(doc, Serial3);
        
        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          return;
        };
      
      char str[6];

      weatherIcon.setPic(getIconIndex(doc["weather"]["icon"]));
      city.setText(doc["name"]);
      temp.setText(printf(str, "%d", (int)doc["main"]["temp"]));
      feelTemp.setText(printf(str, "%d", (int)doc["main"]["feels_like"]));
      pressure.setText(printf(str, "%d", (int)doc["main"]["pressure"]));
      humidity.setText(printf(str, "%d", (int)doc["main"]["humidity"]));

      Serial.println(getIconIndex(doc["weather"]["icon"]));
      //Serial.println(String(doc["name"]));
      Serial.println(printf(str, "%d", (int)doc["main"]["temp"]));
      Serial.println(printf(str, "%d", (int)doc["main"]["feels_like"]));
      Serial.println(printf(str, "%d", (int)doc["main"]["pressure"]));
      Serial.println(printf(str, "%d", (int)doc["main"]["humidity"]));
      }
    }
  }
  //while(1);
}
