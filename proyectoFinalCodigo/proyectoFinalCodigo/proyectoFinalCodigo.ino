// #define POT_PIN_2 'sindefinir'
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <ESP8266WiFi.h>

#define TFT_CS D1
#define TFT_RST D0
#define TFT_DC D2
#define TFT_MOSI D7
#define TFT_CLK D5
#define TFT_BL D6
#define TFT_VCC VIN
#define TFT_GND GND
#define SPEAKER_PIN D8
#define POT_PIN_1 A0
#define BUTTON_PIN D4

//leer imagnes
//no lo he logrado xd
const char* ssid = "Proyecto ITI";
const char* password = "12345678";

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
const uint16_t white = 0xffff;
const uint16_t black = 0x0000;
const uint16_t turquesa = 0xADF7;
const uint16_t rosaClaro = 0xE112;
const uint16_t rosaOscuro = 0xFFC0CB;
const uint16_t rojo = 0xF800;

// Variables para los potenciómetros y el botón
int potValue1 = 0;
int potValue2 = 0;
int selectedOptionMenuPrincipal = 0;
int selectedOptionMenuSecundario = 0;
int selectedOptionMenuBrillo = 0;

// Número de opciones en los menus
int numOptionsMenuPrincipal = 4;
int numOptionsMenuSecundario = 4;
int numOptionsMenuBrillo = 6;

bool buttonPressed = false;

// Arreglo con las opciones del menú
char optionsMenuPrincipal[4][10] = { "siguiente", "Numeros", "Wifi", "Brillo" };
char optionsmenuSecundario[4][13] = { "volver", "Letras", "Demostracion" };
char menuBrillo[6][12] = { "volver", "Brillo 1%", "Brillo 25%", "Brillo 50%", "Brillo 75%", "Brillo 100%" };

bool estadoWifi; // Estado actual del WiFi

void setup() {
  Serial.begin(9600);
  // Configuración de la pantalla

  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);  // Orientación horizontal
  tft.fillScreen(turquesa);
  analogWrite(TFT_BL, 80);  // Establecer el brillo en 50%

  // Configuración de los pines de los potenciómetros y el botón
  pinMode(POT_PIN_1, INPUT);
  // pinMode(POT_PIN_2, INPUT); //potenciometro 2
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() {
  menuPrincipal();
}

void beep() {
  tone(SPEAKER_PIN, 2000, 100);  // genera un tono de 1000 Hz durante 500 ms
}

void leerPotenciometros() {
  // Obtener el valor de los potenciómetros y convertirlos a un índice para la opción seleccionada
  potValue1 = analogRead(POT_PIN_1);
  // potValue2 = analogRead(POT_PIN_2);

  selectedOptionMenuPrincipal = map(potValue1, 0, 1023, 0, numOptionsMenuPrincipal - 1);
  selectedOptionMenuSecundario = map(potValue1, 0, 1023, 0, numOptionsMenuSecundario - 1);
  selectedOptionMenuBrillo = map(potValue1, 0, 1023, 0, numOptionsMenuBrillo - 1);

  // Mapear el valor del primer potenciómetro a un rango de 10 valores
  int potRange1 = map(potValue1, 0, 1023, 0, 17);

  // Imprimir el valor del primer potenciómetro en el monitor serie
  // Serial.print("Valor del potenciómetro 1: ");
  // Serial.println(potRange1);

  // Mapear el valor del segundo potenciómetro a un rango de 10 valores
  // int potRange2 = map(potValue2, 0, 1023, 0, 10);

  // Imprimir el valor del segundo potenciómetro en el monitor serie
  // Serial.print("Valor del potenciómetro 2: ");
  // Serial.println(potRange2);
}
