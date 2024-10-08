void memoryFlash() {
  // Leer las credenciales almacenadas
  preferences.begin("wifi", true);
  ssid = preferences.getString("ssid", "");
  password = preferences.getString("password", "");
  ap_ssid = preferences.getString("ap_ssid", default_ap_ssid);
  ap_password = preferences.getString("ap_password", default_ap_password);
  preferences.end();
  preferences.begin("settings", false);
  DISPENSE_DURATION = preferences.getInt("duration", 2000);  // Valor predeterminado
  preferences.end();
}

void wifiInit() {

  if (ssid != "" && password != "") {
    // Intentar conectarse a la red WiFi guardada
    WiFi.begin(ssid.c_str(), password.c_str());
    int counter = 0;
    while (WiFi.status() != WL_CONNECTED && counter < 20) {
      delay(500);
      counter++;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("Conectado a la red WiFi guardada.");
    } else {
      Serial.println("No se pudo conectar a la red WiFi guardada, activando el punto de acceso.");
    }
  } else {
    Serial.println("No se encontraron credenciales guardadas");
  }

  configurarAP();

  // Configurar manejadores de rutas
  server.on("/", handleRoot);
  server.on("/scan", handleScan);
  server.on("/connect", HTTP_POST, handleConnect);
  server.on("/configAP", HTTP_POST, handleAPconfig);
  server.on("/setDispenseDuration", HTTP_POST, handleSetDispenseDuration);  // Nueva ruta para configurar el tiempo de dispensado
  server.on("/toggleAlexaSearch", HTTP_POST, handleToggleAlexaSearch);
  server.on("/toggleAP", HTTP_POST, handleToggleAP);
  server.on("/alimentar", HTTP_POST, handleAlimentar);
  server.on("/update", HTTP_POST, handleUpdate);
  // Iniciar el servidor
  server.begin();
}

void configurarAP() {
  WiFi.softAPdisconnect(true);  // Desconectar cualquier AP previo

  if (ap_ssid == "" || ap_ssid == "No configurado") {
    ap_ssid = default_ap_ssid;  // Si no hay SSID guardado, usar el predeterminado
  }

  WiFi.softAP(ap_ssid.c_str(), ap_password.c_str());  // Iniciar el AP con el SSID y contraseña guardados
  // WiFi.softAPConfig(local_IP, gateway, subnet);  // Configurar la IP del AP

  Serial.print("AP configurado con el nombre: ");
  Serial.println(ap_ssid);
  estadoAP = true;
}

void toggleAP() {
  if (estadoAP) {
    estadoAP = false;
    WiFi.softAPdisconnect(true);  // Apaga el AP
    Serial.println("Access Point apagado.");
  } else {
    if (ap_ssid == "" || ap_ssid == "No configurado") {
      ap_ssid = default_ap_ssid;  // Si no hay SSID guardado, usar el predeterminado
    }

    WiFi.softAP(ap_ssid.c_str(), ap_password.c_str());  // Iniciar el AP con el SSID y contraseña guardados
    Serial.print("AP configurado con el nombre: ");
    Serial.println(ap_ssid);
    estadoAP = true;
  }
}

void alexaInit() {
  fauxmo.addDevice("Dispensador");
  if (search){
  fauxmo.createServer(true);
  }
  fauxmo.setPort(80);
  fauxmo.enable(true);
  fauxmo.onSetState([](unsigned char device_id, const char* device_name, bool state, unsigned char value) {
    Serial.print("\nDevice: ");
    Serial.print(device_name);
    Serial.print("\nId ");
    Serial.print(device_id);
    Serial.print("\n   state: ");
    Serial.println(state ? "ON!" : "OFF");

    if (device_id == 0) {  //Id de computer del primer disposivo
      servoOnAction = true;
    }
  });
}
