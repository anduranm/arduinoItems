const int ledPin = 2; // Pin donde está conectado el LED integrado en el ESP32 Dev

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH); // Enciende el LED
  delay(2000); // Espera 2 segundos
  digitalWrite(ledPin, LOW); // Apaga el LED
  delay(2000); // Espera 2 segundos
}