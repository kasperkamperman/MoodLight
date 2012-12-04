/* MoodLight: Library with MoodLight functions 
   Created by Kasper Kamperman, February 26, 2011.
   http://www.kasperkamperman.com
   Released into the public domain.

   You can find the code without use of the library at:
   http://www.kasperkamperman.com/blog/arduino/arduino-programming-hsb-to-rgb/
*/ 

// Include the MoodLight library.
#include <MoodLight.h>

// inputs
int sensorPin = 0;

// outputs
int ledPinR = 9;  // pwm pin with red led
int ledPinG = 10; // pwm pin with green led
int ledPinB = 11; // pwm pin with blue led

// other variables
int sensorVal;   // store value from sensorPin

int hue;         // use value between 0 - 359
int saturation;  // use value between 0 - 255
int brightness;  // use value between 0 - 255

// create MoodLight object
MoodLight ml = MoodLight(); 

void setup() {  
  
   pinMode(ledPinR, OUTPUT);  
   pinMode(ledPinG, OUTPUT);  
   pinMode(ledPinB, OUTPUT);   
   
}

void loop() { 
  
  // read the sensor (potmeter)
  sensorVal = analogRead(sensorPin); 
  
  // map the value from 0-1023 to a value between 0 and 359
  hue        = map(sensorVal,0, 1023,0, 359);
  saturation = 255; 
  brightness = 255; 
  
  // set the Moodlight values  
  ml.setHSB(hue, saturation , brightness);

  // read the Red, Green and Blue values
  // and write them to the led pins
  analogWrite(ledPinR, ml.getRed());
  analogWrite(ledPinG, ml.getGreen());
  analogWrite(ledPinB, ml.getBlue());  
  
}
