// Assuming Arduino Mega

#include <ServoInput.h>
ServoInputPin<18> ch1; // Forward and Backward: 0 to 255
ServoInputPin<19> ch2; // Right and Left : -100 to 100 
ServoInputPin<20> ch3; // Drum ON/OFF (Need to get range)
ServoInputPin<21> ch4;

#define Motor_1_Direction 8 // Motor 1: Right Motor
#define Motor_1_Speed 9
#define Motor_2_Direction 4 // Motor 2: Left Motor
#define Motor_2_Speed 5


#define Drum_Relay 7 // Drum Motor

int SpeedVal = 0;
 
void setup() {
 Serial.begin(115200);

  pinMode(Motor_1_Direction, OUTPUT);
  pinMode(Motor_1_Speed, OUTPUT);
  pinMode(Motor_2_Direction, OUTPUT);
  pinMode(Motor_2_Speed, OUTPUT);
  pinMode(Drum_Relay, OUTPUT);
  


}
 

void loop() {
  const float Deadzone = 0.15;  // 15%
  int speed = ch1.mapDeadzone(-255, 255, Deadzone);
  int dir = ch2.mapDeadzone(-100, 100, Deadzone);
  if(speed > 0) {
    Serial.print("Forward ");
    Serial.print(speed);
    Serial.println("%");
    // motors movement
    analogWrite(Motor_1_Speed, 0);
    analogWrite(Motor_2_Speed, 0);
    //Ramps up the speed in the clockwise direction.
    digitalWrite(Motor_1_Direction, LOW);
    digitalWrite(Motor_2_Direction, LOW);

      analogWrite(Motor_1_Speed, speed);
      analogWrite(Motor_2_Speed, speed);
      delay(10);
    
  }

   if(speed < 0) {
    Serial.print("Backward");
    Serial.print(speed);
    Serial.println("%");
    // motors movement
    analogWrite(Motor_1_Speed, 0);
    analogWrite(Motor_2_Speed, 0);
    //Ramps up the speed in the anticlockwise direction.
    digitalWrite(Motor_1_Direction, HIGH);
    digitalWrite(Motor_2_Direction, HIGH);
 
 for (SpeedVal = 0; SpeedVal < 255; SpeedVal++) {
      analogWrite(Motor_1_Speed, SpeedVal);
      analogWrite(Motor_2_Speed, SpeedVal);
      delay(1);
  }
   }
  else {
    Serial.print("Not Forward or Backward");
  }


  if(dir > 0)  //Right
    {
    Serial.println("Right");
    analogWrite(Motor_1_Speed, 0);
    analogWrite(Motor_2_Speed, 0);
    //Ramps up the speed in the counter clockwise direction.
    digitalWrite(Motor_1_Direction, HIGH); // Right Back
    digitalWrite(Motor_2_Direction, LOW); // Left Forward
    //Loop increases the speed slowly until it reaches max speed.
    for (SpeedVal = 0; SpeedVal < 255; SpeedVal++) {
      analogWrite(Motor_1_Speed, SpeedVal);
      analogWrite(Motor_2_Speed, SpeedVal);
      delay(1);
    }
  }

  if(dir < 0)  //Right
  {
    Serial.println("Left");
    analogWrite(Motor_1_Speed, 0);
    analogWrite(Motor_2_Speed, 0);
    //Ramps up the speed in the counter clockwise direction.
    digitalWrite(Motor_1_Direction, LOW); // Right Forward
    digitalWrite(Motor_2_Direction, HIGH); // Left backward
    //Loop increases the speed slowly until it reaches max speed.
    for (SpeedVal = 0; SpeedVal < 255; SpeedVal++) {
      analogWrite(Motor_2_Speed, SpeedVal);
      analogWrite(Motor_1_Speed, SpeedVal);
      delay(1);
    }
  }  
  
  else 
  {
    Serial.println(" Not Left Or Right");
  }

  
}
