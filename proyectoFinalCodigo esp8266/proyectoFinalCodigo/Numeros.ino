// Variables para los potenciómetros y el botón
int selectedOptionMenuImagenes = 0;
// Número de opciones en los menus
int numOptionsMenuImagenes = 73;

char optionImg[100][7] = { "volver", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
                           "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46",
                           "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70", "71", "72", "73",
                           "74", "75", "76", "77", "78", "79", "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", "97", "98", "99" };

void leerPotenciometrosNum() {
  // Obtener el valor de los potenciómetros y convertirlos a un índice para la opción seleccionada
  potValue1 = analogRead(POT_PIN_1);
  // potValue2 = analogRead(POT_PIN_2);
  selectedOptionMenuImagenes = map(potValue1, 0, 1023, -1, numOptionsMenuImagenes - 1);

  // Mapear el valor del primer potenciómetro a un rango de # valores
  int potRange1 = map(potValue1, 0, 1023, 0, 10);

  // Imprimir el valor del primer potenciómetro en el monitor serie
  Serial.print("Valor del potenciómetro 1: ");
  Serial.println(potRange1);
}

void numeros() {
  int activarMenu = 1;
  while (activarMenu == 1) {
    leerPotenciometrosNum();

    for (int i = 0; i < numOptionsMenuImagenes; i++) {
      tft.setTextSize(1);
      int16_t x, y;
      uint16_t w, h;
      tft.getTextBounds(optionImg[i], 0, 0, &x, &y, &w, &h);
      if (i == 0) {
        tft.setCursor((tft.width() - w) / 2, 5);
      } else {
        tft.setCursor(5 + ((i - 1) % 9) * (w + 5), 25 + ((i - 1) / 9) * (h + 5));
      }
      if (i == selectedOptionMenuImagenes) {
        tft.setTextColor(ST7735_WHITE);
      } else {
        tft.setTextColor(black);
      }
      tft.print(optionImg[i]);
      // Esperar un poco antes de leer los potenciómetros nuevamente
      delay(0);
    }

    // Chequear si el botón ha sido presionado
    if (!digitalRead(BUTTON_PIN) && !buttonPressed) {
      buttonPressed = true;

      // Acción a tomar cuando el botón es presionado
      switch (selectedOptionMenuImagenes) {
        case 0:
          activarMenu = 0;
          tft.fillScreen(turquesa);
          beep();
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
