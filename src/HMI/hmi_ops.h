#ifndef __HMI_OPS_H__
#define __HMI_OPS_H__

#include <ArduinoJson.h>

static bool docUpdated = false;
static DynamicJsonDocument doc(4096);

void pullJson(void);
byte getIconIndex(const char*);
void updateHmi(const DynamicJsonDocument&);

#endif
