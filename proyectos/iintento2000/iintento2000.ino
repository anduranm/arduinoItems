#include <ESP8266WiFi.h>

// Declarar pines de la matriz LED
const int ROW_1 = D0;
const int ROW_2 = D1;
const int ROW_3 = D2;
const int ROW_4 = D3;
const int ROW_5 = D4;
const int ROW_6 = D5;
const int ROW_7 = D6;
const int ROW_8 = D7;
const int COL_1 = D8;
const int COL_2 = D1;
const int COL_3 = D2;
const int COL_4 = A0;
const int COL_5 = D3;
const int COL_6 = D4;
const int COL_7 = D5;
const int COL_8 = D6;

void setup() {
  // Conectar a la red WiFi
  WiFi.begin("No puedes entrar", "P81M40A21H");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red WiFi...");
  }

  // Inicializar los pines de la matriz LED como salida
  pinMode(ROW_1, OUTPUT);
  pinMode(ROW_2, OUTPUT);
  pinMode(ROW_3, OUTPUT);
  pinMode(ROW_4, OUTPUT);
  pinMode(ROW_5, OUTPUT);
  pinMode(ROW_6, OUTPUT);
  pinMode(ROW_7, OUTPUT);
  pinMode(ROW_8, OUTPUT);
  pinMode(COL_1, OUTPUT);
  pinMode(COL_2, OUTPUT);
  pinMode(COL_3, OUTPUT);
  pinMode(COL_4, OUTPUT);
  pinMode(COL_5, OUTPUT);
  pinMode(COL_6, OUTPUT);
  pinMode(COL_7, OUTPUT);
  pinMode(COL_8, OUTPUT);
}

void loop() {
  // Código para controlar la matriz LED
}
