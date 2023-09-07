#include "main.h"

#define BT_RESET 4
#define BT_CHNG_MODE 2

Adafruit_NeoPixel pixels = Adafruit_NeoPixel();

void read_keyb();

void setup() {
  Serial.begin(115200);
  pinMode(BT_CHNG_MODE, INPUT_PULLUP);
  pinMode(BT_RESET, INPUT);
  initNeopixel(&pixels);
  initNetworkService();
  initRestWebServer();
}

void loop() {
  //heartBeat();
  //efeitoConectando();
  read_keyb();
  handleLedRing();
  restWebServerHandleClient();
}

void read_keyb() {
  static char flag1 = 0,
              flag2 = 0;

  if (!digitalRead(BT_RESET)) {
    flag1 = 1;
  }

  if (digitalRead(BT_CHNG_MODE)) {
    flag2 = 1;
  }
  
  if (!digitalRead(BT_CHNG_MODE) && flag2) {
    flag2 = 0;
    delay(130);
    mudaEfeito();
  }

  if (digitalRead(BT_RESET) && flag1) {    
    flag1 = 0;
    delay(130);
    resetNetworkConfig();
  }
}