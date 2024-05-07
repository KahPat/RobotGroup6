//Ultrasonic sensor readings

void readUltrasonic() {
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;  // Calculate the distance

  Serial.print("Distance: ");
  Serial.println(distance);  // Print the distance on the Serial Monitor
  delay(500);               // Wait for a second to get stable readings
}


