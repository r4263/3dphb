// Libraries
#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <AsyncTCP.h>
#include <AsyncUDP.h>
#include <NetBIOS.h>
#include <Adafruit_NeoPixel.h>
#include "FS.h"


// Defines


// Objects/classes instantiations
AsyncWebServer server(80);
Adafruit_NeoPixel status(1, 48, NEO_GRB + NEO_KHZ800);

// Variable definitions
const char *ssid = "";
const char *password = "";

// Functions declarations
void init();
void statusLED();



void setup() {
  status.begin();
  init();
}

void loop() {

}

void statusLED(){
}

void init(){
  Serial.begin(115200);

  if (!LittleFS.begin())
  {
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to Wi-Fi network");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
  server.serveStatic("/static/", LittleFS, "/");

  server.begin();
}

// void loadCredentials() {
//   EEPROM.begin(512);
//   EEPROM.get(0, NetworkSSID);
//   EEPROM.get(0 + sizeof(NetworkSSID), Password);
//   EEPROM.get(0 + sizeof(NetworkSSID) + sizeof(Password), Gateway);
//   EEPROM.get(0 + sizeof(NetworkSSID) + sizeof(Password) + sizeof(Gateway), StaticIP);
//   char ok[2 + 1];
//   EEPROM.get(0 + sizeof(NetworkSSID) + sizeof(Password) + sizeof(Gateway) + sizeof(StaticIP), ok);
//   EEPROM.end();
//   if (String(ok) != String("OK")) {
//     Serial.println();
//     Serial.println("ok ausente");
//     Serial.println();
//     NetworkSSID[0] = 0;
//     Password[0] = 0;
//   }else{
//   Serial.println();
//   Serial.println("ok presente");
//   Serial.println();
//   }
//
//   Serial.println();
//   Serial.println("Recovered credentials:");
//   Serial.print("Network SSID: "); Serial.println(NetworkSSID);
//   Serial.print("Network PSK: "); Serial.println(Password);
//   Serial.print("Gateway: "); Serial.println(Gateway);
//   Serial.print("IPv4: "); Serial.println(StaticIP);
// }

// void saveCredentials() {
//   SSIDHolder.toCharArray(NetworkSSID, SSIDHolder.length() + 1);
//   PSKHolder.toCharArray(Password, PSKHolder.length() + 1);
//   GatewayHolder.toCharArray(Gateway, GatewayHolder.length() + 1);
//   StaticIPHolder.toCharArray(StaticIP, StaticIPHolder.length() + 1);
//
//   EEPROM.begin(512);
//   EEPROM.put(0, NetworkSSID);
//   EEPROM.put(0 + sizeof(NetworkSSID), Password);
//   EEPROM.put(0 + sizeof(NetworkSSID) + sizeof(Password), Gateway);
//   EEPROM.put(0 + sizeof(NetworkSSID) + sizeof(Password) + sizeof(Gateway), StaticIP);
//   char ok[2 + 1] = "OK";
//   EEPROM.put(0 + sizeof(NetworkSSID) + sizeof(Password) + sizeof(Gateway) + sizeof(StaticIP), ok);
//   EEPROM.commit();
//   EEPROM.end();
// }

// void IPconversion(String IPHolder, String GatewayHolder) {
//   int GatewayIndex = 0, IPIndex = 0;
//
//   for (int i = 0; i < IPHolder.length(); i++ )
//   {
//     char c = IPHolder[i];
//     if ( c == '.' )
//     {
//       IPIndex++;
//       continue;
//     }
//     IPVector[IPIndex] *= 10;
//     IPVector[IPIndex] += c - '0';
//   }
//
//   for (int i = 0; i < GatewayHolder.length(); i++ )
//   {
//     char c = GatewayHolder[i];
//     if ( c == '.' )
//     {
//       GatewayIndex++;
//       continue;
//     }
//     GatewayVector[GatewayIndex] *= 10;
//     GatewayVector[GatewayIndex] += c - '0';
//   }
// }

  // status.setPixelColor(0,status.Color(255,255,255));
  // status.show();
  // status.clear();