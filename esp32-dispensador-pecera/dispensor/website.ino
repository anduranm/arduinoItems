void handleSetDispenseDuration() {
  if (server.hasArg("duration")) {
    DISPENSE_DURATION = server.arg("duration").toInt();

    // Guardar el tiempo de dispensador en las preferencias
    preferences.begin("settings", false);
    preferences.putInt("duration", DISPENSE_DURATION);
    preferences.end();

      server.sendHeader("Location", "/");  // Redirigir a la página principal
  server.send(303);  
  } else {
    server.send(400, "text/html", "<h1>Error: se requiere el parámetro 'duration'</h1>");
  }
}

void handleScan() {
  int n = WiFi.scanNetworks();
  String json = "[";
  for (int i = 0; i < n; ++i) {
    if (i > 0) json += ",";
    json += "\"" + WiFi.SSID(i) + "\"";
  }
  json += "]";
  server.send(200, "application/json", json);
}

void handleConnect() {
  ssid = server.arg("ssid");
  password = server.arg("password");
  ap_ssid = server.arg("ap_ssid");
  ap_password = server.arg("ap_password");
  if (ap_ssid == "") ap_ssid = "Dispensador_AP";
  if (ap_password == "") ap_password = "default";
  

  // Guardar las credenciales en la memoria flash
  preferences.begin("wifi", false);
  preferences.putString("ssid", ssid);
  preferences.putString("password", password);
  preferences.end();

  // Intentar conectarse a la red seleccionada
  WiFi.begin(ssid.c_str(), password.c_str());

  // Esperar a que se conecte
  int counter = 0;
  while (WiFi.status() != WL_CONNECTED && counter < 20) {
    delay(500);
    counter++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Conectado exitosamente!");
  } else {
    Serial.print("Sin connexion!");
  }
  server.sendHeader("Location", "/");  // Redirigir a la página principal
  server.send(303);
}

void handleAPconfig() {
  ap_ssid = server.arg("ap_ssid");
  ap_password = server.arg("ap_password");

  if (ap_ssid == "") ap_ssid = "Dispensador_AP";
  if (ap_password == "") ap_password = "default";

  String response = "<html><body>";
  response += "<h1>Configurando Access Point</h1>";
  response += "<p>Por favor, espera unos momentos.</p>";
  response += "</body></html>";
  server.send(200, "text/html", response);

  // Guardar las credenciales del Access Point en la memoria flash
  preferences.begin("wifi", false);
  preferences.putString("ap_ssid", ap_ssid);
  preferences.putString("ap_password", ap_password);
  preferences.end();

  configurarAP();  // Llamar a la función que vuelve a configurar el AP
}

void handleToggleAP() {
  toggleAP();                          // Alternar el estado del AP
  server.sendHeader("Location", "/");  // Redirigir a la página principal
  server.send(303);                    // Enviar un código de redirección
}

void handleAlimentar() {
  servoOnAction = true;
  server.sendHeader("Location", "/");  // Redirigir a la página principal
  server.send(303);
}

void handleToggleAlexaSearch() {
  search = !search;  // Toggle the search state
  if (search) {
    Serial.println("Buscando dispositivos Alexa...");
    // Add any additional code needed to initiate the search process
  } else {
    Serial.println("Búsqueda desactivada.");
    // Add any code needed to stop the search process if applicable
  }

  // Send response to the client
  String response = "<html><body>";
  response += "<h1>Estado de búsqueda Alexa: " + String(search ? "Buscando" : "Desactivado") + "</h1>";
  response += "<a href='/'>Volver</a>";  // Link to return to the main page
  response += "</body></html>";

  server.sendHeader("Location", "/");  // Redirigir a la página principal
  server.send(303);
}

void handleRoot() {
  // Recuperar configuraciones existentes
  preferences.begin("wifi", false);
  String savedSSID = preferences.getString("ssid", "No configurado");
  String savedPassword = preferences.getString("password", "No configurado");
  String savedAPSSID = preferences.getString("ap_ssid", "Dispensador");
  String savedAPPassword = preferences.getString("ap_password", "No configurado");
  preferences.end();

  // Recuperar la duración del dispensador
  preferences.begin("settings", false);
  DISPENSE_DURATION = preferences.getInt("duration", 2000);  // Valor predeterminado
  preferences.end();

  // Verificar el estado de conexión a Internet
  String internetStatus = (WiFi.status() == WL_CONNECTED) ? "Conectado" : "Desconectado";
  String connectedSSID = WiFi.SSID();        // Red a la que está conectado
  String connectedPassword = savedPassword;  // Contraseña de la red conectada (si está almacenada)
  IPAddress ip = WiFi.localIP();
  String ipString = ip.toString();  // Convertir a string para mostrar
  String apStatus = estadoAP ? "Encendido" : "Apagado";
  String alexaSearch = (search) ? "Buscando" : "Búsqueda desactivada";

  String html = R"rawliteral(
  <!DOCTYPE html>
<html lang="en">

<meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Configurar WiFi</title>
    <style>
        body {
            display: flex;
            justify-content: center;
            align-items: center;
            margin-top: 10vw;
            font-family: Arial, sans-serif;
        }

        .container {
            text-align: center;
            border: 1px solid #ccc;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
        }

        select,
        input {
            width: 100%;
            padding: 10px;
            margin: 10px 0;
            border-radius: 5px;
            border: 1px solid #ccc;
        }

        input[type="submit"],
        .buttonConfig {
            background-color: #22a378;
            color: white;
            border: none;
            cursor: pointer;
            border-radius: 10px;
            transition: background-color 0.3s ease, box-shadow 0.3s ease, transform 0.2s ease;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
        }

        input[type="submit"]:hover,
        .buttonConfig:hover {
            background-color: #1e8d6b;
            box-shadow: 0 8px 12px rgba(0, 0, 0, 0.2), 0 4px 6px rgba(0, 0, 0, 0.1);
            transform: translateY(-2px);
        }

        input[type="submit"]:active,
        .buttonConfig:active {
            background-color: #1e8d6b;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.15);
            transform: translateY(0);
        }

        .hidden {
            display: none;
        }

        .buttonConfig {
            width: 100%;
            height: 8vw;
            font-size: 1.8vw;
            font-weight: bold;
        }
        .form-control {
            width: 80%;
        }
        .network {
            display: flex;
            gap: 12px;
        }
    </style>


</head>

<body>
    <div class="container">
        <h1>Estado de conexión:</h1> 
        <span>)rawliteral"
                + internetStatus + R"rawliteral(</span>
      <h2>IP: )rawliteral"
                + ipString + R"rawliteral(:8080</h2> 
        <h2>Alimentar Peces</h2>
        <form action="/alimentar" method="POST">
        <input type="submit" value="Activar Alimentación">
        </form>
        <h2>Configurar Tiempo del Dispensador</h2>
        <form action="/setDispenseDuration" method="POST" class="mb-3">
            <label for="duration">Tiempo en milisegundos:</label>
            <input type="text" id="duration" name="duration" class="form-control" value=")rawliteral"
                + String(DISPENSE_DURATION) + R"rawliteral("><br>
            <input type="submit" value="Actualizar Tiempo" class="btn btn-success">
        </form>

        <h2>Modo de búsqueda de Alexa</h2>
        <form action="/toggleAlexaSearch" method="POST">
        <input type="submit" value=")rawliteral"
                + alexaSearch + R"rawliteral(" class="btn btn-success">
        </form>
        <h2>Estado del Access Point: )rawliteral"
                + apStatus + R"rawliteral(</h2>
        <form action="/toggleAP" method="POST">
            <input type="submit" value=")rawliteral"
                + (estadoAP ? "Apagar AP" : "Encender AP") + R"rawliteral(" class="btn btn-primary">
        </form>

        <div class="network">
            <button class="buttonConfig" id="buttonApConfig">Config Access Point</button>
            <button class="buttonConfig" id="buttonWifiConfig">Config WIFI</button>
        </div>

        <div class="accessPoint hidden">
            <h1>Config Access Point</h1>
            <form action="/configAP" method="POST">
                <label for="ap_ssid">Access Point Name:</label>
                <input type="text" name="ap_ssid" value=")rawliteral"
                + savedAPSSID + R"rawliteral("><br>
                <label for="ap_password">Password AP:</label>
                <input type="text" name="ap_password" value=")rawliteral"
                + savedAPPassword + R"rawliteral("><br>
                <input type="submit" value="saveAP">
            </form>
        </div>
        <div class="wifi hidden">
            <h1>Configurar WIFI</h1>
            <form action="/connect" method="POST">
                <label for="ssid">SSID:</label>
                <select id="ssid" name="ssid"></select><br>
                <label for="password">Password:</label>
                <input type="text" name="password" value=""><br>
                <input type="submit" value="Connect">
            </form>
            <h2>Red Guardada:</h2> 
            <span>)rawliteral"
                + connectedSSID + R"rawliteral( </span>
        <h2>Contraseña de red:</h2> <span>)rawliteral"
                + connectedPassword + R"rawliteral(</span>
        </div>
    </div>
    <script>
        document.getElementById("buttonApConfig").addEventListener("click", function () {
            document.querySelector(".accessPoint").classList.toggle("hidden");
            document.querySelector(".wifi").classList.add("hidden");
        });
        document.getElementById("buttonWifiConfig").addEventListener("click", function () {
            document.querySelector(".wifi").classList.toggle("hidden");
            document.querySelector(".accessPoint").classList.add("hidden");
        });

        function updateNetworks(networks) {
            const select = document.getElementById('ssid');
            select.innerHTML = '';
            networks.forEach(network => {
                const option = document.createElement('option');
                option.value = network;
                option.text = network;
                select.add(option);
            });
        }

        function fetchNetworks() {
            fetch('/scan')
                .then(response => response.json())
                .then(data => updateNetworks(data))
                .catch(error => console.error('Error:', error));
        }

        document.querySelector('form[action="/configAP"]').addEventListener('submit', function(e) {
            const password = document.querySelector('input[name="ap_password"]').value;

            if (password.length > 0 && password.length < 8) {
                e.preventDefault();  // Evita que el formulario se envíe
                alert('El password debe tener al menos 8 caracteres o estar vacío.');
            }
        });

        document.addEventListener('DOMContentLoaded', fetchNetworks);

        document.getElementById('duration').addEventListener('input', function (e) {
            // Elimina cualquier carácter no numérico
            this.value = this.value.replace(/[^0-9]/g, '');
            
            // Asegúrate de que el valor no sea menor que 0
            if (this.value !== '' && parseInt(this.value) < 0) {
                this.value = '0';
            }
        });
    </script>
</body>

</html>
  )rawliteral";

  server.send(200, "text/html", html);
}