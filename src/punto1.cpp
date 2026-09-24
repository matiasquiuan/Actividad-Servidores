#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CESJT";
const char* password = "ITISJTSMG";

WebServer server(80);
const int pines[6] = {2, 32, 33, 25, 26, 27};
int animacion = 0; 
bool Led1 = LOW;
bool Led2 = HIGH;
unsigned long tiempo = 0;
const unsigned long intervalo = 1000;

const char HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>webos</title>
  <style>
    body { font-family: sans-serif; text-align: center; margin-top: 80px; }
    .btn { padding: 15px 30px; font-size: 20px; text-decoration: none; border-radius: 5px; color: white; margin: 10px; display: inline-block; }
    .one { background-color: #0ce21a; }
    .two { background-color: #d0e20c; }
    .off { background-color: #1106e6; }
  </style>
</head>
<body>
  <h1>Comandos</h1>
  <a href="/animacion1" class="btn one">1</a>
  <a href="/animacion2" class="btn two">2</a>
  <a href="/off" class="btn off">OFF</a>
</body>
</html>
)rawliteral";

void off() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(pines[i], LOW);
  }
}

void reinicio() {
  Led1 = LOW;
  Led2 = HIGH;
  tiempo = millis();
}

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 6; i++) {
    pinMode(pines[i], OUTPUT);
  }
  off();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.on("/", []() {
    server.send(200, "text/html", HTML);
  });

  server.on("/animacion1", []() {
    animacion = 1;
    reinicio();
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/animacion2", []() {
    animacion = 2;
    reinicio();
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/off", []() {
    animacion = 0;
    off();
    server.sendHeader("Location", "/");
    server.send(303);
  });
 Serial.println("\nOK!");
  Serial.print("IP: http://");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  server.handleClient();
 if (animacion > 0 && (millis() - tiempo >= intervalo)) {
   tiempo = millis();
  Led1 = !Led1;
  Led2 = !Led1;
 if (animacion == 1) {
      digitalWrite(2, Led2);
      digitalWrite(32, Led2);
      digitalWrite(33, Led2);
      digitalWrite(25, Led1);
      digitalWrite(26, Led2);
      digitalWrite(27, Led2);
    } 
     else if (animacion == 2) {
      digitalWrite(2, Led1);
      digitalWrite(32, Led2);
      digitalWrite(33, Led1);
      digitalWrite(25, Led2);
      digitalWrite(26, Led1);
      digitalWrite(27, Led2);
    }
  }
}