# Roadmap — arduinoItems

Fuentes: `CLAUDE.md` (estado: referencia, «se consulta, no se desarrolla»), hallazgos de `docs/BORDES.md`, comentarios del código. No hay `TODO`/`FIXME` explícitos (solo notas como «no lo he logrado» en `PF/proyectoFinalCodigo.ino:19`, lectura de imágenes desde SD). Sin tareas abiertas en Forja asociadas (sin verificar). El repo es de referencia: lo que sigue es lo que valdría la pena si algún proyecto se retoma, y el código mantenido vive en `arduinoPersonal`.

## Prioridad alta (seguridad, si se vuelve a usar el hardware)
1. Autenticación en el panel del dispensador y en `/update`; no mostrar claves en la página (B-01, B-03).
2. Lista de chats autorizados y validación del índice en el bot WakeOnLan; verificar el certificado de Telegram (B-09, B-10, B-11).
3. AP del dispensador con clave por defecto aleatoria y validación de longitud en el servidor (B-07).
4. OTA firmada o con hash y solo por HTTPS (B-04).
5. Sacar los valores de WiFi y de API del código a un archivo no versionado (patrón `config.h` + `.gitignore`) (B-02).

## Prioridad media
6. Servo sin `delay` (máquina de estados) y tope para `duration` (B-06).
7. Tiempo máximo en la espera de WiFi y reintentos con espera creciente (B-13, B-23).
8. Responder siempre en las rutas del servidor LED (B-14).
9. Menús sin recursión (bucle principal con estado) y opción fantasma (B-15, B-16).
10. Escapar HTML/JSON del panel (B-08c).

## Prioridad baja
11. Retirar o mover a un repo aparte el material de terceros (`otros proyectos/`, `CoolTermWin64Bit/`, `hackwifi/`) y los zips duplicados (B-24, B-27, B-28).
12. Ajustar zona horaria, país y fórmula de Kelvin del clima (B-21).
13. Corregir o descartar el intento de Bluetooth del micro:bit (B-29).
14. Pruebas de compilación en CI (PlatformIO o `arduino-cli`) para los proyectos propios (B-32).
15. Pendiente de la nota del proyecto: la lectura de imágenes desde SD en el proyecto final.
