The Arduino board is Arduino Pro mini 328 - 3.3V Atmega328.
(not 5V). Selecting the wrong one in Arduino IDE will mess out output even we can upload sketch.

On Linux machine, I don't need to worry about driver. 
On Windodws machine, I need to install driver. Check http://arduino.cc/en/Guide/ArduinoProMini.

The AD8232 heat rate monitor hookup guide is available on https://learn.sparkfun.com/tutorials/ad8232-heart-rate-monitor-hookup-guide/all

In processing sketch, the 'Serial.list()[]' port number is the last one shown on my Processing IDE.
It is counting from zero.

The sensor pad is be found on intenet: biomedical sensor pad covidien.
