#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <WiFiUDP.h>----------------------------

#include <WakeOnLan.h>
#include <UniversalTelegramBot.h>
// Library for interacting with the Telegram API
// Search for "Telegegram" in the Library manager and install
// The universal Telegram library
// https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot

#include <ArduinoJson.h>
// Library used for parsing Json from the API responses
// NOTE: There is a breaking change in the 6.x.x version,
// install the 5.x.x version instead
// Search for "Arduino Json" in the Arduino Library manager
// https://github.com/bblanchon/ArduinoJson

char ssid[] = "";         // your network SSID (name)
char password[] = ""; // your network password
// Get from the "botFather" on telegram mi bot 
#define TELEGRAM_BOT_TOKEN "000" //here it goes the key for you telegrambot


struct targetDevice {
  byte mac[6]; //The targets MAC address
  String deviceName;
};

// Add or remove devices from this list
// To get mac address On windows, 
//         - open cmd
//         - type "ipconfig /all"
//         - copy the value for "physical address" (highlight and right click to copy)

targetDevice devices[] ={
  {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, "Send WOL to PC"}, //heres mac
  {{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, "Send WOL to TV"} //here mac
};

// Change to match how many devices are in the above array.
int numDevices = 2;

//------- ---------------------- ------

WiFiUDP UDP;
/**
 * This will brodcast the Magic packet on your entire network range.
 */
IPAddress computer_ip(255,255,255,255); //todo el margen de ips a los que se puede enviar

void sendWOL();


// This is the Wifi client that supports HTTPS
WiFiClientSecure client;
UniversalTelegramBot bot(TELEGRAM_BOT_TOKEN, client);

int delayBetweenChecks = 1000;
unsigned long lastTimeChecked;   //last time messages' scan has been done
