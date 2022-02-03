#ifndef __HOST_DATA_H__
#define __HOST_DATA_H__

#include "secrets.h"

static const char* host = "api.openweathermap.org";
static const int httpPort = 80;
static String url = "/data/2.5/forecast?q=brest,fr&units=metric&appid=" + apiKey;

#endif
