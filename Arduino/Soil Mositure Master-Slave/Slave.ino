#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>
#include <Servo.h>

#define SERVO_PIN 9                 // Servo control pin
Adafruit_LiquidCrystal lcd(0);      // Initialize LCD (I2C address 0x20)
Servo waterServo;                   // Create a Servo object

String receivedMessage = "";        // Variable to store received message

void setup() {
  waterServo.attach(SERVO_PIN);     // Attach the servo to the control pin
  waterServo.write(0);              // Start servo at 0° (water off)

  Wire.begin(0x08);                 // Initialize I2C with the slave address
  Wire.onReceive(receiveEvent);     // Register the receive event
  lcd.begin(16, 2);                 // Initialize a 16x2 LCD
  lcd.print("Awaiting data...");    // Display initial message
  Serial.begin(9600);               // Start Serial Monitor for debugging
}

void loop() {
  if (receivedMessage == "Soil Dry") {
    waterServo.write(90);           // Rotate servo to 90° (simulate watering)
    lcd.setCursor(0, 0);
    lcd.print("Status: WATERING "); // Display status
  } else if (receivedMessage == "Soil Moist") {
    waterServo.write(0);            // Rotate servo to 0° (stop watering)
    lcd.setCursor(0, 0);
    lcd.print("Status: STOPPED  "); // Display status
  }

  // Display the received message on the second line
  lcd.setCursor(0, 1);
  lcd.print("Msg: ");
  lcd.print(receivedMessage);
  lcd.print("  ");  // Clear leftover characters

  delay(1000);  // Delay to avoid rapid toggling
}

void receiveEvent(int bytes) {
  char buffer[32];                  // Buffer to store incoming data
  Wire.readBytes(buffer, bytes);    // Read the incoming data
  receivedMessage = String(buffer); // Convert buffer to a String
  receivedMessage.trim();           // Remove any trailing whitespace
  Serial.println("Message received: " + receivedMessage); // Debugging
}
