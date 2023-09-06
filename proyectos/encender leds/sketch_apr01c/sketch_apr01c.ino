// Definir los pines de las filas A y B
const int filaA[] = {D0, D1, D2, D3, D4, D5, D6, D7};
const int filaB[] = {D8, D7, D6, D5, D4, D3, D2, D1};

// Definir la matriz LED
int matriz[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

void setup() {
  // Configurar los pines de las filas A y B como salida
  for (int i = 0; i < 8; i++) {
    pinMode(filaA[i], OUTPUT);
    pinMode(filaB[i], OUTPUT);
  }
}

void loop() {
  // Encender cada LED de la matriz en secuencia
  for (int fila = 0; fila < 8; fila++) {
    for (int columna = 0; columna < 8; columna++) {
      // Encender el LED en la posición (fila, columna)
      matriz[fila][columna] = 1;
      actualizarMatriz();
      delay(100);
      // Apagar el LED en la posición (fila, columna)
      matriz[fila][columna] = 0;
    }
  }
}

void actualizarMatriz() {
  // Actualizar la matriz LED en función de la matriz de estado
  for (int fila = 0; fila < 8; fila++) {
    for (int columna = 0; columna < 8; columna++) {
      // Encender o apagar el LED en la posición (fila, columna)
      if (matriz[fila][columna] == 1) {
        digitalWrite(filaA[fila], HIGH);
        digitalWrite(filaB[columna], LOW);
      } else {
        digitalWrite(filaA[fila], LOW);
        digitalWrite(filaB[columna], HIGH);
      }
    }
  }
}
