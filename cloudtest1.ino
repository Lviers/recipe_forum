#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MQUnifiedsensor.h>

// Define the I2C address for the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Replace 0x27 with your I2C address if different

// MQ-135 Settings
#define Board "Arduino"
#define Pin A0
#define Type "MQ-135"
#define Voltage_Resolution 5
#define ADC_Bit_Resolution 10
#define RatioMQ135CleanAir 3.6
MQUnifiedsensor MQ135(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.print("Air Quality Mon.");

  // Initialize Serial
  Serial.begin(9600);
  
  // Initialize MQ-135
  MQ135.setRegressionMethod(1); // PPB
  MQ135.init();

  // Calibration of the MQ-135 (optional)
  Serial.println("Calibrating MQ-135...");
  for(int i = 1; i <= 10; i++){
    MQ135.update();
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done!");
}

void loop() {
  // Read MQ-135 Sensor
  MQ135.update();
  float airQuality = MQ135.readSensor();

  // Print the results to the Serial Monitor
  Serial.print("Air Quality: ");
  Serial.print(airQuality);
  Serial.println(" PPM");

  // Display the results on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Air Quality:");
  lcd.setCursor(0, 1);
  lcd.print(airQuality);
  lcd.print(" PPM");

  delay(2000); // Delay for 2 seconds before the next reading
}
