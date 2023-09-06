void toggleWiFi() {
  if (estadoWifi) { // Si el WiFi está encendido, se apaga
    WiFi.disconnect();
    WiFi.softAPdisconnect(true);
    estadoWifi = false;
    Serial.println("WiFi apagado");
  } else { // Si el WiFi está apagado, se enciende
    WiFi.softAP("Proyecto ITI", "12345678");
    estadoWifi = true;
    Serial.println("WiFi encendido");
  }
}