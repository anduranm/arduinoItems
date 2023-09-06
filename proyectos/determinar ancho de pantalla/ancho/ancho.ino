#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library.
#include <SPI.h>

#define TFT_CS    10
#define TFT_RST   9
#define TFT_DC    8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.initR(INITR_BLACKTAB); // initialize a ST7735S chip, black tab
  
  tft.fillScreen(ST7735_CYAN);
  tft.drawRect(0, 0, tft.width(), tft.height(), ST7735_WHITE);
}

void loop() {
}
