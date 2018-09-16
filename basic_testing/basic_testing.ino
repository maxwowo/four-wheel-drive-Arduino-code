// -------------------------------------------------------
// Global Variables
// -------------------------------------------------------
int leftEnable = 10;
int leftLogicPinOne = 9;
int leftLogicPin2 = 8;

int rightEnable = 5;
int rightLogicPinOne = 7;
int rightLogicPinTwo = 6;

int sensorTrigPin = 12;
int sensorEchoPin = 13;

char currentDirection = 's';

// -------------------------------------------------------
// The setup() function runs once, when the sketch starts
// -------------------------------------------------------
void setup(){ 
  // Initialize the serial communications
  Serial.begin(9600);

  // Set up the pins for the ultrasonic sensor 
  setupSensorPins();

  // Set up the pins for the motors 
  setupMotorPins();
}

// -------------------------------------------------------
// The loop() function runs over and over again
// -------------------------------------------------------
void loop(){
  enableMotors();

  // See if there's incoming serial data
  if (Serial.available() > 0) {
    currentDirection = receiveCommand();
  }

  // If there is obstacle in front and robot is currently travelling forward 
  if (getDistance() <= 20 && currentDirection == 'f') {
    // Stop 
    currentDirection = 's';
  }

  // Execute any commands entered 
  executeCommand(currentDirection);

  // Small delay for a character to arrive
  delay(10);
}

// -------------------------------------------------------
// The executeCommand() function executes any valid commands 
// entered 
// -------------------------------------------------------
void executeCommand(char currentDirection) {
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
// The receiveCommand() function checks and returns any 
// valid serial command 
// -------------------------------------------------------
char receiveCommand() {
  // Read the oldest byte in the serial buffer:
  char incomingByte = Serial.read();

  // Is this a direction; 'f' 'b' 'l' 'r' 's'
  if (incomingByte == 'f') {
    Serial.println("Forwards");
    currentDirection = 'f';
  }
  else if (incomingByte == 'b') {
    Serial.println("Backwards");
    currentDirection = 'b';
  }
  else if (incomingByte == 'l') {
    Serial.println("Turn Left");
    currentDirection = 'l';
  }
  else if (incomingByte == 'r') {
    Serial.println("Turn Right");
    currentDirection = 'r';
  }
  else if (incomingByte == 's') {
    Serial.println("Stop");
    currentDirection = 's';
  }

  return incomingByte;
}

// -------------------------------------------------------
// The setupSensorPins() function sets up the pins for the 
// ultrasonic sensor 
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
// The sendTriggerPulse() function sends a trigger pulse 
// using the ultrasonic sensor 
// -------------------------------------------------------
void sendTriggerPulse(int sensorTrigPin) {
  // Send the 10 usec trigger pulse
  digitalWrite(sensorTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorTrigPin, LOW);
}

// -------------------------------------------------------
// The waitEchoPinHigh() function waits for the echo pin
// to go high 
// -------------------------------------------------------
void waitEchoPinHigh(unsigned long clockMax, int sensorEchoPin) {
  // Wait for the echo pin to go high
  while ((micros() < clockMax) && (digitalRead(sensorEchoPin) == LOW));
}

// -------------------------------------------------------
// The waitEchoPinLow() function waits for the echo pin to 
// go low 
// -------------------------------------------------------
void waitEchoPinLow(unsigned long clockMax, int sensorEchoPin) {
  // Read the sensor delay time by waiting for the echo pin to go low
  while ((micros() < clockMax) && (digitalRead(sensorEchoPin) == HIGH));
}

// -------------------------------------------------------
// The calculateDistance() function calculates and 
// returns the distance between the ultrasonic sensor and 
// any solid object in front using maths 
// -------------------------------------------------------
float calculateDistance(unsigned long clockStart) {
  return float(micros() - clockStart) / 58.0;
}

// -------------------------------------------------------
// The getDistance() function returns the distance between 
// the ultrasonic sensor  and any solid object in front 
// -------------------------------------------------------
float getDistance() {
  // Local variables
  unsigned long clockStart;
  unsigned long clockMax;
  unsigned long timeMax = 60000;
  float distance;
    
  sendTriggerPulse(sensorTrigPin);

  // Once triggered it take about 500 usec for the echo pin to go high
  // Set the max wait time
  clockMax = micros() + 1000;

  waitEchoPinHigh(clockMax, sensorEchoPin);
  
  // Initialise the echo timer
  clockStart = micros();
  clockMax = clockStart + timeMax;

  waitEchoPinLow(clockMax, sensorEchoPin);
  
  // Calculate the distance in cm
  return calculateDistance(clockStart);
}

// -------------------------------------------------------
// The setupRightMotorPins() function sets up the motors 
// on the right side of the robot 
// -------------------------------------------------------
void setupRightMotorPins() {
  pinMode(rightEnable, OUTPUT);
  pinMode(rightLogicPinOne, OUTPUT);
  pinMode(rightLogicPinTwo, OUTPUT);

  Serial.print("Right Motor Pin 1 = ");
  Serial.println(rightLogicPinOne);
    
  Serial.print("Right Motor Pin 2 = ");
  Serial.println(rightLogicPinTwo);
}

// -------------------------------------------------------
// The setupLeftMotorPins() function sets up the motors 
// on the left side of the robot 
// -------------------------------------------------------
void setupLeftMotorPins() {
  pinMode(leftEnable, OUTPUT);
  pinMode(leftLogicPinOne, OUTPUT);
  pinMode(leftLogicPin2, OUTPUT);

  Serial.print("Left Motor Pin 1 = ");
  Serial.println(leftLogicPinOne);

  Serial.print("Left Motor Pin 2 = ");
  Serial.println(leftLogicPin2);
}

// -------------------------------------------------------
// The setupMotorPins() function sets up the motors on 
// both sides of the robot 
// -------------------------------------------------------
void setupMotorPins() {
  // Print the program details
  Serial.println("-------------------------------------");
  Serial.println("Program: Motor Controller Interface"); 
  Serial.println("Initializing ...");

  // Configuration the motor pins
  setupRightMotorPins();
  setupLeftMotorPins();

  // Initialization completed successfully
  Serial.println("Initialization complete");
}

// -------------------------------------------------------
// The enableLeftMotors() function 
// -------------------------------------------------------
void enableLeftMotors() {
  digitalWrite(leftEnable, HIGH);
}

// -------------------------------------------------------
// The enableRightMotors() function 
// -------------------------------------------------------
void enableRightMotors() {
  digitalWrite(rightEnable, HIGH);
}

// -------------------------------------------------------
// The disableLeftMotors() function 
// -------------------------------------------------------
void disableLeftMotors() {
  digitalWrite(leftEnable, LOW);
}

// -------------------------------------------------------
// The disableRightMotors() function 
// -------------------------------------------------------
void disableRightMotors() {
  digitalWrite(rightEnable, LOW);
}

// -------------------------------------------------------
// The enableMotors() function 
// -------------------------------------------------------
void enableMotors() {
  enableLeftMotors();
  enableRightMotors();
}

// -------------------------------------------------------
// The disableMotors() function 
// -------------------------------------------------------
void disableMotors() {
  disableLeftMotors();
  disableRightMotors();
}

// -------------------------------------------------------
// The leftSideForward() function drives the motors on the 
// left side of the robot forwards
// -------------------------------------------------------
void leftSideForward() {
  digitalWrite(leftLogicPinOne, HIGH);
  digitalWrite(leftLogicPin2, LOW);
}

// -------------------------------------------------------
// The rightSideForward() function drives the motors on the
// right side of the robot forwards
// -------------------------------------------------------
void rightSideForward() {
  digitalWrite(rightLogicPinOne, HIGH);
  digitalWrite(rightLogicPinTwo, LOW);
}

// -------------------------------------------------------
// The leftSideBackward() function drives the motors on the 
// left side of the robot backwards
// -------------------------------------------------------
void leftSideBackward(){
  digitalWrite(leftLogicPinOne, LOW);
  digitalWrite(leftLogicPin2, HIGH);
}

// -------------------------------------------------------
// The rightSideBackward() function drives the motors on 
// the right side of the robot backwards
// -------------------------------------------------------
void rightSideBackward() {
  digitalWrite(rightLogicPinOne, LOW);
  digitalWrite(rightLogicPinTwo, HIGH);
}

// -------------------------------------------------------
// The rightSideBrake() function applies brake to the 
// motors on the right side of the robot 
// -------------------------------------------------------
void rightSideBrake() {
  digitalWrite(rightLogicPinOne, HIGH);
  digitalWrite(rightLogicPinTwo, HIGH);
}

// -------------------------------------------------------
// The leftSideBrake() function applies brake to the 
// motors on the left side of the robot 
// -------------------------------------------------------
void leftSideBrake() {
  digitalWrite(leftLogicPinOne, HIGH);
  digitalWrite(leftLogicPin2, HIGH);
}

// -------------------------------------------------------
// The travelForward() function makes the robot go 
// forwards
// -------------------------------------------------------
void travelForward() {
  leftSideForward();
  rightSideForward();
}

// -------------------------------------------------------
// The travelBackward() function makes the robot go 
// backwards 
// -------------------------------------------------------
void travelBackward() {
  leftSideBackward();
  rightSideBackward();
}

// -------------------------------------------------------
// The turnLeft() function makes the robot turn left 
// -------------------------------------------------------
void turnLeft() {
  leftSideBackward();
  rightSideForward();
}

// -------------------------------------------------------
// The turnRight() function makes the robot turn right 
// -------------------------------------------------------
void turnRight() {
  rightSideBackward();
  leftSideForward();
}

// -------------------------------------------------------
// The brake() function stops the robot 
// -------------------------------------------------------
void brake() {
  leftSideBrake();
  rightSideBrake();
}
