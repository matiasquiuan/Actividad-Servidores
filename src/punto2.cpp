#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CESJT";
const char* password = "itsjt";
WebServer server(80);
int num = 11;
int display = 1;

const int dis1[7] = {25, 26, 12, 14, 27, 33, 32}; 
const int dis2[7] = {21, 19, 16, 17, 18, 22, 23}; 

int pad[11][7] = {//numeros del 7seg(0 al 9)
  {1, 1, 1, 1, 1, 1, 0},//0 
  {0, 1, 1, 0, 0, 0, 0},//1 
  {1, 1, 0, 1, 1, 0, 1},//2
  {1, 1, 1, 1, 0, 0, 1},//3 
  {0, 1, 1, 0, 0, 1, 1},//4 
  {1, 0, 1, 1, 0, 1, 1},//5 
  {1, 0, 1, 1, 1, 1, 1},//6 
  {1, 1, 1, 0, 0, 0, 0},//7 
  {1, 1, 1, 1, 1, 1, 1},//8 
  {1, 1, 1, 1, 0, 1, 1}, //9 
  {0, 0, 0, 0, 0, 0, 0} //off 
};

String dis_txt;

const char HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>servidor</title>
  <style>
    body { background-color: #ffffff; font-family: Arial, sans-serif; text-align: center; padding: 30px 10px; }
    h1 { color: #000000; }
    .btn-main { display: inline-block; padding: 12px 28px; margin: 5px; font-size: 18px; color: white; background-color: #007bff; text-decoration: none; border-radius: 5px; }
    .panel-num { display: flex; justify-content: center; flex-wrap: wrap; max-width: 350px; margin: 25px auto 0 auto; }
    .btn-display { display: inline-block; padding: 10px 18px; margin: 5px; font-size: 16px; color: white; background-color: #28a745; text-decoration: none; border-radius: 5px; }
  </style>
</head>
<body>
  <h1>7 segmentos</h1>
  <a href="/display" class="btn-display">dis_txt</a>
    
  <div class="panel-num">
    <a href="/0" class="btn-main">0</a>
    <a href="/1" class="btn-main">1</a>
    <a href="/2" class="btn-main">2</a>
    <a href="/3" class="btn-main">3</a>
    <a href="/4" class="btn-main">4</a>
    <a href="/5" class="btn-main">5</a>
    <a href="/6" class="btn-main">6</a>
    <a href="/7" class="btn-main">7</a>
    <a href="/8" class="btn-main">8</a>
    <a href="/9" class="btn-main">9</a>
    <a href="/OFF" class="btn-main">OFF</a>
  </div>

</body>
</html>
)rawliteral";


void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 7; i++) { //configuracion de pines para los display
    pinMode(dis1[i], OUTPUT);
    pinMode(dis2[i], OUTPUT);
  }
  for (int i = 0; i < 7; i++) {
    digitalWrite(dis1[i], LOW);
    digitalWrite(dis2[i], LOW);
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.on("/", []() {
    server.send(200, "text/html", HTML);
  });
  server.on("/display", []() {//para el display
    String pagina=HTML;
    if(display = 1) dis_txt="Display 2";
    else dis_txt="Display 1";
    pagina.replace("dis_txt", dis_txt);
    display=2;
    
    server.send(200, "text/html", pagina);
  });

  //--------------para los pad de numeros-----------------------------
  server.on("/0", []() {//para 0
    num = 0;
    server.sendHeader("Location", "/");
    server.send(303);
  });
  server.on("/1", []() {//para 1
    num = 1;
    server.sendHeader("Location", "/");
    server.send(303);
  });
  server.on("/2", []() {//para 2
    num = 2;
    server.sendHeader("Location", "/");
    server.send(303);
  });
  server.on("/3", []() {//para 3
    num = 3;
    server.sendHeader("Location", "/");
    server.send(303);
  });
  server.on("/4", []() {//para 4
    num = 4;
    server.sendHeader("Location", "/");
    server.send(303);
  });
  server.on("/5", []() {//para 5
    num = 5;
    server.sendHeader("Location", "/");
    server.send(303);
  });
  server.on("/6", []() {//para 6
    num = 6;
    server.sendHeader("Location", "/");
    server.send(303);
  });
  server.on("/7", []() {//para 7
    num = 7;
    server.sendHeader("Location", "/");
    server.send(303);
  });
  server.on("/8", []() {//para 8
    num = 8;
    server.sendHeader("Location", "/");
    server.send(303);
  });
  server.on("/9", []() {//para 9
    num = 9;
    server.sendHeader("Location", "/");
    server.send(303);
  });
//--------------------------------------------------
  server.on("/OFF", []() {//para el apagado del num
    num = 10;
    server.sendHeader("Location", "/");
    server.send(303);
  });
  Serial.println("\nconectado");
  Serial.print("IP: http://");
  Serial.println(WiFi.localIP());
  server.begin();
}
void loop() {
    switch(display){
    case 1: //si el display es el 1
        for(int i=0;i<11;i++){//preguntamos por los numeros del 1 al 10
            if(num==i){//si es igual a el numero elegido
                for(int j=0;j<7;j++){
                    digitalWrite(dis1[j], pad[i][j]);//prende el display 1 en el numero seleccionado
                }
            }
        }
        break;
    
    case 2:
        for(int i=0;i<11;i++){//preguntamos por los numeros del 1 al 10
            if(num==i){//si es igual a el numero elegido
                for(int j=0;j<7;j++){
                    digitalWrite(dis2[j], pad[i][j]);//prende el display 2 en el numero seleccionado
                }
            }
        }
        break;
    }
  server.handleClient();
}