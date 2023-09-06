#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS   D1
#define TFT_RST  D0
#define TFT_DC   D2
#define TFT_MOSI D7
#define TFT_CLK  D5
#define TFT_BL   3
#define TFT_VCC  VIN
#define TFT_GND  GND

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);
const uint16_t white = 0xffff;
const uint16_t black = 0x0000;
const uint16_t turquesa = 0xADF7;
const uint16_t rosaClaro = 0xE112;
const uint16_t rosaOscuro = 0xFFC0CB;

//0xFF69B4 morado 

void setup() {
  tft.initR(INITR_BLACKTAB);  // Inicializa la pantalla
  pinMode(TFT_BL, OUTPUT);
  analogWrite(TFT_BL, 50);  // Enciende la pantalla al máximo brillo
  tft.setRotation(1);  // Gira la pantalla 90 grados (modo horizontal)

  // Configura la fuente y el tamaño del texto
  tft.setTextWrap(true);
  tft.setTextSize(2);
  tft.setTextColor(ST7735_WHITE);
}
