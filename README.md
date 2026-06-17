# 🚀 Introducción al Internet de las Cosas (IoT) con ESP32

¡Bienvenido! Este repositorio contiene todo lo necesario para ejecutar tu primera simulación de Internet de las Cosas (IoT) utilizando un microcontrolador ESP32. Este proyecto está diseñado para que cualquier estudiante pueda experimentar con el desarrollo de hardware desde su navegador, sin necesidad de comprar componentes físicos.

## 🧠 Arquitectura del Proyecto

Este prototipo demuestra los tres pilares fundamentales de un sistema IoT:
1. **Cerebro (Microcontrolador):** Utilizamos el **ESP32**, un chip potente con conectividad Wi-Fi integrada.
2. **Sentidos (Sensores):** Implementamos un **DHT22** para medir la temperatura y humedad del entorno en tiempo real.
3. **Músculos (Actuadores):** Un **LED Rojo** que simula una alarma visual, activándose cuando la temperatura supera un límite seguro.

## 🔌 Esquemático de Conexiones

Si deseas replicar este circuito, aquí tienes la tabla de enrutamiento:

| Componente | Pin del Componente | Pin del ESP32 | Función |
| :--- | :--- | :--- | :--- |
| **DHT22** | VCC | 3V3 | Alimentación |
| **DHT22** | SDA (Data) | GPIO 15 | Línea de datos |
| **DHT22** | GND | GND | Tierra |
| **LED Rojo** | Ánodo (+) | GPIO 2 | Señal de control |
| **Resistencia** | Terminal 1 | Cátodo LED (-) | Límite de corriente (220Ω) |
| **Resistencia** | Terminal 2 | GND | Cierre a Tierra |

## 🚀 ¿Cómo ejecutar la simulación?

1. Abre la plataforma de simulación gratuita: [Wokwi](https://wokwi.com/).
2. Inicia un nuevo proyecto en blanco para **ESP32**.
3. Copia el contenido del archivo `sketch.ino` de este repositorio y pégalo en el editor de código.
4. Agrega los componentes (DHT22, LED y Resistencia) siguiendo la tabla de conexiones.
5. Presiona el botón **"Play"** (▶️) para iniciar la simulación.
6. **¡Interactúa!** Haz clic sobre el sensor DHT22 durante la simulación y desliza la temperatura por encima de los 30°C. Observa cómo el sistema toma decisiones por sí solo.

---

## 👨‍🏫 Autoría y Contacto

**Mtro. Saul Isai Soto Ortiz** *Profesor Titular A | Ingeniería en Tecnologías de la Información y Comunicaciones* **Instituto Tecnológico Superior del Occidente del Estado de Hidalgo (ITSOEH)**

*La programación y la electrónica nos permiten automatizar el mundo.*
