#include <ArduinoJson.h>
#include <SerialCmd.h>
#include "hmi_ops.h"
#include "sleep.h"

const int wakeUpPin = 21;
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

  pinMode(wakeUpPin, INPUT);
  //serCmd.AddCmd("SLEEP", SERIALCMD_FROMSERIAL, goToSleep);
  serCmd.AddCmd("SEROK", SERIALCMD_FROMSERIAL, SerialOK);
  serCmd.AddCmd("PULLJS", SERIALCMD_FROMSERIAL, PullJson);
};

bool jsonToRequest = false;
bool docUpdated = false;
bool HMIUpdated = false;
DynamicJsonDocument doc(4096);
  
void loop() {
  serCmd.ReadSer();

  if (jsonToRequest) {
    Serial3.print("REQJSO\n");
    jsonToRequest = false;
  }
  
  //update screen when JSON doc is updated
  if (docUpdated) {
    HMIUpdated = UpdateHmi(doc);
    docUpdated = false;
    //delay(120000);//delay for 2 min when updated
  }  

  //send go to sleep signal to ESP and board sleeps if HMI is updated
  if (HMIUpdated) {
    HMIUpdated = false;
    Serial3.print("SLEEP\n"); 
    Serial.println("go to sleep");
    goToSleep();

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);                       
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(300); 
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);                       
    digitalWrite(LED_BUILTIN, LOW);
    delay(300); 
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300);                       
    digitalWrite(LED_BUILTIN, LOW);
    pinMode(LED_BUILTIN, INPUT);
  }
};
