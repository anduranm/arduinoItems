#include <Arduino.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <AsyncTCP.h>
#include "fauxmoESP.h"
#include <HTTPClient.h>
#include <Update.h>

// Crear instancia de Preferences para almacenar credenciales
Preferences preferences;
/************************/
#define CURRENT_VERSION "0.1.0r"  // Versión actual del ESP32  
const char* firmwareUrl = "https://raw.githubusercontent.com/Pryxe/firmware-dispensador/refs/heads/now/dispensor.ino.merged.bin";
const char* versionUrl = "https://raw.githubusercontent.com/Pryxe/firmware-dispensador/refs/heads/now/version.txt";
// Nombre del punto de acceso por defecto y contraseña
const char *default_ap_ssid = "Dispensador";
const char *default_ap_password = ""; // Cambiar por la contraseña deseada

// IPAddress local_IP(192, 168, 0, 1);   // Cambia a una IP libre en tu red
// IPAddress gateway(192, 168, 0, 1);      // IP de la puerta de enlace
// IPAddress subnet(255, 255, 255, 0);     // Máscara de subred
// Crear instancia del servidor web
WebServer server(8080);

// Variables para almacenar el SSID y la contraseña seleccionados
String ssid = "";
String password = "";
String ap_ssid = "";
String ap_password = "";


// Pines del dispensador
#define SERVO_PIN 15         // Pin al que está conectado el servo motor
#define SERVO_ANGLE_OPEN 0 // Ángulo de apertura (para liberar comida)
#define SERVO_ANGLE_CLOSE 160  // Ángulo de cerrado

int DISPENSE_DURATION;  
Servo myServo; 
bool servoOnAction = false;
bool estadoAP = false;
bool search = false;

fauxmoESP fauxmo;

