void robotLogic() {
  motorLogic(); //Process motor logic based on IR sensor values
}

void motorLogic() { // Logic to tell the motors how to operate 

  int* IRvalues;
  IRvalues = readInfrared(); // Read the current state of the IR sensors

  if (IRvalues[1] == 1 && IRvalues[2] == 1) {
    motorControl(200, 200); // move robot straight forward
    currentState = "Forward";
  } else if (IRvalues[1] == 0 && IRvalues[2] == 1) {
    motorControl(150, 200); // move robot straight forward
    currentState = "Left";
  } else if (IRvalues[1] == 1 && IRvalues[2] == 0) {
    motorControl(200, 150); // move robot straight forward
    currentState = "Right";
  } else if (IRvalues[0] == 1 && IRvalues[1] == 1 && IRvalues[2] == 1 && IRvalues[3] == 1) {
    // If none of the IR sensors detect a line, continue the last state detected by the centre IR sensors 
    if (currentState == "Forward") {
      motorControl(200, 200); // straight forward
    } else if (currentState == "Left") {
      motorControl(150, 200); // slight left
    } else if (currentState == "Right") {
      motorControl(200, 150); // slight right
    }
  }
}











