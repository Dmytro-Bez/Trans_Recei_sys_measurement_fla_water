#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <WiFi.h>
//#include <HTTPClient.h>

const char* ssid = "EE";                        //Login
const char* password = "EE@05kilogram";         //Password  
const char* server = "api.thingspeak.com";
RF24 radio(4, 5);                               //CE, CSN
const byte address[6] = "00001";
String apiKey = "C25ICK6FHOR7PST4";
WiFiClient client;

void wifi_init();

void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  wifi_init();
  Serial.println("INIT");
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)){                             //Check to connect for the wifi
    if (radio.available()) {
      int text;
      radio.read(&text, sizeof(text));
      Serial.print("Level water=");
      Serial.println(text);
      if (client.connect(server, 80)){
        Serial.println("Server HTTP work");
        String postStr = apiKey;
        postStr += "&field1=";
        postStr += String(text);
        postStr += "\r\n\r\n\r\n\r\n";

        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(postStr.length());
        client.print("\n\n");
        client.print(postStr);
      } else {
        Serial.print("Error HTTP!");
      }
      client.stop();
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
