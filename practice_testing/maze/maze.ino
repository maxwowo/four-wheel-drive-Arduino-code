int trigPin = 10;    // Define Trigger pins
int lefttrigPin= 8;
int righttrigPin= 7;

int echoPin = A5;    // Define Echo pins
int leftechoPin=A4;
int rightechoPin=A3;

int leftEnable = 6;   // Define Left side motors
int leftLogicPinOne = A2;
int leftLogicPinTwo = 3;

int rightEnable = 5;    //Define right side motors
int rightLogicPinOne = 11;
int rightLogicPinTwo = 9;

long duration, cm, leftcm,durationleft,rightcm,durationright;
int currentdirection,s,f,b;

int turnDelay = 350;
int frontBackPwm = 100;
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
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
  pinMode(leftEnable, OUTPUT);
  pinMode(leftLogicPinOne, OUTPUT);
  pinMode(leftLogicPinTwo, OUTPUT);

  //set all varibles to 0
  cm=0;
  rightcm=0;
  leftcm=0;
  currentdirection = s;
  delay(2000);
}
 
void loop() {
  calculate_front();
  calculate_right();
  calculate_left();
  
  if (cm >= 25 && currentdirection == s) 
    {
      travel_forward();
      currentdirection=f;
    }
  else if (cm <= 24 && leftcm > rightcm && currentdirection == f)
    {
      brake();
      turn_left();
      delay(turnDelay);
      brake();
      delay(1000);
    }
  else if (cm <= 24 && rightcm > leftcm && currentdirection == f)
    {
      brake();
      turn_right();
      delay(turnDelay);
      brake();
      delay(1000);
    }
  else if (leftcm <= 30 && rightcm <= 30 && cm <= 30 && currentdirection == f)
    {
      travel_backwards();
      calculate_left();
      calculate_right();
      currentdirection = b;
      if (rightcm>= 25  && currentdirection == b)
          {
           brake();
           Serial.print("braking ");
           turn_left();
           delay(turnDelay);
           brake();
           Serial.print("travel backwards left ");
          }
      else if (leftcm>=25 && currentdirection == b)
          {
          brake();
          turn_right();
          delay(turnDelay);
          brake();
          }
     }
}

 
void calculate_front(){

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  cm = (duration/2)*0.0343;
}

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
  analogWrite(rightEnable,frontBackPwm);
  analogWrite(leftEnable, frontBackPwm);
  digitalWrite(rightEnable,HIGH);
  digitalWrite(leftEnable,HIGH);
  digitalWrite(leftLogicPinOne, HIGH);
  digitalWrite(leftLogicPinTwo, LOW);
  digitalWrite(rightLogicPinOne, HIGH);
  digitalWrite(rightLogicPinTwo, LOW);
}

void travel_backwards(){
  analogWrite(rightEnable,frontBackPwm);
  analogWrite(leftEnable, frontBackPwm);
  digitalWrite(rightEnable,HIGH);
  digitalWrite(leftEnable,HIGH);
  digitalWrite(leftLogicPinOne, LOW);
  digitalWrite(leftLogicPinTwo, HIGH);
  digitalWrite(rightLogicPinOne, LOW);
  digitalWrite(rightLogicPinTwo, HIGH);
}

void turn_left(){
  analogWrite(rightEnable,255);
  analogWrite(leftEnable,255);
  digitalWrite(rightEnable,HIGH);
  digitalWrite(leftEnable,HIGH);
  digitalWrite(leftLogicPinOne, LOW);
  digitalWrite(leftLogicPinTwo, HIGH);
  digitalWrite(rightLogicPinOne, HIGH);
  digitalWrite(rightLogicPinTwo, LOW);
}

void turn_right(){
  analogWrite(rightEnable,255);
  analogWrite(leftEnable,255);
  digitalWrite(rightEnable,HIGH);
  digitalWrite(leftEnable,HIGH);
  digitalWrite(rightLogicPinOne, LOW);
  digitalWrite(rightLogicPinTwo, HIGH);
  digitalWrite(leftLogicPinOne, HIGH);
  digitalWrite(leftLogicPinTwo, LOW);
}

void brake(){
  
  analogWrite(rightEnable,255);
  analogWrite(leftEnable,255);
  digitalWrite(rightEnable,HIGH);
  digitalWrite(leftEnable,HIGH);
  digitalWrite(leftLogicPinOne, HIGH);
  digitalWrite(leftLogicPinTwo, HIGH);
  digitalWrite(rightLogicPinOne, HIGH);
  digitalWrite(rightLogicPinTwo, HIGH);
}

