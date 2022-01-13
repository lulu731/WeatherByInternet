#ifndef __HMI_OPS_H__
#define __HMI_OPS_H__

NexText city = NexText(0, 14, "city");

NexPicture weatherIcon = NexPicture(0, 13, "weather_icon");
NexText temp = NexText(0, 15, "temp");
NexText feelTemp = NexText(0, 16    , "feel_temp");
NexText pressure = NexText(0, 17, "pressure");
NexText humidity = NexText(0, 18, "humidity");

NexPicture w_i1 = NexPicture(0, 10, "w_i1");
NexText temp1 = NexText(0, 30, "temp1");
NexText press1 = NexText(0, 50, "press1");
NexText wind1 = NexText(0, 40, "wind1");
NexText hum1 = NexText(0, 60, "hum1");

NexPicture w_i2 = NexPicture(0, 12, "w_i2");
NexText temp2 = NexText(0, 32, "temp2");
NexText press2 = NexText(0, 52, "press2");
NexText wind2 = NexText(0, 42, "wind2");
NexText hum2 = NexText(0, 62, "hum2");

NexPicture w_i3 = NexPicture(0, 19, "w_i3");
NexText temp3 = NexText(0, 33, "temp1");
NexText press3 = NexText(0, 53, "press3");
NexText wind3 = NexText(0, 43, "wind3");
NexText hum3 = NexText(0, 63, "hum3");

NexPicture w_i4 = NexPicture(0, 18, "w_i4");
NexText temp4 = NexText(0, 34, "temp4");
NexText press4 = NexText(0, 54, "press4");
NexText wind4 = NexText(0, 44, "wind4");
NexText hum4 = NexText(0, 64, "hum4");

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


  sprintf(str, "%d", (int)(doc["main"]["temp"]));
  strcat(str, " °C");
  temp.setText(str);

  sprintf(str, "%d", (int)(doc["main"]["feels_like"]));
  strcat(str, " °C");
  feelTemp.setText(str);

  sprintf(str, "%d", (int)(doc["main"]["pressure"]));
  strcat(str, " hPa");
  pressure.setText(str);

  sprintf(str, "%d", (int)(doc["main"]["humidity"]));
  strcat(str, "%");
  humidity.setText(str);
}

#endif
