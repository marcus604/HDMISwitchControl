#include "WiFi.h"
#include "WifiConfig.h"

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 4;

IRsend irsend(kIrLed);

int ir_code_hdmi_one = 0x40BF10EF;
int ir_code_hdmi_two = 0x40BF50AF;
int ir_code_power = 0x40BF00FF;
int ir_code_toggle = 0x40BF708F;

const int port = 8888;

WiFiServer server(port);
WiFiClient client;

void ConnectToWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, WiFiPassword);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
}

void setup() {
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1);
  ConnectToWiFi();
  server.begin();
}

void loop() {
  client = server.available();
  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        if (currentLine.endsWith("GET /hdmi_one")) {
          irsend.sendNEC(ir_code_hdmi_one);
        }
        if (currentLine.endsWith("GET /hdmi_two")) {
          irsend.sendNEC(ir_code_hdmi_two);
        }
        if (currentLine.endsWith("GET /power")) {
          irsend.sendNEC(ir_code_power);
        }
        if (currentLine.endsWith("GET /toggle")) {
          irsend.sendNEC(ir_code_toggle);
        }
      }
    }
    client.stop();
  }
}

