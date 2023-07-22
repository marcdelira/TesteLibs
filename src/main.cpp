#include "main.h"
//#include <ESP8266WebServer.h>
//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
//#include <ESP8266mDNS.h>



//#define HTTP_REST_PORT 8080
//ESP8266WebServer httpRestServer(HTTP_REST_PORT);

#define BT1 4
#define BT2 2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel();

//void getHelloWorld();
//void restServerRouting();
void read_keyb();

void setup() {
  Serial.begin(115200);
  initNeopixel(&pixels);
  pinMode(BT1, INPUT_PULLUP);
  pinMode(BT2, INPUT_PULLUP);
}

void loop() {
  //heartBeat();
  //efeitoConectando();
  read_keyb();
  handleLedRing();
}

void getHelloWorld() {}
void restServerRouting() {}

void read_keyb() {
  static char flag1 = 0,
              flag2 = 0;

  if (!digitalRead(BT1)) {
    flag1 = 1;
  }

  if (!digitalRead(BT2)) {
    flag2 = 1;
  }

  if (digitalRead(BT1) && flag1) {
    flag1 = 0;
    //heartBeat();
    setEfeitoSelecionado(EFEITO_CONECTANDO);
    delay(130);
  }

  if (digitalRead(BT2) && flag2) {
    flag2 = 0;
    setEfeitoSelecionado(EFEITO_HEART_BEAT);
    delay(130);
  }
}