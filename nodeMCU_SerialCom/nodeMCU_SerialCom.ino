#include <ArduinoJson.h>
#include <SoftwareSerial.h>
SoftwareSerial s(6,5);

void setup() {
  Serial.begin(9600);
  s.begin(9600);
  while(!Serial)continue;
}

void loop() {
    StaticJsonBuffer<1000> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(s);

    if(Serial.available()){
      Serial.println("JSON received and parsed");
      root.prettyPrintTo(Serial);
      Serial.println("");
      Serial.print("Current: ");
      float data1 = root["cur"];
      Serial.println(data1);
      Serial.print("Power: ");
      float data2 = root["pow"];
      Serial.println(data2);
      Serial.print("Status: ");
      bool data3 = root["stat"];
      Serial.println(data3);
      Serial.println("");
      Serial.println("-----------------------------");
      Serial.println("");
    }
}
