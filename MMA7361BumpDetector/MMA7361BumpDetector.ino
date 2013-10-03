/* Using the MMA7361 Accelerometer as an impact sensor
  This is a simple sketch dependent on the work of Russell Cameron (OddBott) of
  Dagu Robots that demonstrates the use of an accelerometer as an impact or "bump" sensor.
  Note that on the Dagu MicroMagician board that the accelerometer is hardwired in.
  This example is for Arduino boards and an outboard MMA7361.  For purposes of
  this demonstration, there is an LED wired to digital pin 13, the sleep pin on the MMA7361
  is on digital 12 and kept HIGH so that the unit doesn't go to sleep, and the X, Y and Z pins
  are attached to analog 0, 1 and 2 respectively.  Almoost all of this code is just lifted wholesale
  from the Micromagician library and examples provided with it.  All I did was define pins and
  adjust it a little for the purpose at hand.
*/
int xaxis, yaxis, zaxis;
int oldx, oldy, oldz;
int deltx, delty, deltz;
int LEDPin = 13;
int sleepPin = 12;
int vibration, magnitude, sensitivity, devibrate;
void setup()
{
  pinMode (LEDPin, OUTPUT);
  pinMode (sleepPin, OUTPUT);
  sensitivity=50;
  devibrate=50;
  digitalWrite (sleepPin, HIGH);
}
void loop()
{
 
  int oldx=xaxis;                                             // local variables store previous axis readings for comparison
  int oldy=yaxis;
  int oldz=zaxis;

  vibration--;                                                // loop counter prevents false triggering 
  if(vibration<0) vibration=0;                                // as robot vibrates due to impact

  xaxis=analogRead(0);                                        // new axis readings are taken - very time consuming
  yaxis=analogRead(1);                                        // each analogRead takes aproximately 260uS
  zaxis=analogRead(2);
  if(vibration>0) return;                                     // until vibration has subsided no further calculations required

  deltx=xaxis-oldx;                                           // delta between old and new axis readings
  delty=yaxis-oldy;
  deltz=zaxis-oldz;
  magnitude=sqrt(sq(deltx)+sq(delty)+sq(deltz));              // magnitude of delta x,y,z using pythagorus

  if (magnitude>sensitivity)                                  // has a new impact occured
  {
    vibration=devibrate;                                      // reset anti-vibration counter
    digitalWrite (LEDPin, HIGH);
    delay (500);
    digitalWrite (LEDPin,LOW);
  }
  else
  {
    magnitude=0;                                              // no impact detected
    digitalWrite (LEDPin,LOW);  
  }
}

