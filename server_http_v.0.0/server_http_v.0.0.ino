#include <SPI.h>                                                    /*Added libery sys*/
#include <nRF24L01.h>
#include <RF24.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "**";                                            //Login
const char* password = "**";                                        //Password  
const char* server = "192.168.1.188";                               //IP web
RF24 radio(4, 5);                                                   //CE, CSN pin connect to the SPI
const byte address[6] = "00001";
String apiKey = "C25ICK6FHOR7PST4";

void wifi_init();                                                   //Prototype connecting Wifi

void setup() {
  Serial.begin(115200);
  radio.begin();                                                    //Lis. radio connect
  radio.openReadingPipe(0, address);                                //Open wire radio
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();                                           //Start listening radio connections
  wifi_init();                                                      //Start Wifi
  Serial.println("INIT");
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)){                             //Check to connect for the wifi
    if (radio.available()) {
      int dates;
      radio.read(&dates, sizeof(dates));
      Serial.print("Level water=");
      Serial.println(dates);
     HTTPClient http;   
     http.begin("http://192.168.1.188:7000/send_data");             //Specify destination for HTTP request
     http.addHeader("Content-Type", "text");                        //Specify content-type header
     String httpRequestData =  String(dates);
     int httpResponseCode = http.POST(httpRequestData);             //Send the actual POST request
     if(httpResponseCode>0){
      String response = http.getString();                           //Get the response to the request
      Serial.println(httpResponseCode);                             //Print return code
      Serial.println(response);                                     //Print request answer
     } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
     }
     http.end();                                                    //Free resources
   }
  }
}

void wifi_init(){
  WiFi.begin(ssid, password);
  if(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi..");
  } else{
    Serial.println("Not connecting Wi-Fi!");
  }
}
