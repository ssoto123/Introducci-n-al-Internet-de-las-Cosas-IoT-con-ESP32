#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// ------------ WIFI ------------
const char* WIFI_SSID = "";
const char* WIFI_PASSWORD = "";

// ------------ PINES ------------
#define DHT_PIN 4
#define DHT_TYPE DHT22

const int LED_PIN = 16;

// ------------ SENSOR ------------
DHT dhtSensor(DHT_PIN, DHT_TYPE);

// ------------ TEMPORIZADOR ------------
unsigned long ultimoEnvio = 0;
const unsigned long intervaloLectura = 2000; // 2 segundos

void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  // Inicializar DHT22
  dhtSensor.begin();

  delay(2000);

  // Conexión WiFi
  Serial.print("Conectando a la red WiFi local");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  WiFi.setSleep(false);

  Serial.println("\n¡Conexión Exitosa!");
  Serial.print("IP Asignada: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  // Ejecutar cada 2 segundos sin bloquear el ESP32
  if (millis() - ultimoEnvio >= intervaloLectura) {

    ultimoEnvio = millis();

    float temperatura = dhtSensor.readTemperature();
    float humedad = dhtSensor.readHumidity();

    // Verificar lectura válida
    if (isnan(temperatura) || isnan(humedad)) {
      Serial.println("Error al leer el sensor DHT22");
      return;
    }

    Serial.print("Temperatura: ");
    Serial.print(temperatura, 1);
    Serial.print("°C | Humedad: ");
    Serial.print(humedad, 1);
    Serial.println("%");

    // Lógica del actuador
    if (temperatura >= 25.0) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("[ALERTA] Temperatura Crítica. Actuador ENCENDIDO.");
    } else {
      digitalWrite(LED_PIN, LOW);
      Serial.println("[INFO] Temperatura Normal. Actuador APAGADO.");
    }

    // -------- ENVÍO A DWEET --------
    if (WiFi.status() == WL_CONNECTED) {

      HTTPClient http;

      String serverPath =
        "http://dweet.cc/dweet/for/demo-iot-itsoeh?temperatura=" +
        String(temperatura, 1) +
        "&humedad=" +
        String(humedad, 1);

      Serial.println();
      Serial.println("URL:");
      Serial.println(serverPath);

      http.setTimeout(5000);
      http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

      if (http.begin(serverPath)) {

        int httpResponseCode = http.GET();

        Serial.print("HTTP: ");
        Serial.println(httpResponseCode);

        if (httpResponseCode > 0) {

          String payload = http.getString();

          Serial.println("Respuesta del servidor:");
          Serial.println(payload);

        } else {

          Serial.print("Error HTTP: ");
          Serial.println(http.errorToString(httpResponseCode));
        }

        http.end();

      } else {

        Serial.println("No se pudo iniciar la conexión HTTP");
      }

    } else {

      Serial.println("Error: WiFi desconectado");
    }
  }

  // Aquí pueden ejecutarse otras tareas sin bloquearse
}
