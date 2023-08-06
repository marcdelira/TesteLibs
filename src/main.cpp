#include "main.h"

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
//#include <ESP8266mDNS.h>

#include <DNSServer.h>
#include <WiFiManager.h>



//#define HTTP_REST_PORT 8080
//ESP8266WebServer httpRestServer(HTTP_REST_PORT);

#define BT_RESET 4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel();

//void getHelloWorld();
//void restServerRouting();
void read_keyb();

void setup() {
  Serial.begin(115200);
  initNeopixel(&pixels);
  // pinMode(BT1, INPUT_PULLUP);
  pinMode(BT_RESET, INPUT);

  WiFiManager wifiManager;
  wifiManager.setConfigPortalTimeout(240);

  // Cria um access point chamado "nome da rede" e senha "senha"
  if (!wifiManager.autoConnect("ESP_ARDUINOECIA", "arduinoecia")) {
    Serial.println(F("Falha na conexão. Resetar e tentar novamente..."));
    delay(3000);
    ESP.restart();
    delay(5000);
  }

  // mensagem em caso de conexão bem sucedida
  Serial.println(F("Conectando na rede Wifi"));
  Serial.print(F("Endereço IP: "));
  Serial.println(WiFi.localIP());
}

void loop() {
  //heartBeat();
  //efeitoConectando();
  read_keyb();
  // handleLedRing();
}

void getHelloWorld() {}
void restServerRouting() {}

void read_keyb() {
  static char flag1 = 0;

  if (!digitalRead(BT_RESET)) {
    flag1 = 1;
  }

  if (digitalRead(BT_RESET) && flag1) {
    WiFiManager wm;
    wm.resetSettings();
    Serial.println(F("Configurações resetadas"));
    ESP.restart();
    flag1 = 0;
    delay(130);
  }
}