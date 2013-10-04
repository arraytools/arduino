/* Modified from http://learn.adafruit.com/adxl345-digital-accelerometer?view=all
 */
int xaxis, yaxis, zaxis;
int LEDPin = 13;
int sleepPin = 12;
void setup()
{
  pinMode (LEDPin, OUTPUT);
  pinMode (sleepPin, OUTPUT);
  digitalWrite (sleepPin, HIGH);
  Serial.begin (9600);
}
void loop()
{
//  Serial.println("Type key when ready...");
//  while (!Serial.available()){} // wait for a character
  delay(1000);
  xaxis=analogRead(0);                                        // new axis readings are taken - very time consuming
  yaxis=analogRead(1);                                        // each analogRead takes aproximately 260uS
  zaxis=analogRead(2);

    Serial.print("X: "); // 160 when x-axis is down,320 when x-axis is parallel to ground, 490 when face up.
    Serial.print(xaxis);
    Serial.print(",  Y: "); // 190 when y-axis is down, 355 when y-axis is parallel to ground, 520 when face up.
    Serial.print(yaxis);
    Serial.print(",  Z: "); // 150 when z-axis is up, 300 when z-axis is parallel to ground, 480 when face down.
    Serial.print(zaxis);
    Serial.println(); Serial.println();

   while (Serial.available())
   {
      Serial.read(); // clear the input buffer
   }
}


