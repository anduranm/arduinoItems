# Operación — arduinoItems

## 1. Variables y configuración
No hay variables de entorno: la configuración está en el código o en NVS.

| Nombre | Tipo | Dónde |
|---|---|---|
| `default_ap_ssid`, `default_ap_password` | SECRETO (la clave) / CONFIGURACIÓN (el nombre) | `DISP/config.h:18-19` |
| `firmwareUrl`, `versionUrl`, `CURRENT_VERSION` | CONFIGURACIÓN | `DISP/config.h:14-16` |
| `SERVO_PIN`, `SERVO_ANGLE_OPEN`, `SERVO_ANGLE_CLOSE` | CONFIGURACIÓN | `DISP/config.h:35-37` |
| `ssid`, `password` (WiFi) | SECRETO | `server/server.ino`, `PF/proyectoFinalCodigo.ino`, `CLIMA/*.ino`, `WOL/WakeOnLan-ESP8266.ino` |
| `TELEGRAM_BOT_TOKEN` | SECRETO | `WOL/WakeOnLan-ESP8266.ino:22` |
| `openWeatherMapApiKey`, `city`, `countryCode` | SECRETO (la clave) / CONFIGURACIÓN | `CLIMA/*.ino` |
| NVS `wifi` (`ssid`, `password`, `ap_ssid`, `ap_password`), NVS `settings` (`duration`) | SECRETO | dispensador, en la flash de la placa |

Los secretos no deben subirse con valores reales (ver `docs/BORDES.md` B-02). Rutas de `DISP/` = `esp32-dispensador-pecera/dispensor/`.

## 2. Compilar y cargar
1. Instalar Arduino IDE (o PlatformIO) y los paquetes de placa ESP32 y ESP8266.
2. Instalar las librerías necesarias (ver `docs/ARQUITECTURA.md` §7); las copias de referencia están en `librerias/`. WakeOnLan requiere ArduinoJson 5.x (`WOL/WakeOnLan-ESP8266.ino:13-15`).
3. Abrir la carpeta del proyecto (no un `.ino` suelto en los proyectos multi-archivo), elegir placa y puerto, y cargar.
4. Para el dispensador: editar `config.h` (AP, URL de OTA, pin del servo) antes de cargar.

No hay CI, instaladores ni versiones etiquetadas.

## 3. Operación del dispensador
| Acción | Cómo |
|---|---|
| Entrar al panel | Conectarse al AP de la placa o a la misma red y abrir `http://<ip>:8080` |
| Alimentar | Botón del panel o «Alexa, enciende Dispensador» |
| Cambiar la cantidad | Duración en ms en el panel (por defecto 2000) |
| Cambiar de red WiFi | Panel › Configurar WiFi |
| Actualizar firmware | `GET /update` (hay que subir primero el binario y la versión a las URL de `config.h`) |
| Restablecer | Borrar la flash del ESP32 (las credenciales viven en NVS); sin verificar el procedimiento exacto |

## 4. Respaldos
No hay datos de usuario salvo NVS en cada placa (no hay forma de respaldarlo desde el repo). El código se respalda con git. Los esquemas incluidos son imágenes (`weather/…/schmatics*.jpg`, `proyectos/LED_Matrix_Pong_game_Arduino/Circuit Diagram…jpg`, `WakeOnLan-ESP8266/important.png`).

## 5. Monitoreo
Solo Serial (115200 para el dispensador, el clima y WakeOnLan; 9600 para el proyecto final y Pong). No hay registro remoto ni alarmas.

## 6. Runbook
| Síntoma | Causa probable | Acción |
|---|---|---|
| El dispensador no conecta a la red | Credenciales equivocadas guardadas (B-08) | Entrar por su AP y volver a enviar la red |
| No aparece el AP | Clave de menos de 8 caracteres (B-07) | Fijar una de 8 o más o dejarla vacía |
| Alexa no lo encuentra | Búsqueda desactivada o fauxmo en otro puerto | Activar «búsqueda de Alexa» en el panel y repetir el descubrimiento |
| El panel «se congela» al alimentar | `delay` del servo (B-06) | Esperar; reducir la duración |
| El bot no responde | Sin WiFi, token incorrecto o Telegram caído | Revisar Serial (¿IP?, ¿«got response»?) |
| `/wol` no enciende | MAC de ejemplo (ceros) o equipo sin WOL en BIOS | Poner la MAC real (B-12) |
| El clima imprime `{}` o error | Sin Internet, clave inválida o ciudad mal escrita | Revisar la URL en Serial |
| `/pattern1` no responde en el navegador | Falta `server.send` (B-14) | El cambio sí se aplica a los pines; recargar `/` |
| Pantalla sin imagen | Pines TFT distintos al cableado | Comparar `#define TFT_*` con el montaje |

## 7. Seguridad operativa
No exponer el panel (8080) ni el puerto 80 a Internet. Cambiar la clave del AP antes de usar el dispensador en una red compartida. No dejar el bot de Telegram público.
