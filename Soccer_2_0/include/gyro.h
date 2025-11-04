#pragma once

#include "Arduino.h"
#include "global.h"
#include "function_for_angle.h"


int16_t gyro_data() 
{
  static double angle = 0;

  if (Serial3.available() >= 2)
  {
    byte prev_sense = Serial3.read();
   
    if (prev_sense == 255)
    {
      byte sense = Serial3.read();
      angle = lead_to_degree_borders((byte)sense * 2);
    }
  }

  return angle;
}

