#include <WiFi.h>
#include "DHTesp.h"

// Red virtual de Wokwi que evita bloqueos de firewall en redes escolares[cite: 1]
const char* WIFI_SSID = "Wokwi-GUEST"; 
const char* WIFI_PASSWORD = "";

// Definición de pines[cite: 1]
const int DHT_PIN = 15;
const int LED_PIN = 2;

DHTesp dhtSensor;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  
  // Inicialización del sensor[cite: 1]
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  
  // Conexión WiFi Simulada[cite: 1]
  Serial.print("Conectando a la red WiFi local");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n¡Conexión Exitosa con la Nube!");
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
    
    // Lógica del Actuador (El Cerebro decide)[cite: 1]
    if (data.temperature > 30.0) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("[ALERTA] Temperatura Crítica. Actuador ENCENDIDO.");
    } else {
      digitalWrite(LED_PIN, LOW);
      Serial.println("[INFO] Temperatura Normal. Actuador APAGADO.");
    }
  }
  
  Serial.println("Enviando telemetría al servidor central...");
  delay(2000); // Muestreo cada 2 segundos para dinamismo en vivo[cite: 1]
}
