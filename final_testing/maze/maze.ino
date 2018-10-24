int leftEnable = 6;
int leftLogicPinOne = A2;
int leftLogicPinTwo = 3;

int rightEnable = 5;
int rightLogicPinOne = 11;
int rightLogicPinTwo = 9;

int frontTrigPin = 10;
int leftTrigPin = 8;
int rightTrigPin = 7;

int frontEchoPin = A5;
int rightEchoPin = A3;
int leftEchoPin= A4;

int pwmDutyCycle = 255;
int rightDistance, leftDistance, frontDistance;

int distanceThreshold = 10;
int leftRightThreshold = 15;

int rightTurnDelay = 100;
int leftTurnDelay = 100;

int slightDelay = 150;

void setup(){ 
  Serial.begin(9600);

  setupSensorPins();

  setupMotorPins();

  delayMicroseconds(4000);
}

void loop(){  
  setMotorSpeed(pwmDutyCycle);

  readDistance();

  if (rightDistance > leftDistance) {
    turnRight();
    delay(rightTurnDelay);
    readDistance();
    if (frontDistance > distanceThreshold) {
      travelForward();
      delay(slightDelay);
    }
    else {
      travelBackward();
      delay(2 * rightTurnDelay);
      turnRight();
      delay(8 * rightTurnDelay);
    }
  }
  else if (leftDistance >= rightDistance) {
    turnLeft();
    delay(leftTurnDelay); 
    readDistance();  
    if (frontDistance > distanceThreshold) {
      travelForward();
      delay(slightDelay);
    }
    else {
      travelBackward();
      delay(2 * rightTurnDelay);
      turnLeft();
      delay(8 * leftTurnDelay);
    }
  }
}

void readDistance() {
  rightDistance = getDistance(rightTrigPin, rightEchoPin);
  leftDistance = getDistance(leftTrigPin, leftEchoPin);
  frontDistance = getDistance(frontTrigPin, frontEchoPin);
}

void setMotorSpeed(int pwmDutyCycle) {
  analogWrite(leftEnable, pwmDutyCycle);
  analogWrite(rightEnable, pwmDutyCycle);
}

void setupSensorPins() {
  pinMode(frontTrigPin, OUTPUT);
  digitalWrite(frontTrigPin, LOW);

  pinMode(leftTrigPin, OUTPUT);
  digitalWrite(leftTrigPin, LOW);

  pinMode(rightTrigPin, OUTPUT);
  digitalWrite(rightTrigPin, LOW);
  
  pinMode(frontEchoPin, INPUT);
  pinMode(rightEchoPin, INPUT);
  pinMode(leftEchoPin, INPUT);
}

void sendTriggerPulse(int sensorTrigPin) {
  digitalWrite(sensorTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorTrigPin, LOW);
}

void waitEchoPinHigh(unsigned long clockMax, int pin) {
  while ((micros() < clockMax) && (digitalRead(pin) == LOW));
}

void waitEchoPinLow(unsigned long clockMax, int pin) {
  while ((micros() < clockMax) && (digitalRead(pin) == HIGH));
}

float calculateDistance(unsigned long clockStart) {
  return float(micros() - clockStart) / 58.0;
}

float getDistance(int trigPin, int echoPin) {
  unsigned long clockStart;
  unsigned long clockMax;
  unsigned long timeMax = 60000;
  float distance;
  
  sendTriggerPulse(trigPin);

  clockMax = micros() + 1000;

  waitEchoPinHigh(clockMax, echoPin);
  
  clockStart = micros();
  clockMax = clockStart + timeMax;

  waitEchoPinLow(clockMax, echoPin);
  
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
