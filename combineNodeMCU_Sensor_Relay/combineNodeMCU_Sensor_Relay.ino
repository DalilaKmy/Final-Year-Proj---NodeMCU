#include <Robojax_AllegroACS_Current_Sensor.h>
const int VIN = A0; // define the Arduino pin A0 as voltage input (V in)
const float VCC = 5.0;// supply voltage
const int MODEL = 2;   // enter the model (see above list)
int RelayPin = D7;
Robojax_AllegroACS_Current_Sensor robojax(MODEL,VIN);
 
void setup(){ 
   Serial.begin(9600);
   pinMode(RelayPin, OUTPUT);
}
 
void loop(){
    float I = robojax.getCurrent();
    float P = VIN*I;
    
 // Let's turn on the relay...
   digitalWrite(RelayPin, LOW);
   Serial.println("Relay On");
   Serial.println(String("I = ") + I + " Amp\t"); 
   Serial.println(String("P = ") + P + " Watts\n");  
   delay(3000);
   
 // Let's turn off the relay...
  digitalWrite(RelayPin, HIGH);
  Serial.println("Relay Off");
  Serial.println(String("I = ") + I + " Amp\t"); 
  Serial.println(String("P = ") + P + " Watts\n");  
  delay(3000);
   
}
 
