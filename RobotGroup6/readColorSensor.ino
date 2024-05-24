tcs3200 tcs(COLOR_0, COLOR_1, COLOR_2, COLOR_3, COLOR_OUT);

const int RED_THRESHOLD = 500;
const int GREEN_THRESHOLD = 300;
const int BLUE_THRESHOLD = 200;

int avgRed = 0;
int avgGreen = 0;
int avgBlue = 0;

void readColorSensor() {
  const int samples = 5;
  long sumRed = 0, sumGreen = 0, sumBlue = 0, sumWhite = 0;

  for (int i = 0; i < samples; i++) {
    sumRed += tcs.colorRead('r');
    sumGreen += tcs.colorRead('g');
    sumBlue += tcs.colorRead('b');
    sumWhite += tcs.colorRead('c');
  }

  avgRed = sumRed / samples;
  avgGreen = sumGreen / samples;
  avgBlue = sumBlue / samples;
  int avgWhite = sumWhite / samples;

  // Serial.print("Average Color Sensor Readings: ");
  // Serial.print(" R= ");
  // Serial.print(avgRed);
  // Serial.print(" G= ");
  // Serial.print(avgGreen);
  // Serial.print(" B= ");
  // Serial.print(avgBlue);
  // Serial.print(" W(clear)= ");
  // Serial.println(avgWhite);
}

void detectColor() {
  readColorSensor();

  if (avgRed > RED_THRESHOLD && avgGreen < GREEN_THRESHOLD && avgBlue < BLUE_THRESHOLD) {
    Serial.println("Detected: Red");
  } else if (avgRed < RED_THRESHOLD && avgGreen > GREEN_THRESHOLD && avgBlue < BLUE_THRESHOLD) {
    Serial.println("Detected: Green");
  } else if (avgRed < RED_THRESHOLD && avgGreen < GREEN_THRESHOLD && avgBlue > BLUE_THRESHOLD) {
    Serial.println("Detected: Blue");
  } else {
    Serial.println("Unknown color detected");
    
  }
}