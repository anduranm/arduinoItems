void menuSecundario() {
  int activarSecundario = 1;
  while (activarSecundario == 1) {
    leerPotenciometros();

    // Dibujar las opciones del menú
    for (int i = 0; i < numOptionsMenuSecundario; i++) {
      tft.setCursor(10, 20 + i * 20);
      tft.setTextSize(1);
      if (i == selectedOptionMenuSecundario) {
        tft.setTextColor(ST7735_WHITE);
      } else {
        tft.setTextColor(black);
      }
      tft.print(optionsmenuSecundario[i]);

      // Esperar un poco antes de leer los potenciómetros nuevamente
      delay(0);

      // Chequear si el botón ha sido presionado
      if (!digitalRead(BUTTON_PIN) && !buttonPressed) {
        buttonPressed = true;

        // Acción a tomar cuando el botón es presionado
        switch (selectedOptionMenuSecundario) {
          case 0:
            activarSecundario = 0;
            tft.fillScreen(turquesa);
            beep();
            menuPrincipal();
            break;
          case 1:
            activarSecundario = 0;
            tft.fillScreen(turquesa);
            beep();
            letrasMayus();
            break;
          case 2:
            activarSecundario = 0;
            tft.fillScreen(turquesa);
            beep();
            animacionesGeometricas();
            break;
        }
      } else if (digitalRead(BUTTON_PIN)) {
        buttonPressed = false;
      }
    }
  }
}
