#include <SoftwareSerial.h>
#include <Servo.h>
#include <NewPing.h>

SoftwareSerial espSerial(2, 3);//Rx, Tx pin

//our L298N control pins
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 5;
const int RightMotorBackward = 4;

//sensor pins
#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2

//lighting system 
int backled= 12;

#define maxDistance 150//Max distance value
#define maxBackDistance 200
int backDistance=100;

//boolean goesForward = false;
int angle=0, distance=0; //Angle value, Distance Value

NewPing sonar(trig_pin, echo_pin, maxBackDistance); //sensor function
Servo servo_motor; //our servo name

void setup() {
  Serial.begin(115200);
  espSerial.begin(115200);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  pinMode(backled, OUTPUT);
  servo_motor.attach(10);
  servo_motor.write(90);

}

void loop() {
  backDistance = readPing();
//  Serial.println(backDistance);
//  delay(1000);
  if (espSerial.available()) {
    String data = espSerial.readStringUntil('\n');
    data.trim();

    // Extract individual values from the received string
    int commaIndex = data.indexOf(",");
    if (commaIndex != -1) {
      String value1String = data.substring(0, commaIndex);
      String value2String = data.substring(commaIndex + 1);

      //Convert the extracted strings to integers
      angle = value1String.toInt();//Angle value
      distance = value2String.toInt();//Distance

    if(angle>=0 && angle<=180){
      if(angle>=85 && angle<=95){
        servo_motor.write(90);
        if(distance>=145 && distance<=155){
        moveStop();
        }
      else if(distance >= 156){
        int delY = (distance - 155)*(3/5.5);
        int y =delY *500/30;
        moveForward();
        delay(y);
        }
        else{
          int delY = (145-distance)*(3/5.5);
          int y =delY *500/30;
          if(backDistance<=30){
            moveStop();
            delay(200);
            }
          else{
            moveBackward();
            delay(y);
            }
          }
       }
      //Turn left code
      else if(angle>95 && angle<=180){
        int newAngle = angle-90;
        int x = (500*newAngle)/90;
        servo_motor.write(angle);
        digitalWrite(LeftMotorBackward, HIGH);
        digitalWrite(RightMotorForward, HIGH);
        digitalWrite(LeftMotorForward, LOW);
        digitalWrite(RightMotorBackward, LOW);
        delay(x);
        digitalWrite(LeftMotorForward, LOW);//Forward mode off
        digitalWrite(RightMotorForward, LOW);//Forward mode off
        digitalWrite(LeftMotorBackward, LOW);
        digitalWrite(RightMotorBackward, LOW);
        //Distance value execute
        if(distance>=145 && distance<=155){
          moveStop();
          delay(200);
          }
        else if(distance >= 156){
          int delY = (distance - 155)*(3/5.5);
          int y =delY *500/30;
          moveForward();
          delay(y);
          }
        else{
          int delY = (145-distance)*(3/5.5);
          int y =delY *500/30;
          if(backDistance<=30){
            moveStop();
            delay(200);
            }
           else{
            moveBackward();
            delay(y);
            }
          }
        }
      //Turn right code
      else if(angle<85 && angle>=0){
        int newAngle = 90 - angle;
        int x = (500*newAngle)/90;
        servo_motor.write(angle);
        digitalWrite(LeftMotorForward, HIGH);
        digitalWrite(RightMotorBackward, HIGH);
        digitalWrite(LeftMotorBackward, LOW);
        digitalWrite(RightMotorForward, LOW);
        delay(x);
        digitalWrite(LeftMotorForward, LOW);//Forward mode off
        digitalWrite(RightMotorForward, LOW);//Forward mode off
        digitalWrite(LeftMotorBackward, LOW);
        digitalWrite(RightMotorBackward, LOW);
        //Distance value execute
        if(distance>=145 && distance<=155){
          moveStop();
          delay(200);
          } 
        else if(distance >= 156){
            int delY = (distance - 155)*(3/5.5);
            int y =delY *500/30;
            moveForward();
            delay(y);
            }
          else{
            int delY = (145-distance)*(3/5.5);
            int y =delY *500/30;
            if(backDistance<=30){
              moveStop();
              delay(200);
              }
            else{
              moveBackward();
              delay(y);
              }
            }
          }
        }
      }
    }
  else{
    moveStop();
  }
}
void moveForward(){
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW); 
}
void moveStop(){
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}
void moveBackward(){
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
}
int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}
