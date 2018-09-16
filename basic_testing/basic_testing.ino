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
// The setup() method runs once, when the sketch starts
// -------------------------------------------------------
void setup(){ 
  // Initialize the serial communications
  Serial.begin(9600);

  setupSensorPins();

  setupMotorPins();
}

// -------------------------------------------------------
// The loop() method runs over and over again
// -------------------------------------------------------
void loop(){
  turnOnMotors();

  // See if there's incoming serial data:
  if (Serial.available() > 0){
    currentDirection = getDirectionCommand();
  }

  if (getDistance() <= 20) {
    currentDirection = 's';
  }

  executeDirectionCommand(currentDirection);

  // Small delay for a character to arrive
  delay(10);
}

void executeDirectionCommand(char currentDirection) {
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

char getDirectionCommand() {
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

float getDistance() {
  // Local variables
  unsigned long clockStart;
  unsigned long clockMax;
  unsigned long timeMax = 60000;
  float distance;
  
  // Send the 10 usec trigger pulse
  digitalWrite(sensorTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorTrigPin, LOW);
  
  // Once triggered it take about 500 usec for the echo pin to go high
  // Set the max wait time
  clockMax = micros() + 1000;

  // Wait for the echo pin to go high
  while ((micros() < clockMax) && (digitalRead(sensorEchoPin) == LOW));
  
  // Initialise the echo timer
  clockStart = micros();
  clockMax = clockStart + timeMax;

  // Read the sensor delay time by waiting for the echo pin to go low
  while ((micros() < clockMax) && (digitalRead(sensorEchoPin) == HIGH));
  
  // Calculate the distance in cm
  distance = float(micros() - clockStart) / 58.0;
  
  return distance;
}

void setupRightMotorPins() {
  pinMode(rightEnable, OUTPUT);
  pinMode(rightLogicPinOne, OUTPUT);
  pinMode(rightLogicPinTwo, OUTPUT);

  Serial.print("Right Motor Pin 1 = ");
  Serial.println(rightLogicPinOne);
    
  Serial.print("Right Motor Pin 2 = ");
  Serial.println(rightLogicPinTwo);
}

void setupLeftMotorPins() {
  pinMode(leftEnable, OUTPUT);
  pinMode(leftLogicPinOne, OUTPUT);
  pinMode(leftLogicPin2, OUTPUT);

  Serial.print("Left Motor Pin 1 = ");
  Serial.println(leftLogicPinOne);

  Serial.print("Left Motor Pin 2 = ");
  Serial.println(leftLogicPin2);
}

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


void turnOnMotorA() {
  digitalWrite(leftEnable, HIGH);
}

void turnOnMotorB() {
  digitalWrite(rightEnable, HIGH);
}

void turnOffMotorA() {
  digitalWrite(leftEnable, LOW);
}

void turnOffMotorB() {
  digitalWrite(rightEnable, LOW);
}

void turnOnMotors() {
  turnOnMotorA();
  turnOnMotorB();
}

void turnOffMotors() {
  turnOffMotorA();
  turnOffMotorB();
}

void leftSideForward() {
  digitalWrite(leftLogicPinOne, HIGH);
  digitalWrite(leftLogicPin2, LOW);
}

void rightSideForward() {
  digitalWrite(rightLogicPinOne, HIGH);
  digitalWrite(rightLogicPinTwo, LOW);
}

void leftSideBackward(){
  digitalWrite(leftLogicPinOne, LOW);
  digitalWrite(leftLogicPin2, HIGH);
}

void rightSideBackward() {
  digitalWrite(rightLogicPinOne, LOW);
  digitalWrite(rightLogicPinTwo, HIGH);
}

void rightSideBrake() {
  digitalWrite(rightLogicPinOne, HIGH);
  digitalWrite(rightLogicPinTwo, HIGH);
}

void leftSideBrake() {
  digitalWrite(leftLogicPinOne, HIGH);
  digitalWrite(leftLogicPin2, HIGH);
}

void travelForward() {
  leftSideForward();
  rightSideForward();
}

void travelBackward() {
  leftSideBackward();
  rightSideBackward();
}

void turnLeft() {
  leftSideBackward();
  rightSideForward();
}

void turnRight() {
  rightSideBackward();
  leftSideForward();
}

void brake() {
  leftSideBrake();
  rightSideBrake();
}

