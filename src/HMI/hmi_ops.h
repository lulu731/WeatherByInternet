#ifndef __HMI_OPS_H__
#define __HMI_OPS_H__

NexText city = NexText(0, 2, "city");

NexPicture weatherIcon = NexPicture(0, 1, "weather_icon");
NexText temp = NexText(0, 3, "temp");
NexText feelTemp = NexText(0, 4, "feel_temp");
NexText pressure = NexText(0, 5, "pressure");
NexText humidity = NexText(0, 6, "humidity");

const char* pictures[] = {"01d", "02d", "03d", "04d", "09d", "10d", "11d", "13d", "50d", "01n", "02n", "03n", "04n", "09n", "10n", "11n", "13n", "50n"};

byte getIconIndex(const char* ch) {
  for (byte index = 0; index < 18; index++) {
    if (strcmp(pictures[index], ch)== 0){
      return index; 
    }
  }
  return 0;
}

void updateHmi(const StaticJsonDocument<1024>& doc) {
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
}

#endif
