///////////libarry//////////
#include <Servo.h>
#include <Stepper.h>
#include <SoftwareSerial.h>
/////////////variable/////////
char command = 0;
int speedR = 90;
int speedL = 90;
unsigned char speed_limit = 200;

// camera

int pos =0;
int limit = 91;
const int stepsPerRevolution = 200;


///////////////////define
#define mlb  8
#define mrb  9

#define laser 24
bool status = 0;


int trigPin = 12;
int echoPin = 13;




//  IN1-IN3-IN2-IN4 
Stepper camera_step = Stepper(stepsPerRevolution, 8, 10, 9, 11);
Servo camera_servo;   

int t = 0 , s = 2;
int duration  , distance;

void motor(int left, int right, int time) {
  //////////right/////////
  if (right < 0) {
    analogWrite(2, -right);
    analogWrite(3, 0);
  } else {
    analogWrite(2, 0);
    analogWrite(3, right);
  }

  /////////left////////
  if (left < 0) {
    analogWrite(4, -left);
    analogWrite(5, 0);
  } else {
    analogWrite(4, 0);
    analogWrite(5, left);
  }
  delay(time);
}






void setup() {
  
  Serial.begin(9600);
  /////////////////srf front////////////
  pinMode(trigPin, OUTPUT);
  // Set the echo pin as INPUT
  pinMode(echoPin, INPUT);

  ////////////pinMode/////////
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  ////////////microw/////////
  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  ////////////////

  pinMode(laser,OUTPUT);
  //_______________CAMERA_____________
  camera_servo.attach(22);
}
void conntrol()
{
  while (Serial.available() > 0) {
    command = Serial.read();
   

    
   //_____________CAMERA_____________ 
   // step
   if(command == 'l'){
      camera_step.setSpeed(30);
	    camera_step.step(stepsPerRevolution);
      delay(150);
   }
   else if(command == 'r'){
       camera_step.setSpeed(30);
	    camera_step.step(-stepsPerRevolution);
      delay(150);
   }
   // servo
   else if(command == 'u'){
      
      if(pos < limit){
            pos = pos + 5;
      }
      camera_servo.write(pos); 
      delay(15);
   }
   else if(command == 'd'){
    if(pos > 0){
            pos = pos - 5;
      }
      camera_servo.write(pos);
      delay(15); 
   }
   else if(command == '*'){
       
      digitalWrite(laser,1); 
      delay(1000);
      digitalWrite(laser,0); 
   }

   //_____________DISTANCE CONTROL_____________ 
   //  TIME
    if(command == '+'){
      t += 100;
      Serial.print("TIME = ");
      Serial.println(t);
      if(t>3000){
        t = 0;
        Serial.println("TIME RESETTED");
      }
    }
    else if(command == '-'){
      t -= 100;
      Serial.print("TIME = ");
      Serial.println(t);
      if(t<0){
        t = 0;
        Serial.println("TIME RESETTED");
      }
    }




 //_____________Forward_____________
    if (command == 'F') {
      if(distance > 10){
      motor(speedL ,speedR,0);
      delay(t);
        }
    }
    //motor(-speedL,-speedR,0);
 //_____________Backward_____________
    else if (command == 'B') {
      motor(-speedL,-speedR,0);
      delay(t);
    }
    

    //_____________LEFT_____________
    else if (command == 'L') {
      motor(-200,200,0);
      delay(t);
    }
    //_____________RIGHT_____________
    else if (command == 'R') {
      motor(200,-200,0);
      delay(t);
    }
    
   motor(0,0,0);

   
    } // WHILE



}

int calculateDistance(){ 
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
  return distance;
}

void loop() 
{
  
conntrol();  
digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.034/2;
 

    
}  




