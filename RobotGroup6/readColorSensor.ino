// Define the TCS3200 color sensor object
tcs3200 tcs(COLOR_0, COLOR_1, COLOR_2, COLOR_3, COLOR_OUT);

const int RED_THRESHOLD = 5;
const int GREEN_THRESHOLD = 5;
const int BLUE_THRESHOLD = 5;

enum Color {
  RED,
  GREEN,
  BLUE,
  YELLOW,
  BLACK,
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
      WiFiDrv::analogWrite(25, 0);    //Green
      WiFiDrv::analogWrite(26, 255);  //Red
      WiFiDrv::analogWrite(27, 0);    //Blue
      break;
    case GREEN:
      Serial.println("Detected color: Green");
      WiFiDrv::analogWrite(25, 255);  //Green
      WiFiDrv::analogWrite(26, 0);    //Red
      WiFiDrv::analogWrite(27, 0);    //Blue
      break;
    case BLUE:
      Serial.println("Detected color: Blue");
      WiFiDrv::analogWrite(25, 0);    //Green
      WiFiDrv::analogWrite(26, 0);    //Red
      WiFiDrv::analogWrite(27, 255);  //Blue
      break;
    case YELLOW:
      Serial.println("Detected color: Yellow");
      WiFiDrv::analogWrite(25, 255);  //Green
      WiFiDrv::analogWrite(26, 255);  //Red
      WiFiDrv::analogWrite(27, 0);    //Blue
      break;
    case BLACK:
      Serial.println("Detected color: Black");
      WiFiDrv::analogWrite(25, 0);    //Green
      WiFiDrv::analogWrite(26, 0);  //Red
      WiFiDrv::analogWrite(27, 0);    //Blue
      break;
    case NONE:
      Serial.println("No color detected");
      break;
  }
}

Color detectColor(int avgRed, int avgGreen, int avgBlue) {
  // Define expected values for each color
  const int redExpected[] = { 28, 7, 10 };
  const int greenExpected[] = { 20, 30, 23 };
  const int blueExpected[] = { 8, 10, 22 };
  const int yellowExpected[] = { 55, 36, 20 };
  const int blackExpected[] = { 7, 6, 8 };

  // Check for red
  if (abs(avgRed - redExpected[0]) < RED_THRESHOLD && abs(avgGreen - redExpected[1]) < GREEN_THRESHOLD && abs(avgBlue - redExpected[2]) < BLUE_THRESHOLD) {
    return RED;
  }

  // Check for green
  if (abs(avgRed - greenExpected[0]) < RED_THRESHOLD && abs(avgGreen - greenExpected[1]) < GREEN_THRESHOLD && abs(avgBlue - greenExpected[2]) < BLUE_THRESHOLD) {
    return GREEN;
  }

  // Check for blue
  if (abs(avgRed - blueExpected[0]) < RED_THRESHOLD && abs(avgGreen - blueExpected[1]) < GREEN_THRESHOLD && abs(avgBlue - blueExpected[2]) < BLUE_THRESHOLD) {
    return BLUE;
  }

  // Check for yellow
  if (abs(avgRed - yellowExpected[0]) < RED_THRESHOLD && abs(avgGreen - yellowExpected[1]) < GREEN_THRESHOLD && abs(avgBlue - yellowExpected[2]) < BLUE_THRESHOLD) {
    return YELLOW;
  }

  // Check for black
  if (abs(avgRed - blackExpected[0]) < RED_THRESHOLD && abs(avgGreen - blackExpected[1]) < GREEN_THRESHOLD && abs(avgBlue - blackExpected[2]) < BLUE_THRESHOLD) {
    return BLACK;
  }
  return NONE;  // No color detected
}