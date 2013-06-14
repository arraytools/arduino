// http://arduino-info.wikispaces.com/SmallSteppers

/* YourDuino.com Example Software Sketch
   Small Stepper Motor and Driver
   http://arduino-direct.com/sunshop/index.php?l=product_detail&p=126
   terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <Stepper.h>

/*-----( Declare Constants, Pin Numbers )-----*/
#define STEPS  100   //Number of steps per revolution


/*-----( Declare objects )-----*/
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to

//The pin connections need to be 4 pins connected
// to Motor Driver In1, In2, In3, In4  and then the pins entered
// here in the sequence 1-3-2-4 for proper sequencing
Stepper small_stepper(STEPS, 8, 10, 9, 11);

/*-----( Declare Variables )-----*/

int  Steps2Take;


void setup()   /*----( SETUP: RUNS ONCE )----*/
{

  // set the speed of the motor 
  small_stepper.setSpeed(200);  
}/*--(end setup )---*/

void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  small_stepper.setSpeed(1);   // Show the 4 step sequence 
  Steps2Take  =  4;  // Rotate CW
  small_stepper.step(Steps2Take);
  delay(2000);
  
  small_stepper.setSpeed(100);   
  Steps2Take  =  800;  // Rotate CW
  small_stepper.step(Steps2Take);
  delay(2000);
  
  small_stepper.setSpeed(200);  // 200 a good max speed??
  Steps2Take  =  -800;  // Rotate CCW
  small_stepper.step(Steps2Take);
  delay(2000);

}/* --(end main loop )-- */

/* ( THE END ) */

