# CLAUDE.md — arduinoItems

> El **almacén** de Arduino: librerías de terceros, herramientas descargadas y proyectos de
> referencia. **No es código propio** — para eso está el repo hermano `arduinoPersonal`.
> Se lee y se copia adaptando; no se mantiene.

**Resumen en el vault:** `Projects/arduinoItems.md` en
`E:/OnWork/Obsidian Voult/Software Engineer enterprise-voult-obsidian`.

---

## 🚨 Este repo es el ejemplo de por qué existe `.cbmignore`

Indexado en crudo daba **8.628 nodos, casi todos de Adafruit**: `search_graph` empezaba a devolver
código de terceros como si fuera de la casa. Con el `.cbmignore` puesto quedó en **981**, y esos sí
son propios.

| Excluido | Qué es |
|---|---|
| `librerias/`, `proyectos/libraries/`, `*/libraries/` | Adafruit, GFX, BusIO… |
| `otros proyectos/` | Proyectos bajados (ArduinoHttpClient y compañía) |
| `CoolTermWin64Bit/` | Terminal serie descargada, 58 MB |
| `hackwifi/`, `hack wifi ESP8266/` | Material de referencia |

**No quites esas líneas.** Si algún día el grafo devuelve código que no reconocés, mirá primero qué
se está indexando.

## 🗂️ Lo que sí es propio

`esp32-dispensador-pecera/` (dispensador para peces con web), `weather/`,
`proyectoFinalCodigo esp8266/`, `WakeOnLan-ESP8266/`, `server/`, `microbit/`, `ESP32/`, `ESP8266/`.

## ⚠️ Trampas

- **Los `arduino_secrets.h` que aparecen versionados son de los ejemplos de la librería** y traen
  las cadenas vacías (`#define SECRET_SSID ""`). Auditados el 2026-09-08: no hay secretos reales.
  No los confundas con un descuido.
- El repo pesa **~250 MB** en disco. No lo clones "por si acaso".

## 📌 Estado

**Referencia.** Último commit: 2026-02-24. Se consulta, no se desarrolla.
