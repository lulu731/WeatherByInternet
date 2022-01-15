#include "hmi_ops.h"
#include <Nextion.h>

NexText city = NexText(0, 14, "city");

NexPicture weatherIcon = NexPicture(0, 13, "weather_icon");
NexText temp = NexText(0, 15, "temp");
NexText feelTemp = NexText(0, 16, "feel_temp");
NexText pressure = NexText(0, 17, "pressure");
NexText humidity = NexText(0, 18, "humidity");

NexPicture w_i1 = NexPicture(0, 3, "w_i1");
NexText temp1 = NexText(0, 4, "temp1");
NexText press1 = NexText(0, 6, "press1");
NexText wind1 = NexText(0, 5, "wind1");
NexText hum1 = NexText(0, 1, "hum1");

NexPicture w_i2 = NexPicture(0, 7, "w_i2");
NexText temp2 = NexText(0, 21, "temp2");
NexText press2 = NexText(0, 23, "press2");
NexText wind2 = NexText(0, 22, "wind2");
NexText hum2 = NexText(0, 19, "hum2");

NexPicture w_i3 = NexPicture(0, 8, "w_i3");
NexText temp3 = NexText(0, 9, "temp1");
NexText press3 = NexText(0, 11, "press3");
NexText wind3 = NexText(0, 10, "wind3");
NexText hum3 = NexText(0, 2, "hum3");

NexPicture w_i4 = NexPicture(0, 12, "w_i4");
NexText temp4 = NexText(0, 24, "temp4");
NexText press4 = NexText(0, 26, "press4");
NexText wind4 = NexText(0, 25, "wind4");
NexText hum4 = NexText(0, 20, "hum4");

NexObject day0[] = { weatherIcon, temp, feelTemp, pressure, humidity};
NexObject day1[] = { w_i1, temp1, press1, wind1, hum1 };
NexObject day2[] = { w_i2, temp2, press2, wind2, hum2 };
NexObject day3[] = { w_i3, temp3, press3, wind3, hum3 };
NexObject day4[] = { w_i4, temp4, press4, wind4, hum4 };

const char* pictures[] = {"01d", "02d", "03d", "04d", "09d", "10d", "11d", "13d", "50d", "01n", "02n", "03n", "04n", "09n", "10n", "11n", "13n", "50n"};

byte getIconIndex(const char* ch) {
  for (byte index = 0; index < 18; index++) {
    if (strcmp(pictures[index], ch) == 0) {
      return index;
    }
  }
  return 0;
}

void updateHmi(const StaticJsonDocument<1024>& doc) {
  char str[10];
  const char* icon = doc["weather"][0]["icon"];
  weatherIcon.setPic(getIconIndex(icon));
  city.setText(doc["name"]);


  sprintf(str, "%f%.1", (doc["main"]["temp"]).as<float>());
  strcat(str, " °C");
  temp.setText(str);

  sprintf(str, "%f%.1", (doc["main"]["feels_like"]).as<float>());
  strcat(str, " °C");
  feelTemp.setText(str);

  sprintf(str, "%d", (doc["main"]["pressure"]).as<int>());
  strcat(str, " hPa");
  pressure.setText(str);

  sprintf(str, "%d", (doc["main"]["humidity"]).as<int>());
  strcat(str, "%");
  humidity.setText(str);
}
