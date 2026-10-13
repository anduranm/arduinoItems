# Especificación de Requisitos de Software (ERS) — arduinoItems

Formato basado en IEEE 830 / ISO/IEC/IEEE 29148. Repositorio remoto: `anduranm/arduinoItems`. Índice codebase-memory: `E-OnWork-PeakCore Solutions-laboratorio-arduinoItems`.
Fuente de verdad: el código. Lo que no se pudo comprobar en un equipo físico se marca «sin verificar». Los sketches son firmware: no hay forma de ejecutarlos sin la placa, por lo que ningún requisito se probó en hardware en esta revisión.

## 1. Introducción

### 1.1 Propósito
Describir de forma verificable qué contiene el repositorio `arduinoItems`: el almacén de proyectos de firmware (ESP32, ESP8266, Arduino, micro:bit) de Andrés Durán, más librerías y herramientas de terceros que se conservan para consulta.

### 1.2 Alcance
- **Propio (≈ 60 archivos versionados)**: 7 proyectos de firmware descritos en esta ERS (ver 2.2).
- **De terceros (≈ 3.460 archivos, el 98 % del repo)**: `librerias/` (269), `otros proyectos/` (1.931), `proyectos/libraries/` (844), `CoolTermWin64Bit/` (181), `hackwifi/` (226) y `hack wifi ESP8266/` (9). Se conservan como referencia, **no se mantienen y no se documentan requisito por requisito**; `.cbmignore` los excluye del grafo.
- Fuera de alcance: carcasas, esquemas eléctricos más allá de las imágenes incluidas, servidores externos (bot de Telegram, Alexa, OpenWeatherMap) y el repo hermano `arduinoPersonal` (código propio mantenido).

### 1.3 Definiciones
| Término | Significado |
|---|---|
| Sketch | Programa de Arduino (`.ino`); una carpeta con varios `.ino` se compila como uno. |
| NVS / Preferences | Memoria no volátil del ESP32 (`Preferences`). |
| AP | Punto de acceso WiFi creado por la propia placa. |
| fauxmo | Librería que hace que la placa se anuncie como dispositivo WeMo para Alexa. |
| WOL | Wake-on-LAN: paquete mágico UDP que enciende un equipo por su MAC. |
| OTA | Actualización de firmware por red. |
| ST7735 | Pantalla TFT de 128x160 usada en varios prototipos. |

### 1.4 Referencias
`CLAUDE.md`, `.cbmignore`, nota del vault sobre arduinoItems (sin verificar ubicación), repo hermano `arduinoPersonal`.

## 2. Descripción general

### 2.1 Perspectiva
No es una aplicación: es una colección de sketches independientes que se abren con el IDE de Arduino (o PlatformIO). Cada carpeta es un proyecto; no comparten código propio entre sí. Detalle en `docs/ARQUITECTURA.md`.

### 2.2 Proyectos propios
| Proyecto | Placa | Qué hace |
|---|---|---|
| `esp32-dispensador-pecera/dispensor` | ESP32 | Dispensador de comida con servo, panel web, Alexa (fauxmo) y OTA. |
| `WakeOnLan-ESP8266` | ESP8266 | Bot de Telegram que enciende equipos por WOL y simula el botón de encendido de un PC. |
| `proyectoFinalCodigo esp8266` | ESP8266 | Consola de menús en pantalla TFT con potenciómetro y botón. |
| `weather` | ESP8266 | Estación meteorológica (OpenWeatherMap + NTP), con y sin pantalla; es una copia de un proyecto abierto. |
| `server` | ESP8266 | Servidor web que dibuja dos patrones en una matriz de LEDs. |
| `proyectos/` (20 sketches) | Uno, Mega, ESP8266 | Pruebas: matriz LED, pantalla, menús, Pong. |
| `ESP32/`, `microbit/` | ESP32, micro:bit | Pruebas mínimas (LED parpadeante, plantilla vacía, intento de Bluetooth). |

### 2.3 Usuarios
Un único rol: la persona que programa y usa las placas. Los proyectos con red tienen además «usuarios del panel» (dispensador), «chats de Telegram» (WakeOnLan) y «dispositivos Alexa»; ninguno tiene autenticación propia (ver `docs/BORDES.md`).

### 2.4 Restricciones
Arduino IDE con paquetes de placa ESP32 y ESP8266; librerías de `librerias/` (versiones antiguas, p. ej. ArduinoJson 5.x exigido por el comentario de `WakeOnLan-ESP8266.ino:13-15`); credenciales escritas en el código o en `config.h`.

### 2.5 Supuestos
La red WiFi es de confianza; Telegram, OpenWeatherMap y los servidores de firmware están disponibles.

## 3. Requisitos funcionales

Rutas relativas a la raíz del repo. `DISP` = `esp32-dispensador-pecera/dispensor`, `WOL` = `WakeOnLan-ESP8266`, `PF` = `proyectoFinalCodigo esp8266/proyectoFinalCodigo`, `CLIMA` = `weather/ESP8266-Weather-Station-V2-main`.

### Dispensador de pecera
| ID | Requisito | Criterio de aceptación | Módulo |
|---|---|---|---|
| RF-01 | Guardar y leer en NVS el WiFi, el AP y la duración del servo. | Tras reiniciar, la placa reutiliza los valores; duración por defecto 2000 ms. | `DISP/init.ino:1-11` |
| RF-02 | Conectarse al WiFi guardado al arrancar. | Hasta 20 intentos de 500 ms; si falla, sigue operando con su AP. | `DISP/init.ino:14-31` |
| RF-03 | Mantener un AP propio. | El AP se crea siempre al arrancar con el nombre guardado o el por defecto. | `DISP/init.ino:50-63` |
| RF-04 | Servir un panel web en el puerto 8080 con 9 rutas. | `/`, `/scan`, `/connect`, `/configAP`, `/setDispenseDuration`, `/toggleAlexaSearch`, `/toggleAP`, `/alimentar`, `/update`. | `DISP/init.ino:37-47` |
| RF-05 | Dispensar comida manualmente. | `POST /alimentar` abre el servo (pin 15) 0°, espera la duración y cierra a 160°. | `DISP/website.ino:85-89`, `DISP/dispensor.ino:17-28` |
| RF-06 | Dispensar por Alexa. | El dispositivo «Dispensador» al encenderse activa el mismo movimiento. | `DISP/init.ino:82-101` |
| RF-07 | Configurar la duración. | `POST /setDispenseDuration` guarda `duration` en NVS. | `DISP/website.ino:1-15` |
| RF-08 | Listar redes WiFi. | `GET /scan` devuelve un arreglo JSON de nombres. | `DISP/website.ino:17-26` |
| RF-09 | Cambiar de red WiFi. | `POST /connect` guarda ssid/clave y reintenta 20 veces. | `DISP/website.ino:28-55` |
| RF-10 | Cambiar nombre y clave del AP. | `POST /configAP` los guarda y reconfigura el AP. | `DISP/website.ino:57-77` |
| RF-11 | Encender/apagar el AP desde el panel. | `POST /toggleAP` alterna el AP. | `DISP/website.ino:79-83`, `DISP/init.ino:65-80` |
| RF-12 | Activar la búsqueda de Alexa. | `POST /toggleAlexaSearch` alterna `search`. | `DISP/website.ino:91-101` |
| RF-13 | Actualizar el firmware por red. | `GET /update` compara versiones y, si difieren, descarga y reinicia. | `DISP/website.ino:103-175` |

### WakeOnLan por Telegram
| ID | Requisito | Criterio de aceptación | Módulo |
|---|---|---|---|
| RF-14 | Escuchar mensajes de Telegram. | Consulta `getUpdates` cada 1 s con long poll de 60 s. | `WOL/The_important.ino:80-93`, `WOL/SET.ino:32` |
| RF-15 | Responder `/start` con las opciones. | Mensaje con `/wol` y `/setPC`. | `WOL/The_important.ino:64-66` |
| RF-16 | `/wol` ofrece un teclado con los dispositivos. | Un botón por entrada de `devices[]` (2 en el código). | `WOL/The_important.ino:50-61` |
| RF-17 | Enviar el paquete mágico. | Al pulsar un botón se hace broadcast UDP con la MAC elegida. | `WOL/The_important.ino:32-38` |
| RF-18 | `/setPC` conmuta el encendido físico de un PC. | «Switch» alterna el pin D1 a OUTPUT durante una vuelta del loop (~75 ms). | `WOL/The_important.ino:4-18,40-47,69-75` |

### Consola de menús (proyecto final)
| ID | Requisito | Criterio de aceptación | Módulo |
|---|---|---|---|
| RF-19 | Menú principal por potenciómetro y botón. | A0 mapea la opción resaltada; el botón la ejecuta con un beep. | `PF/Menu.ino:3-65`, `PF/proyectoFinalCodigo.ino:76-98` |
| RF-20 | Submenú de letras y demostración geométrica. | «Letras» y «Demostracion» abren sus pantallas; «volver» regresa. | `PF/Menu2.ino`, `PF/Letras.ino`, `PF/geometria.ino` |
| RF-21 | Galería de números (73 opciones). | El potenciómetro recorre las opciones. | `PF/Numeros.ino` |
| RF-22 | Cinco niveles de brillo. | PWM 25, 64, 127, 191 o 225 en la luz de fondo. | `PF/brillo.ino:25-52` |
| RF-23 | Encender/apagar un AP. | La opción Wifi alterna el AP «Proyecto ITI». | `PF/Wifi.ino:1-12` |

### Otros
| ID | Requisito | Criterio de aceptación | Módulo |
|---|---|---|---|
| RF-24 | Consultar el clima cada 10 s. | Imprime temperatura (°C), presión, humedad, viento y hora NTP. | `CLIMA/esp8266_weather_forcast_v2/esp8266_weather_forcast_v2.ino:44-92` |
| RF-25 | Mostrar el clima en pantalla TFT. | Variante con iconos en la ST7735. | `CLIMA/esp8266_weather_forcast_with_display_v2.ino:192-350` |
| RF-26 | Servir patrones en matriz de LEDs por web. | `/pattern1` y `/pattern2` ponen los pines en el patrón. | `server/server.ino:48-109` |
| RF-27 | Juego Pong en matriz 8x8. | Dos raquetas por potenciómetros A6/A7 y pelota con rebotes. | `proyectos/LED_Matrix_Pong_game_Arduino/LED_Matrix_Pong_game_Arduino.ino` (copia con autoría de terceros en la cabecera) |
| RF-28 | Ingresar nombre y apellido con pulsador y Serial. | Muestra los datos en la TFT y vuelve con el pulsador. | `proyectos/pulsador con pantallla/sketch_apr05e/sketch_apr05e.ino:83-128` |
| RF-29 | Pruebas de matriz LED, pantalla ST7735 y menús. | Sketches de prueba sin interfaz de red. | `proyectos/*` (resto) |

## 4. Requisitos no funcionales

| ID | Categoría | Requisito | Estado |
|---|---|---|---|
| RNF-01 | Seguridad | El panel y los comandos requieren autenticación. | **No cumple**: ninguna ruta del dispensador, el servidor LED ni el bot comprueba identidad (B-01, B-05, B-09). |
| RNF-02 | Seguridad | Sin secretos reales en el repositorio. | **No cumple**: hay valores aparentes de WiFi y una clave de API en el código (B-02). |
| RNF-03 | Seguridad | Actualización de firmware firmada. | **No cumple** (B-04). |
| RNF-04 | Seguridad | TLS verificado hacia Telegram. | **No cumple**: `setInsecure()` (B-10). |
| RNF-05 | Fiabilidad | Un fallo de red no bloquea la placa. | Parcial: dispensador sí; WiFi de `server` y `weather` espera para siempre (B-13). |
| RNF-06 | Rendimiento | La respuesta del panel no debe bloquearse. | **No cumple**: el servo bloquea el loop hasta `DISPENSE_DURATION` + 3 s (B-06). |
| RNF-07 | Privacidad | La clave WiFi no se muestra en pantalla. | **No cumple**: el panel imprime la clave guardada (B-03). |
| RNF-08 | Portabilidad | Compila con paquetes de placa actuales. | Sin verificar (comentarios piden versiones antiguas). |
| RNF-09 | Responsive | El panel web se ve en celular. | Parcial: `viewport` presente, tamaños con `vw` (sin verificar visualmente). |
| RNF-10 | Mantenibilidad | El grafo no se llena de código ajeno. | Cumple por `.cbmignore` (≈ 980 nodos propios). |

## 5. Interfaces externas
- **Telegram Bot API** (HTTPS, token del bot): WakeOnLan.
- **OpenWeatherMap** (HTTP, clave en la URL): `weather`.
- **NTP** `pool.ntp.org`: `weather`.
- **Alexa** (descubrimiento WeMo/fauxmo): dispensador.
- **Servidor de firmware** (URL en `config.h`): OTA del dispensador.
- **Hardware**: servo (pin 15), pantallas ST7735, matrices LED 8x8, potenciómetros, botones, parlante.

## 6. Modelo de datos
Solo el dispensador persiste datos (NVS/Preferences):
| Espacio | Claves |
|---|---|
| `wifi` | `ssid`, `password`, `ap_ssid`, `ap_password` |
| `settings` | `duration` (ms) |
El resto de sketches no guarda estado.

## 7. Trazabilidad RF → módulo → prueba
No hay pruebas automatizadas ni CI. **Ningún RF (RF-01…RF-29) tiene prueba.** La verificación es manual sobre la placa.

| RF | Módulo | Prueba |
|---|---|---|
| RF-01 a 13 | `DISP/` | Sin prueba |
| RF-14 a 18 | `WOL/` | Sin prueba |
| RF-19 a 23 | `PF/` | Sin prueba |
| RF-24, 25 | `CLIMA/` | Sin prueba |
| RF-26 a 29 | `server/`, `proyectos/` | Sin prueba |
