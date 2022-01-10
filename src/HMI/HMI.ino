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

bool foundReadyJson = false;
void loop() {
  if (!foundReadyJson) {
    if (Serial3.findUntil("readyJson\r\n", "\n")) {
      foundReadyJson = true;
    }
  } else {
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, Serial3);

    if (error) {
      //Serial.print(F("deserializeJson() failed: "));
      //Serial.println(error.f_str());
      foundReadyJson = false;
      return;
    };

    char str[6];
    const char* icon = doc["weather"][0]["icon"];
    weatherIcon.setPic(getIconIndex(icon));
    city.setText(doc["name"]);


    sprintf(str, "%d", (int)(doc["main"]["temp"]));
    temp.setText(str);
    sprintf(str, "%d", (int)(doc["main"]["feels_like"]));
    feelTemp.setText(str);
    sprintf(str, "%d", (int)(doc["main"]["pressure"]));
    pressure.setText(str);
    sprintf(str, "%d", (int)(doc["main"]["humidity"]));
    humidity.setText(str);

    foundReadyJson = false;
  }
}
