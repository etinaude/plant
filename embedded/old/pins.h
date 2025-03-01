// ~~~ INPUT PINS ~~~
#define LDR_1_PIN 37

#define DHT11_PIN 39

#define I2C_SDA 18
#define I2C_SCL 33

#define SOIL_1_PIN 1
#define SOIL_2_PIN 3
#define SOIL_3_PIN 2

// ~~~ OUTPUT PINS ~~~
#define PUMP_1_PIN 34
#define PUMP_2_PIN 18
#define PUMP_3_PIN 21

#define FAN_PIN 16
#define LED_PIN 17
#define STATUS_LED_PIN 24
// ~~~ ~~~ ~~~ ~~~


void setupPins() {
  Wire.begin(I2C_SDA, I2C_SCL);

  pinMode(LDR_1_PIN, INPUT);
  pinMode(DHT11_PIN, INPUT);
  pinMode(SOIL_1_PIN, INPUT);
  pinMode(SOIL_2_PIN, INPUT);
  pinMode(SOIL_3_PIN, INPUT);
  // adcAttachPin(SOIL_1_PIN);


  pinMode(PUMP_1_PIN, OUTPUT);
  pinMode(PUMP_2_PIN, OUTPUT);
  pinMode(PUMP_3_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}