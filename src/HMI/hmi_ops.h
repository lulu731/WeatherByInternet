#ifndef __HMI_OPS_H__
#define __HMI_OPS_H__

#include <ArduinoJson.h>

static bool docUpdated = false;
static bool HMIUpdated = false;
static DynamicJsonDocument doc(4096);

void pullJson();
byte getIconIndex(const char*);
bool updateHmi(const DynamicJsonDocument&);

#endif
