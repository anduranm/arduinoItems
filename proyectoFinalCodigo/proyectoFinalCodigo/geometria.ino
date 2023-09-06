int buttonState;  // declarar buttonState aquí para que esté en el ámbito correcto
int currentShape = 0;
unsigned long lastShapeChangeTime = 0;

void drawGeometricShapes(int potValue1, int shapeIndex) {
  // Map potValue1 (0-1023) to range of colors (0-255)
  int colorValue = map(potValue1, 0, 1023, 0, 255);

  // Set background color using potValue1
  tft.fillScreen(tft.color565(255 - colorValue, 255 - colorValue, 255 - colorValue));

  // Set shape position and size based on screen size and potValue1
  int shapeSize = map(potValue1, 0, 1023, 10, 100);
  int screenWidth = tft.width();
  int screenHeight = tft.height();
  int shapeX = (screenWidth - shapeSize) / 2;
  int shapeY = (screenHeight - shapeSize) / 2;

  // Draw selected shape
  switch (shapeIndex) {
    case 0:
      // Draw circle
      tft.fillCircle(shapeX + shapeSize / 2, shapeY + shapeSize / 2, shapeSize / 2, tft.color565(colorValue, 0, 0));
      break;
    case 1:
      // Draw square
      tft.fillRect(shapeX, shapeY, shapeSize, shapeSize, tft.color565(0, colorValue, 0));
      break;
    case 2:
      // Draw triangle
      tft.fillTriangle(shapeX, shapeY + shapeSize, shapeX + shapeSize / 2, shapeY, shapeX + shapeSize, shapeY + shapeSize, tft.color565(0, 0, colorValue));
      break;
    case 3:
      // Draw diamond
      tft.fillTriangle(shapeX + shapeSize / 2, shapeY, shapeX, shapeY + shapeSize / 2, shapeX + shapeSize / 2, shapeY + shapeSize, tft.color565(colorValue, colorValue, 0));
      tft.fillTriangle(shapeX + shapeSize / 2, shapeY, shapeX + shapeSize / 2, shapeY + shapeSize, shapeX + shapeSize, shapeY + shapeSize / 2, tft.color565(colorValue, colorValue, 0));
      break;
    case 4:
      // Draw cross
      tft.drawLine(shapeX, shapeY, shapeX + shapeSize, shapeY + shapeSize, tft.color565(colorValue, 0, colorValue));
      tft.drawLine(shapeX, shapeY + shapeSize, shapeX + shapeSize, shapeY, tft.color565(colorValue, 0, colorValue));
      break;
    case 5:
      // Draw sphere
      tft.fillCircle(shapeX + shapeSize / 2, shapeY + shapeSize / 2, shapeSize / 2, tft.color565(0, colorValue, colorValue));
      break;
    case 6:
      // Draw cone
      tft.fillTriangle(shapeX + shapeSize / 2, shapeY, shapeX, shapeY + shapeSize, shapeX + shapeSize, shapeY + shapeSize, tft.color565(colorValue, 0, colorValue));
      tft.fillCircle(shapeX + shapeSize / 2, shapeY + shapeSize - shapeSize / 4, shapeSize / 4, tft.color565(colorValue, 0, colorValue));
      break;
    case 7:
      // Draw hexagon
      int hexSide = shapeSize / 2;
      int hexHeight = sqrt(3) * hexSide / 2;
      tft.fillTriangle(shapeX + hexSide, shapeY, shapeX + hexSide / 2, shapeY + hexHeight, shapeX + hexSide + hexSide / 2, shapeY + hexHeight, tft.color565(colorValue, 0, 0));
      tft.fillTriangle(shapeX + hexSide, shapeY + shapeSize, shapeX + hexSide / 2, shapeY + shapeSize - hexHeight, shapeX + hexSide + hexSide / 2, shapeY + shapeSize - hexHeight, tft.color565(colorValue, 0, 0));
      tft.fillRect(shapeX, shapeY + hexHeight, shapeSize, shapeSize - 2 * hexHeight, tft.color565(0, colorValue, 0));
      break;
  }
}

void animacionesGeometricas() {
  volatile bool animacionesGeometricas = true;
  int buttonState;
  int lastButtonState = LOW;
  int rectX = 0;
  int potValue1 = 0;  // Declarar la variable potValue1
  unsigned long startTime = millis();
  unsigned long elapsedTime = 0;  // Agregar esta línea
  
  while (animacionesGeometricas) {
    potValue1 = analogRead(POT_PIN_1);
    buttonState = digitalRead(BUTTON_PIN);

    if (lastButtonState == HIGH && buttonState == LOW) {
      animacionesGeometricas = false;
      tft.fillScreen(turquesa);
      beep();
      menuPrincipal();
      break;
    }

    lastButtonState = buttonState;

    drawGeometricShapes(potValue1, currentShape);

    int rectSpeed = map(potValue1, 0, 1023, 1, 10);
    rectX += rectSpeed;
    if (rectX > tft.width()) {
      rectX = 0;
    }


    elapsedTime = millis() - startTime;  // Agregar esta línea
    if (elapsedTime >= 0) {              // cada
      currentShape = (currentShape + 1) % 7;
      drawGeometricShapes(potValue1, currentShape);
      lastShapeChangeTime = millis();
    }

  }
}
