#include "ledring.h"

Adafruit_NeoPixel* ledRing;
char efeitoSelecionado = 0;
bool habilitaEfeitoConectando = false;
bool habilitaEfeitoHeartBeat  = false;

void initNeopixel(Adafruit_NeoPixel* neoPixel) {
  ledRing = neoPixel;
  ledRing->setPin(PIN);
  ledRing->updateLength(NUMPIXEL);
  ledRing->updateType(NEO_GRB + NEO_KHZ800);
  ledRing->begin();
  ledRing->clear();
  //ledRing->setPixelColor(0, ledRing->Color(0, 0, 150));
  ledRing->show();
}

void setEfeitoSelecionado(char efeito) {
  efeitoSelecionado = efeito;
}

void colorWipe(uint32_t color32, boolean isDelay) {
  for (int i = 0; i < ledRing->numPixels(); i++) {
    ledRing->setPixelColor(i, color32);
    ledRing->show();
    if (isDelay)
      delay(3); //Intervalo para a execução de cada comando para cada LED 
  }
}

void heartBeat() {
  const int batimentoMinimo = 30,
            picoAtrio       = 150,
            picoVentriculo  = 255;
  
  ledRing->clear();
  
  // movimento átrio
  for (int i = batimentoMinimo - 20; i <= picoAtrio; i = i + 15) {
    colorWipe(ledRing->Color(i, 0, 0), false);
    delay(10);
  }

  delay(60);
  
  for (int i = picoAtrio; i >= 90; i = i - 15) {
    colorWipe(ledRing->Color(i, 0, 0), false);
    delay(20);
  }

  delay(100);

  // movimento ventrículo
  for (int i = 90; i <= picoVentriculo; i = i + 15) {
    colorWipe(ledRing->Color(i, 0, 0), false);
    delay(5);
  }

  delay(60);
  
  for (int i = picoVentriculo; i >= 15; i = i - 15) {
    colorWipe(ledRing->Color(i, 0, 0), false);
    delay(10);
  }

  delay(350);
}


void testaIntensidade() {
  int valores[] = {50, 100, 150, 200, 255, 0};
  
  for (ulong i = 0; i < (sizeof(valores) / sizeof(valores[0])); i++) {
    colorWipe(ledRing->Color(valores[i], 0, 0), true);
  }
  delay(100);

  for (ulong i = 0; i < (sizeof(valores) / sizeof(valores[0])); i++) {
    colorWipe(ledRing->Color(0, valores[i], 0), true);
  }
  delay(100);
  
  for (ulong i = 0; i < (sizeof(valores) / sizeof(valores[0])); i++) {
    colorWipe(ledRing->Color(0, 0, valores[i]), true);
  }
  delay(100);
}


void efeitoConectando() {
  uint32_t color32;
  static bool acende = true;
  static ulong timeSave = 0;
  uint espera = 741;
  static u_char index = 0;

  if (acende) {
    color32 = ledRing->Color(50, 50, 50);
   } else {
     color32 = ledRing->Color(0, 0, 0);
  }
  
  if (millis() - timeSave >= espera) {
    ledRing->setPixelColor(index, color32);
    ledRing->show();
    timeSave = millis();
    
    if (index < NUMPIXEL - 1) {
      index++;
    } else {
      acende = !acende;
      index = 0;
    }
  }

}

void handleLedRing() {

  switch (efeitoSelecionado) {
    case 1:
      habilitaEfeitoConectando = !habilitaEfeitoConectando;
      if (habilitaEfeitoConectando)
        efeitoConectando();
      break;
    case 2:
      habilitaEfeitoHeartBeat = !habilitaEfeitoHeartBeat;
      if (habilitaEfeitoHeartBeat)
        heartBeat();
      break;
    default:
      efeitoSelecionado = 0;
  }
}