void brillo() {
  int activarBrillo = 1;
  while (activarBrillo == 1) {
    leerPotenciometros();

    // Dibujar las opciones del menú
    for (int i = 0; i < numOptionsMenuBrillo; i++) {
      tft.setCursor(10, 15 + i * 20);
      tft.setTextSize(1);
      if (i == selectedOptionMenuBrillo) {
        tft.setTextColor(ST7735_WHITE);
      } else {
        tft.setTextColor(black);
      }
      tft.print(menuBrillo[i]);

      // Esperar un poco antes de leer los potenciómetros nuevamente
      delay(0);

      // Chequear si el botón ha sido presionado
      if (!digitalRead(BUTTON_PIN) && !buttonPressed) {
        buttonPressed = true;

        // Acción a tomar cuando el botón es presionado
        switch (selectedOptionMenuBrillo) {
          case 0:
            activarBrillo = 0;
            tft.fillScreen(turquesa);
            beep();
            menuPrincipal();
            break;
          case 1:
            beep();
            analogWrite(TFT_BL, 25);
            break;
          case 2:
            beep();
            analogWrite(TFT_BL, 64);
            break;
          case 3:
            beep();
            analogWrite(TFT_BL, 127);
            break;
          case 4:
            beep();
            analogWrite(TFT_BL, 191);
            break;
          case 5:
            beep();
            analogWrite(TFT_BL, 225);
            break;
        }
      } else if (digitalRead(BUTTON_PIN)) {
        buttonPressed = false;
      }
    }
  }
}