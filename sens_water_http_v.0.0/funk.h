#include"val.h"

void read_sensor(){
    sens_val = analogRead(0);
    
    currentMillis = millis();                               //Call delay functions
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        if(sens_val >= 600 && sens_val <= 800){
            Serial.print("Water % =");
            Serial.println(sens_val);
        }
    }
}
