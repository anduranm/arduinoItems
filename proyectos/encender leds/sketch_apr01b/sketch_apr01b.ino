// Definir los pines a los que está conectada la matriz LED
//int fila1[] = {0, 2, 4, 5, 12, 14, 13, 16}; // Fila A original modificado en orden {16, 5, 4, 0, 2, 14, 12, 13}
int fila1[] = {0,2,4,5, 12, 14, 13, 16,18,19, 20,22}; // Fila A
int fila2[] = {0}; // Fila B
//int fila2[] = {15, 2, 0, 4, 5, 16, 14, 12}; // Fila B  original

void setup() {
  // Configurar los pines como salidas
  for (int i = 0; i < 8; i++) {
    pinMode(fila1[i], OUTPUT);
    pinMode(fila2[i], OUTPUT);
  }
}

void loop() {
  // Encender todos los LED de manera secuencial
  for (int i = 0; i < 8; i++) {
    digitalWrite(fila1[i], HIGH); // Encender la fila A
    delay(1);                    // Esperar # milisegundos
    digitalWrite(fila1[i], LOW);  // Apagar la fila A
    digitalWrite(fila2[i], HIGH); // Encender la fila B
    delay(1);                    // Esperar # milisegundos
    digitalWrite(fila2[i], LOW);  // Apagar la fila B
  }
}
