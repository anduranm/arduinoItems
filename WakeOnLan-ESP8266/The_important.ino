int senalSimulatorPin = D1; // Pin para controlar la señal (cambia esto según tu configuración)
bool outputMode = false; // Variable para alternar entre OUTPUT e INPUT

void sendSignalToTurnOnOrOff() {

  
  // Cambia el modo del pin dinámicamente
    if (outputMode) {
      Serial.println("Switching to OUTPUT...");
      pinMode(senalSimulatorPin, OUTPUT);
    }else{
      pinMode(senalSimulatorPin, INPUT); // Cambia el pin a modo INPUT
      Serial.println("Switching  to INPUT...");
    }

    delay(75);
    outputMode = false;
}

bool switchingInProgress = false; // Variable para evitar múltiples cambios de outputMode

void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    // Si el tipo es "callback_query", un botón del teclado en línea fue presionado
    if (bot.messages[i].type == F("callback_query")) {
      Serial.print("Call back button pressed with text: ");
      Serial.println(text);

      if (text.startsWith("WOL")) {
        text.replace("WOL", "");
        int index = text.toInt();
        Serial.print("Sending WOL to: ");
        Serial.println(devices[index].deviceName);
        WakeOnLan::sendWOL(computer_ip, UDP, devices[index].mac, sizeof devices[index].mac);
      }

      // Verificar si el callback es para encender
      if (text == F("Switch") && !switchingInProgress) {
        switchingInProgress = true; // Evitar más cambios hasta que se complete
        outputMode = !outputMode; // Cambiar el modo
        Serial.println("Nice");
        bot.sendMessage(chat_id, "Switching PC...", "Markdown");
        switchingInProgress = false;
      }
    } else {
      // Cuando no es un callback, procesa los comandos normales
      if (text == F("/wol")) {
        // Crear un teclado en línea para enviar WOL a los dispositivos
        String keyboardJson = "[";
        for (int i = 0; i < numDevices; i++) {
          keyboardJson += "[{ \"text\" : \"" + devices[i].deviceName + "\", \"callback_data\" : \"WOL" + String(i) + "\" }]";
          if (i + 1 < numDevices) {
            keyboardJson += ",";
          }
        }
        keyboardJson += "]";
        bot.sendMessageWithInlineKeyboard(chat_id, "Send WOL to following devices:", "", keyboardJson);
      }

      // Cuando se recibe el comando "/start", mostrar opciones disponibles
      if (text == F("/start")) {
        bot.sendMessage(chat_id, "The options are /wol to wake a device at home or /setPC to Turn On or Off your computer: \n", "Markdown");
      }

      // Cuando se recibe el comando "/set", mostrar opciones para encender o apagar
      if (text == F("/setPC")) {
        String keyboardJson = "[";
        // Si el dispositivo está encendido, muestra la opción de apagar
        keyboardJson += "[{ \"text\" : \"Switch\", \"callback_data\" : \"Switch\" }]";
        keyboardJson += "]";
        bot.sendMessageWithInlineKeyboard(chat_id, "Switch PC between On & Off?", "", keyboardJson);
      }
    }
  }
}

void loop() {
  if (millis() > lastTimeChecked + delayBetweenChecks) {
    // getUpdates returns 1 if there is a new message from Telegram
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    if (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
    }

    lastTimeChecked = millis();
  }
  sendSignalToTurnOnOrOff(); // Llama a la función para enviar la señal de encendido
}
