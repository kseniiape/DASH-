#pragma once
#include "Arduino.h"
#include "global.h"
#include "function_for_angle.h"
#include "move.h"
#include "for_strategy.h"
#include "config.h"


double convert_dist(double max_dist, double dist)
{
  double _data = (dist - max_dist) / max_dist + 1;

  if (_data > 1)
    _data = 1;
  else if (_data < 0)
    _data = 0;

  return _data;
}

int16_t exponential_detour(double ball_angle, double distance, double k1_angle, double k2_angle, double k1_dist, double k2_dist)
{
  double angK = k1_angle * pow(ec, double(k2_angle * abs(ball_angle)));

  if (angK > 90)
    angK = 90;

  distance = convert_dist(min_dist_to_ball, distance);

  double distK = k1_dist * pow(ec, double(k2_dist * distance));

  if (distK > 1)
    distK = 1;

double _data;
  if (ball_angle > 0)
    _data = angK * distK;
  else
    _data = -angK * distK;

  return _data;
}

void ball_capture()
{
    forward::angle = ball::angle + exponential_detour(ball::angle, ball::distance, 0.6, 0.14, 0.25, 1.4);//0.022, 0.142, 23, 60
    forward::speed = 210;
    if(ball::distance > 7 && abs(ball::angle) > 25) forward::speed = 170;
    //move_angle_speed(forward::angle, forward::speed, 0);
    //Serial.println(forward::angle);
}


void d_ball_capture() {
    forward::angle = 180;
}


void control_outs_forward(double angle, int speed)
{
    angle = lead_to_degree_borders(angle);
    if ((robot::x < forward::outs::right_near_point::x) or (robot::x > forward::outs::left_far_point::x))
    {
        if (robot::x > forward::outs::left_far_point::x)
        {
            if ((lead_to_degree_borders(angle + robot::local_angle)) < 20 or (lead_to_degree_borders(angle + robot::local_angle)) > 160)
            {
                if ((lead_to_degree_borders(angle + robot::local_angle)) < -90 or (lead_to_degree_borders(angle + robot::local_angle)) > 160)
                angle = 160 - robot::local_angle;
                else
                angle = 20 - robot::local_angle;
            }
        }
        else
            {
            if ((lead_to_degree_borders(angle + robot::local_angle)) > -20 or (lead_to_degree_borders(angle + robot::local_angle)) < -160)
            {
                if ((lead_to_degree_borders(angle + robot::local_angle)) > 90 or (lead_to_degree_borders(angle + robot::local_angle)) < -160)
                angle = -160 - robot::local_angle;
                else
                angle = -20 - robot::local_angle;
            }
        }
  }

  if ((robot::x >  forward::outs::left_far_point::x - forward::outs::dist_slowdown))
  {
    if ((lead_to_degree_borders(angle + robot::local_angle)) < 20 or (lead_to_degree_borders(angle + robot::local_angle)) > 160)
      forward::speed = constrain(speed, -speed_constrain, speed_constrain);
  }

  if ((robot::x < forward::outs::right_near_point::x + forward::outs::dist_slowdown))
  {
    if ((lead_to_degree_borders(angle + robot::local_angle)) > -20 or (lead_to_degree_borders(angle + robot::local_angle)) < -160)
      forward::speed = constrain(speed, -speed_constrain, speed_constrain);
  }

  if ((robot::y > forward::outs::left_far_point::y) or (robot::y < forward::outs::right_near_point::y))
  {
    if (robot::y > forward::outs::left_far_point::y)
    {
      if (abs(lead_to_degree_borders(angle + robot::local_angle)) < 120)
      {
        if ((lead_to_degree_borders(angle + robot::local_angle)) > 0)
          angle = 120 - robot::local_angle;
        else
          angle = -120 - robot::local_angle;
      }
    }

    else
    {
      if (abs(angle + robot::local_angle) > 60)
      {
        if ((lead_to_degree_borders(angle + robot::local_angle)) > 0)
          angle = 60 - robot::local_angle;
        else
          angle = -60 - robot::local_angle;
      }
    }
  }

  if ((robot::y > forward::outs::left_far_point::y - forward::outs::dist_slowdown))
  {
    if (abs(lead_to_degree_borders(angle + robot::local_angle)) < 120)
      forward::speed = constrain(speed, -speed_constrain, speed_constrain);
  }

  if (robot::y < forward::outs::right_near_point::y +forward::outs::dist_slowdown)
  {
    if (abs(lead_to_degree_borders(angle + robot::local_angle)) > 60)
      forward::speed = constrain(speed, -speed_constrain, speed_constrain);
  }
    forward::angle = angle;
    forward::speed = speed;
/*Serial.print(forward::angle);
Serial.print(' ');
Serial.println(forward::speed);*/
}

void forward()
{
    double angle = 0;

    //1 - capture, 2 - move to goal, 3 - kick
    forward::speed = 180;
    //ball_capture();
    
    if (!dribler)
    {
        //1 - capture, 2 - move to goal, 3 - kick
        static int state = 1;
        float k_angle = 0.1, k_distance = 0.3;
        switch (state)
        {
            case 1:
                ball_capture();
                if (if_ball_in_leadle1) state = 2;
                if (abs(ball::angle < 25) && ball::distance < 40) forward::speed = constrain(forward::speed, -150, 150);
                //forward::speed = 130 +k_angle*abs(ball::angle) + k_distance*ball::distance; 
                break;
            case 2:
                forward::angle = 0;
                forward::speed = 200;
                if (goal::enemy::distance < 100) state = 3;
                //else 
                if (!if_ball_in_leadle1) state = 1;
                break;
            case 3:
                forward::speed = 200;
                kick();
                if (!if_ball_in_leadle1) state = 1;
                else state = 2;
                break;
        }
        if (goal::enemy::if_notice) angle = goal::enemy::local_angle + robot::local_angle;
        //Serial.println(angle);
    }

    else
    {   //1 - capture, 2 - move to point, 3 - kick
        forward::speed = 180;
        static int state = 1;
        switch (state)
        {
            case 1:
                forward::angle = 0;
                angle = lead_to_degree_borders(ball::angle + robot::local_angle);
                if (abs(ball::angle) < 90) 
                {
                    dribler_power(1500);
                    forward::speed = 140;
                }
                else dribler_power(1000);
                if (if_ball_in_leadle1) state = 2;
                timers::state_forward1 = millis();
                timers::state_forward2 = millis();

                break;
            
            case 2:
                int x_point = -40, y_point = 130;
                dribler_power(1500);
                if (millis() - timers::state_forward1 < 500) forward::speed = 0;
                else {
                    move_to_point(x_point, y_point);
                    forward::angle = goalkeeper::angle;
                    forward::speed = goalkeeper::speed;
                    angle = 180;
                }
                if (!if_ball_in_leadle1) state = 1;
                if (abs(x_point - robot::x) < 15 && abs(y_point - robot::y) < 15) state = 3;
                timers::state_forward2 = millis();
                break;
            case 3:
                if (millis() - timers::state_forward2 < 500) forward::speed = 0;
                else {
                    kick();
                    turn(200);
                    delay(500);
                }
                if (!if_ball_in_leadle1) state = 1;
                timers::state_forward1 = millis();
                break;
        }
        
    }
   control_outs_forward(forward::angle, forward::speed);

   /*Serial.print(forward::angle);
    Serial.print(' ');
    Serial.println(forward::speed);*/
    move_angle_speed(forward::angle, forward::speed, angle);
}