#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


const char* ssid     = ""; // the name of the wifi Ex:"OG575757"
const char* password = ""; // password for the wifi connection Ex."Password"


int wifiStatus;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(200);

  Serial.println();
  Serial.println();
  Serial.print("You are connecting to: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  wifiStatus = WiFi.status();

  if(wifiStatus == WL_CONNECTED) {
    Serial.println("");
    Serial.println("Your ESP is connected!");
    Serial.println("Your IP address is: ");
    Serial.println(WiFi.localIP());

    HTTPClient http;
    
    String url = "http://192.168.0.127:5000/nodemcu/";
    String message = String(random(0, 10)) + "/" + String(random(0, 10));
    Serial.print("Requesting URL: ");
    Serial.println(url);
    http.begin(url);
//    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
//    int httpCode = http.GET();
    int httpCode = http.POST(message);
    Serial.println(httpCode);
    http.end();
    // This will send the request to the server
    delay(30000);
//    Serial.println("Goodnight");
//    ESP.deepSleep(30e6);
  }
  else{
    Serial.println("");
    Serial.println("WiFi not connected");
  }
  delay(1000);
}
