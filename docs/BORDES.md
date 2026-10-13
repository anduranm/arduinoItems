# Bordes y casos límite — arduinoItems

Hallazgos de seguridad marcados «⚠️ Seguridad». Lo anotado se leyó en el código; nada se probó en hardware, por lo que los efectos físicos dicen «sin verificar en placa». **Los valores de credenciales no se copian aquí.** Rutas: `DISP/` = `esp32-dispensador-pecera/dispensor/`, `WOL/` = `WakeOnLan-ESP8266/`, `PF/` = `proyectoFinalCodigo esp8266/proyectoFinalCodigo/`, `CLIMA/` = `weather/ESP8266-Weather-Station-V2-main/`.

## Seguridad y privacidad (dispensador)
- **B-01 ⚠️ Seguridad — Panel sin autenticación.** Las 9 rutas (`DISP/init.ino:37-45`) responden a cualquiera con acceso a la red o al AP, incluidas `/connect`, `/configAP`, `/alimentar` y `/update`. `GET /update` además se dispara con un simple enlace (cambio de estado por GET).
- **B-02 ⚠️ Seguridad — Credenciales versionadas.** Hay valores aparentes (no placeholders) de WiFi en `server/server.ino:5-6`, `PF/proyectoFinalCodigo.ino:20-21`, `CLIMA/…/esp8266_weather_forcast_v2.ino:8-9` y `CLIMA/…/esp8266_weather_forcast_with_display_v2.ino:20-21`; una clave de OpenWeatherMap de 32 caracteres en `…v2.ino:10` y `…with_display_v2.ino:22`; y una clave literal para el AP «Proyecto ITI» en `PF/Wifi.ino:8`. Que sean reales o de ejemplo, sin verificar. El token del bot en `WOL/WakeOnLan-ESP8266.ino:22` es un marcador. Los `arduino_secrets.h` de las librerías vienen vacíos (auditado el 2026-09-08 según `CLAUDE.md`).
- **B-03 ⚠️ Seguridad — El panel muestra claves.** La página incluye la clave del AP en un campo de texto (`DISP/website.ino:434`) y la clave de la red WiFi guardada en pantalla (`:451`).
- **B-04 ⚠️ Seguridad — OTA sin verificación.** Descarga y flashea lo que sirva `firmwareUrl` (`DISP/website.ino:103-124`) sin firma ni hash; decide por simple desigualdad de versión (`:156`), por lo que también permite volver a una versión anterior. Las URL de `config.h:15-16` usan HTTPS (`raw.githubusercontent.com`), que cifra el transporte pero no autentica el binario.
- **B-05 ⚠️ Seguridad — Alexa/fauxmo sin autenticación.** Cualquier dispositivo que descubra el «Dispensador» en la red lo activa (`DISP/init.ino:82-101`); el puerto 80 es de fauxmo y el panel va en el 8080.
- **B-07 ⚠️ Seguridad — AP abierto por defecto.** `default_ap_password` está vacío en `DISP/config.h:19`; `WiFi.softAP(ssid, "")` crea una red sin clave (`DISP/init.ino:57`). Si el usuario fija una clave de menos de 8 caracteres, el ESP32 rechaza crear el AP y el panel solo lo valida en el navegador (`DISP/website.ino:482-488`).
- **B-08 Credenciales guardadas antes de comprobar.** `/connect` persiste ssid y clave antes de intentar la conexión (`DISP/website.ino:38-41`); un dato equivocado queda guardado y se reintenta en cada arranque (hasta 10 s de espera).
- **B-08b ⚠️ Seguridad — Claves en claro en NVS.** `Preferences` no cifra por sí solo; quien lea la flash obtiene la clave WiFi (sin verificar si el cifrado de flash está activo).
- **B-08c ⚠️ Seguridad — Salida HTML sin escapar.** El nombre del AP, la clave y el SSID se insertan en la página sin escapar (`DISP/website.ino:432-451`), y `/scan` arma JSON concatenando nombres de red sin escapar comillas (`:22`): un SSID con comillas o etiquetas rompe el JSON o inyecta HTML en el panel.

## Seguridad (bot y otros)
- **B-09 ⚠️ Seguridad — Bot sin lista de chats autorizados.** `chat_id` solo se usa para responder (`WOL/The_important.ino:24`); cualquier persona que encuentre el bot puede lanzar `/wol` y `/setPC`.
- **B-10 ⚠️ Seguridad — TLS sin verificar.** `client.setInsecure()` (`WOL/SET.ino:25`) acepta cualquier certificado hacia `api.telegram.org`.
- **B-11 ⚠️ Seguridad — Índice sin validar.** El texto del botón `WOL<n>` viene de Telegram; `toInt()` y `devices[index]` no comprueban el rango (`WOL/The_important.ino:34-37`): un `callback_data` manipulado lee fuera del arreglo (de 2 elementos).
- **B-12 Dispositivos de ejemplo.** Las MAC de `devices[]` son ceros (`WOL/WakeOnLan-ESP8266.ino:37-38`) y `numDevices` se mantiene a mano (`:42`); un desajuste con el tamaño del arreglo da lecturas fuera de rango.
- **B-12b Pulso del botón de encendido.** `sendSignalToTurnOnOrOff` se ejecuta en cada vuelta del loop con `delay(75)` (`WOL/The_important.ino:16,92`), frenando el sondeo; `switchingInProgress` se pone y se quita en la misma función (`:41-46`) y no protege nada. El nivel eléctrico real del pin D1 al pasar a OUTPUT, sin verificar en placa.
- **B-24 ⚠️ Seguridad — Material ofensivo de terceros.** `hackwifi/` y `hack wifi ESP8266/` contienen firmware de desautenticación WiFi, un portal cautivo de captura de claves y herramientas de flasheo de terceros (≈ 235 archivos). Son referencia, no código propio; usarlos contra redes ajenas es ilegal. No se documentan.

## Concurrencia y rendimiento
- **B-06 Servo bloqueante.** `handleServo` hace `delay(1000)` + `DISPENSE_DURATION` + `delay(1000)` (`DISP/dispensor.ino:17-27`); durante ese tiempo no se atiende web ni Alexa. `duration` se convierte con `toInt()` sin tope ni signo (`DISP/website.ino:3`): un valor enorme o negativo bloquea la placa o dispara el watchdog (sin verificar en placa).
- **B-13 Espera infinita de WiFi.** `server/server.ino:39-42` y `CLIMA/…v2.ino:29-32` esperan sin límite; con red caída la placa no avanza. El dispensador sí limita a 20 intentos.
- **B-14 Rutas sin respuesta.** `pattern1` y `pattern2` no llaman a `server.send` (`server/server.ino:88-109`); el cliente espera hasta agotar el tiempo.
- **B-14b Pines de arranque.** `server.ino` y varios sketches usan D3, D4 y D8 como salida; en ESP8266 son pines de arranque y pueden impedir el inicio o alterar el modo (sin verificar en placa).
- **B-15 Recursión de menús.** `menuPrincipal`, `menuSecundario` y `brillo` se llaman entre sí en lugar de retornar (`PF/Menu2.ino:30`, `PF/brillo.ino:30`); cada «volver» consume pila. Tras muchas navegaciones puede reiniciarse la placa (sin verificar en placa).
- **B-16 Opción fantasma.** `numOptionsMenuSecundario = 4` pero hay 3 etiquetas (`PF/proyectoFinalCodigo.ino:40,47`): al extremo del potenciómetro se selecciona una opción vacía sin acción.
- **B-17 Memoria.** `handleRoot` construye en el heap una página de ~350 líneas por petición (`DISP/website.ino:177-460`); con peticiones repetidas fragmenta la memoria (sin medir).
- **B-18 Doble respuesta.** `updatePage` envía la respuesta antes de comprobar la versión y luego intenta enviar otra (`DISP/website.ino:168,173`); la segunda se pierde.
- **B-19 Aceleración rota.** `_speed - 0;` no hace nada (`proyectos/LED_Matrix_Pong_game_Arduino/…ino:129`): el juego no acelera (código de terceros adaptado).
- **B-20 Entrada por Serial sin tiempo límite.** `ingresar_nombre_y_apellido` espera con `while(true)` (`proyectos/pulsador con pantallla/sketch_apr05e/sketch_apr05e.ino:83-128`).

## Datos, tiempo y red
- **B-21 Zona horaria y país fijos.** `CLIMA` usa `utcOffsetInSeconds = 19800` (UTC+5:30) y `countryCode = "IN"` del proyecto original (`…v2.ino:12,19`); sin cambio horario. La conversión resta 273, no 273,15 (`:59`).
- **B-22 HTTP en claro.** La consulta de clima va por HTTP con la clave en la URL (`…v2.ino:47`).
- **B-23 Sin red o terceros caídos.** Telegram, OpenWeatherMap, NTP y el servidor OTA caídos: el bot reintenta cada segundo, el clima imprime errores y sigue, la OTA devuelve «No hay actualizaciones». Ningún proyecto tiene reintentos con espera creciente.
- **B-25 Entradas fuera de tablero.** Arreglos de pines con valores inexistentes o repetidos (`proyectos/encender leds/sketch_apr01b/sketch_apr01b.ino:3-4` usa los pines 18, 19, 20 y 22 y recorre `fila2[i]` hasta 8 con un solo elemento; `proyectos/intento1000/1001/1001.ino:3` incluye 1 y 3, TX/RX). Son bocetos de prueba.
- **B-26 Datos vacíos.** `devices[]` con MAC cero no enciende nada; una lista vacía en `/scan` deja el selector vacío.

## Repositorio
- **B-27 98 % terceros.** ≈ 3.460 de 3.520 archivos son de terceros; el clon pesa ≈ 326 MB. Mantener `.cbmignore` (ver `CLAUDE.md`).
- **B-28 Archivos duplicados y binarios.** Zips versionados de librerías y proyectos (`Time-master.zip`, `SD-master.zip`, `ESP8266-Weather-Station-V2-main.zip`) y la terminal `CoolTermWin64Bit/` (181 archivos); sin verificar procedencia ni licencias.
- **B-29 `microbit/intento conectarse bluetooth.py`.** Usa un módulo `bluetooth` con una API (`on_data_received`, `connect`) que no corresponde al MicroPython oficial del micro:bit; es un intento, sin verificar.
- **B-30 Autoría de terceros.** `LED_Matrix_Pong_game_Arduino.ino:2-12` conserva la autoría original; `weather/` es copia de un proyecto abierto. Revisar licencias antes de reutilizar.
- **B-31 Migraciones.** Las claves de NVS no tienen versión; cambiar sus nombres obligaría a reconfigurar a mano.
- **B-32 Sin pruebas ni CI.**
