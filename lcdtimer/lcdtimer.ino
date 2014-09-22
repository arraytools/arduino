/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

unsigned long i, j;
unsigned long second;
const int pos1=3, pos2=9;

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Ready. Let's go!");
  i = 0;
  j = 0;
}

void loop() {
  // print the number of seconds since reset:
  second = millis()/1000; // in seconds
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(pos2, 1);  
  lcd.print(second);
  
  if ((second % 60)  == 0) 
  {
     lcd.setCursor(pos1, 1);
     lcd.print(i);
     lcd.setCursor(pos2, 1);
     i++;
     delay(1000); // create minute
     //if ( i % 60 == 0)
     //{
     //   lcd.print(j);
     //   j++;
     //}
  }
  int x;
  x = analogRead(0);
  if (x < 60) {
    lcd.setCursor(0, 0);
    lcd.print("Turn right.     ");
    lcd.setCursor(pos2, 1);
  }
  else if (x < 200) {
    lcd.setCursor(0, 0);
    lcd.print("Stand up.       ");
    lcd.setCursor(pos2, 1);
  }
  else if (x < 400) {
    lcd.setCursor(0, 0);
    lcd.print("Sit down.       ");
    lcd.setCursor(pos2, 1);
  }
  else if (x < 600) {
    lcd.setCursor(0, 0);
    lcd.print("Turn left.      ");
    lcd.setCursor(pos2, 1);
  }  
  else if (x < 800) {
    lcd.setCursor(0, 0);
    lcd.print("     NSWYW      ");
    lcd.setCursor(pos2, 1);
  }  
}

