#include <ArduinoJson.h>
#include <SerialCmd.h>
#include "hmi_ops.h"

SerialCmd serCmd(Serial3, SERIALCMD_LF);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial3.begin(115200);
  while (!Serial3) {
    ;
  }
  serCmd.AddCmd("SEROK", SERIALCMD_FROMSERIAL, SerialOK);
  serCmd.AddCmd("PULLJS", SERIALCMD_FROMSERIAL, PullJson);
};

bool jsonToRequest = false;
bool docUpdated = false;
DynamicJsonDocument doc(4096);
  
void loop() {
  serCmd.ReadSer();

  if (jsonToRequest) {
    Serial3.print("REQJSO\n");
    jsonToRequest = false;
  }
  
  //update screen when JSON doc is updated
  if (docUpdated) {
    UpdateHmi(doc);
    docUpdated = false;
    jsonToRequest = true;
    delay(120000);//delay for 2 min when updated
  }
};
