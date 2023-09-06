int fila1[] = {0, 1, 2, 3, 4, 5, 6, 7}; // Fila A
int fila2[] = {15, 14, 13, 12, 11, 10, 9, 8}; // Fila B
int col[] = {14, 12, 13, 15, 3, 1, 9, 10}; // Columnas
void setup() {
  // Configurar los pines como salidas
  for (int i = 0; i < 8; i++) {
    pinMode(fila1[i], OUTPUT);
    pinMode(fila2[i], OUTPUT);
    pinMode(col[i], OUTPUT);
  }
}

void loop() {
  // Encender todos los LEDs
  for (int i = 0; i < 8; i++) {
    // Encender la columna i
    digitalWrite(col[i], HIGH);

    // Encender todas las filas
    for (int j = 0; j < 8; j++) {
      digitalWrite(fila1[j], HIGH);
      digitalWrite(fila2[j], HIGH);
    
    }

    // Apagar la columna i
    digitalWrite(col[i], LOW);
  }
}
