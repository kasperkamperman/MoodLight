/*
  MoodLight.h - Library with MoodLight functions 
  Created by Kasper Kamperman, February 26, 2011.
  http://www.kasperkamperman.com
  Released into the public domain.
  
  setHSB() function based on <http://www.codeproject.com/miscctrl/CPicker.asp>  
  dim_curve idea by Jims <http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1174674545>
  
  Dim_curve 'lookup table' to compensate for the nonlinearity of human vision.
  
  Used to make 'dimming' look more natural. 
  
  Exponential function used to create values below : 
  x from 0 - 255 : y = round(pow( 2.0, x+64/40.0) - 1)   
  
*/

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "MoodLight.h"

// dim curve
uint8_t dc[256] = {
    0,   1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   3,   3,
    3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,   4,   4,
    4,   4,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   6,   6,
    6,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,   7,   8,   8,   8,   8,
    8,   8,   9,   9,   9,   9,   9,   9,   10,  10,  10,  10,  10,  11,  11,  11,
    11,  11,  12,  12,  12,  12,  12,  13,  13,  13,  13,  14,  14,  14,  14,  15,
    15,  15,  16,  16,  16,  16,  17,  17,  17,  18,  18,  18,  19,  19,  19,  20,
    20,  20,  21,  21,  22,  22,  22,  23,  23,  24,  24,  25,  25,  25,  26,  26,
    27,  27,  28,  28,  29,  29,  30,  30,  31,  32,  32,  33,  33,  34,  35,  35,
    36,  36,  37,  38,  38,  39,  40,  40,  41,  42,  43,  43,  44,  45,  46,  47,
    48,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,
    63,  64,  65,  66,  68,  69,  70,  71,  73,  74,  75,  76,  78,  79,  81,  82,
    83,  85,  86,  88,  90,  91,  93,  94,  96,  98,  99,  101, 103, 105, 107, 109,
    110, 112, 114, 116, 118, 121, 123, 125, 127, 129, 132, 134, 136, 139, 141, 144,
    146, 149, 151, 154, 157, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 190,
    193, 196, 200, 203, 207, 211, 214, 218, 222, 226, 230, 234, 238, 242, 248, 255,
};

MoodLight::MoodLight()
{	// dim_curve int 
    /* see post: http://arduino.cc/forum/index.php/topic,53807.0.html
       maybe a type mistake prevented from using the global directly. 
    */
	_dim_curve = dc;
}


void MoodLight::setHSB(int hue, int sat, int val) { 
  /* convert hue, saturation and brightness ( HSB/HSV ) to RGB
     The dim_curve is used only on brightness/value and on saturation (inverted).
     This looks the most natural.      
  */
  
  val = dc[val];
  sat = 255-dc[255-sat];
  
  int r;
  int g;
  int b;
  int base;
  
  if (sat == 0) { // Acromatic color (gray). Hue doesn't mind.
  
    _red   = val;
    _green = val;
    _blue  = val; 
   
  } else  { 
    
    base = ((255 - sat) * val)>>8;
  
    switch(hue/60) {
	case 0:
		r = val;
		g = (((val-base)*hue)/60)+base;
		b = base;
	break;
	
	case 1:
		r = (((val-base)*(60-(hue%60)))/60)+base;
		g = val;
		b = base;
	break;
	
	case 2:
		r = base;
		g = val;
		b = (((val-base)*(hue%60))/60)+base;
	break;
	
	case 3:
		r = base;
		g = (((val-base)*(60-(hue%60)))/60)+base;
		b = val;
	break;
	
	case 4:
		r = (((val-base)*(hue%60))/60)+base;
		g = base;
		b = val;
	break;
	
	case 5:
		r = val;
		g = base;
		b = (((val-base)*(60-(hue%60)))/60)+base;
	break;
    }
      
    _red   = r;
    _green = g;
    _blue  = b; 
  }   

}

int MoodLight::getRed(){

  return _red;

}

int MoodLight::getGreen(){

  return _green; 

}

int MoodLight::getBlue(){

  return _blue;

}

int MoodLight::getDc(int val){
  return dc[val];
}

