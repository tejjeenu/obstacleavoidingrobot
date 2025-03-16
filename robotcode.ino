#include <AFMotor.h>   //Download and Install AFMotor.h Library

AF_DCMotor motor1(1); 
AF_DCMotor motor2(2);
AF_DCMotor motor3(3); 
AF_DCMotor motor4(4); 

int trigpin = 2;
int echopin = A0;
int pingtraveltime;
int distance;
String directions[] = {"left", "right"};

int motorspeed = 100;
int stoppingdelay = 2000;
String readString;

void setup() {
  Serial.begin(9600);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  motor1.setSpeed(motorspeed);   //Set Motor Speed
  motor2.setSpeed(motorspeed);
  motor3.setSpeed(motorspeed + 20);
  motor4.setSpeed(motorspeed + 20);
}

void sendbeam(){
   digitalWrite(trigpin, LOW);
   delayMicroseconds(10);
   digitalWrite(trigpin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigpin, LOW);
   pingtraveltime = pulseIn(echopin, HIGH);
   delay(25);
   distance = (pingtraveltime * 0.034) / 2;
}

void Forward(){
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
}


void rotateright(int del){
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
    delay(del);
    Stop(500);  
}

void rotateleft(int del){
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
    delay(del);
    Stop(500);  
}

void tiltright(int del){
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
    delay(del);
    Stop(500);
}

void tiltleft(int del){
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
    delay(del);
    Stop(500);
}

void Stop(int del){
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    delay(del);
}

void choosedirection(String dir, int del){
  if(dir == "left")
  {
    rotateleft(del);
  }

  if(dir == "right")
  {
    rotateright(del);
  }
}


void avoidancesequence(){
    tiltleft(800);
    sendbeam();
    int leftdistance = distance;
    tiltright(800); 

    tiltright(800);
    sendbeam();
    int rightdistance = distance;
    tiltleft(800);

    if(leftdistance >= 100 and rightdistance >= 100){
        String randomdir = directions[random(0,1)];
        int randomdelay = random(400, 501);
        choosedirection(randomdir, randomdelay);
    }
     
    else if(leftdistance <= 30 and rightdistance <= 30){
        String randomdir = directions[random(0,1)];
        int randomdelay = random(790, 811);
        choosedirection(randomdir, randomdelay);
    }

    else if(leftdistance > rightdistance){
        String dir = "left";
        int randomdelay = random(400, 501);
        choosedirection(dir, randomdelay);
    }

    else if(leftdistance < rightdistance){
        String dir = "right";
        int randomdelay = random(400, 501);
        choosedirection(dir, randomdelay);
    }
    
    else if(leftdistance = rightdistance){
        String randomdir = directions[random(0,1)];
        int randomdelay = random(400, 501);
        choosedirection(randomdir, randomdelay);
    }
}

void loop()
{
   digitalWrite(trigpin, LOW);
   delayMicroseconds(10);
   digitalWrite(trigpin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigpin, LOW);
   pingtraveltime = pulseIn(echopin, HIGH);
   delay(25);
   distance = (pingtraveltime * 0.034) / 2;
   //Serial.println(distance);
   if(distance <= 20){
      Stop(3000);
      avoidancesequence();
   }
   Forward();
}
