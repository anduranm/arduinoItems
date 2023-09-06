const int ROWS = 8; // número de filas
const int COLS = 8; // número de columnas

// Define las conexiones de los pines de la matriz LED
int fila[8] = {D0, D1, D2, D3, D4, D5, D6, D7};
int columna[8] = {D8, D1, D2, A0, D3, D4, D5, D6};

void setup() {
  // Configura los pines como salidas
  for (int i = 0; i < 8; i++) {
    pinMode(fila[i], OUTPUT);
    pinMode(columna[i], OUTPUT);
  }
}

void loop() {
  // Enciende solo el LED 
  digitalWrite(fila[4], LOW);  // 
  digitalWrite(columna[7], HIGH);  // 
}
