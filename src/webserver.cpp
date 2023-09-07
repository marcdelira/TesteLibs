#include "webserver.h"
#include "ledring.h"

ESP8266WebServer server(80);

void getHelloWorld() {
  server.send(200, "text/json", "{\"name\": \"Hello World!\"}");
}

void restServerRouting() {
  server.on("/", 
    HTTP_GET,
    []() {
      server.send(200, F("text/html"),
      F("Welcome to the Rest Web Server!"));
    });

    server.on(F("/helloworld"), HTTP_GET, getHelloWorld);
}

void handleNotFound() {
  String message = "File not found";

  server.send(404, "text/plain", message);
}

void restWebServerHandleClient() {
  server.handleClient();
}

void initRestWebServer() {
  // Activate mDNS this is used to be able to connect to the server
  // with local DNS hostmane esp8266.local
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  //Set server routing
  restServerRouting();

  // Set not found response
  server.onNotFound(handleNotFound);

  // Start server
  server.begin();
  Serial.println("HTTP Server started");
  MDNS.addService("http", "tcp", 80);
  Serial.println(MDNS.hostname(0));
}