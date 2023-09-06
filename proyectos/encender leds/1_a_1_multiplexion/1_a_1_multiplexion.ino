int fila1[8] = {9, 10, 11, 12, A0, A1, A2, A3}; // Fila 1
int fila2[8] = {3, 4, 5, 6, 7, 8, A4, A5}; // Fila 2
int col[8] = {2, A6, A7, 13, 12, 10, 9, 8}; // Columnas


void setup() {
  for(int i = 0; i < 8; i++){
    pinMode(col[i], OUTPUT);
    digitalWrite(col[i], HIGH);
    pinMode(fila1[i], OUTPUT);
    digitalWrite(fila1[i], HIGH);
    pinMode(fila2[i], OUTPUT);
    digitalWrite(fila2[i], HIGH);
  }
}

void loop() {
  int selectedCol = 1; // Seleccionamos la columna 1
  int selectedRow = 0; // Seleccionamos la fila 1
  digitalWrite(col[0], LOW); // Encender la primera columna
digitalWrite(col[4], LOW); // Encender la quinta columna
}
