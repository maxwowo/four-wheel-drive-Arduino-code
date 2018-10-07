<<<<<<< HEAD
int trigPin = 10;    // Define Trigger pins
int lefttrigPin= 8;
int righttrigPin= 7;

int echoPin = A5;    // Define Echo pins
int leftechoPin=A4;
int rightechoPin=A3;

int leftEnable = 6;   // Define Left side motors
=======
int leftEnable = 6;
>>>>>>> d2886adf21b18a961cbba0d276fd7f84b6b3fd39
int leftLogicPinOne = A2;
int leftLogicPinTwo = 3;

int rightEnable = 5;    //Define right side motors
int rightLogicPinOne = 11;
int rightLogicPinTwo = 9;

int frontTrigPin = 10;
int leftTrigPin = 8;
int rightTrigPin = 7;

<<<<<<< HEAD
long duration, cm, leftcm,durationleft,rightcm,durationright;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  pinMode(12,OUTPUT);
  digitalWrite(12,HIGH);
  //Define inputs and outputs for sensors
  pinMode(trigPin, OUTPUT);
  pinMode(lefttrigPin, OUTPUT);
  pinMode(righttrigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(leftechoPin, INPUT);
  pinMode(rightechoPin, INPUT);

  //Define input and output pin for motors
  pinMode(rightEnable, OUTPUT);
  pinMode(rightLogicPinOne, OUTPUT);
  pinMode(rightLogicPinTwo, OUTPUT);
=======
int frontEchoPin = A5;
int rightEchoPin = A3;
int leftEchoPin= A4;

int pwmDutyCycle = 255;
int rightDistance, leftDistance, frontDistance;

void setup(){ 
  Serial.begin(9600);

  setupSensorPins();

  setupMotorPins();
}

void loop(){  
  setMotorSpeed(pwmDutyCycle);

  rightDistance = getDistance(rightTrigPin);
  leftDistance = getDistance(leftTrigPin);
  frontDistance = getDistance(frontTrigPin);

  if (frontDistance >= 20) {
    travelForward();
  }
  else if (leftDistance >= 20) {
    turnLeft();
  }
  else if (rightDistance >= 20) {
    turnRight();
  }
  else {
    travelBackward();
  }
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

float getDistance(int pin) {
  unsigned long clockStart;
  unsigned long clockMax;
  unsigned long timeMax = 60000;
  float distance;
  
  sendTriggerPulse(pin);

  clockMax = micros() + 1000;

  waitEchoPinHigh(clockMax, pin);
  
  clockStart = micros();
  clockMax = clockStart + timeMax;

  waitEchoPinLow(clockMax, pin);
  
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

>>>>>>> d2886adf21b18a961cbba0d276fd7f84b6b3fd39
  pinMode(leftEnable, OUTPUT);
  pinMode(leftLogicPinOne, OUTPUT);
  pinMode(leftLogicPinTwo, OUTPUT);

<<<<<<< HEAD
}
 
void loop() {
  travel_forward();
  calculate_front();
  Serial.print(cm);
  Serial.print("frontcm, ");
  if (cm >= 10) 
    {
      travel_forward();
    }
    else
    {
      brake();
      calculate_left();
      Serial.print(cm);
      Serial.print("frontcm, ");
      Serial.print(leftcm);
      Serial.print("leftcm, ");
      if(leftcm>=10)
        {
          turn_left();
          delay(2000);
          travel_forward();
        }
        else
        {
          calculate_right();
          if(rightcm>=10)
            {
              turn_right();
              delay(10000);
              travel_forward();
            }
            else
            {
              travel_backwards();
              if(leftcm>=10)
              {
                brake();
                turn_left();
                delay(10000);
                travel_forward();
              }
            }
          }
       }
}

void calculate_front(){

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
=======
  Serial.print("Left Motor Pin 1 = ");
  Serial.println(leftLogicPinOne);
>>>>>>> d2886adf21b18a961cbba0d276fd7f84b6b3fd39

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  cm = (duration/2)*0.0343;
}

<<<<<<< HEAD
void calculate_left(){

  digitalWrite(lefttrigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(lefttrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(lefttrigPin, LOW);
 
  pinMode(leftechoPin, INPUT);
  durationleft = pulseIn(leftechoPin, HIGH);
 
  leftcm = (durationleft/2)*0.0343;
}

void calculate_right(){
  
  digitalWrite(righttrigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(righttrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(righttrigPin, LOW);
 
  pinMode(rightechoPin, INPUT);
  durationright = pulseIn(rightechoPin, HIGH);
 
  rightcm = (durationright/2)*0.0343;
}

void travel_forward(){
  digitalWrite(leftLogicPinOne, HIGH);
  digitalWrite(leftLogicPinTwo, LOW);
=======
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
>>>>>>> d2886adf21b18a961cbba0d276fd7f84b6b3fd39
  digitalWrite(rightLogicPinOne, HIGH);
  digitalWrite(rightLogicPinTwo, LOW);
}

<<<<<<< HEAD
void travel_backwards(){
  digitalWrite(leftLogicPinOne, LOW);
  digitalWrite(leftLogicPinTwo, HIGH);
=======
void leftSideBackward(){
  digitalWrite(leftLogicPinOne, LOW);
  digitalWrite(leftLogicPinTwo, HIGH);
}

void rightSideBackward() {
>>>>>>> d2886adf21b18a961cbba0d276fd7f84b6b3fd39
  digitalWrite(rightLogicPinOne, LOW);
  digitalWrite(rightLogicPinTwo, HIGH);
}

<<<<<<< HEAD
void turn_left(){
  digitalWrite(leftLogicPinOne, LOW);
  digitalWrite(leftLogicPinTwo, HIGH);
=======
void rightSideBrake() {
>>>>>>> d2886adf21b18a961cbba0d276fd7f84b6b3fd39
  digitalWrite(rightLogicPinOne, HIGH);
  digitalWrite(rightLogicPinTwo, LOW);
}

<<<<<<< HEAD
void turn_right(){
  digitalWrite(rightLogicPinOne, LOW);
  digitalWrite(rightLogicPinTwo, HIGH);
  digitalWrite(leftLogicPinOne, HIGH);
  digitalWrite(leftLogicPinTwo, LOW);
}

void brake(){
  digitalWrite(leftLogicPinOne, HIGH);
  digitalWrite(leftLogicPinTwo, HIGH);
  digitalWrite(rightLogicPinOne, HIGH);
  digitalWrite(rightLogicPinTwo, HIGH);
=======
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
>>>>>>> d2886adf21b18a961cbba0d276fd7f84b6b3fd39
}