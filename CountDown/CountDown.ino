/*
	Bomb Defuse Countdown Timer
  Code for Bomb Desfuser Escape Room for Stargate After Prom Party
  
	Author: E. Goyette

*/

// include the SevenSegmentTM1637 library
//#include "SevenSegmentTM1637.h"
#include "SevenSegmentExtended.h"


#define RED 9
#define BLUE 10
#define GREEN 11
#define PIN_CLK 4   // define CLK pin (any digital pin)
#define PIN_DIO 5   // define DIO pin (any digital pin)

#define MINLEVEL 25
#define MAXLEVEL 200

/* initialize global TM1637 Display object
*  The constructor takes two arguments, the number of the clock pin and the digital output pin:
* SevenSegmentTM1637(byte pinCLK, byte pinDIO);
*/
SevenSegmentExtended display(PIN_CLK, PIN_DIO);

const unsigned int clockSpeed = 600;    // speed up clock for demo 60 = 1 second per tick

// run setup code
void setup() {
  //Serial.begin(9600);         // initializes the Serial connection @ 9600 baud
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  
  display.begin();            // initializes the display
  display.setBacklight(50);  // set the brightness to 100 %
  delay(1000);                // wait 1000 ms
  display.printTime( (uint8_t)0, (uint8_t)0);
  delay(1000);
};

// run loop (forever)
void loop() {

  uint8_t minutes;
  uint8_t seconds;
  
  display.printTime(minutes, seconds, true);
  
  for (minutes = 15; minutes > 0; minutes--) {

      if ( minutes >= 11 ){
        analogWrite(GREEN, map(minutes, 11, 15, MINLEVEL, MAXLEVEL));
        analogWrite(BLUE, 0);
        analogWrite(RED, 0);
      }
      else if ( minutes >= 6 ){
        analogWrite(GREEN, map(minutes, 6, 10, MINLEVEL, MAXLEVEL));
        analogWrite(RED, map(minutes, 6, 10, MINLEVEL, MAXLEVEL));
        analogWrite(BLUE, 0);
      }
      else {
        analogWrite(RED, map(minutes, 0, 5, MAXLEVEL, MINLEVEL));
        analogWrite(GREEN, 0);
        analogWrite(BLUE, 0);
      }
      
    for (seconds = 60; seconds > 0; seconds--) {
      display.printTime((uint8_t)(minutes - 1), (uint8_t)(seconds - 1));
      delay(60000 / clockSpeed);
    };
    
    seconds = 60;
  }
};
