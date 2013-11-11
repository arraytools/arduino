// http://thoughtfix.com/blog/2012/3/25/arduino-boe-shield-ping-and-a-servo.html
// BOE Shield code from "Robotics with the BOE Bot"
// Roaming With Whiskers source, modified to use a PING)))
// sensor on the PING))) servo bracket.
// Using code from the Ping))) example sketch.

#include <Servo.h>                           // Include servo library
Servo servoLeft;                             // Declare left, right and Ping))) servos
Servo servoRight;
Servo PingServo;
int minSafeDist = 11 ;                        // Minimum distance in inches
int pingPin = 10;                             // PING input on 10 so the last servo port is used.
int centerDist, leftDist, rightDist;          // Define distance variables
long duration, inches, cm;                    // Define variables for Ping)))


void setup()                                 // Built-in initialization block
{ 
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone
  servoLeft.attach(13);                      // Attach left signal to pin 13 
  servoRight.attach(12);                     // Attach right signal to pin 12
  PingServo.attach(11);
}  

void loop(){
  LookAhead();
  if(inches >= minSafeDist) /* If the inches in front of an object is greater than or equal to the minimum safe distance (11 inches), react*/
  {
    forward (121); //Go Forward
    delay(110); // Wait 0.11 seconds
  }
  else // If not:
  {
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);
    LookAround(); // Check your surroundings for best route
    if(rightDist > leftDist) // If the right distance is greater than the left distance , turn right
    {
      turnRight (250); // Turn Right      
    }
    else if (leftDist > rightDist) // If the left distance is greater than the right distance , turn left
    {
      turnLeft (250); // Turn Left
    }
    else
    {
      backward (250); // Go Backward
    }
    delay (250);
  }
}

void forward(int time)                       // Forward function
{
  servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1300);        // Right wheel clockwise
  delay(time);                               // Maneuver for time ms
}

void turnLeft(int time)                      // Left turn function
{
  servoLeft.writeMicroseconds(1300);         // Left wheel clockwise
  servoRight.writeMicroseconds(1300);        // Right wheel clockwise
  delay(time);                               // Maneuver for time ms
}

void turnRight(int time)                     // Right turn function
{
  servoLeft.writeMicroseconds(1700);         // Left wheel counterclockwise
  servoRight.writeMicroseconds(1700);        // Right wheel counterclockwise
  delay(time);                               // Maneuver for time ms
}

void backward(int time)                      // Backward function
{
  servoLeft.writeMicroseconds(1300);         // Left wheel clockwise
  servoRight.writeMicroseconds(1700);        // Right wheel counterclockwise
  delay(time);                               // Maneuver for time ms
}

unsigned long ping() {
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW); //Send a low pulse
  delayMicroseconds(2); // wait for two microseconds
  digitalWrite(pingPin, HIGH); // Send a high pulse
  delayMicroseconds(5); // wait for 5 micro seconds
  digitalWrite(pingPin, LOW); // send a low pulse
  pinMode(pingPin,INPUT); // switch the Pingpin to input
  duration = pulseIn(pingPin, HIGH); //listen for echo
  /*Convert micro seconds to Inches
   -------------------------------------*/
  cm = microsecondsToCentimeters(duration);
  inches = microsecondsToInches(duration);
}

long microsecondsToInches(long microseconds) // converts time to a distance
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) // converts time to a distance
{
  return microseconds / 29 / 2;
}

void LookAhead() {
  PingServo.write(90);// angle to look forward
  delay(175); // wait 0.175 seconds
  ping();
}

void LookAround(){
  PingServo.write(20); // 20° angle
  delay(320); // wait 0.32 seconds
  ping();
  rightDist = inches; //get the right distance
  PingServo.write(160); // look to the other side
  delay(620); // wait 0.62 seconds
  ping(); 
  leftDist = inches; // get the left distance
  PingServo.write(90); // 90° angle
  delay(275); // wait 0.275 seconds
}
