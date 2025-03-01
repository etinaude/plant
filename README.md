# 🪴 Plant 🪴


This is a project to keep my plants from dying! It uses a range of sensors to water and light the plant at an ideal time. It also monitors some environmental factors and uses a fan to remove more CO2 and VOCs from the air. All of these are then made available on a web dashboard. It deactivates during the night so you can have it in a bedroom without the lights or motors waking you up.

### Monitors

- 💧 Soil Moisture (used to water plant)
- ☀️ Light (used to turn on glow lights)
- 🌡️ Air Temperature
- ☁️ Air Quailty (CO2 and VOC)
- 💦 Air Humidity


## 📈 Dashboard
<!-- ## [📈 Dashboard](https://plant.etinaude.dev) // -->

### ✔️ Prerequisite

- [BunJs](https://bunjs.dev) or npm
- Set up Firebase with a real-time database
- Add firebase keys to `webapp/src/keys.json`

### 📚 Install Libraries

`bun i`

### 🏃 Run

`bun run dev`

## ⚡ Electronics

### [Easy EDA Schematic]([https://easyeda.com/editor#id=12a974c2c440434495f13cfdb8ba623a](https://oshwlab.com/etinaude/plant))

### 🔋 Components

| 🧮 Logic                      | ➡️ Input                              | Output ➡️   |
| ----------------------------- | ------------------------------------- | ----------- |
| Lolin S2 mini (ESP32-S2)      | CCS811 Air quality sensor             | 5v Pump     |
| uln2003 Transistor IC         | DHT22 Temperature and Humidity Sensor | 5v Leds     |
| 5v 3A PSU                     | Capacity soil moisture sensor         | 5v 40mm fan |
|                               | LDR                                   |             |

## 💾 Embedded System

### ✔️ Prerequisite

- [VS code](https://code.visualstudio.com/)
- [Platform IO](https://platformio.org/)

### 📚 Install Libraries

Install the platform IO libraries:

### 🏃 Run

add `embedded/keys.h` with this content:

```cpp
#define SSID ""  // WiFi SSID
#define PASSWORD ""  // WiFi Password
#define REFERENCE_URL "" // Firebase realtime database reference URL
```

Make sure the ESP32 has Arduino firmware flashed. Verify the code compiles then upload it to the ESP32 

## 📸 Images

| 🔋 PCB                    | ⚡ Electronics                            | 📈 Dashboard                  |
| ------------------------- | ----------------------------------------- | ----------------------------- |
| ![PCB](./images/pcb.jpeg) | ![Electronics](./images/electronics.jpeg) | ![graph](./images/graph.jpeg) |
