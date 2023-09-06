#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// Definimos los pines para la pantalla TFT
#define TFT_CS  D1
#define TFT_RST D0
#define TFT_DC  D2
#define TFT_SCLK D5
#define TFT_MOSI D7

// Definimos las dimensiones de la pantalla TFT
#define TFT_WIDTH  128
#define TFT_HEIGHT 160

// Creamos el objeto de la pantalla TFT
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// Definimos los pines para el pulsador
#define PIN_PULSADOR  D3

// Definimos los estados del menú
#define OPCION_1  1
#define OPCION_2  2
#define OPCION_3  3
#define SALIR     4

// Variables para guardar el nombre y el apellido ingresados
String nombre = "";
String apellido = "";

// Función para mostrar la pantalla de bienvenida
void mostrar_pantalla_bienvenida() {
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 50);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  tft.println("Bienvenido!");
}

// Función para mostrar el menú en la pantalla TFT
void mostrar_menu(int opcion_actual) {
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);

  if (opcion_actual == OPCION_1) {
    tft.println("> Opcion 1");
  } else {
    tft.println("  Opcion 1");
  }

  if (opcion_actual == OPCION_2) {
    tft.println("> Opcion 2");
  } else {
    tft.println("  Opcion 2");
  }

  if (opcion_actual == OPCION_3) {
    tft.println("> Ingresar nombre y apellido");
  } else {
    tft.println("  Ingresar nombre y apellido");
  }

  if (opcion_actual == SALIR) {
    tft.println("> Salir");
  } else {
    tft.println("  Salir");
  }
}

// Función para detectar la pulsación del pulsador
bool leer_pulsador() {
  int estado_pulsador = digitalRead(PIN_PULSADOR);
  delay(50); // debounce
  if (estado_pulsador == HIGH) {
    return true;
  } else {
    return false;
  }
}

// Función para ingresar nombre y apellido
void ingresar_nombre_y_apellido() {
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 50);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  tft.println("Ingrese nombre:");

  while (true) {
    if (leer_pulsador()) {
      break;
    }
  }

  while (true) {
    if (leer_pulsador()) {
      break;
    }
  }

  nombre = Serial.readStringUntil('\n');

  // Leer el apellido
  tft.println("Apellido:");
  while (true) {
    if (Serial.available() > 0) {
      apellido = Serial.readStringUntil('\n');
      break;
    }
  }

  // Mostrar el apellido en la pantalla TFT
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);
  tft.println("Nombre: " + nombre);
  tft.println("Apellido: " + apellido);
  tft.println("");
  tft.println("Presione para volver");
  
  // Esperar a que se presione el pulsador para volver
  while (true) {
    if (leer_pulsador()) {
      break;
    }
  }
}
