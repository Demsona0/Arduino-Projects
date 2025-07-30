#include <Servo.h>

// Pin Definitions
const int TRIGGER_PIN = 8;
const int ECHO_PIN = 6;
const int GREEN_LED = 3;
const int RED_LED = 4;
const int SERVO_PIN = 9;

Servo barrierServo;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize pins
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Initialize servo
  barrierServo.attach(SERVO_PIN);
  barrierServo.write(0);  // Start with barrier closed
  
  delay(1000); // Initial delay
}

long getDistance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  return pulseIn(ECHO_PIN, HIGH);
}

void loop() {
  // Calculate distance in cm (0.0343 cm/μs divided by 2 for round trip)
  float distance = getDistance() * 0.034 / 2;
  
  // Print raw sensor reading and calculated distance
  Serial.print("Raw: ");
  Serial.print(getDistance());
  Serial.print(" μs | Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  if (distance <= 10) {
    // Object detected within 50cm
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    barrierServo.write(90);  // Open barrier
    Serial.println("Access granted - barrier open");
  } else {
    // No object detected
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    barrierServo.write(0);  // Close barrier
    Serial.println("Access denied - barrier closed");
  }
  
  delay(200); // Short delay between readings
}