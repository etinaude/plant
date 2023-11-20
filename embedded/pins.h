// ~~~ INPUT PINS ~~~
#define LDR_1_PIN 37

#define DHT11_PIN 39

#define I2C_SDA 18
#define I2C_SCL 33

#define SOIL_1_PIN 16
#define SOIL_2_PIN 23
#define SOIL_3_PIN 23

// ~~~ OUTPUT PINS ~~~
#define PUMP_1_PIN 5
#define PUMP_2_PIN 3
#define PUMP_3_PIN 24

#define FAN_PIN 24
#define LED_PIN 11
#define STATUS_LED_PIN 24
// ~~~ ~~~ ~~~ ~~~


void setupPins() {
  Wire.begin(I2C_SDA, I2C_SCL);

  pinMode(LDR_1_PIN, INPUT);
  pinMode(DHT11_PIN, INPUT);
  pinMode(SOIL_1_PIN, INPUT);
  pinMode(SOIL_2_PIN, INPUT);
  pinMode(SOIL_3_PIN, INPUT);
  adcAttachPin(SOIL_1_PIN);


  pinMode(PUMP_1_PIN, OUTPUT);
  pinMode(PUMP_2_PIN, OUTPUT);
  pinMode(PUMP_3_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}