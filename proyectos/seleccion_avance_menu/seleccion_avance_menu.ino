#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

#define TFT_CS    D1
#define TFT_RST   D0
#define TFT_DC    D2
#define TFT_MOSI  D7
#define TFT_CLK   D5
#define TFT_BL    D6   // En tu caso el pin BL está conectado a 3V
#define TFT_VCC   VIN
#define TFT_GND   GND

#define POT_PIN_1 A0
#define POT_PIN_2 D3
#define BUTTON_PIN D4

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
int numOptionsMenuPrincipal = 3;
int numOptionsMenuSecundario = 4; // Número de opciones en el menú secundario
bool buttonPressed = false;

// Arreglo con las opciones del menú
char options[3][10] = {"OPCION 1", "OPCION 2", "OPCION 3"};
char menuSecundario[4][10] = {"VOLVER", "OPCION 2", "OPCION 3", "OPCION 4"};

void setup() {
  Serial.begin(9600);

  // Configuración de la pantalla
  
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1); // Orientación horizontal 
  tft.fillScreen(turquesa);
  analogWrite(TFT_BL, 80); // Establecer el brillo en 50%
   
  // Configuración de los pines de los potenciómetros y el botón
  pinMode(POT_PIN_1, INPUT);
  pinMode(POT_PIN_2, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  menuPrincipal();
}

void leerPotenciometros() {
  // Obtener el valor de los potenciómetros y convertirlos a un índice para la opción seleccionada
  potValue1 = analogRead(POT_PIN_1);
  potValue2 = analogRead(POT_PIN_2);
  selectedOptionMenuPrincipal = map(potValue1, 0, 1023, 0, numOptionsMenuPrincipal - 1);
  selectedOptionMenuSecundario = map(potValue1, 0, 1023, 0, numOptionsMenuSecundario - 1);

  // Mapear el valor del primer potenciómetro a un rango de 10 valores
  int potRange1 = map(potValue1, 0, 1023, 0, 10);

  // Imprimir el valor del primer potenciómetro en el monitor serie
  Serial.print("Valor del potenciómetro 1: ");
  Serial.println(potRange1);

  // Mapear el valor del segundo potenciómetro a un rango de 10 valores
  int potRange2 = map(potValue2, 0, 1023, 0, 10);

  // Imprimir el valor del segundo potenciómetro en el monitor serie
  Serial.print("Valor del potenciómetro 2: ");
  Serial.println(potRange2);
}

void menuPrincipal() {
  int activarPrincipal=1;
  while (activarPrincipal == 1) {
    leerPotenciometros();
    
    // Dibujar las opciones del menú
    for (int i = 0; i < numOptionsMenuPrincipal; i++) {
      tft.setCursor(10, 20 + i*20);
      tft.setTextSize(1);
      if (i == selectedOptionMenuPrincipal) {
        tft.setTextColor(ST7735_WHITE);
      } else {
        tft.setTextColor(black);
      }
      tft.print(options[i]);
    }

    // Esperar un poco antes de leer los potenciómetros nuevamente
    delay(50);

    // Chequear si el botón ha sido presionado
    if (!digitalRead(BUTTON_PIN) && !buttonPressed) {
      buttonPressed = true;

      // Acción a tomar cuando el botón es presionado
      switch(selectedOptionMenuPrincipal) {
        case 0:
            activarPrincipal = 0;
            tft.fillScreen(turquesa);
            menu1();
          break;
        case 1:
          // Acción para la opción 2
          break;
        case 2:
          // Acción para la opción 3
          break;
      }
    } else if (digitalRead(BUTTON_PIN)) {
      buttonPressed = false;
    }
  }
}

void menu1() {
   int activarSecundario = 1;
  while (activarSecundario == 1) {
    leerPotenciometros();
    
    // Dibujar las opciones del menú
    for (int i = 0; i < numOptionsMenuSecundario; i++) {
    tft.setCursor(10, 20 + i*20);
    tft.setTextSize(1);
    if (i == selectedOptionMenuSecundario) {
      tft.setTextColor(ST7735_WHITE);
    } else {
      tft.setTextColor(ST7735_RED);
    }
    tft.print(menuSecundario[i]);

    // Esperar un poco antes de leer los potenciómetros nuevamente
    delay(50);

    // Chequear si el botón ha sido presionado
    if (!digitalRead(BUTTON_PIN) && !buttonPressed) {
    buttonPressed = true;

      // Acción a tomar cuando el botón es presionado
      switch(selectedOptionMenuSecundario) {
      case 0:
        activarSecundario = 0;
        tft.fillScreen(turquesa);
        menuPrincipal();
        break;
      case 1:
        // Acción para la opción 2
        break;
      case 2:
        // Acción para la opción 3
        break;
    }
    } else if (digitalRead(BUTTON_PIN)) {
    buttonPressed = false;
  }
  }
 }
}
