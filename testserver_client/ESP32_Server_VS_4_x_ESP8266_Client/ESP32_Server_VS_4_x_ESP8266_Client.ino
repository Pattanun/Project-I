#include <Arduino.h>

#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#include "SPIFFS.h"

#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <FS.h>

#endif

#include <ESPAsyncWebServer.h>
AsyncWebServer server(80); //server port 80

const char* ssid = "Chico Changnoi_2.4GHz";
const char* password = "0822875587";
uint8_t pin_led = 2;
bool ledmode = true;

IPAddress local_IP(192, 168, 1, 65);

IPAddress gateway(192, 168, 88, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);//optional
IPAddress secoundaryDNS(8, 8, 4, 4);//optional


void setup()
{
  Serial.begin(115200);
  pinMode(pin_led, OUTPUT);
  delay(2000);
  //Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  WiFi.disconnect();
  delay(500);
  WiFi.mode(WIFI_STA);
  //COnfigures sttic IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS)) {
    Serial.println("STA Failed to configur");
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    digitalWrite(pin_led,0);
    delay(500);
    Serial.println("Connecting to WiFi..");
    digitalWrite(pin_led,1);
    delay(500);
  }
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/index.html", "text/html", false);
    });

    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/favicon.ico", "image", false);
    });

    server.on("/opMode", HTTP_GET, [](AsyncWebServerRequest *request){
      static String opmode="Auto";
      if (opmode=="Auto"){
        opmode="Manual";
        ledmode=false;
      }
      else{
        opmode="Auto";
        ledmode=true;
      }
      request->send(200,"text/plain",opmode+"\n\n");
    });

    server.on("/toggleLED", HTTP_GET, [](AsyncWebServerRequest *request){
           String led_stat="";
           if(ledmode==false){
              toggleLED();
              led_stat=getLEDStat();
            }
           else{
              led_stat="N/A";
            }
            request->send(200,"text/plain",led_stat+"\n\n");
      });

     server.on("/ledstat", HTTP_GET, [](AsyncWebServerRequest *request){
            String led_stat="";
            led_stat=getLEDStat();
            request->send(200,"text/plain", led_stat+"\n\n");    
      });

      server.begin();
}
  bool autoMode = true;
  bool manMode = false;

  void loop(){
    if(ledmode==autoMode){
       static double ti=500;
       static double pvtime=millis();
       double elaps=millis()-pvtime;
        if (elaps>=ti){
          pvtime=(millis()+ti-elaps);
          toggleLED();  
        }//Fi kraprib
      }
    }

    void toggleLED()
    {
      digitalWrite(pin_led, !digitalRead(pin_led));
    }

    String getLEDStat()
    {
      //toggleLED();
      String led_state = digitalRead(pin_led) ? "> OFF" : "> ON";
      return(led_state);
    }
