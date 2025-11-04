#pragma once

#include "Arduino.h"

#include "config.h"
#include "global.h"


void detect_ball()
{
    int data[32];
    for (int i = 0; i < 16; i++)
    {
      digitalWrite(ADDR_P1, tssop::ir_addr[i][0]);
      digitalWrite(ADDR_P2, tssop::ir_addr[i][1]);
      digitalWrite(ADDR_P3, tssop::ir_addr[i][2]);
      digitalWrite(ADDR_P4, tssop::ir_addr[i][3]);
      delayMicroseconds(10);
      data[i] = !digitalRead(BALL_SEN_SIGNAL_1);
    }

    for (int i = 0; i < 16; i++)
    {
      digitalWrite(ADDR_P1, tssop::ir_addr[i][0]);
      digitalWrite(ADDR_P2, tssop::ir_addr[i][1]);
      digitalWrite(ADDR_P3, tssop::ir_addr[i][2]);
      digitalWrite(ADDR_P4, tssop::ir_addr[i][3]);
      delayMicroseconds(10);
      data[i+16] = !digitalRead(BALL_SEN_SIGNAL_2);
    }

    double x = 0;
    double y = 0;
    for (int i = 0; i < 32; i++)
    {
      x += data[i] * sin((tssop::delta_angle * i) / 57.3);
      y += data[i] * cos((tssop::delta_angle * i) / 57.3);
    }

    ball::angle = -lead_to_degree_borders(atan2(x, y) * 57.3)-ball::null_angle;
    ball::distance = sqrt(x * x + y * y);
      
    if (ball::angle == ball::null_angle and ball::distance == 0) ball::angle = 0;
  /*for(int i = 0; i<32; i++ ) 
  {
    Serial.print(data[i]);
    Serial.print(' ');
  }
  Serial.println(' ');*/
}
