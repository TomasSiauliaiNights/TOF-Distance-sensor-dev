# TOF Distance Sensor
[![Platform: Arduino](https://img.shields.io/badge/Platform-Arduino-teal.svg)](https://www.arduino.cc/)

A compact, laser-based **Time-of-Flight (ToF) distance sensor** module with an Arduino-compatible library. Measures distance by timing an infrared laser pulse reflection — providing fast, accurate, millimeter-resolution readings regardless of target color or surface reflectance.

---

## Features

- **Time-of-Flight laser ranging** — distance measurement in millimeters
- **Three output modes** — Digital (default), PWM, and Serial (half-duplex UART)
- **Configurable via Serial** — switch to Serial mode to adjust sensor parameters
- **Wide compatibility** — works with Arduino Uno/Mega/Nano, ESP32, ESP8266, Raspberry Pi Pico, and other microcontrollers

---

## Specifications

| Parameter | Value |
|---|---|
| Measurement principle | Time-of-Flight (ToF) laser ranging |
| Output modes | Digital (default), PWM, Serial (half-duplex UART) |
| Output data | Distance in millimeters (mm) |
| Supply voltage | 3.3 V – 5 V (see your board's datasheet) |
| Connector | 0.6 mm pitch connector (https://www.aliexpress.com/item/1005007526912566.html)|

> **Full electrical specs and mechanical dimensions** are in [`TOF distance sensor.pdf`](TOF%20distance%20sensor.pdf). Sensor CAD drawings are in the [`drawings/`](drawings/) folder.

---

## Output Modes

The sensor supports three output modes. The default is **Digital**.

### Digital (default)
The signal pin goes HIGH or LOW based on whether an object is detected within the configured threshold distance. No additional configuration needed — just read the pin state.

### PWM
The sensor outputs a PWM signal on the signal pin. The pulse width or duty cycle corresponds to the measured distance. Read it with `pulseIn()` on Arduino.

### Serial (half-duplex UART)
In Serial mode, the sensor transmits distance and config data over a single-wire half-duplex UART connection. This mode also allows you to **configure sensor parameters** (thresholds, measurement rate, etc.) by sending commands back to the sensor over the same wire.

> To switch between modes, you first need to enter Serial mode and send the appropriate configuration commands. See the example sketch and datasheet for the command protocol.

---

## Wiring
 **Very important! The sensor signal needs a pull-up resistor. You can use software pull-up or if used with the example Serial example, you will need hardware 4-10k pull-up resistor**
 
### Digital Mode (default)

| Sensor Pin | Arduino Uno | Description |
|---|---|---|
| VCC | 3.3 V or 5 V | Power supply |
| GND | GND | Ground |
| SIGNAL | Any digital pin | HIGH/LOW distance threshold output |

### PWM Mode

| Sensor Pin | Arduino Uno | Description |
|---|---|---|
| VCC | 3.3 V or 5 V | Power supply |
| GND | GND | Ground |
| SIGNAL | Any digital pin | PWM output (use `pulseIn()` to read) |

### Serial Mode (half-duplex)

| Sensor Pin | Arduino Uno | Description |
|---|---|---|
| VCC | 3.3 V or 5 V | Power supply |
| GND | GND | Ground |
| SIGNAL | Software Serial RX/TX pin | Half-duplex UART (single wire for both TX and RX) |

> **Note:** Because Serial mode uses half-duplex (one wire for both sending and receiving), you need a software serial library that supports single-wire mode, or a hardware UART with the TX and RX pins tied together through a resistor. See the example sketch for implementation details.

See the [`drawings/`](drawings/) folder for detailed wiring diagrams.

---

## Getting Started

### 1. Upload the example

1. Go to **File → Examples → TOF-Distance-sensor → SensorExample**.
2. Select your board under **Tools → Board**.
3. Select the correct port under **Tools → Port**.
4. Click **Upload** (→ arrow button).
5. Open **Tools → Serial Monitor** (set the baud rate to match the example sketch).

You should see distance values streaming in the Serial Monitor. Place your hand or an object in front of the sensor and watch the values change.

### 2. Quick usage examples

**Digital mode (simplest):**
```cpp
const int sensorPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
}

void loop() {
  int state = digitalRead(sensorPin);
  if (state == HIGH) {
    Serial.println("Object detected within threshold");
  } else {
    Serial.println("No object detected");
  }
  delay(100);
}
```

> For **Serial mode** (with full parameter configuration), see the complete example in [`Examples/SensorExample/`](Examples/SensorExample/).
---

## Troubleshooting

| Problem | Solution |
|---|---|
| No output signal at all | Check VCC and GND connections. Verify the sensor indicator LED is reactive to an object. Check if you have connected a pull-up resistor.|
| Serial mode: no data received | Verify you're using the correct baud rate. Check that the half-duplex wiring is correct (pull-up resistor is connected). Make sure the software serial library supports single-wire mode. |
---

## Documentation

- **[Datasheet (PDF)](TOF%20distance%20sensor.pdf)** — full electrical and mechanical specifications
- **[Drawings](drawings/)** — board dimensions and wiring diagrams
- **[Example sketch](Examples/SensorExample/)** — ready-to-run Arduino code
- **[Changelog](CHANGELOG.md)** — version history and updates

---

## Contributing

Contributions are welcome! If you find a bug or have a feature request:

1. Open an [Issue](https://github.com/Mindaugas1207/TOF-Distance-sensor/issues) describing the problem or idea.
2. Fork the repository and create a branch for your changes.
3. Submit a [Pull Request](https://github.com/Mindaugas1207/TOF-Distance-sensor/pulls) with a clear description of what you changed and why.

---


This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.
