// Definir los pines correspondientes a las filas y columnas de la matriz LED
const int fila[] = {D0, D1, D2, D3, D4, D5, D6, D7};
const int columna[] = {D1, D2, D3, D4, D5, D6, D8, D9};

void setup() {
  // Configurar los pines como salida
  for (int i = 0; i < 8; i++) {
    pinMode(fila[i], OUTPUT);
    pinMode(columna[i], OUTPUT);
  }
}

void loop() {
  // Encender las filas secuencialmente
  for (int i = 0; i < 8; i++) {
    // Encender la fila actual y apagar el resto de las filas
    digitalWrite(fila[i], HIGH);
    for (int j = 0; j < 8; j++) {
      digitalWrite(fila[j], LOW);
    }

    // Encender la columna correspondiente a cada diodo
    for (int j = 0; j < 8; j++) {
      digitalWrite(columna[j], HIGH);
      delay(10); // Ajusta el tiempo de encendido aquí si es necesario
      digitalWrite(columna[j], LOW);
    }
  }
}
