#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <ESP8266WiFi.h>        

#define FIREBASE_HOST "" 
#define FIREBASE_AUTH ""
#define WIFI_SSID ""
#define WIFI_PASSWORD ""

#include <Robojax_AllegroACS_Current_Sensor.h>

const int VIN = A0; // define the Arduino pin A0 as voltage input (V in)
const float VCC = 5.0;// supply voltage
const int MODEL = 2;   // enter the model (see above list)
int RelayPin = D7;

Robojax_AllegroACS_Current_Sensor robojax(MODEL,VIN);

void setup(){ 
   Serial.begin(9600);
   pinMode(RelayPin, OUTPUT);
   
   WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
   Serial.print("Connecting to ");
   Serial.print(WIFI_SSID);
   while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
      Serial.print('.');
      delay(1000);
   }
   Serial.println();
   Serial.print("Connected with IP: ");
   Serial.println(WiFi.localIP());
   Serial.println();
  
   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
 
void loop(){
    float I = robojax.getCurrent();
    float P = VIN*I;
 
   String stat1 = Firebase.getString("/Device1/Status");
   if(stat1 == "on")
   {
     digitalWrite(RelayPin, LOW);
     Serial.println("Relay Off");
     Serial.print("Current: ");
     Serial.print(I);
     String curr = String(I) + String("Amp");
  
     Serial.print(" Power: ");
     Serial.print(P);
     String powr = String(P) + String("Watts");
  
     Firebase.setString("/Device1/Current", curr);
     Firebase.setString("/Device1/Power", powr);
     if(Firebase.failed())
       {
        Serial.print("pushing failed");
        Serial.println(Firebase.error());
        return;
       } 
   }
   else
   {
     digitalWrite(RelayPin, HIGH);
     Serial.println("Relay On");
     Serial.print("Current: ");
     Serial.print(I);
     String curr = String(I) + String("Amp");
  
     Serial.print(" Power: ");
     Serial.print(P);
     String powr = String(P) + String("Watts");
    
     Firebase.setString("/Device1/Current", curr);
     Firebase.setString("/Device1/Power", powr);
     if(Firebase.failed())
       {
        Serial.print("pushing failed");
        Serial.println(Firebase.error());
        return;
       }
   }

   Serial.println();
}
 
