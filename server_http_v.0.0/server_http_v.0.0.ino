#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "EE";                        //Login
const char* password = "EE@05kilogram";         //Password

void setup() {
  Serial.begin(115200);
  delay(500);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi..");
  }
  Serial.println("Not connecting Wi-Fi!");
}

void loop() {
  if ((WiFi.status() == WL_CONNECTED)){                             //Check to connect for the wifi
    HTTPClient http;                                                //Creating object HTTP
    http.begin("http://*");     //Connecting to the web
    int httpCode = http.GET();                                      //Ping GET
    if (httpCode > 0){                                              //Check                               
      String payload = http.getString();                            //Display messeger web
      Serial.println(httpCode);
      Serial.println(payload);
    }
    else {
      Serial.println("Error HTTP-get");
    }
    http.end();                                                     //Disconnect web
  }
  delay(10000);
}
