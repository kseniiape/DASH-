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
    forward::angle = ball::angle + exponential_detour(ball::angle, ball::distance, 0.7, 0.15, 0.3, 1.4);//0.022, 0.142, 23, 60
    //forward::speed = 200;
    if(ball::distance > 7 && abs(ball::angle) > 20) forward::speed = 130;
    //move_angle_speed(forward::angle, forward::speed, 0);
    //Serial.println(forward::angle);
}


void d_ball_capture() {
    forward::angle = 180;
}


void control_outs_forward(double angle, int speed)
{
    /*if (robot::y > 170) 
    {
        forward::outs::left_far_point::x =   forward::outs::left_far_point::x - 5;
        forward::outs::right_near_point::x = forward::outs::right_near_point::x+  5;
    }*/
    angle = lead_to_degree_borders(angle);
    double absolute_angle = lead_to_degree_borders(angle + robot::local_angle);
    if(robot::x < forward::outs::right_near_point::x)
    {
        //Serial.println('*');
        angle = lead_to_degree_borders(-90 - robot::local_angle);
        // if(robot::x < forward::outs::right_near_point::x)
        // {
        //     //Serial.println('**');
        //     //if(absolute_angle > 90 || absolute_angle <= -160) angle = lead_to_degree_borders(-160-robot::local_angle);
        //     //else if (absolute_angle > -20 && absolute_angle <= 90) angle = lead_to_degree_borders(-20-robot::local_angle);

        //     speed = constrain(speed, -speed_constrain, speed_constrain);
        // }
        // else
        // {
        //     if(absolute_angle > -20 || absolute_angle < -160)speed = constrain(speed, -speed_constrain, speed_constrain);
        // }
    }
    else if (robot::x < forward::outs::right_near_point::x + forward::outs::dist_slowdown ) speed = constrain(speed, -speed_constrain, speed_constrain);
    else if (robot::x > forward::outs::left_far_point::x)
    {
        //Serial.println('/');
        //if(robot::x > forward::outs::left_far_point::x)
        //{
            /*Serial.print(absolute_angle);
            Serial.print(' ');
            Serial.println(robot::local_angle);*/
            /*if(absolute_angle <= -90 || absolute_angle >= 160) angle = lead_to_degree_borders(160-robot::local_angle);
            else if (absolute_angle <= 20 && absolute_angle > -90) angle = lead_to_degree_borders(20-robot::local_angle);
            speed = constrain(speed, -speed_constrain, speed_constrain);
        }
        else
        {
            if(absolute_angle < 20 || absolute_angle > 160)speed = constrain(speed, -speed_constrain, speed_constrain);
        }*/
       angle = lead_to_degree_borders(90 - robot::local_angle);
    }
    else if (robot::x > forward::outs::left_far_point::x - forward::outs::dist_slowdown ) speed = constrain(speed, -speed_constrain, speed_constrain);


    if(robot::y < forward::outs::right_near_point::y)
    {
        angle = lead_to_degree_borders(0- robot::local_angle);
        /*//Serial.println('+');
        if(robot::y < forward::outs::right_near_point::y)
        {
            //Serial.println('+*');
            if(absolute_angle >= 70) angle = lead_to_degree_borders(70-robot::local_angle);
            else if (absolute_angle <= -70) angle = lead_to_degree_borders(-70-robot::local_angle);
            speed = constrain(speed, -speed_constrain, speed_constrain);
        }
        else
        {
            if(absolute_angle > 70 || absolute_angle < -70)speed = constrain(speed, -speed_constrain, speed_constrain);
        }*/

    }
    else if(robot::y < forward::outs::right_near_point::y + forward::outs::dist_slowdown) speed = constrain(speed, -speed_constrain, speed_constrain);

    else if(robot::y > forward::outs::left_far_point::y)
    {
        angle = lead_to_degree_borders(180 - robot::local_angle);
        //Serial.println('=');
        /*if(robot::y > forward::outs::left_far_point::y)
        {
            //Serial.println('=*');
            if(absolute_angle < 110 && absolute_angle >= 0) angle = lead_to_degree_borders(110-robot::local_angle);
            else if (absolute_angle > -110 && absolute_angle < 0) angle = lead_to_degree_borders(-110-robot::local_angle);
            speed = constrain(speed, -speed_constrain, speed_constrain);
        }
        else
        {
            if(absolute_angle > 110 || absolute_angle < -110)speed = constrain(speed, -speed_constrain, speed_constrain);
        }*/

    }
    else if(robot::y > forward::outs::left_far_point::y - forward::outs::dist_slowdown ) speed = constrain(speed, -speed_constrain, speed_constrain);
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
    forward::speed = 210;
    //ball_capture();
    
    if (!dribler)
    {
        static int state = 1;
        switch (state)
        {
            case 1:
                ball_capture();
                if (if_ball_in_leadle1) state = 2;
                break;
            case 2:
                forward::angle = 0;
                //if (goal::enemy::distance < 100) state = 3;
                //else 
                if (!if_ball_in_leadle1) state = 1;
                break;
            case 3:
                kick();
                if (!if_ball_in_leadle1) state = 1;
                else state = 2;
                break;
        }
        if (goal::enemy::if_notice) angle = goal::enemy::local_angle + robot::local_angle;
        //Serial.println(angle);
    }

    else
    {   
        static int x_point = -50, y_point = 140;
        static int state1 = 1, state2 = 1;
        static int state_ball = 1;
        /*Serial.println('/');
        Serial.print(state_ball);
        Serial.println('.');*/
        switch(state_ball)
        {
            case 1:
                /*Serial.print(state1);
                Serial.println('/');*/
                dribler_power(1000);
                if (goal::enemy::if_notice) angle = goal::enemy::local_angle + robot::local_angle;
                timers::ball_capture = millis();
                if(abs(ball::angle) >= 130 && abs(lead_to_degree_borders(robot::local_angle)) <  60) state_ball = 2;
                switch (state1)
                {
                    case 1:
                        ball_capture();
                        if (if_ball_in_leadle1) state1 = 2;
                        break;
                    case 2:
                        forward::angle = 0;
                        //if (goal::enemy::distance < 120) state1 = 3;
                        //else 
                        if (!if_ball_in_leadle1) state1 = 1;
                        break;
                    case 3:
                        kick();
                        if (!if_ball_in_leadle1) state1 = 1;
                        else state1 = 2;
                        break;
                }
                if (goal::enemy::if_notice) angle = goal::enemy::local_angle + robot::local_angle;
                break;
            case 2:
                forward::speed = 150;
               /*Serial.print(state2);
                Serial.println('-');*/
                if(abs(ball::angle) <= 110 || abs(lead_to_degree_borders(robot::local_angle)) >  80) state_ball = 1;
                switch (state2)
                {
                    case 1:
                    timers::d_capture = millis();
                        if (abs(ball::angle) > 120) 
                        {
                            if (ball::distance >= 7) 
                            {
                                dribler_power(1400);
                                forward::speed = 120;
                            }
                            else dribler_power(1200);
                        }
                        else dribler_power(1000);
                        d_ball_capture();
                        angle = lead_to_degree_borders(ball::angle + robot::local_angle + 180);
                        if (if_ball_in_leadle2) state2 = 2;
                        timers::ball_capture = millis();
                        break;
                    case 2:
                    timers::d_capture = millis();
                        dribler_power(1500);
                        if((millis() - timers::ball_capture) < 2000) forward::speed = 0;
                        else move_to_point(x_point, y_point);
                        angle = 0;
                        if (abs(x_point - robot::x) < 15 &&  abs(y_point - robot::y) < 15) 
                        {
                            state2 = 3;
                        } 
                        else if (!if_ball_in_leadle2) state2 = 1;
                        break;
                    case 3:
                        timers::ball_capture = millis();
                        if (millis() - timers::d_capture < 500) forward::speed = 0;
                        else {
                        dribler_power(1400);
                        turn(255);
                        delay(250);
                        state2 = 1;
                        dribler_power(1000);
                        timers::d_capture = millis();
                        }
                        angle = 0;
                        
                        break;
                }
                break;
        }
    }

   control_outs_forward(forward::angle, forward::speed);

   /*Serial.print(forward::angle);
    Serial.print(' ');
    Serial.println(forward::speed);*/
    move_angle_speed(forward::angle, forward::speed, angle);
}