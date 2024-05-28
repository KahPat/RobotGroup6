#include <tcs3200.h>
#include <WiFiNINA.h>

#define IR_1 4
#define IR_2 7
#define IR_3 8
#define IR_4 12

#define COLOR_0 A0
#define COLOR_1 A1
#define COLOR_2 A2
#define COLOR_3 A3
#define COLOR_OUT A4

#define MOTOR_PIN1 3
#define MOTOR_PIN2 5
#define MOTOR_PIN3 6
#define MOTOR_PIN4 9

#define TRIG_PIN 10
#define ECHO_PIN 11

#define LED_R 25
#define LED_G 26
#define LED_B 27

//Turning Logic
String turnDirection = "";      // Keep track of the current turn direction
String lastTurnDirection = "";  // Store the last turn direction to decide the next turn if sharp turn is detected
bool isTurning = false;         // Flag to show if the robot is turning or not
bool wallDetected = false;      // Flag to show if the robot has detected a wall with the ultrasonic sensor

unsigned long irSensorMillis = 0;     //timer to track last report of IR sensors
unsigned long colorSensorMillis = 0;  //timer to track the last report of the color sensors
unsigned long ultrasonicMillis = 0;   //timer to track the last report of ultrasonic sensor

//Get the current run time in millisecond
unsigned long currentMillis = millis();

// State logic
String currentState = "Null";
String oldCurrentState = "Null";

unsigned long currentDistance = 0;  // tracks the distance from the ultrasonic sensor

void setup() {
  Serial.begin(115200);

  pinMode(IR_1, INPUT);
  pinMode(IR_2, INPUT);
  pinMode(IR_3, INPUT);
  pinMode(IR_4, INPUT);

  //Setup Motor Pins
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);
  pinMode(MOTOR_PIN4, OUTPUT);

  //Setup Ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);  // Sets the trigPin as an Output
  pinMode(ECHO_PIN, INPUT);   // Sets the echoPin as an Input

  // Setup onboard RGB LED pins
  WiFiDrv::pinMode(LED_R, OUTPUT); // Define red LED
  WiFiDrv::pinMode(LED_G, OUTPUT); // Define green LED
  WiFiDrv::pinMode(LED_B, OUTPUT); // Define blue LED
}

void loop() {

  //Get the current run time in millisecond
  currentMillis = millis();

  //Check the states of the IR sensors every 200 ms
  if (currentMillis - irSensorMillis >= 100) {
    irSensorMillis = currentMillis;
    readInfrared();
  }

  //Read the color sensor
  if (currentMillis - colorSensorMillis >= 100) {
    colorSensorMillis = currentMillis;
    readColorSensor();
  }

  //Reads ultrasonic sensor readings every 20 ms
  if (currentMillis - ultrasonicMillis >= 20) {
    ultrasonicMillis = currentMillis;
    readUltrasonic();
  }

  // Serial.println(currentState);
  robotLogic();

  WiFiDrv::analogWrite(25, 255); //Red
  WiFiDrv::analogWrite(26, 255); //Green
  WiFiDrv::analogWrite(27, 255); //Blue
}