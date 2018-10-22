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

void setup(){ 
  Serial.begin(9600);

  setupMotorPins();

  delay(4000);
}

void loop(){  
  setMotorSpeed(pwmDutyCycle);

  travelForward();
  delay(5000);
  
  travelBackward();
  delay(1000);

  turnLeft();
  delay(1000);

  travelForward();
  delay(5000);
}

void setMotorSpeed(int pwmDutyCycle) {
  analogWrite(leftEnable, pwmDutyCycle);
  analogWrite(rightEnable, pwmDutyCycle);
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
