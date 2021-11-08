#include <Arduino.h>
#include "loramesher.h"
#include <WiFi.h>
#include "LoRa.h"
#include "HttpClient.h"
#include <SPI.h>
#include <functional>



#define BAND 866E6
uint32_t notConnectedCounter = 0;
int status = WL_IDLE_STATUS;
LoraMesher* radio ;
 char ssid[] = "OPPO_A9_2020";
const char password[] = "5a9a7f6643ca";
//const char password[] = "E2zeYs8s4t6uZJ86z2C9";
const uint16_t port = 40351;
const char* host = "192.168.1.52/24";
WiFiClient client;
 // your network passwor
     // the Wifi radio's status
     void printMacAddress() {
  // the MAC address of your Wifi shield
  byte mac[6];

  // print your MAC address:
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
  Log.verbose(F("MAC: : : : : :" CR));

}
void printEncryptionType(int thisType) {
  // read the encryption type and print out the name:
  switch (thisType) {
    case ENC_TYPE_WEP:
      Serial.println("WEP");
      break;
    case ENC_TYPE_TKIP:
      Serial.println("WPA");
      break;
    case ENC_TYPE_CCMP:
      Serial.println("WPA2");
      break;
    case ENC_TYPE_NONE:
      Serial.println("None");
      break;
    case ENC_TYPE_AUTO:
      Serial.println("Auto");
      break;
  }
}

     void listNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  Serial.flush();
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1) {
    Serial.println("Couldn't get a wifi connection");
    while (true);
  }

  // print the list of networks seen:
  Serial.print("number of available networks:");
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.print("\tEncryption: ");
    printEncryptionType(WiFi.encryptionType(thisNet));
  }
}

void printWifiData() {
  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  
  //Serial.print("MAC address: ");
  
  //Serial.print(mac[5], HEX);
  
  Serial.print(":");
  
  
  Serial.print(mac[4], HEX);
  
  Serial.print(":");
 
  Serial.print(mac[3], HEX);
  
  Serial.print(":");
 
  Serial.print(mac[2], HEX);
  
  Serial.print(":");
 
  Serial.print(mac[1], HEX);
  
  //Log.verbose(mac[1],HEX);
  
  Serial.print(":");
  Serial.println(mac[0], HEX);
  
  Log.verbose(F("MAC address: %X : %X : %X: %X : %X : %X " CR),mac[5],mac[4],mac[3],mac[2],mac[1],mac[0]);

}

void printCurrentNet(){
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Log.verbose("SSID:%s ",WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  
  Serial.print("BSSID: ");
  Serial.print(bssid[5], HEX);
  Serial.print(":");
  Serial.print(bssid[4], HEX);
  Serial.print(":");
  Serial.print(bssid[3], HEX);
  Serial.print(":");
  Serial.print(bssid[2], HEX);
  Serial.print(":");
  Serial.print(bssid[1], HEX);
  Serial.print(":");
  Serial.println(bssid[0], HEX);
  
  Log.verbose(F("%X:%X:%X:%X:%X:%X" CR), bssid[5], bssid[4], bssid[3], bssid[2], bssid[1], bssid[0]);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  //Serial.print("signal strength (RSSI):");
  Log.verbose(F("signal strength(RSSI): %x" CR),rssi);
  //Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  
  //Log.verbose(F(" Encryption Type: %X " CR), encryption);
  Serial.println();
}

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
    //WiFi.mode(WIFI_STA);
  //radio = new LoraMesher();
  Serial.flush();

  //SPI.begin(SCK, MISO, MOSI, SS);
  //LoRa.setPins(SS, RST, DIO0);
  //if (!LoRa.begin(BAND)) {
   // Serial.println("No se ha podido iniciar LoRa");
   // while (1);
 // }
  delay(5000);
   
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  printMacAddress();

  // check for the presence of the shield:

  /*while (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    Log.trace("WiFi shield not present" CR);
    // don't continue:
    while (true);
  }*/
 
  /*String fv = WiFi.firmwareVersion();
  Log.trace("Firmware version is : %s" CR,fv);
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
    Log.trace("Please upgrade the firmware" CR);
  }*/

   Log.verbose(F("Current status 1 %d" CR), status);
   
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    
    delay(500);
    Serial.println("Me estoy conectando a WiFi");
    Log.trace("Attempting to connect to WPA SSID:%s " CR);
    status = WiFi.begin(ssid, password);
    notConnectedCounter++;
    if(notConnectedCounter > 50) { // Reset board if not connected after 5s
        Serial.println("Resetting due to Wifi not connecting...");
        ESP.restart();
    }
    Serial.println(ssid);
    delay(10000);
  
    
    // Connect to WPA/WPA2 network:
    
    
    Log.verbose(F("Current status 2:%d" CR), status);
    // wait 10 seconds for connection:
    
  }

  // you're connected now, so print out the data:
 // Serial.print("You're connected to the network");
  Log.trace("You're connected to the network" CR);
  //printCurrentNet();
  //printWifiData();
  Serial.flush();

}




void loop() {
   Serial.println("Scanning available networks...");
  listNetworks();
  delay(10000);
  /*
  // put your main code here, to run repeatedly:
   sleep(7);
  radio->sendDataPacket();
  Serial.flush();
*/
}