// ~~~ INPUT PINS ~~~
#define LDR_1_PIN 21
#define LDR_2_PIN 22
#define LDR_3_PIN 23

#define DHT11_PIN 24

#define I2C_SDA 33
#define I2C_SCL 35

#define SOIL_1_PIN 25
#define SOIL_2_PIN 26
#define SOIL_3_PIN 27

// ~~~ OUTPUT PINS ~~~
#define PUMP_1_PIN 12
#define PUMP_2_PIN 13
#define PUMP_3_PIN 14

#define FAN_PIN 9
#define LED_PIN 10
#define STATUS_LED_PIN 11


// ~~~ ~~~ ~~~ ~~~


void setupPins() {
  pinMode(LDR_1_PIN, INPUT);
  pinMode(LDR_2_PIN, INPUT);
  pinMode(LDR_3_PIN, INPUT);
  pinMode(DHT11_PIN, INPUT);
  pinMode(SOIL_1_PIN, INPUT);
  pinMode(SOIL_2_PIN, INPUT);
  pinMode(SOIL_3_PIN, INPUT);

  pinMode(PUMP_1_PIN, OUTPUT);
  pinMode(PUMP_2_PIN, OUTPUT);
  pinMode(PUMP_3_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}