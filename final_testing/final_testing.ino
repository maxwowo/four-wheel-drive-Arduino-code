int leftEnable = 6;
int leftLogicPinOne = A2;
int leftLogicPinTwo = 3;

int rightEnable = 5;
int rightLogicPinOne = 11;
int rightLogicPinTwo = 9;

int frontTrigPin = 10;
int leftTrigPin = 8;
int rightTrigPin = 7;

int frontSensorEchoPin = A5;
int rightSensorEchoPin = A3;
int leftSensorEchoPin= A4;

int pwmDutyCycle = 255;

void setup(){ 
  Serial.begin(9600);

  setupSensorPins();

  setupMotorPins();
}

void loop(){
  setMotorSpeed(pwmDutyCycle);
  setMotorDirection(currentDirection);

  currentDirection = checkObstacle(currentDirection);

}

char checkObstacle(char currentDirection) {
  if (getDistance() <= 20 && currentDirection == 'f') {
    currentDirection = 's';
  }

  return currentDirection;
}

void setMotorSpeed(int pwmDutyCycle) {
  analogWrite(leftEnable, pwmDutyCycle);
  analogWrite(rightEnable, pwmDutyCycle);
}

void setupSensorPins() {
  Serial.begin(9600); 
  
  Serial.println("-------------------------------------");
  Serial.println("Program: HC-SR04"); 
  Serial.println("Initializing ...");

  pinMode(sensorTrigPin, OUTPUT);
  digitalWrite(sensorTrigPin, LOW);
  pinMode(frontSensorEchoPin, INPUT);
  pinMode(rightSensorEchoPin, INPUT);
  pinMode(leftSensorEchoPin, INPUT);

  Serial.print("sensor Trig Pin = ");
  Serial.println(sensorTrigPin);
  Serial.print("sensor Echo Pin = ");
  Serial.println(frontSensorEchoPin);

  Serial.println("Initialization complete");
}

void sendTriggerPulse(int sensorTrigPin) {
  digitalWrite(sensorTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorTrigPin, LOW);
}

void waitEchoPinHigh(unsigned long clockMax, int frontSensorEchoPin) {
  while ((micros() < clockMax) && (digitalRead(frontSensorEchoPin) == LOW));
}

void waitEchoPinLow(unsigned long clockMax, int frontSensorEchoPin) {
  while ((micros() < clockMax) && (digitalRead(frontSensorEchoPin) == HIGH));
}

float calculateDistance(unsigned long clockStart) {
  return float(micros() - clockStart) / 58.0;
}

float getDistance() {
  unsigned long clockStart;
  unsigned long clockMax;
  unsigned long timeMax = 60000;
  float distance;
  
  sendTriggerPulse(sensorTrigPin);

  clockMax = micros() + 1000;

  waitEchoPinHigh(clockMax, frontSensorEchoPin);
  
  clockStart = micros();
  clockMax = clockStart + timeMax;

  waitEchoPinLow(clockMax, frontSensorEchoPin);
  
  return calculateDistance(clockStart);
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
  pinMode(leftLogicPinTwo, OUTPUT);

  Serial.print("Left Motor Pin 1 = ");
  Serial.println(leftLogicPinOne);

  Serial.print("Left Motor Pin 2 = ");
  Serial.println(leftLogicPinTwo);
}

void setupMotorPins() {
  Serial.println("-------------------------------------");
  Serial.println("Program: Motor Controller Interface"); 
  Serial.println("Initializing ...");

  setupRightMotorPins();
  setupLeftMotorPins();

  Serial.println("Initialization complete");
}

void leftSideForward() {
  digitalWrite(leftLogicPinOne, HIGH);
  digitalWrite(leftLogicPinTwo, LOW);
}

void rightSideForward() {
  digitalWrite(rightLogicPinOne, HIGH);
  digitalWrite(rightLogicPinTwo, LOW);
}

void leftSideBackward(){
  digitalWrite(leftLogicPinOne, LOW);
  digitalWrite(leftLogicPinTwo, HIGH);
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
  digitalWrite(leftLogicPinTwo, HIGH);
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