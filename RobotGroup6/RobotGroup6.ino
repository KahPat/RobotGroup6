#include <tcs3200.h>

#define IR_1 2
#define IR_2 4
#define IR_3 7
#define IR_4 8

#define COLOR_0 A0
#define COLOR_1 A1
#define COLOR_2 A2
#define COLOR_3 A3
#define COLOR_OUT A4



unsigned long irSensorMillis = 0; //timer to track last report of IR sensors
unsigned long colorSensorMillis = 0; //timer to track the last report of the color sensors

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IR_1, INPUT);
  pinMode(IR_2, INPUT);
  pinMode(IR_3, INPUT);
  pinMode(IR_4, INPUT);

}

void loop() {
  //Get the current run time in milliseconds
  unsigned long currentMillis = millis();

  //Check the states of the IR sensors every 500 ms
  if (currentMillis - irSensorMillis >= 500) {
    irSensorMillis = currentMillis;
    readInfrared();
  }

  //Read the color sensor
  if (currentMillis - colorSensorMillis >= 250) {
    colorSensorMillis = currentMillis;
    readColorSensor();
  }
}