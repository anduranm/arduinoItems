#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS    D1
#define TFT_RST   D0
#define TFT_DC    D2
#define TFT_MOSI  D7
#define TFT_CLK   D5
#define TFT_BL    3   // En tu caso el pin BL está conectado a 3V
#define TFT_VCC   VIN
#define TFT_GND   GND

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);

const uint16_t white = 0xFFFF;
const uint16_t black = 0x0000;
const uint16_t red = 0xF800;

void setup() {
  tft.initR(INITR_BLACKTAB);

  tft.setTextWrap(false); // Deshabilitar el ajuste automático de texto
  tft.fillScreen(black);
  tft.drawRect(0, 0, tft.width(), tft.height(), white); // Borde blanco
}

void loop() {
  int corazonSize = 20; // Tamaño del corazón
  int corazonX = tft.width() / 2; // Coordenada X del centro del corazón
  int corazonY = tft.height() / 2; // Coordenada Y del centro del corazón
  int corazonTopX = corazonX; // Coordenada X del vértice superior del corazón
  int corazonTopY = corazonY - corazonSize; // Coordenada Y del vértice superior del corazón
  int corazonLeftX = corazonX - corazonSize; // Coordenada X del vértice izquierdo del corazón
  int corazonRightX = corazonX + corazonSize; // Coordenada X del vértice derecho del corazón
  
  // Dibujar triángulo izquierdo del corazón
  tft.fillTriangle(corazonLeftX, corazonY, corazonTopX, corazonTopY, corazonX, corazonY, red);
  
  // Dibujar triángulo derecho del corazón
  tft.fillTriangle(corazonX, corazonY, corazonTopX, corazonTopY, corazonRightX, corazonY, red);
  
  // Dibujar círculo en el centro del corazón
  tft.fillCircle(corazonX, corazonY, corazonSize / 2, red);
  
  delay(1000);
}
