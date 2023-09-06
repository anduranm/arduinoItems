#include <Adafruit_NeoPixel.h>

#define LED_PIN 5
#define LED_COUNT 64

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  leds.begin();
}

void loop() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int index = i * 8 + j;
      leds.setPixelColor(index, 255, 255, 255);
    }
    leds.show();
    delay(500);
    for (int j = 0; j < 8; j++) {
      int index = i * 8 + j;
      leds.setPixelColor(index, 0, 0, 0);
    }
    leds.show();
  }
}
