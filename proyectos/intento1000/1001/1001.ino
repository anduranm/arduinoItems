int fila1[] = {0, 2, 4, 5, 12, 13, 14, 16}; // Fila A
int fila2[] = {15, 2, 0, 4, 5, 16, 14, 12}; // Fila B
int col[] = {14, 12, 13, 15, 3, 1, 9, 10}; // Columnas


void setup() {
  // Configurar los pines como salida
  for (int i = 0; i < 8; i++) {
    pinMode(fila1[i], OUTPUT);
    pinMode(col[i], OUTPUT);
    pinMode(fila2[i], OUTPUT);
  }
}

void loop() {
  // Encender las filas secuencialmente
  for (int i = 0; i < 8; i++) {
    // Encender la fila actual y apagar el resto de las filas
    digitalWrite(fila1[i], HIGH);
    for (int j = 0; j < 8; j++) {
      digitalWrite(fila1[j], LOW);
    }

    // Encender la columna correspondiente a cada diodo
    for (int j = 0; j < 8; j++) {
      digitalWrite(col[j], HIGH);
      delay(10); // Ajusta el tiempo de encendido aquí si es necesario
      digitalWrite(col[j], LOW);
    }
    for(int i = 0; i < 8; i++){
    pinMode(fila2[i], OUTPUT);
    digitalWrite(fila2[i], HIGH);
  }
  }
}
