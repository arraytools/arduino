
/*
 * Sony_IR_Shield_Multi_Bot_v0_8
 * BOE Shield-Bot application under SONY TV remote control.
 * You can also press Power, then 3 for object following mode,
 * or Power, then 2 for IR roaming mode.  
 * Press any key (except Power) to exit either mode 2 or mode 3 and 
 * get back to driving your robot around with the SONY TV remote.
 * Source: http://learn.parallax.com/BoeShield/IrRemoteMultiShieldBot
 *
 * by Andy Lindsay
 * v0.82
 * 
 * NOTE: Find a bug or typo?  Have a commment?  Email editor@parallax.com
 */
                                                                                
#include <Servo.h>                           // Include servo library
 
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;
 
const int ServoLeftPin = 13;                 // I/O pin constants 
const int ServoRightPin = 12;
const int IrDetLeftPin = 10;
const int IrDetPin = 10;
const int IrLedLeftPin = 9;
const int LedLeftPin = 8;   
const int LedRightPin = 7;
const int BeeperPin = 4;
const int IrDetRightPin = 3;
const int IrLedRightPin = 2;


const byte Enter = 11;                       // Non-alpha remote button constants
const byte ChUp = 16;
const byte ChDn = 17;
const byte VolUp = 18;
const byte VolDn = 19;
const byte Power = 21;

const int setpoint = 2;                      // Target distances
const int kpl = -50;                         // Proportional control constants 
const int kpr = -50;
 
int irPulse;                                 // Stores pulses from IR detector
int remoteCode;                              // Stores code from remote
int mode = 1;                                // Stores mode

void setup()                                 // Setup runs once then loop takes over
{
  tone(BeeperPin, 3000, 1000);               // Play tone for 1 second
  delay(1000);                               // Delay to finish tone
  
  pinMode(LedLeftPin, OUTPUT);               // Indicator LEDs
  pinMode(LedRightPin, OUTPUT);
}

void loop()                                  // Auto-repeats after setup
{
  int remoteCode = GetIrCode();              // Get code from remote
  
  // Note, detaching servos is nice because they stay still regardless of
  // whether or not they are calibrated.  This prevents them from turning 
  // gradually if they are out of calibration.
  if(remoteCode == -1)                       // If nothing, detach servos
  {
    if((servoLeft.attached()==true) && (servoRight.attached()==true))
    {
      servoLeft.detach();
      servoRight.detach();
    }
  }
  else                                       // Otherwise, remote code received,
  {                                          // so attach/re-attach them.
    if((servoLeft.attached()==false) && (servoRight.attached()==false))
    {
      servoLeft.attach(ServoLeftPin);
      servoRight.attach(ServoRightPin);
    }
  }  
  // Padding to ignore end of remote code before attempting to detect objects.
  // This sketch only collects first 7 of 12 remote bits.  So delay for the 
  // rest of the remote message is required before attempting object detection.
  // Otherwise, the remote's signaling would interfere with the IR object detection.
  delay(10); 
  
  // IR object detection
  int irl=irDetect(IrLedLeftPin, IrDetLeftPin, 38000);            // Check for object on left     
  delay(1);                                  // Wait 1 ms
  int irr=irDetect(IrLedRightPin,  IrDetRightPin, 38000);            // Check for object on right

  // Decide what to do with the remote code.  Implement number pad control
  // and equivalent channel/volume control.
  switch(remoteCode)                         
  {
    case 1:                                  // 1 -> pivot left
      if(irr==0)                             // Stay still & complain if object on left
      {
        maneuver(0, 0);                      // Stop UFN
        digitalWrite(LedRightPin, HIGH);
        tone(BeeperPin, 4500, 20);
        delay(50);
        digitalWrite(LedRightPin, LOW);
        delay(50);
      }
      else                                  // No object in way?  Pivot left!    
      {
        maneuver(0, 200, 20);               // Execute maneuver for at least 20 ms
      }  
      break;                                // If this case, then done, skip other cases.
      
    case 2:                                 // 2 button
    case ChUp:                              // or Channel up button
      if((irl == 0)&&(irr==0))              // Don't go if object detected on either side 
      {
        maneuver(0, 0);
        digitalWrite(LedLeftPin, HIGH);
        digitalWrite(LedRightPin, HIGH);
        tone(BeeperPin, 4500, 20);
        delay(50);
        digitalWrite(LedLeftPin, LOW);
        digitalWrite(LedRightPin, LOW);
        delay(50);
      }
      else                                  // If no object, forward for at lest 20 ms
      {
        maneuver(200, 200, 20);
      }  
      break;
      
    case 3:                                // 3 button
      if(irl==0)                           // No pivot right if object on right
      {
        maneuver(0, 0);
        digitalWrite(LedLeftPin, HIGH);
        tone(BeeperPin, 4500, 20);
        delay(50);
        digitalWrite(LedLeftPin, LOW);
        delay(50);
      }
      else                                 // No obstacle on right?   
      {
        maneuver(200, 0, 20);              // Pivot right for at least 20 ms
      }  
      break;
      
    case 4:                                // 4 button pressed
    case VolDn:                            // Or volume down button pressed
      maneuver(-200, 200, 20);             // Rotate left in place for at least 20 ms
      break;
      
    case 5:                                // 5 button pressed
      maneuver(0, 0, 20);                  // Stay still for at least 20 ms
      break;
      
    case 6:                                // 6 button pressed
    case VolUp:                            // or volume up button pressed
      maneuver(200, -200, 20);             // Rotate right in place at least 20 ms
      break;
      
    case 7:                                // 7 button pressed
      maneuver(0, -200, 20);               // Pivot backward-left for at least 20 ms
      break;
      
    case 8:                                // 8 button pressed
    case ChDn:                             // or channel down button pressed
      maneuver(-200, -200, 20);            // Back up for at least 20 ms
      break;
      
    case 9:                                // 9 button pressed
      maneuver(-200, -0, 20);              // Pivot backward-right for at least 20 ms
      break;
      
    // Whoa, somebody pressed power, to select a new mode.
    case Power:                            
      mode = -1;                           // Clear current mode  
      servoLeft.detach();                  // Stop servos
      servoRight.detach();
      tone(BeeperPin, 3500, 100);          // Beep to indicate first button pressed
      delay(200);                          // Wait for beep + 100 more ms pause

      do                                   // Wait for valid IR code
      {
        mode = GetIrCode();
      }while((mode == -1) || (mode == Power)); 
      // Keep checking until code other than timeout (-1) or repeated Power button IR message.
      // Power button repeats every 40 ms or so, so it's easy to get more than one.
      
      tone(BeeperPin, 3500, 100);          // Beep twice for second button press
      delay(200);
      tone(BeeperPin, 3500, 100);
      delay(200);
      
      switch(mode)                         // Select function based on mode selection
      {
        case 2:                            // Mode = 2?  Call roam
          roam();
          break;
        case 3:                            // Mode = 3?  Call follow
          follow();
          break;
        default:                           // Mode = anything else?  Mode = IR remote controlled
          mode = 1;
          break;
      }
    // Back to outer switch...case.  Take no action if timeout (-1) or any non mapped remote
    // code is received.
    default:                               
      servoLeft.detach();                
      servoRight.detach();
      break;
  }   
}                                          // Loop function auto-repeats at this point


/*
 * Roam and avoid objects
 * Sources: http://learn.parallax.com/ShieldRobot (Chapter 7)
 *          http://learn.parallax.com/node/299
 *          http://learn.parallax.com/node/307
 * Modified to check IR Remote between IR sensors.
 */ 
void roam()
{
  int irCode = -1;                               // Declare IR variable
  servoLeft.attach(ServoLeftPin);                // Attach servos
  servoRight.attach(ServoRightPin);
  while(irCode == -1)                            // Roaming loop
  {
    irCode = GetIrCode();                        // Check IR code
    if(irCode==-1)                               // If timeout (-1), keep roaming
    {
      int irLeft = irDetect(IrLedLeftPin, IrDetLeftPin, 38000);       // Check for object on left
      int irRight = irDetect(IrLedRightPin, IrDetRightPin, 38000);       // Check for object on right

      if((irLeft == 0) && (irRight == 0))        // If both sides detect
      {
        maneuver(-200, -200, 1);                 // Backward 20 milliseconds
      }
      else if(irLeft == 0)                       // If only left side detects
      {
        maneuver(200, -200, 1);                  // Right for 20 ms
      }
      else if(irRight == 0)                      // If only right side detects
      {
        maneuver(-200, 200, 1);                  // Left for 20 ms
      }
      else                                       // Otherwise, no IR detects
      {
        maneuver(200, 200, 1);                   // Forward 20 ms
      }
    }                               
    else                                         // Else if incoming IR code
    {
      mode = 1;                                  // Set mode to 1
      digitalWrite(LedLeftPin, LOW);             // Turn off lights
      digitalWrite(LedRightPin, LOW);
      return;                                    // Return to loop function
    }
  }  
} 

/*
 * Follow object placed a few inches in front of the IR detectors
 * Source: http://learn.parallax.com/ShieldRobot (Chapter 8)
 * Modified to check IR Remote between IR sensors.
 */ 
void follow()                                       
{
  int irCode = -1;                               // Declare IR code variable
  servoLeft.attach(ServoLeftPin);                          // Attach servos
  servoRight.attach(ServoRightPin);

  // Repeat loop as long as GetIrCode times out and returns -1.
  while(irCode == -1)                            
  {
    irCode = GetIrCode();                        // Check for IR code
    if(irCode==-1)                               // If timeout (-1), then follow
    {
      // Measure left and right distances.
      int irLeft = irDistance(IrLedLeftPin, IrDetLeftPin);     
      int irRight = irDistance(IrLedRightPin, IrDetRightPin);
  
      // Left and right proportional control calculations
      int driveLeft = (setpoint - irLeft) * kpl;     
      int driveRight = (setpoint - irRight) * kpr;
  
      maneuver(driveLeft, driveRight, 1);       // drive levels set speeds
    }
    else                                        // If incoming remote code
    {
      mode = 1;                                 // Set mode to 1 (remote controlled)
      digitalWrite(LedLeftPin, LOW);            // Turn lights off
      digitalWrite(LedRightPin, LOW);
      return;                                   // Return to loop function
    }
  }  
} 

/*
 * Get rough distance measurement with BOE Shield-Bot's IR sensors.
 * Parameters: irLedPin - I/O pin connected to IR LED
 *             irReceiverPin - I/O pin connected to IR receiver
 * Returns: Distance zone (0...4)
 * Source: http://learn.parallax.com/ShieldRobot (Chapter 8)
 */ 
int irDistance(int irLedPin, int irReceivePin)
{  
  int distance = 0;
  for(long f = 38000; f <= 42000; f += 1000) {
    distance += irDetect(irLedPin, irReceivePin, f);
  }
  return distance;
}

/*
 * Check if an object is in the path of an IR LED with the kind of IR
 * receiver normally found in a TV set.
 * Parameters: irLedPin - I/O pin connected to IR LED
 *             irReceiverPin - I/O pin connected to IR receiver
 *             freqency - IR LED on/off frequency, most sensitive at 38000.
 * Returns: 0 if object detected or 1 if not
 * Sources: http://learn.parallax.com/node/299 (Chapter 7 start through Activity 1)
 * Modified to turn on lights if object detected or off if not detected.
 */ 
int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  if(irLedPin==IrLedLeftPin)                            // If left IR check
  { 
    if(ir==0)                                // If object detected
    {
      digitalWrite(LedLeftPin, HIGH);        // ..then turn on left LED
    }
    else                                     // If no object
    {
      digitalWrite(LedLeftPin, LOW);         // ..then turn off left LED
    }
  }
  if(irLedPin==IrLedRightPin)                // Repeat process for right LED
  { 
    if(ir==0)
    {
      digitalWrite(LedRightPin, HIGH);
    }
    else
    {
      digitalWrite(LedRightPin, LOW);
    }
  }
  delay(1);                                  // Down time before recheck
  return ir;                                 // Return 1 no detect, 0 detect
}     

/*
 * Check for and decode SONY TV remote messages coming from the IR TV detector in a TV set.
 * Returns: Code for button pressed on remote, or -1 if timeout (no code received).
 * Source: http://www.parallax.com/tabid/768/ProductID/149/Default.aspx
 * Modified for Arduino.
 */ 
int GetIrCode(){
  unsigned long irPulse = -1;                // Local variables    
  int irCode = 0;
  do{
    // Use pulseIn with 15 ms timeout if mode is roaming or following, or 50 ms timeout for control by TV remote.
    if((mode==3)||(mode==2)) irPulse = pulseIn(IrDetPin, LOW, 15000); else irPulse = pulseIn(IrDetPin, LOW, 50000); 
    // If timeout, return -1.
    if(irPulse==0) return -1;
  }while((irPulse <= 2000) || (irPulse >= 2800));
  // While condition filters for valid pulses and filters fluorescent ballast interference 
  
  // Capture first 7 of 12 bits from the remote.
  for(int i = 0; i <= 6; i++)
  {
    irPulse = pulseIn(IrDetPin, LOW, 2000);
    if((irPulse > 1000) && (irPulse < 1400)) bitSet(irCode, i);
  }

  // Convert alphanumeric codes to their corresponding button values.  
  if(irCode <= 9) irCode++;
  if(irCode == 10) irCode = 0;

  return irCode;
}

/*
 * Control BOE Shield-Bot servo direction, speed, set and forget version.
 * Parameters: speedLeft - left servo speed
 *             speedRight - right servo speed
 *             Backward  Linear  Stop  Linear   Forward
 *             -200      -100......0......100       200
 */ 
void maneuver(int speedLeft, int speedRight)
{
  // Call maneuver with just 1 ms blocking; servos will keep going indefinitely.
  maneuver(speedLeft, speedRight, 1);              
}

/*
 * Control BOE Shield-Bot servo direction, speed and maneuver duration.   
 * Parameters: speedLeft - left servo speed
 *             speedRight - right servo speed
 *             Backward  Linear  Stop  Linear   Forward
 *             -200      -100......0......100       200
 *             msTime - time to block code execution before another maneuver
 * Source:     http://learn.parallax.com/ManeuverFunction
 */ 
void maneuver(int speedLeft, int speedRight, int msTime)
{
  servoLeft.writeMicroseconds(1500 + speedLeft);   // Set Left servo speed
  servoRight.writeMicroseconds(1500 - speedRight); // Set right servo speed
  if(msTime==-1)                                   // if msTime = -1
  {                                  
    servoLeft.detach();                            // Stop servo signals
    servoRight.detach();   
  }
  delay(msTime);                                   // Delay for msTime
}

  

