// MC Li EMF Detector Nov 9, 2013

int inPin = 5;          // analog 5
int val = 0;            // where to store info from analog 5
int pin11 = 11;         // output of red led

byte seven_seg_digits[10][7] = { { 1,1,1,1,1,1,0 },  // = 0
                                 { 0,1,1,0,0,0,0 },  // = 1
                                 { 1,1,0,1,1,0,1 },  // = 2
                                 { 1,1,1,1,0,0,1 },  // = 3
                                 { 0,1,1,0,0,1,1 },  // = 4
                                 { 1,0,1,1,0,1,1 },  // = 5
                                 { 1,0,1,1,1,1,1 },  // = 6
                                 { 1,1,1,0,0,0,0 },  // = 7
                                 { 1,1,1,1,1,1,1 },  // = 8
                                 { 1,1,1,0,0,1,1 }   // = 9
                                 };
                                                           
void setup() { 
  pinMode(2, OUTPUT);  // specify Display outputs
  pinMode(3, OUTPUT); 
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT); 
  pinMode(7, OUTPUT); 
  pinMode(8, OUTPUT); 
  writeDot(0);  // start with the "dot" off
}

void writeDot(byte dot) {
  digitalWrite(9, dot);
}

void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, 1 - seven_seg_digits[digit][segCount]);
    ++pin;
  }
}

void loop() {
 
//  val = analogRead(inPin);          // reads in the values from analog 5 and
//  Serial.println(val);               // use output to aid in calibrating                                 //assigns them to val
//  if(val >= 1){
//   
//    val = constrain(val, 1, 100);   // mess with these values                                      
//    val = map(val, 1, 100, 1, 255); // to change the response distance of the device
//    analogWrite(pin11, val);        // *note also messing with the resistor should change 
//                                    // the sensitivity
//
//   }else{                           // analogWrite(pin11, val); just tuns on the led with
//                                    // the intensity of the variable val
//    analogWrite(pin11, 0);          // the else statement is just telling the microcontroller
//                                    // to turn off the light if there is no EMF detected
//    sevenSegWrite(0);                               
//  }

    for(byte count=9; count >=0; --count) {                                   
      //if (val > 25*count) {
        delay(1000);
        sevenSegWrite(count);
      //}         
    }        
  delay(4000);
}

