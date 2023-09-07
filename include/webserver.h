#ifndef WEBSERVER_H
#define WEBSERVER_H

  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
  #include <ESP8266mDNS.h>

  void initRestWebServer();
  void restWebServerHandleClient();

#endif //WEBSERVER_H