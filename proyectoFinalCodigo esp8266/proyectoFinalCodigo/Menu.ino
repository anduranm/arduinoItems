

void menuPrincipal() {
  int activarPrincipal = 1;
  while (activarPrincipal == 1) {
    leerPotenciometros();

    // Dibujar las opciones del menú
    for (int i = 0; i < numOptionsMenuPrincipal; i++) {
      tft.setCursor(10, 20 + i * 20);
      tft.setTextSize(1);
      if (i == selectedOptionMenuPrincipal) {
        tft.setTextColor(ST7735_WHITE);
      } else {
        if (i == 2) {
          if (estadoWifi) {
            tft.setTextColor(ST7735_GREEN);  // Si WiFi está encendido, poner texto en color verde
          } else {
            tft.setTextColor(ST7735_RED);  // Si WiFi está apagado, poner texto en color rojo
          }
        } else {
          tft.setTextColor(black);
        }
      }
      tft.print(optionsMenuPrincipal[i]);
    }

    // Esperar un poco antes de leer los potenciómetros nuevamente
    delay(0);

    // Chequear si el botón ha sido presionado
    if (!digitalRead(BUTTON_PIN) && !buttonPressed) {
      buttonPressed = true;

      // Acción a tomar cuando el botón es presionado
      switch (selectedOptionMenuPrincipal) {
        case 0:
          activarPrincipal = 0;
          tft.fillScreen(turquesa);
          beep();
          menuSecundario();
          break;
        case 1:
          activarPrincipal = 0;
          tft.fillScreen(turquesa);
          beep();
          numeros();
          break;
        case 2:
          tft.fillScreen(turquesa);
          beep();
          toggleWiFi();
          break;
        case 3:
          activarPrincipal = 0;
          tft.fillScreen(turquesa);
          beep();
          brillo();
          break;
      }
    } else if (digitalRead(BUTTON_PIN)) {
      buttonPressed = false;
    }
  }
}

