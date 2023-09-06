#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Define el nombre y la contraseña de la red Wi-Fi
const char* ssid = "No puedes entrar";
const char* password = "P81M40A21H";
  

ESP8266WebServer server(80);

// Define los pines de salida conectados a la matriz de LEDs
const int pinA1 = D0;
const int pinA2 = D1;
const int pinB1 = D2;
const int pinB2 = D3;
const int pinC1 = D4;
const int pinC2 = D5;
const int pinD1 = D6;
const int pinD2 = D7;
const int pinOE = D8;

void setup() {
  // Inicializa los pines de la matriz de LEDs como salida
  pinMode(pinA1, OUTPUT);
  pinMode(pinA2, OUTPUT);
  pinMode(pinB1, OUTPUT);
  pinMode(pinB2, OUTPUT);
  pinMode(pinC1, OUTPUT);
  pinMode(pinC2, OUTPUT);
  pinMode(pinD1, OUTPUT);
  pinMode(pinD2, OUTPUT);
  pinMode(pinOE, OUTPUT);

  // Enciende el pin OE para activar la matriz de LEDs
  digitalWrite(pinOE, LOW);

  // Conecta a la red Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red Wi-Fi...");
  }

  Serial.println("Conexión establecida");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Define las rutas de la página web
  server.on("/", handleRoot);
  server.on("/pattern1", pattern1);
  server.on("/pattern2", pattern2);
  server.onNotFound(handleNotFound);

  // Inicia el servidor web
  server.begin();
  Serial.println("Servidor iniciado");
}
void loop() {
  // Maneja las conexiones del servidor web
  server.handleClient();
}

// Función para manejar la página principal
void handleRoot() {
  // Carga la página HTML
  String html = "<html><head><title>Matriz de LEDs</title></head><body>";
  html += "<h1>Matriz de LEDs</h1>";
  html += "<p>Seleccione un patrón:</p>";
  html += "<ul>";
  html += "<li><a href=\"/pattern1\">Patrón 1</a></li>";
  html += "<li><a href=\"/pattern2\">Patrón 2</a></li>";
  html += "</ul>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

// Función para manejar rutas desconocidas
void handleNotFound() {
  // Carga la página de error 404
  String html = "<html><head><title>Error 404</title></head><body>";
  html += "<h1>Error 404: página no encontrada</h1>";
  html += "<p><a href=\"/\">Volver a la página principal</a></p>";
  html += "</body></html>";
  server.send(404, "text/html", html);
}

// Función para encender la matriz de LEDs con el patrón 1
void pattern1() {
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, HIGH);
digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, LOW);
  digitalWrite(pinC1, LOW);
  digitalWrite(pinC2, LOW);
  digitalWrite(pinD1, LOW);
  digitalWrite(pinD2, LOW);
}

// Función para encender la matriz de LEDs con el patrón 2
void pattern2() {
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, LOW);
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, HIGH);
  digitalWrite(pinC1, HIGH);
  digitalWrite(pinC2, LOW);
  digitalWrite(pinD1, LOW);
  digitalWrite(pinD2, LOW);
}
