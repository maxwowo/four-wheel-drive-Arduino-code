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
  pinMode(leftEnable, OUTPUT);
  pinMode(leftLogicPinOne, OUTPUT);
  pinMode(leftLogicPinTwo, OUTPUT);

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
  digitalWrite(leftLogicPinOne, HIGH);
  digitalWrite(leftLogicPinTwo, LOW);
  digitalWrite(rightLogicPinOne, HIGH);
  digitalWrite(rightLogicPinTwo, LOW);
}

void travel_backwards(){
  digitalWrite(leftLogicPinOne, LOW);
  digitalWrite(leftLogicPinTwo, HIGH);
  digitalWrite(rightLogicPinOne, LOW);
  digitalWrite(rightLogicPinTwo, HIGH);
}

void turn_left(){
  digitalWrite(leftLogicPinOne, LOW);
  digitalWrite(leftLogicPinTwo, HIGH);
  digitalWrite(rightLogicPinOne, HIGH);
  digitalWrite(rightLogicPinTwo, LOW);
}

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
}