#pragma once

#include "buttons.h"
#include "camera.h"
#include "config.h"


#include "robot_update.h"
#include "tssop.h"
#include "move.h"
#include "global.h"
#include "dribler.h"
#include "robot_update.h"

void robot_update();

void ball_distance_angle() {
  if (ball::angle_tssop == 0 && ball::distance_tssop < 1) {
    ball::angle = ball::angle_camera; 
    ball::distance = ball::distance_camera;
  }
  else {
    if (ball::angle_camera == 0 && ball::distance_camera ==0) {
      ball::angle = ball::angle_tssop; 
      ball::distance = ball::distance_tssop;
    }
    else {
      ball::angle = (ball::angle_camera+ ball::angle_tssop)/2;
      ball::distance = (ball::distance_camera+ ball::distance_tssop)/2;
    }
  }
  #if ROLE == 1
  if (ball::angle == 0 && ball::distance <= 1) 
    {
      ball::angle = ball::prev_angle;
      ball::distance = ball::prev_distance;
    }
  else
    {
      ball::prev_angle = ball::angle;
      ball::prev_distance = ball::distance;
  }
  #endif
} 

void kick()
{
  if ((millis() - timers::kick) > 1000)
  {
    digitalWrite(KICK_PIN1, 0);
    digitalWrite(KICK_PIN1, 1);
    delay(15);
    digitalWrite(KICK_PIN1, 0);
    timers::kick = millis();
  }
}

void if_notice_goal()
{
  if (goal::our::distance == 0)
    goal::our::if_notice = false;
  else
    goal::our::if_notice = true;
  if (goal::enemy::distance == 0)
    goal::enemy::if_notice = false;
  else
    goal::enemy::if_notice = true;
}

void coordinates_robot()
{
  float o_a = lead_to_degree_borders(goal::our::local_angle + robot::local_angle);
  float e_a = lead_to_degree_borders(goal::enemy::local_angle + robot::local_angle);
  float x_o = goal::our::x + goal::our::distance * sin((180 - o_a) * 3.14 / 180.0);
  float y_o = goal::our::y + goal::our::distance * cos((180 - o_a) * 3.14 / 180.0);
  float x_e = goal::enemy::x + goal::enemy::distance * sin(e_a * 3.14 / 180.0);
  float y_e = goal::enemy::y - goal::enemy::distance * cos(e_a * 3.14 / 180.0);

  
  if (goal::our::if_notice == true and goal::enemy::if_notice == true)
  {
    float k = ((goal::our::distance - goal::enemy::distance + goal::enemy::y - goal::our::x) /(2 * (goal::enemy::y - goal::our::x)));
    
    robot::y = (1 - k) * y_o + k * y_e;
    robot::x = (1 - k) * x_o + k * x_e;
  }
  else
  {
    if (goal::our::if_notice == true)
    {
      robot::y = y_o;
      robot::x = x_o;
    }
    else
    {
      robot::y = y_e;
      robot::x = x_e;
    }
  }
  static double x_soft_c = 0;
  static double y_soft_c = 0;
  x_soft_c = k_coordinates * robot::x + x_soft_c * (1 - k_coordinates);
  y_soft_c = k_coordinates * robot::y + y_soft_c * (1 - k_coordinates);
  robot::x = x_soft_c;
  robot::y = y_soft_c;
}

void if_sen_leadle1()
{
  uint16_t opto_sens = analogRead(SEN_LEADLE1);
  //Serial.println(opto_sens);
  //delay(100);
   if ((opto_sens > 380 || opto_sens < 20) && abs(ball::angle)  < 40)
  {
    if_ball_in_leadle1 = true;
    timers::leadle1 = millis();
  }
    else
  {
    if ((millis() - timers::leadle1) > 50) if_ball_in_leadle1 = false; 
  }
}

void if_sen_leadle2()
{
  uint16_t opto_sens = analogRead(SEN_LEADLE2);
  //Serial.println(opto_sens);
  if (opto_sens > 450 && abs(ball::angle) > 120)
  {
    if_ball_in_leadle2 = 1;
    timers::leadle2 = millis();
  }
    else
  {
    if ((millis() - timers::leadle2) > 100) if_ball_in_leadle2 = false; 
  }
}



