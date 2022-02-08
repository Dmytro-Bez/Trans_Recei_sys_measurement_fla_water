//#include "funk.h"
#define SENSOR 0

int sens_val;
unsigned long currentMillis = 0;                          //Create variable mil.sec
unsigned long previousMillis = 0;
const long interval = 2000;  
     
void setup() {
  Serial.begin(115200);

}

void loop() {
  currentMillis = millis();                               //Call delay functions
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    sens_val = analogRead(0);
    if(sens_val >= 0 && sens_val <= 800){
      Serial.print("Water %=");
      Serial.println(sens_val);
    }
  }
}
