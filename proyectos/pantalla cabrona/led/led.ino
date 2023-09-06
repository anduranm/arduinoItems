#include <Adafruit_GFX.h> // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library.
#include <SPI.h>

#define TFT_RST D0
#define TFT_CS D1
#define TFT_DC D2

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC , TFT_RST);

const uint16_t white = 0xffff;
const uint16_t black = 0x0000;

void setup() {
//  Serial.begin(115200);

  tft.initR(INITR_BLACKTAB); // initialize a ST7735S chip, black tab

  tft.setTextWrap(false);
  tft.fillScreen(black);
  tft.setTextColor(white);
  tft.setTextSize(0.5);
  tft.setCursor(20, 0);
  tft.println("Hola broskis!");
  
  tft.setTextSize(0.005);
  tft.setCursor(10, 30);
  tft.println("Que tal la vida?");
}

void loop() {
}
