int pinI1=8;//define I1 interface
int pinI2=11;//define I2 interface
int speedpinA=9;//enable motor A
int pinI3=12;//define I3 interface
int pinI4=13;//define I4 interface
int steerpinB=10;//enable motor B
int speed_drive =420;//define the speed of drive motor
int speed_steer =1524;//define the speed of steering motor
const int pingPin_R = 7;//sets the pin for the PING sensor on the right side of the car
const int pingPin_C = 6;//sets the pin for the PING sensor in the center side of the car
const int pingPin_L = 5;//sets the pin for the PING sensor on the left side of the car
long duration_C, inches_C,duration_R, inches_R,duration_L, inches_L;
 
void setup()
{
  pinMode(pinI1,OUTPUT);
  pinMode(pinI2,OUTPUT);
  pinMode(speedpinA,OUTPUT);
  pinMode(pinI3,OUTPUT);
  pinMode(pinI4,OUTPUT);
  pinMode(steerpinB,OUTPUT);
}
 
void loop()
{
  int i;
  int j = 1;
  delay(5000);
  for(i=0; i<1; i*1){
  j++;
  getping_all();


//all clear, no obstacles within 30" in any direction
  if(inches_C >= 30 && inches_R >= 30 && inches_L >= 30)
  {
   forward();
  }
 
//obstacle(s) within 0-6" range
  else if (inches_L < 6 || inches_C < 6 || inches_R < 6)
  {
   stop();
   backward();
   delay(1500);
   stop();
     if(j%3 == 0){ //This if/else statement is designed to build a little "randomness"
     back_right(); //into the robot's movements, so it is less likely to become stuck
     back_right(); //in a loop, performing the same actions over and over which only.
     left();
     j=1;
     }
   else{
     back_left();
     back_left();
     right();
     }
  }
 
//obstacle(s) within 6"-12" range
 
  //obstacle on left and center and right
  else if (inches_R < 12 && inches_C < 12 && inches_L < 12)
  {
   stop();
   backward();
   delay(1500);
   back_left();
   stop();
   right();
   forward();
  }
  //obstacle on center OR left and right
  else if (inches_L >= 12 && inches_R >= 12 && inches_C < 12 ||
            inches_C >= 12 && inches_R < 12 && inches_L < 12)
  {
   stop();
   backward();
   delay(1500);
   back_left();
   stop();
   right();
   forward();
  }
  //obstacle on left and center
  else if (inches_R >= 12 && inches_C < 12 && inches_L < 12)
  {
   stop();
   backward();
   delay(1500);
   back_left();
  }
  //obstacle on right and center
  else if (inches_L >= 12 && inches_C < 12 && inches_R < 12)
  {
   stop();
   backward();
   delay(1500);
   back_right();
  }
  //obstacle on right
  else if (inches_L >= 12 && inches_C >= 12 && inches_R < 12)
  {
   left();
   left();
   
  }
  //obstacle on left
  else if (inches_R >= 12 && inches_C >= 12 && inches_L < 12)
  {
   right();
   right();
  }
 
//obstacle(s) within 12"-30" range
 
  //obstacle on left and center
  else if (inches_R >= 30 && inches_C < 30 && inches_L < 30)
  {
   right();
   right();
  }
  //obstacle on right and center
  else if (inches_L >= 30 && inches_C < 30 && inches_R < 30)
  {
   left();
   left();
  }
  //obstacle on right and left
  else if (inches_C >= 30 && inches_L < 30 && inches_R < 30)
  {
   forward();
  }
  //obstacle on right
  else if (inches_L >= 30 && inches_C >= 30 && inches_R < 30)
  {
   left();
  }
  //obstacle on left
  else if (inches_R >= 30 && inches_C >= 30 && inches_L < 30)
  {
   right();
  }
  //obstacle on center
  else if (inches_L >= 30 && inches_R >= 30 && inches_C < 30)
  {
   if(j % 2 == 0){
     left();
     j=1;
   }
   else{
     right();
    }
  }  
  }
}
 
void forward()
{// turns on drive motor in forward and leaves it on
     analogWrite(speedpinA,speed_drive);//inputs speed_drive value to set the speed
     digitalWrite(pinI2,LOW);//turn DC Motor A move anticlockwise
     digitalWrite(pinI1,HIGH);
}
void backward()//
{// turns on drive motor in reverse and leaves it on
     analogWrite(speedpinA,speed_drive);//inputs speed_drive value to set the speed
     digitalWrite(pinI2,HIGH);//turn DC Motor A move clockwise
     digitalWrite(pinI1,LOW);
}
void right()//
{
     analogWrite(steerpinB,speed_steer);
     digitalWrite(pinI4,HIGH);//turn DC Motor B move clockwise
     digitalWrite(pinI3,LOW);
     forward();
     delay(300);
     analogWrite(steerpinB,LOW);
}
void back_left()//
{
     analogWrite(steerpinB,speed_steer);
     digitalWrite(pinI4,HIGH);//turn DC Motor B move clockwise
     digitalWrite(pinI3,LOW);
     delay(250);
     backward();
     delay(500);
     stop();
     delay(250);
}
void left()//
{
     analogWrite(steerpinB,speed_steer);
     digitalWrite(pinI4,LOW);//turn DC Motor B move anticlockwise
     digitalWrite(pinI3,HIGH);
     forward();
     delay(300);
     analogWrite(steerpinB,LOW);
}
void back_right()//
{
     analogWrite(steerpinB,speed_steer);
     digitalWrite(pinI4,LOW);//turn DC Motor B move anticlockwise
     digitalWrite(pinI3,HIGH);
     delay(250);
     backward();
     delay(500);
     stop();
     delay(250);
}
void stop()//stop both motors
{
     digitalWrite(speedpinA,LOW);// Unenble the pin, to stop the motor. 
     digitalWrite(steerpinB,LOW);// Unenble the pin, to stop the motor.
}
 void getping_C()//get distance from center PING
{
      pinMode(pingPin_C, OUTPUT);
      digitalWrite(pingPin_C, LOW);
      delayMicroseconds(2);
      digitalWrite(pingPin_C, HIGH);
      delayMicroseconds(5);
      digitalWrite(pingPin_C, LOW);
      pinMode(pingPin_C, INPUT);
      duration_C = pulseIn(pingPin_C, HIGH);
      inches_C = microsecondsToInches(duration_C);
}
 void getping_R()//get distance from right PING
{
      pinMode(pingPin_R, OUTPUT);
      digitalWrite(pingPin_R, LOW);
      delayMicroseconds(2);
      digitalWrite(pingPin_R, HIGH);
      delayMicroseconds(5);
      digitalWrite(pingPin_R, LOW);
      pinMode(pingPin_R, INPUT);
      duration_R = pulseIn(pingPin_R, HIGH);
      inches_R = microsecondsToInches(duration_R);
}
 void getping_L()//get distance from left PING
{
      pinMode(pingPin_L, OUTPUT);
      digitalWrite(pingPin_L, LOW);
      delayMicroseconds(2);
      digitalWrite(pingPin_L, HIGH);
      delayMicroseconds(5);
      digitalWrite(pingPin_L, LOW);
      pinMode(pingPin_L, INPUT);
      duration_L = pulseIn(pingPin_L, HIGH);
      inches_L = microsecondsToInches(duration_L);
}
  void getping_all()
{
  getping_C();
  delay(2);
  getping_R();
  delay(2);
  getping_L();
  delay(2);
}
  long microsecondsToInches(long microseconds){
    return microseconds / 74 / 2;}

/* The above converts the time of the return to inches as explained here: <a href="http://learn.parallax.com/kickstart/28015" rel="nofollow">http://learn.parallax.com/kickstart/28015
</a>*/
