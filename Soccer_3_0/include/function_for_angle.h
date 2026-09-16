#pragma once

#include "Arduino.h"
#include "global.h"

int16_t lead_to_degree_borders(int angle)
{
  while (angle > 180) angle -= 360;
  while (angle < -180) angle += 360;
  return angle;

}