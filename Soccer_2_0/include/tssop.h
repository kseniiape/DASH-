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

    ball::angle_tssop = -lead_to_degree_borders(atan2(x, y) * 57.3)-ball::null_angle;
    ball::distance_tssop = sqrt(x * x + y * y);
     #if ROLE == 2 
    if (ball::angle_tssop == -ball::null_angle && ball::distance_tssop <= 2) {
      ball::angle_tssop = 0;
    }
      /*x_soft = k_ball * x + x_soft * (1 - k_ball);
      y_soft = k_ball * y + y_soft * (1 - k_ball);
      ball::angle = -lead_to_degree_borders(atan2(x_soft, y_soft) * 57.3) -ball::null_angle;
      ball::distance = sqrt(x_soft * x_soft + y_soft * y_soft);*/
      //ball::angle = -lead_to_degree_borders(atan2(x, y) * 57.3)-ball::null_angle;
    
    #else
    if (ball::angle_tssop == -ball::null_angle && ball::distance_tssop <= 2) {
      ball::angle_tssop = 0;
    }
    //ball::angle = -lead_to_degree_borders(atan2(x, y) * 57.3)-ball::null_angle;
    //ball::distance = sqrt(x * x + y * y);
    /*if (ball::angle == -ball::null_angle && ball::distance <= 1) 
    {
      ball::angle = ball::prev_angle;
      ball::distance = ball::prev_distance;
    }
    else
    {
      ball::prev_angle = ball::angle;
      ball::prev_distance = ball::distance;

    }*/
    #endif
    /*Serial.println(ball::angle);
  for(int i = 0; i<32; i++ ) 
  {
    Serial.print(data[i]);
    Serial.print(' ');
  }
  Serial.println(' ');*/


}
