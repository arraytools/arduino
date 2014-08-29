// Source: http://robotosh.blogspot.com/2012/07/arduino-jy-mcu-bluetooth.html
// Step 1: Do not connect bluetooth module 
// Step 2: upload the sketch to arduino
// step 3: Connect bluetooth module to an arduino uno.
//         Also connect an LED with resistor in serial.
// step 4: Power on Arduino by a 9V battery instead of USB.
// step 5: Turn on bluetooth on your computer. Find 'linvor' device.
// step 6: Find out the COM port the device is connected to.
// step 7: Open Arduino program. Click on 'Tools' and choose the right serial port.
//         Now open the 'Serial Monitor'. 
//         Be sure to have the right baud rate selected (9600bps)
//         Try to write capital 'H' or capital 'L' in the text box and hit Enter.

char val; // variable to receive data from the serial port
int ledpin = 8; // LED connected to pin 48 (on-board LED)

void setup() {

  pinMode(ledpin, OUTPUT);  // pin 48 (on-board LED) as OUTPUT
  Serial.begin(9600);       // start serial communication at 9600bps
}

void loop() {

  if( Serial.available() )       // if data is available to read
  {
    val = Serial.read();         // read it and store it in 'val'
  }
  if( val == 'H' )               // if 'H' was received
  {
    digitalWrite(ledpin, HIGH);  // turn ON the LED
  } else { 
    digitalWrite(ledpin, LOW);   // otherwise turn it OFF
  }
  delay(100);                    // wait 100ms for next reading
} 
