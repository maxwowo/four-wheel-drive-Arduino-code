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
int frontBackPwm = 255;
 
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
  
  if (cm >= 25) 
    {
      travel_forward();
    }
    else {
        brake();
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

void travel_forward(){ 
  analogWrite(rightEnable,frontBackPwm);
  analogWrite(leftEnable, frontBackPwm);
  digitalWrite(leftLogicPinOne, HIGH);
  digitalWrite(leftLogicPinTwo, LOW);
  digitalWrite(rightLogicPinOne, HIGH);
  digitalWrite(rightLogicPinTwo, LOW);
}

void brake(){
  digitalWrite(leftLogicPinOne, HIGH);
  digitalWrite(leftLogicPinTwo, HIGH);
  digitalWrite(rightLogicPinOne, HIGH);
  digitalWrite(rightLogicPinTwo, HIGH);
}

