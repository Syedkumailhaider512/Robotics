#include <Wire.h>  // Include the I2C library

#define SLAVE_ADDRESS 0x08  // I2C address of the slave Arduino
int soilMoisturePin = A0;  // Soil moisture sensor connected to A0

void setup() {
  Wire.begin();  // Start I2C communication as master
  Serial.begin(9600);  // Start Serial Monitor
}

void loop() {
  int soilMoisture = analogRead(soilMoisturePin);  // Read soil moisture level
  String message;

  if (soilMoisture < 500) {  // Soil is dry
    message = "Soil Dry";
  } else {  // Soil is moist
    message = "Soil Moist";
  }

  // Send the message to the slave
  Wire.beginTransmission(SLAVE_ADDRESS);  // Begin I2C communication
  Wire.write(message.c_str());  // Send the message
  Wire.endTransmission();  // End I2C communication

  Serial.println("Message sent: " + message);  // Debugging
  delay(1000);  // Delay for 1 second
}
