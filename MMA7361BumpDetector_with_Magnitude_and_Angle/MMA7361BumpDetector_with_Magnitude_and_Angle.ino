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

byte updateflag;
int xaxis, yaxis, zaxis;
int deltx, delty, deltz;
int LEDPin = 13;
int sleepPin = 12;
int vibration, magnitude, sensitivity, devibrate;
double angle;
unsigned long time1,time2;

void setup()
{
  pinMode (LEDPin, OUTPUT);
  pinMode (sleepPin, OUTPUT);
  sensitivity=50;
  devibrate=50;
  digitalWrite (sleepPin, HIGH);
  Serial.begin(9600);
  time1=micros();
}

void loop()
{
  if (micros()-time1>1999) Impact();                            // call impact routine every 2mS
  if (millis()-time2<500)                                       // is the time less than 500mS from impact event
  {
    digitalWrite (LEDPin, HIGH);                                // Yes: turn on  LED
  }
  else                                          
  {
    digitalWrite (LEDPin,LOW);                                  // No:  turn off LED                            
  }
  
  if(updateflag>0)
  {
    updateflag=0;
    Serial.print("Impact detected!!   Magnitude:");Serial.print(magnitude);
    Serial.print("\t Angle:");Serial.println(angle,2);
  }
}


void Impact()
{
  time1=micros();                                              // resets time value
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

  if (magnitude>sensitivity)                                  // new impact detected
  {
    updateflag=1;
    double X=xaxis-512;                                       // adjust xaxis reading to +/- 512
    double Y=yaxis-512;                                       // adjust yaxis reading to +/- 512
    
    angle=atan2(Y,X)*180/PI;                                  // use atan2 to calculate angle and convert radians to degrees
    angle+=180;                                               // OPTIONAL:converts +/- 180 degrees to 0-360 degrees
    
    vibration=devibrate;                                      // reset anti-vibration counter
    time2=millis();                                           // reset LED timer
  }
  else
  {
    magnitude=0;                                              // reset magnitude of impact to 0
  }
}


