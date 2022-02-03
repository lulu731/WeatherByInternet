#include <ArduinoJson.h>
#include <SerialCmd.h>
#include "hmi_ops.h"


SerialCmd serCmd(Serial3);

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial3.begin(115200);
  while (!Serial3) {
    ;
  }
  serCmd.AddCmd("PULLJS", SERIALCMD_FROMSERIAL, pullJson);
};

bool jsonToRequest = true;
void loop() {
  if (jsonToRequest) {
    Serial3.println("REQJSO");
    jsonToRequest = false;
  }
  serCmd.ReadSer();

  //update screen when JSON doc is updated
  if (docUpdated) {
    updateHmi(doc);
    docUpdated = false;
    jsonToRequest = true;
    delay(120000);//delay for 2 min when updated
  }  
};
