#ifndef __HOST_DATA_H__
#define __HOST_DATA_H__

#include "secrets.h"

const char* host = "api.openweathermap.org";
const int httpPort = 80;
String url = "/data/2.5/weather?q=brest,fr&units=metric&appid=" + apiKey;

#endif
