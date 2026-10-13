# arduinoItems

Almacén de proyectos de firmware (ESP32, ESP8266, Arduino, micro:bit), librerías y herramientas de terceros del laboratorio de PeakCore. **Es material de referencia**: se consulta y se copia adaptando; el código mantenido está en el repo hermano `arduinoPersonal`.

## Proyectos propios
| Carpeta | Qué es |
|---|---|
| `esp32-dispensador-pecera/dispensor` | Dispensador de comida para peces: servo, panel web (puerto 8080), Alexa y actualización por red |
| `WakeOnLan-ESP8266` | Bot de Telegram que enciende equipos por Wake-on-LAN |
| `proyectoFinalCodigo esp8266` | Consola de menús en pantalla TFT con potenciómetro y botón |
| `weather` | Estación meteorológica (copia de un proyecto abierto) |
| `server` | Servidor web para una matriz de LEDs |
| `proyectos/`, `ESP32/`, `microbit/` | Sketches de prueba |

El resto (≈ 98 % de los archivos) es de terceros: `librerias/`, `otros proyectos/`, `CoolTermWin64Bit/`, `hackwifi/`, `proyectos/libraries/`. El `.cbmignore` los excluye del grafo de código; no lo quites.

## Uso
Abrir la carpeta del proyecto con el Arduino IDE o PlatformIO, instalar el paquete de la placa y las librerías, y cargar. Antes de usar un sketch, revisa que no contenga credenciales propias de otra red.

## Avisos
- No dejes valores reales de WiFi, tokens ni claves de API en el código ni los subas al repositorio.
- Varios proyectos exponen servicios sin autenticación; no los publiques a Internet.
- Repo de ≈ 326 MB: no lo clones sin necesidad.

## Documentación (`docs/`)
| Archivo | Contenido |
|---|---|
| [`docs/ERS.md`](docs/ERS.md) | 29 requisitos funcionales por proyecto y trazabilidad |
| [`docs/ARQUITECTURA.md`](docs/ARQUITECTURA.md) | Mapa del repo, estructura de sketches y componentes |
| [`docs/FLUJOS.md`](docs/FLUJOS.md) | 9 flujos del firmware con diagramas en [`docs/flujos/`](docs/flujos/) |
| [`docs/BORDES.md`](docs/BORDES.md) | Casos límite y hallazgos de seguridad |
| [`docs/OPERACION.md`](docs/OPERACION.md) | Configuración, carga y runbook |
| [`docs/ROADMAP.md`](docs/ROADMAP.md) | Mejoras por prioridad |

Contexto para quien mantiene el repo: [`CLAUDE.md`](CLAUDE.md).
