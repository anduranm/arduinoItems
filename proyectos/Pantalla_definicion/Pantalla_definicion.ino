#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define TFT_CS    D1
#define TFT_RST   D0
#define TFT_DC    D2
#define TFT_MOSI  D7
#define TFT_CLK   D5
#define TFT_BL    3   // En tu caso el pin BL está conectado a 3V
#define TFT_VCC   VIN
#define TFT_GND   GND

#define POT_PIN A0
#define BUTTON_PIN D3

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Variables para el potenciómetro y el botón
int potValue = 0;
int selectedOption = 0;
int numOptions = 3;
bool buttonPressed = false;

// Arreglo con las opciones del menú
char options[3][10] = {"OPCION 1", "OPCION 2", "OPCION 3"};

void setup() {
  Serial.begin(9600);

  // Configuración de la pantalla
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);

  // Configuración de los pines del potenciómetro y botón
  pinMode(POT_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // Obtener el valor del potenciómetro y convertirlo a un índice para la opción seleccionada
  potValue = analogRead(POT_PIN);
  selectedOption = map(potValue, 0, 1023, 0, numOptions - 1);

  // Dibujar las opciones del menú
  for (int i = 0; i < numOptions; i++) {
    tft.setCursor(10, 20 + i*20);
    tft.setTextSize(1);
    if (i == selectedOption) {
      tft.setTextColor(ST7735_WHITE);
    } else {
      tft.setTextColor(ST7735_RED);
    }
    tft.print(options[i]);
  }

  // Chequear si el botón ha sido presionado
  if (!digitalRead(BUTTON_PIN) && !buttonPressed) {
    buttonPressed = true;

    // Acción a tomar cuando el botón es presionado
    switch(selectedOption) {
      case 0:
        tft.fillScreen(ST7735_GREEN);
        break;
      case 1:
        tft.fillScreen(ST7735_BLUE);
        break;
      case 2:
        tft.fillScreen(ST7735_YELLOW);
        break;
    }
  } else if (digitalRead(BUTTON_PIN)) {
    buttonPressed = false;
  }
}
