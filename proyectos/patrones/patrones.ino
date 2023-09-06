#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>

// Define los pines a usar para las filas y columnas de la matriz LED
const int FILA1 = D0;
const int FILA2 = D1;
const int FILA3 = D2;
const int FILA4 = D3;
const int FILA5 = D4;
const int FILA6 = D5;
const int FILA7 = D6;
const int FILA8 = D8;

const int COL1 = D8;
const int COL2 = D7;
const int COL3 = D2;
const int COL4 = A0;
const int COL5 = D3;
const int COL6 = D4;
const int COL7 = D5;
const int COL8 = D6;

// Crea un objeto de tipo Adafruit_8x8matrix
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

void setup() {
  // Configura los pines como salida
  pinMode(FILA1, OUTPUT);
  pinMode(FILA2, OUTPUT);
  pinMode(FILA3, OUTPUT);
  pinMode(FILA4, OUTPUT);
  pinMode(FILA5, OUTPUT);
  pinMode(FILA6, OUTPUT);
  pinMode(FILA7, OUTPUT);
  pinMode(FILA8, OUTPUT);
  pinMode(COL1, OUTPUT);
  pinMode(COL2, OUTPUT);
  pinMode(COL3, OUTPUT);
  pinMode(COL4, OUTPUT);
  pinMode(COL5, OUTPUT);
  pinMode(COL6, OUTPUT);
  pinMode(COL7, OUTPUT);
  pinMode(COL8, OUTPUT);

  // Inicializa la matriz LED
  matrix.begin(0x70); // dirección I2C de la matriz
  matrix.clear(); // limpia la matriz
}

void loop() {
  // Enciende LED por LED
  for (int fila = 0; fila < 8; fila++) {
    for (int columna = 0; columna < 8; columna++) {
      matrix.drawPixel(columna, fila, 1);
      matrix.writeDisplay();
      delay(100);
      matrix.drawPixel(columna, fila, 0);
      matrix.writeDisplay();
    }
  }
}
