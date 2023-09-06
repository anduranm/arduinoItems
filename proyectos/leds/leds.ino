#include <Wire.h>
#include "Adafruit_GFX.h"
#include "Adafruit_LEDBackpack.h"

// Definir el objeto de tipo matrix de 8x8 LEDs
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

// Definir el buffer de imagen
byte buffer[8][8] = {
  { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 },
  { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 },
  { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 },
  { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 },
  { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 },
  { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 },
  { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 },
  { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 }
};

void setup() {
  // Inicializar la matriz LED
  matrix.begin();
}

void loop() {
  // Recorrer cada fila de la matriz
  for (int row = 0; row < 8; row++) {
    // Recorrer cada columna de la matriz
    for (int col = 0; col < 8; col++) {
      // Establecer el estado del píxel según el valor del buffer
      if (bitRead(buffer[row][col/8], col%8)) {
        matrix.drawPixel(row, col, LED_ON);
      } else {
        matrix.drawPixel(row, col, LED_OFF);
      }
    }
  }
  
  // Actualizar la matriz LED
  matrix.writeDisplay();
}
