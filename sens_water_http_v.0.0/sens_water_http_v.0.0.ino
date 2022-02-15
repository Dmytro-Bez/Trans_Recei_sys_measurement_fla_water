#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int sens_val;
unsigned long currentMillis = 0;                          //Create variable mil.sec
unsigned long previousMillis = 0;
const long interval = 2000; 
RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Serial.println("Start nrf");
}

void loop() {
  currentMillis = millis();                               //Call delay functions
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    sens_val = analogRead(0);
    if(sens_val >= 0 && sens_val <= 800){
      Serial.print("Water %=");
      Serial.println(sens_val);
      radio.write(&sens_val, sizeof(sens_val));
    }
  }
}
