#include "config.h"

void loop() {
  fauxmo.handle();
  handleServo();
  server.handleClient();
}

void setup() {
  Serial.begin(115200);
  memoryFlash();
  wifiInit();
  alexaInit();
}

//alexa
void handleServo() {
  if (servoOnAction) {
    myServo.attach(15);
    delay(1000);
    myServo.write(SERVO_ANGLE_OPEN);
    delay(DISPENSE_DURATION);
    myServo.write(SERVO_ANGLE_CLOSE);
    servoOnAction = false;  // Reinicia la acción
    delay(1000);
     myServo.detach();
  }
}