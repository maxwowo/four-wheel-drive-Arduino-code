// =======================================================
// ENGG1000 - Computing Technical Stream
// 
// Motor Controller and Ultrasonic Sensor
// 
// Written by Ye Wo z5215628
//
// Some code copied from course notes 
// =======================================================

// -------------------------------------------------------
// Global Variables
// -------------------------------------------------------

// IMPORTANT: left is defined as the left hand side of the 
// robot in bird's-eye view with the ultrasonic sensor
// facing upwards

int leftEnable = 10;
int leftLogicPinOne = 9;
int leftLogicPinTwo = 8;

int rightEnable = 5;
int rightLogicPinOne = 7;
int rightLogicPinTwo = 6;

// Define ultrasonic sensor pins 
int sensorTrigPin = 12;
int sensorEchoPin = 13;

// Set initial command, speed and direction
char command = 0;
int pwmDutyCycle = 255;
char currentDirection = 'f';

// -------------------------------------------------------
// The setup function runs once, when the sketch starts
// -------------------------------------------------------
void setup(){ 
  // Initialize the serial communications
  // Requires Arduino software interface             
  Serial.begin(9600);                                 
                                                         
  // Set up the pins for the ultrasonic sensor
  setupSensorPins();

  // Set up the pins for the motors
  setupMotorPins();
}

// -------------------------------------------------------
// The loop function runs over and over again
// -------------------------------------------------------
void loop(){
  setMotorSpeed(pwmDutyCycle);
  setMotorDirection(currentDirection);

  // Wait for a command from the keyboard
  command = receiveCommand(); 

  // Update the direction and speed of the robot
  currentDirection = updateDirection(command, currentDirection);
  pwmDutyCycle = updateSpeed(command, pwmDutyCycle);

  // Check for any obstacles in front 
  // If there is, turn left until there is no longer 
  // an obstacle in front of it
  checkObstacle(currentDirection);
  
  // Small delay for a character to arrive
  // Requires Arduino software interface   
  delay(10);
}

// -------------------------------------------------------
// The checkObstacle function checks to see if there is 
// any obstacle in front of the robot
// 
// If there is an obstacle, the robot will turn left until 
// there is no longer an obstacle in front of it 
// -------------------------------------------------------
void checkObstacle(char currentDirection) {
  // Check if
  // 
  // 1) there is any obstacle in front of the robot 
  // that is within 20 centimeters to the ultrasonic 
  // sensor 
  // 
  // 2) the robot is currently moving forward
  if (getDistance() <= 20 && currentDirection == 'f') {
    // Turn left for 10000 milliseconds
    turnLeft();

    // Requires Arduino software interface   
    delay(10000);
  }
}

// -------------------------------------------------------
// The executeCommand subroutine executes any valid 
// commands entered 
// -------------------------------------------------------
void setMotorDirection(char currentDirection) {
  // Check which direction is entered in the serial buffer 
  if (currentDirection == 'f') { 
    travelForward();
  }
  else if (currentDirection == 'b') { 
    travelBackward();
  }
  else if (currentDirection == 'l') { 
    turnLeft();
  }
  else if (currentDirection == 'r') { 
    turnRight();
  }
  else if (currentDirection == 's') {
    brake();
  }   
}

// -------------------------------------------------------
// The receiveCommand function returns the oldest byte 
// in the serial buffer if there is any
// -------------------------------------------------------
char receiveCommand(){
  char incomingByte = 0;

  // See if there's incoming serial data:
  // Requires Arduino software interface   
  if (Serial.available() > 0) {

    // Read the oldest byte in the serial buffer
    // Requires Arduino software interface   
    incomingByte = Serial.read();
  }

  return incomingByte;
}

// -------------------------------------------------------
// The updateDirection function updates the travel 
// direction of the robot 
// -------------------------------------------------------
char updateDirection(char command, char currentDirection){
  // Is this a direction; 'f' 'b' 'l' 'r' 's'
  // Requires Arduino software interface   
  if (command == 'f') {
    Serial.println("Forwards");
    currentDirection = 'f';
  }
  else if (command == 'b') {
    Serial.println("Backwards");
    currentDirection = 'b';
  }
  else if (command == 'l') {
    Serial.println("Turn Left");
    currentDirection = 'l';
  }
  else if (command == 'r') {
    Serial.println("Turn Right");
    currentDirection = 'r';
  }
  else if (command == 's') {
    Serial.println("Stop");
    currentDirection = 's';
  }

  return currentDirection;
}

// -------------------------------------------------------
// The updateSpeed function updates the speed of the 
// robot 
// -------------------------------------------------------
int updateSpeed(char command, int pwmDutyCycle){
  
  // Is this a motor speed 0 - 4
  // Requires Arduino software interface   
  if (command == '0') {
    Serial.println("Speed = 0%");
    pwmDutyCycle = 0;
  }
  else if (command == '1') {
    Serial.println("Speed = 25%");
    pwmDutyCycle = 64;
  }
  else if (command == '2') {
    Serial.println("Speed = 50%");
    pwmDutyCycle = 128;
  }
  else if (command == '3') {
    Serial.println("Speed = 75%");
    pwmDutyCycle = 192;
  }
  else if (command == '4') {
    Serial.println("Speed = 100%");
    pwmDutyCycle = 255;
  }

  return pwmDutyCycle;
}

// -------------------------------------------------------
// The setMotorSpeed subroutine sets the speed of the 
// left and right motors 
// -------------------------------------------------------
void setMotorSpeed(int pwmDutyCycle) {
  analogWrite(leftEnable, pwmDutyCycle);
  analogWrite(rightEnable, pwmDutyCycle);
}

// -------------------------------------------------------
// The setupSensorPins subroutine sets up the pins for the 
// ultrasonic sensor 
//
// Requires Arduino software interface   
// -------------------------------------------------------
void setupSensorPins() {
  // Initialize the serial communications
  Serial.begin(9600); 
  
  // Print the program details
  Serial.println("-------------------------------------");
  Serial.println("Program: HC-SR04"); 
  Serial.println("Initializing ...");

  // Set up the pins
  pinMode(sensorTrigPin, OUTPUT);
  digitalWrite(sensorTrigPin, LOW);
  pinMode(sensorEchoPin, INPUT);

  // Print the pin configuration for wiring
  Serial.print("sensor Trig Pin = ");
  Serial.println(sensorTrigPin);
  Serial.print("sensor Echo Pin = ");
  Serial.println(sensorEchoPin);

  // Initialization completed successfully
  Serial.println("Initialization complete");
}

// -------------------------------------------------------
// The sendTriggerPulse subroutine sends a trigger pulse 
// using the ultrasonic sensor 
//
// Requires Arduino software interface   
// -------------------------------------------------------
void sendTriggerPulse(int sensorTrigPin) {
  // Send the 10 usec trigger pulse
  digitalWrite(sensorTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorTrigPin, LOW);
}

// -------------------------------------------------------
// The waitEchoPinHigh subroutine waits for the echo pin
// to go high 
//
// Requires Arduino software interface   
// -------------------------------------------------------
void waitEchoPinHigh(unsigned long clockMax, int sensorEchoPin) {
  // Wait for the echo pin to go high
  while ((micros() < clockMax) && (digitalRead(sensorEchoPin) == LOW));
}

// -------------------------------------------------------
// The waitEchoPinLow subroutine waits for the echo pin to 
// go low 
//
// Requires Arduino software interface   
// -------------------------------------------------------
void waitEchoPinLow(unsigned long clockMax, int sensorEchoPin) {
  // Read the sensor delay time by waiting for the echo pin to go low
  while ((micros() < clockMax) && (digitalRead(sensorEchoPin) == HIGH));
}

// -------------------------------------------------------
// The calculateDistance function calculates and 
// returns the distance between the ultrasonic sensor and 
// any solid object in front using maths 
//
// Requires Arduino software interface   
// -------------------------------------------------------
float calculateDistance(unsigned long clockStart) {
  return float(micros() - clockStart) / 58.0;
}

// -------------------------------------------------------
// The getDistance function returns the distance between 
// the ultrasonic sensor  and any solid object in front 
// -------------------------------------------------------
float getDistance() {
  // Local variables
  unsigned long clockStart;
  unsigned long clockMax;
  unsigned long timeMax = 60000;
  float distance;
  
  // Send a trigger pulse 
  sendTriggerPulse(sensorTrigPin);

  // Once triggered it take about 500 usec for the echo pin to go high
  // Set the max wait time
  // Requires Arduino software interface   
  clockMax = micros() + 1000;

  // Wait for the echo pin to go high 
  waitEchoPinHigh(clockMax, sensorEchoPin);
  
  // Initialise the echo timer
  clockStart = micros();
  clockMax = clockStart + timeMax;

  // Wait for the echo pin to go low 
  waitEchoPinLow(clockMax, sensorEchoPin);
  
  // Calculate the distance in centimeters and return it 
  return calculateDistance(clockStart);
}

// -------------------------------------------------------
// The setupRightMotorPins subroutine sets up the motors 
// on the right side of the robot 
//
// Requires Arduino software interface   
// -------------------------------------------------------
void setupRightMotorPins() {
  // Set up the right motor pins
  pinMode(rightEnable, OUTPUT);
  pinMode(rightLogicPinOne, OUTPUT);
  pinMode(rightLogicPinTwo, OUTPUT);

  // Print the right motor pins for wiring purposes 
  Serial.print("Right Motor Pin 1 = ");
  Serial.println(rightLogicPinOne);
    
  Serial.print("Right Motor Pin 2 = ");
  Serial.println(rightLogicPinTwo);
}

// -------------------------------------------------------
// The setupLeftMotorPins subroutine sets up the motors 
// on the left side of the robot 
//
// Requires Arduino software interface   
// -------------------------------------------------------
void setupLeftMotorPins() {
  // Set up the left motor pins 
  pinMode(leftEnable, OUTPUT);
  pinMode(leftLogicPinOne, OUTPUT);
  pinMode(leftLogicPinTwo, OUTPUT);

  // Print the left motor pins for wiring purposes 
  Serial.print("Left Motor Pin 1 = ");
  Serial.println(leftLogicPinOne);

  Serial.print("Left Motor Pin 2 = ");
  Serial.println(leftLogicPinTwo);
}

// -------------------------------------------------------
// The setupMotorPins subroutine sets up the motors on 
// both sides of the robot 
// -------------------------------------------------------
void setupMotorPins() {
  // Print the program details
  // Requires Arduino software interface   
  Serial.println("-------------------------------------");
  Serial.println("Program: Motor Controller Interface"); 
  Serial.println("Initializing ...");

  // Configuration the motor pins
  setupRightMotorPins();
  setupLeftMotorPins();

  // Initialization completed successfully
  // Requires Arduino software interface   
  Serial.println("Initialization complete");
}

// PinOne | PinTwo | Motor
//  0     | 0      | Coast
//  5v    | 0      | Forward
//  0     | 5v     | Reverse
//  5v    | 5v     | Brake

// -------------------------------------------------------
// The leftSideForward subroutine drives the motors on the 
// left side of the robot forwards
// -------------------------------------------------------
void leftSideForward() {
  digitalWrite(leftLogicPinOne, HIGH);
  digitalWrite(leftLogicPinTwo, LOW);
}

// -------------------------------------------------------
// The rightSideForward subroutine drives the motors on 
// the right side of the robot forwards
// -------------------------------------------------------
void rightSideForward() {
  digitalWrite(rightLogicPinOne, HIGH);
  digitalWrite(rightLogicPinTwo, LOW);
}

// -------------------------------------------------------
// The leftSideBackward subroutine drives the motors on
// the left side of the robot backwards
// -------------------------------------------------------
void leftSideBackward(){
  digitalWrite(leftLogicPinOne, LOW);
  digitalWrite(leftLogicPinTwo, HIGH);
}

// -------------------------------------------------------
// The rightSideBackward subroutine drives the motors on 
// the right side of the robot backwards
// -------------------------------------------------------
void rightSideBackward() {
  digitalWrite(rightLogicPinOne, LOW);
  digitalWrite(rightLogicPinTwo, HIGH);
}

// -------------------------------------------------------
// The rightSideBrake subroutine applies brake to the 
// motors on the right side of the robot 
// -------------------------------------------------------
void rightSideBrake() {
  digitalWrite(rightLogicPinOne, HIGH);
  digitalWrite(rightLogicPinTwo, HIGH);
}

// -------------------------------------------------------
// The leftSideBrake subroutine applies brake to the 
// motors on the left side of the robot 
// -------------------------------------------------------
void leftSideBrake() {
  digitalWrite(leftLogicPinOne, HIGH);
  digitalWrite(leftLogicPinTwo, HIGH);
}

// -------------------------------------------------------
// The travelForward subroutine makes the robot go 
// forwards
// -------------------------------------------------------
void travelForward() {  
  leftSideForward();
  rightSideForward();
}

// -------------------------------------------------------
// The travelBackward subroutine makes the robot go 
// backwards 
// -------------------------------------------------------
void travelBackward() {
  leftSideBackward();
  rightSideBackward();
}

// -------------------------------------------------------
// The turnLeft subroutine makes the robot turn left 
// -------------------------------------------------------
void turnLeft() {
  leftSideBackward();
  rightSideForward();
}

// -------------------------------------------------------
// The turnRight subroutine makes the robot turn right 
// -------------------------------------------------------
void turnRight() {
  rightSideBackward();
  leftSideForward();
}

// -------------------------------------------------------
// The brake subroutine stops the robot 
// -------------------------------------------------------
void brake() {
  leftSideBrake();
  rightSideBrake();
}
