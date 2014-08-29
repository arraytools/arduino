/*
Arduino driver for Android app remote control.
This sketch listens to instructions on the Serial port
then activates motors as required
Then sends back confirmation to the app

Motor shield DFRduino 1A based on L239B
Pin 	        Function
Digital 3 	Motor 1 PWM control
Digital 12 	Motor 1 Direction control 
Digital 11 	Motor 2 PWM control
Digital 13 	Motor 2 Direction control
 */

int const PWMA = 3; 
int const PWMB = 11; 
int const dirA = 12; 
int const dirB = 13; 


void setup() {
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(dirA, OUTPUT);  
  pinMode(dirB, OUTPUT);
  
  //initial set up straight forward, no speed
  digitalWrite(dirA, HIGH);
  digitalWrite(dirB, HIGH);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  
  Serial.begin(9600); 
}

void loop() {
  
  // see if there's incoming serial data:
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    int incomingByte = Serial.read();
    
    // action depending on the instruction
    // as well as sending a confirmation back to the app
    switch (incomingByte) {
      case 'F':
        moveForward(255, true);
        Serial.println("Going forward");
        break;
      case 'R':
        turn(255, true);
        Serial.println("Turning right");
        break;
      case 'L':
        turn(255, false);
        Serial.println("Turning left");
        break;
      case 'B':
        moveForward(255, false);
        Serial.println("Going backwards");
        break;
      case 'S':
        moveForward(0, true);
        Serial.println("Stopping");
        break;
      default: 
        // if nothing matches, do nothing
        break;
    }
  }
}

void moveForward(int speedBot, boolean forward){
//boolean forward controls motor direction
  if (forward){
      digitalWrite(dirA, HIGH);
      digitalWrite(dirB, HIGH);
    }
    else{
      digitalWrite(dirA, LOW);
      digitalWrite(dirB, LOW);
    }
    analogWrite(PWMA, speedBot);
    analogWrite(PWMB, speedBot);

}

void turn(int speedBot, boolean right){
  //boolean right controls motor direction
    if (right){
      digitalWrite(dirA, HIGH);
      digitalWrite(dirB, LOW);
    }
    else{
      digitalWrite(dirA, LOW);
      digitalWrite(dirB, HIGH);
    }
    analogWrite(PWMA, speedBot);
    analogWrite(PWMB, speedBot);
}

