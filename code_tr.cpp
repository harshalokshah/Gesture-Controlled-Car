#include <Wire.h>
#include <MPU6050.h>
#include <SoftwareSerial.h>

MPU6050 mpu;
SoftwareSerial BTSerial(10, 11);  // RX, TX (Connect HC-05 TX to Arduino pin 10)

void setup() {
  Serial.begin(9600);
  BTSerial.begin(38400);  // Use 38400 for better stability
  Wire.begin();
  
  if (!mpu.begin()) {
    Serial.println("MPU6050 init failed!");
    while (1);
  }
  Serial.println("Gesture Transmitter Ready");
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);  // Get accelerometer data

  // Map accelerometer values to directional commands
  char command = 'S';  // Default stop command
  
  if (a.acceleration.y > 2) command = 'F';  // Forward
  else if (a.acceleration.y < -2) command = 'B';  // Backward
  else if (a.acceleration.x < -2) command = 'L';  // Left
  else if (a.acceleration.x > 2) command = 'R';  // Right

  // Send command via Bluetooth
  BTSerial.write(command);
  
  // Debug output
  Serial.print("X: "); Serial.print(a.acceleration.x);
  Serial.print(" Y: "); Serial.print(a.acceleration.y);
  Serial.print(" CMD: "); Serial.println(command);
  
  delay(200);
}