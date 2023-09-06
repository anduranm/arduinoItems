// Definir los pines a los que está conectada la matriz LED
const byte FILAS = 8;
const byte COLUMNAS = 8;

byte filaPines[FILAS][2] = {
  {0, 1}, // Fila 0
  {2, 3}, // Fila 1
  {4, 5}, // Fila 2
  {6, 7}, // Fila 3
  {8, 9}, // Fila 4
  {10, 11}, // Fila 5
  {12, 13}, // Fila 6
  {14, 15}  // Fila 7
};

byte columnaPines[COLUMNAS] = {16, 17, 18, 19, 20, 21, 22, 23}; // Columnas

// Definir la matriz que representa la imagen
byte imagen[FILAS] = {
  B10000000,
  B01000000,
  B01100000,
  B01110000,
  B01101000,
  B00000100,
  B00000010,
  B00000001
};

void setup() {
  // Configurar los pines como salidas
  for (byte i = 0; i < FILAS; i++) {
    pinMode(filaPines[i][0], OUTPUT);
    pinMode(filaPines[i][1], OUTPUT);
  }
  for (byte i = 0; i < COLUMNAS; i++) {
    pinMode(columnaPines[i], OUTPUT);
  }
}

void loop() {
  // Actualizar la imagen
  for (byte i = 0; i < COLUMNAS; i++) {
    // Seleccionar la columna correspondiente
    digitalWrite(columnaPines[i], HIGH);

    // Actualizar las filas
    for (byte j = 0; j < FILAS; j++) {
      digitalWrite(filaPines[j][0], bitRead(imagen[j], i));
      digitalWrite(filaPines[j][1], !bitRead(imagen[j], i));
    }

    // Esperar un breve instante antes de actualizar la siguiente columna
    delayMicroseconds(100);

    // Apagar todas las filas antes de actualizar la siguiente columna
    for (byte j = 0; j < FILAS; j++) {
      digitalWrite(filaPines[j][0], LOW);
      digitalWrite(filaPines[j][1], LOW);
    }

    // Desseleccionar la columna correspondiente
    digitalWrite(columnaPines[i], LOW);
  }
}
