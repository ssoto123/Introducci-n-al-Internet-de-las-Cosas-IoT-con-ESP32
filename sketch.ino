#include <WiFi.h>
#include <HTTPClient.h> // Librería necesaria para enviar datos a la nube
#include "DHTesp.h"

// Red virtual de Wokwi
const char* WIFI_SSID = "Wokwi-GUEST"; 
const char* WIFI_PASSWORD = "";

// Definición de pines
const int DHT_PIN = 15;
const int LED_PIN = 2;

DHTesp dhtSensor;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  // Inicialización del sensor
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  
  // Conexión WiFi
  Serial.print("Conectando a la red WiFi local");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n¡Conexión Exitosa!");
  Serial.print("IP Asignada: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  
  if (dhtSensor.getStatus() != 0) {
    Serial.println("Error al leer el sensor DHT22");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(data.temperature, 1);
    Serial.print("°C | Humedad: ");
    Serial.print(data.humidity, 1);
    Serial.println("%");
    
    // Lógica del Actuador
    if (data.temperature > 30.0) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("[ALERTA] Temperatura Crítica. Actuador ENCENDIDO.");
    } else {
      digitalWrite(LED_PIN, LOW);
      Serial.println("[INFO] Temperatura Normal. Actuador APAGADO.");
    }

    // --- ENVÍO REAL A LA NUBE (HTTP GET) ---
    if(WiFi.status() == WL_CONNECTED){
      HTTPClient http;
      
      // Creamos la URL con los datos del sensor. Usamos un identificador único para el evento.
      String serverPath = "http://dweet.cc/dweet/for/demo-iot-itsoeh?temperatura=" + String(data.temperature, 1) + "&humedad=" + String(data.humidity, 1);
      
      http.begin(serverPath.c_str());
      int httpResponseCode = http.GET(); // Hacemos la petición
      
      if (httpResponseCode > 0) {
        Serial.print("Datos enviados a la nube exitosamente. Código HTTP: ");
        Serial.println(httpResponseCode);
      } else {
        Serial.print("Error al enviar a la nube. Código de error: ");
        Serial.println(httpResponseCode);
      }
      http.end(); // Liberamos recursos
    } else {
      Serial.println("Error: WiFi desconectado");
    }
  }
  
  delay(2000); // Esperamos 2 segundos antes de la siguiente lectura
}
