// Variables para los potenciómetros y el botón
int selectedOptionMenuLetras = 0;
// Número de opciones en los menus
int numOptionsMenuLetras = 28;

char optionLetraMay[28][10] = { "volver", "min", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
char optionLetraMin[28][10] = { "volver", "MAY", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };

void leerPotenciometrosLetras() {
  // Obtener el valor de los potenciómetros y convertirlos a un índice para la opción seleccionada
  potValue1 = analogRead(POT_PIN_1);
  // potValue2 = analogRead(POT_PIN_2);
  selectedOptionMenuLetras = map(potValue1, 0, 1023, 0, numOptionsMenuLetras - 1);

  // Mapear el valor del primer potenciómetro a un rango de # valores
  int potRange1 = map(potValue1, 0, 1023, 0, 28);

  // Imprimir el valor del primer potenciómetro en el monitor serie
  Serial.print("Valor del potenciómetro 1: ");
  Serial.println(potRange1);
}

void letrasMayus() {
  int menuMay = 1;
  while (menuMay == 1) {
    leerPotenciometrosLetras();

    for (int i = 0; i < numOptionsMenuLetras; i++) {
      tft.setTextSize(1);
      int16_t x, y;
      uint16_t w, h;
      tft.getTextBounds(optionLetraMay[i], 0, 0, &x, &y, &w, &h);
      if (i == 0) {
        tft.setCursor((tft.width() - w) / 2, 5);
      } else {
        tft.setCursor(18 + ((i - 1) % 6) * (w + 16), 25 + ((i - 1) / 6) * (h + 10));
      }
      if (i == selectedOptionMenuLetras) {
        tft.setTextColor(ST7735_WHITE);
      } else {
        tft.setTextColor(black);
      }
      tft.print(optionLetraMay[i]);
      // Esperar un poco antes de leer los potenciómetros nuevamente
      delay(0);
    }

    // Chequear si el botón ha sido presionado
    if (!digitalRead(BUTTON_PIN) && !buttonPressed) {
      buttonPressed = true;

      // Acción a tomar cuando el botón es presionado
      switch (selectedOptionMenuLetras) {
        case 0:
          menuMay = 0;
          tft.fillScreen(turquesa);
          beep();
          menuPrincipal();
          break;
        case 1:
          menuMay = 0;
          tft.fillScreen(turquesa);
          beep();
          letrasMinuscula();
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

void letrasMinuscula() {
  int menuMin = 1;
  while (menuMin == 1) {
    leerPotenciometrosLetras();

    for (int i = 0; i < numOptionsMenuLetras; i++) {
      tft.setTextSize(1);
      int16_t x, y;
      uint16_t w, h;
      tft.getTextBounds(optionLetraMin[i], 0, 0, &x, &y, &w, &h);
      if (i == 0) {
        tft.setCursor((tft.width() - w) / 2, 5);
      } else {
        tft.setCursor(18 + ((i - 1) % 6) * (w + 16), 25 + ((i - 1) / 6) * (h + 10));
      }
      if (i == selectedOptionMenuLetras) {
        tft.setTextColor(ST7735_WHITE);
      } else {
        tft.setTextColor(black);
      }
      tft.print(optionLetraMin[i]);
      // Esperar un poco antes de leer los potenciómetros nuevamente
      delay(0);
    }

    // Chequear si el botón ha sido presionado
    if (!digitalRead(BUTTON_PIN) && !buttonPressed) {
      buttonPressed = true;

      // Acción a tomar cuando el botón es presionado
      switch (selectedOptionMenuLetras) {
        case 0:
          menuMin = 0;
          tft.fillScreen(turquesa);
          beep();
          menuPrincipal();
          break;
        case 1:
          menuMin = 0;
          tft.fillScreen(turquesa);
          beep();
          letrasMayus();
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
