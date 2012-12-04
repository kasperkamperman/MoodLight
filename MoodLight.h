/*
  MoodLight.h - Library with MoodLight functions 
  Created by Kasper Kamperman, February 26, 2011.
  http://www.kasperkamperman.com
  Released into the public domain.
  
  More info in the .cpp file.
*/


#ifndef MoodLight_h
#define MoodLight_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class MoodLight
{
  public:
    MoodLight();
    void setHSB(int,int,int);
    int getRed();
    int getGreen();
    int getBlue();
    int getDc(int);
    uint8_t* _dim_curve;    
    
  private:
    
    int  _red;
    int  _green;
    int  _blue;
};

#endif