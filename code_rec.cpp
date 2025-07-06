#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11);  // RX, TX (Connect HC-05 RX to Arduino pin 11)

// Motor control pins
const int leftMotor1 = 2;   // IN1
const int leftMotor2 = 3;   // IN2
const int rightMotor1 = 4;  // IN3
const int rightMotor2 = 5;  // IN4
const int enA = 9;          // Left motor PWM
const int enB = 10;         // Right motor PWM

void setup() {
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  
  Serial.begin(9600);
  BTSerial.begin(38400);  // Match transmitter baud rate
  Serial.println("Motor Receiver Ready");
}

void loop() {
  if (BTSerial.available()) {
    char command = BTSerial.read();
    Serial.print("Executing: "); Serial.println(command);
    
    switch(command) {
      case 'F': forward(); break;
      case 'B': backward(); break;
      case 'L': left(); break;
      case 'R': right(); break;
      default: stopMotors();
    }
  }
}

void forward() {
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  analogWrite(enA, 200);  // 80% speed
  analogWrite(enB, 200);
}

void backward() {
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
  analogWrite(enA, 200);
  analogWrite(enB, 200);
}

void left() {
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);  // Left backward
  digitalWrite(rightMotor1, HIGH); // Right forward
  digitalWrite(rightMotor2, LOW);
  analogWrite(enA, 200);
  analogWrite(enB, 200);
}

void right() {
  digitalWrite(leftMotor1, HIGH);  // Left forward
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH); // Right backward
  analogWrite(enA, 200);
  analogWrite(enB, 200);
}

void stopMotors() {
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
}