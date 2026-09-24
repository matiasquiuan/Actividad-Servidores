#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
const char* ssid = "CESJT";
const char* password = "itsjt";
WebServer server(80);
int semaforo [3] = {32, 33, 25};
int t_2 = millis();
int condicion = 4;
int t1 = 20000;
int t2= 21000;
int t3= 61000; 
int t4 = 62000;
int espera1 = 20000;
int espera2 = 21000; 
int espera3 = 61000;
int espera4= 62000;
const char HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>servidor</title>
    <style>
        .titulo{
            font-family: Impact;
            text-decoration: underline;
            font-size: 45px;
            text-align: center;
            font-weight: bold;
        }
        body{
            background-color: white;
            text-align: center;
        }
        .contenedor-botones {
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 15px;
            margin-bottom: 25px;
        }
        .boton {
            width: 200px;
            height: 200px;
            color: black;
            font-size: 23px;
            border: 3px solid black;
            border-radius: 100px;
            cursor: pointer;
            display: flex;
            align-items: center;
            justify-content: center;
            font-weight: normal;
            text-decoration: none;
        }
        .lento {
            background-color: red;
        }

        .normal {
            background-color: yellow;   
        }

        .rapido {
            background-color: green;
        }

        .emergencia {
            background-color: orange;
        }

        .leyenda-modo {
            font-size: 20px;
        }

        .leyenda-modo b {
            font-weight: bold;
        }
    </style>
</head>
<body>
    <h1 class="titulo">SEMAFORO</h1> 
    <div class="contenedor-botones">
        <a href="/lento" class="boton lento">btn_txt1</a>
        <a href="/normal" class="boton normal">btn_txt2</a>
        <a href="/rapido" class="boton rapido">btn_txt3</a>
        <a href="/emergencia" class="boton emergencia">btn_txt4</a>
    </div>  
    <span class="leyenda-modo">modo_txt</span>
    
</body>
</html>
)rawliteral";



void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 3; i++) {
    pinMode(semaforo[i], OUTPUT);
  }
  for (int i = 0; i < 3; i++) {
    digitalWrite(semaforo[i], LOW);
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.on("/", []() {
    server.send(200, "text/html", HTML);
  });
  
  server.on("/lento", []() {
    t1 = 70000; 
    t2 = 73000; 
    t3 = 123000; 
    t4 = 3000;
    condicion = 4;
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/normal", []() {
    t1 = 45000; 
    t2 = 47000; 
    t3 = 112000; 
    t4 = 114000;
    condicion = 4;
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/rapido", []() {
    t1 = 20000; 
    t2 = 21000; 
    t3 = 61000; 
    t4 = 62000; 
    condicion = 4;
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/emergencia", []() {
    condicion = 5;
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
  const unsigned long t_now = millis();

  if(t_now - t_2 == espera1) {
    condicion = 2;
  } else if (t_now - t_2 == espera2 && condicion == 2) {
    condicion = 3;
    espera1 = t1;
    espera2 = t2;
    espera3 = t3;
    espera4= t4;
  } else if (t_now - t_2 == espera3 && condicion == 3) {
    condicion = 4;
  } else if (t_now - t_2 == espera4&& condicion == 4) {
    condicion = 1;
    t_2 = t_now;
    espera1 = t1;
    espera2 = t2;
    espera3 = t3;
    espera4= t4;
  }

  if (condicion == 1) {
    digitalWrite(semaforo[0], HIGH);
    digitalWrite(semaforo[1], LOW);
    digitalWrite(semaforo[2], LOW);
  }
  if (condicion == 2) { 
    digitalWrite(semaforo[0], LOW);
    digitalWrite(semaforo[1], HIGH);
    digitalWrite(semaforo[2], LOW);
  }
  
  if (condicion == 3) {
    digitalWrite(semaforo[0], LOW);
    digitalWrite(semaforo[1], LOW);
    digitalWrite(semaforo[2], HIGH);
  }

  if (condicion == 4) { 
    digitalWrite(semaforo[0], LOW);
    digitalWrite(semaforo[1], HIGH);
    digitalWrite(semaforo[2], LOW);
  }

  if (condicion == 5) { 
    digitalWrite(semaforo[0], LOW);
    digitalWrite(semaforo[1], HIGH);
    delay(1500);
    digitalWrite(semaforo[2], HIGH);
    digitalWrite(semaforo[1], LOW);
    delay(1500);
    espera1 = t1;
    espera2 = t2;
    espera3 = t3;
    espera4= t4;
  }
}