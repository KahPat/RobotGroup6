
// Define the TCS3200 color sensor object
// Assuming the constructor syntax for the TCS3200 object is correct
// Note: Correct the syntax if needed, e.g., `tcs3200` should be capitalized if it's a class name.
tcs3200 tcs(COLOR_0, COLOR_1, COLOR_2, COLOR_3, COLOR_OUT);

const int RED_THRESHOLD = 5;
const int GREEN_THRESHOLD = 5;
const int BLUE_THRESHOLD = 5;

enum Color {
  RED,
  GREEN,
  BLUE,
  YELLOW,
  NONE
};

Color detectColor(int avgRed, int avgGreen, int avgBlue);

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

  Serial.print("Average Color Sensor Readings: ");
  Serial.print(" R= ");
  Serial.print(avgRed);
  Serial.print(" G= ");
  Serial.print(avgGreen);
  Serial.print(" B= ");
  Serial.print(avgBlue);
  Serial.print(" W(clear)= ");
  Serial.println(avgWhite);

  // Detect the color
  Color detectedColor = detectColor(avgRed, avgGreen, avgBlue);
  switch (detectedColor) {
    case RED:
      Serial.println("Detected color: Red");
      break;
    case GREEN:
      Serial.println("Detected color: Green");
      break;
    case BLUE:
      Serial.println("Detected color: Blue");
      break;
    case YELLOW:
      Serial.println("Detected color: Yellow");
      break;
    case NONE:
      Serial.println("No color detected");
      break;
  }
}

Color detectColor(int avgRed, int avgGreen, int avgBlue) {
  // Define expected values for each color
  const int redExpected[] = {28, 7, 10};
  const int greenExpected[] = {17, 26, 20};
  const int blueExpected[] = {8, 10, 22};
  const int yellowExpected[] = {47, 30, 18};

  // Check for red
  if (abs(avgRed - redExpected[0]) < RED_THRESHOLD &&
      abs(avgGreen - redExpected[1]) < GREEN_THRESHOLD &&
      abs(avgBlue - redExpected[2]) < BLUE_THRESHOLD) {
    return RED;
  }

  // Check for green
  if (abs(avgRed - greenExpected[0]) < RED_THRESHOLD &&
      abs(avgGreen - greenExpected[1]) < GREEN_THRESHOLD &&
      abs(avgBlue - greenExpected[2]) < BLUE_THRESHOLD) {
    return GREEN;
  }

  // Check for blue
  if (abs(avgRed - blueExpected[0]) < RED_THRESHOLD &&
      abs(avgGreen - blueExpected[1]) < GREEN_THRESHOLD &&
      abs(avgBlue - blueExpected[2]) < BLUE_THRESHOLD) {
    return BLUE;
  }

  // Check for yellow
  if (abs(avgRed - yellowExpected[0]) < RED_THRESHOLD &&
      abs(avgGreen - yellowExpected[1]) < GREEN_THRESHOLD &&
      abs(avgBlue - yellowExpected[2]) < BLUE_THRESHOLD) {
    return YELLOW;
  }

  return NONE; // No color detected
}

