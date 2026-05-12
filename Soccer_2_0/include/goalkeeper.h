#pragma once
#include "Arduino.h"
#include "global.h"
#include "move.h"
#include "math.h"
#include "forward.h"

#include <math.h>

struct Point
{
   float x;
   float y;
};


Point findNearPoint (double xr, double yr, double xc, double yc, double r) {
    Point result = {0, 0};
    if (xr == xc)
    { 
        result.x = xc;
        result.y = yc+ r;
        return result;
    }
    if (yr == yc) { 
        result.x = xc+r;
        result.y = yr;
        return result;
    }
    double k = (yc - yr)/(xc-xr);
    double b = yr - k*xr;
    double A = k*k + 1;
    double B = 2*k *(b - yc) - 2*xc;
    double C = (b - yc)*(b - yc) - r*r + xc*xc;

    double D = B*B -4*A*C;
    double sqrtD = sqrt(D);
    double x_roots[2] = {
        (-B + sqrtD) /(2*A),
        (-B - sqrtD) /(2*A)
    };
    for (int i =0; i < 2; i++) {
        float x = x_roots[i];
        if(abs(x - xc) > r) continue;
        if((x-xc)*(xr - xc) < 0) continue;
        float y_candidate = k*x+b;
        if(y_candidate < yc) continue;
        if(x == xc && y_candidate == yc) continue;
        result.x = x;
        result.y = y_candidate;
        return result;
    }
    return result;

}



void line_goal_ball()
{
    /*Serial.print(robot::x);
    Serial.print(' ');*/
    double y = 0;

    //Serial.println('1');
    //y = (goalkeeper::line_ball_goal::major_semi_axis/goalkeeper::line_ball_goal::minor_axis)*sqrt(pow(goalkeeper::line_ball_goal::major_semi_axis,2) - pow(robot::x - goalkeeper::line_ball_goal::x_center, 2));
    double y2 = (goalkeeper::R * goalkeeper::R ) - ((robot::x - goal::our::x) * (robot::x - goal::our::x));
    y = sqrt(y2) + goal::our::y;
    /*double y2 = (goalkeeper::R * goalkeeper::R ) - ((robot::x - goal::our::x) * (robot::x - goal::our::x));
    double y = 0;
    if (y2 >= 0) y = (goalkeeper::line_ball_goal::major_semi_axis/goalkeeper::line_ball_goal::minor_axis)*sqrt(y2);
        else{ y2 = abs(y2);
            y = sqrt(y2) + goal::our::y;
        }*/



    double err_y = y - robot::y;
    
    //Serial.println(robot::y);
    static double err_old_y = err_y, err_i_y = err_y;
    double u_y = err_y*goalkeeper::k::y::kP + (err_y - err_old_y)*goalkeeper::k::y::kD+ err_i_y;
    //u_y = constrain(u_y, -goalkeeper::constrain_y, goalkeeper::constrain_y);

    // Serial.print(' ');

    /*Serial.print(err_y);
    Serial.print(' ');
    Serial.print(u_y);
    Serial.print(' ');*/
    

    double err_x = lead_to_degree_borders((ball::angle - (goal::our::local_angle + 180)));
    /*Serial.print(err_y - err_old_y);
    Serial.print(' ');
    Serial.print(err_i_y);
    Serial.print(' ');*/
    //int err_x = lead_to_degree_borders(lead_to_degree_borders((ball::angle)) - (lead_to_degree_borders(goal::our::local_angle+180)));


    static double err_old_x = err_x, err_i_x = err_x;
    double u_x = err_x*goalkeeper::k::x::kP + (err_x - err_old_x)*goalkeeper::k::x::kD+ err_i_x;
    //Serial.print(err_x - err_old_x);
    //Serial.print(' ');
    /*Serial.print(u_y);
    Serial.print(' ');
    Serial.println(err_y);*/
    //Serial.print(' ');   
    /*Serial.print(err_x);
    Serial.print(' ');
    Serial.print(u_x);
    Serial.print(' ');*/

    //Serial.println(u_x);
    //u_x = constrain(u_x, -goalkeeper::constrain_x, goalkeeper::constrain_x);
    /*if(abs(robot::x) > 35) 
    {
            u_x = constrain(u_x, -goalkeeper::constrain_x1, goalkeeper::constrain_x1);
            u_y = constrain(u_y, -goalkeeper::constrain_y1, goalkeeper::constrain_y1);

    }*/
    /*Serial.print(u_x);
    Serial.print(' ');*/
    /*Serial.print(u_x);
    Serial.print(' ');
    Serial.println(u_y);*/

    /*Serial.print(lead_to_degree_borders((ball::angle + robot::local_angle)));
    Serial.print(' ');
    Serial.print(lead_to_degree_borders(goal::our::local_angle + robot::local_angle + 180));*/
    u_x = constrain(u_x, -190, 190);
    u_y = constrain(u_y, -230, 230);
    double xy_angle = lead_to_degree_borders((90 - (atan2(u_y, u_x)* 180/3.14)));
    int xy = sqrt(pow(u_y, 2) + pow(u_x, 2));
    xy = constrain(xy, -230, 230);

    /*Serial.print(u_y);
    Serial.print(' '); */
    //Serial.print(u_x);
    //Serial.print(' ');    

    
    err_old_y = err_y;
    //////err_i_y += goalkeeper::k::y::kI*err_y;
    //err_i_y = constrain(err_i_y, -100, 100);
    err_old_x = err_x;
    err_i_x += goalkeeper::k::x::kI*err_x;
    err_i_x = constrain(err_i_x, -100, 100);

    goalkeeper::angle = xy_angle - robot::local_angle;
    goalkeeper::speed = xy;
     
    //Serial.println(goalkeeper::angle);
    //move_angle_speed(goalkeeper::angle, goalkeeper::speed, a);
    //move_angle_speed(goalkeeper::angle, goalkeeper::speed, a);
    /*Serial.print(' ');
    Serial.print(goalkeeper::speed);
    Serial.print(' ');    
    Serial.println(goalkeeper::angle);*/
    //double a = ball::angle + robot::local_angle;
    //move_angle_speed(goalkeeper::angle,  goalkeeper::speed, a);
    /*Serial.print(err_y);
    Serial.print(' ');
    Serial.print(u_y);
    Serial.print(' ');
    Serial.print(err_x);
    Serial.print(' ');
    Serial.print(u_x);
    Serial.print(' ');
    Serial.print(goalkeeper::angle);
    Serial.print(' ');
    Serial.print(goalkeeper::speed);
    Serial.print(' ');
    Serial.print(robot::x);
    Serial.print(' ');
    Serial.print(robot::y);
    Serial.print(' ');
    Serial.print(ball::angle);
    Serial.print(' ');
    Serial.println(ball::distance);*/
    //delay(100);
}

void control_outs_goalkeeper(double angle, int speed)
{
    angle = lead_to_degree_borders(angle);
    if (robot::y <  goalkeeper::outs::left_point::y)
    {
        if (abs(lead_to_degree_borders(angle + robot::local_angle)) > 60)
        {
        if ((lead_to_degree_borders(angle + robot::local_angle)) > 0)
            angle = 60 - robot::local_angle;
        else
            angle = -60 - robot::local_angle;
        }
    }

  if (robot::y < goalkeeper::outs::left_point::y + goalkeeper::outs::dist_slowdown)
  {
    if (abs(lead_to_degree_borders(angle + robot::local_angle)) > 60)
      goalkeeper::speed = constrain(speed, -80, 80);
  }

  if ((robot::x >  goalkeeper::outs::left_point::x) or (robot::x <  goalkeeper::outs::right_point::x))
  {
    if (robot::x > goalkeeper::outs::left_point::x)
    {
      if ((lead_to_degree_borders(angle + robot::local_angle) < 20) or (lead_to_degree_borders(angle + robot::local_angle) > 160))
      {
        if ((lead_to_degree_borders(angle + robot::local_angle) < -90) or (lead_to_degree_borders(angle + robot::local_angle) > 160))
          angle = 160 - robot::local_angle;
        else
          angle = 20 - robot::local_angle;
      }
    }
    else
    {
      if ((lead_to_degree_borders(angle + robot::local_angle) > -20) or (lead_to_degree_borders(angle + robot::local_angle) < -160))
      {
        if ((lead_to_degree_borders(angle + robot::local_angle) > 90) or (lead_to_degree_borders(angle + robot::local_angle) < -160))
          angle = -160 - robot::local_angle;
        else
          angle = -20 - robot::local_angle;
      }
    }
  }

  if ((robot::x > goalkeeper::outs::left_point::x - goalkeeper::outs::dist_slowdown))
  {
    if ((lead_to_degree_borders(angle + robot::local_angle)) < 20 or (lead_to_degree_borders(angle + robot::local_angle)) > 160)
      goalkeeper::speed = constrain(speed, -80, 80);
  }

  if ((robot::x < goalkeeper::outs::right_point::x + goalkeeper::outs::dist_slowdown))
  {
    if ((lead_to_degree_borders(angle + robot::local_angle)) > -20 or (lead_to_degree_borders(angle + robot::local_angle)) < -160)
      goalkeeper::speed = constrain(speed, -80, 80);
  }
/*Serial.print(forward::angle);
Serial.print(' ');
Serial.println(forward::speed);*/

    goalkeeper::angle = angle;
    goalkeeper::speed = speed;

}


void goalkeeper_s()
{
    dribler_power(1000);
   static double ball_angle_pre = ball::angle;
    static int ball_distance_pre = ball::distance;
    double a = lead_to_degree_borders(ball::angle + robot::local_angle);
   if (millis() - timers::ball_state >= 6000) 
    {
        timers::forward_state = millis();
        while (millis() - timers::forward_state <= 10000)
        {
            robot_update(); 
            coordinates_robot();
            if (stop_motors) {
                stop_m();
                dribler_power(1000);
            }
            else forward();
        }
        timers::ball_state = millis();
    }
    else
    {
    //Serial.println("+");
        static int state = 1;
        //static int state_goalkepeer = 2;
        if (robot::y >= 80) state = 2;
        else state = 1;
        switch (state)
        {
            case 1:{
            
                if (abs(ball_angle_pre - ball::angle) < 15 && abs(ball_distance_pre - ball::distance) < 50 && (ball::angle || ball::distance));
                else 
                {
                    timers::ball_state = millis();
                    ball_angle_pre = ball::angle;
                    ball_distance_pre = ball::distance;
                }
               
               //Serial.println(state_goalkepeer);

               /*switch (state_goalkepeer)
               {
               case 1: {
                    //Serial.println("1+");
                    if (abs(robot::x) <(goalkeeper::R * 0.8)) state_goalkepeer = 2;
                    double x = 0, y = 0;
                    Point pcircle = findNearPoint(robot::x, robot::y,goal::our::x, goal::our::y, goalkeeper::R);
                    x = pcircle.x;
                    y = pcircle.y;
                    a = constrain(a, -60, 60);
                    move_to_point(x - 10*abs(robot::x)/robot::x, y-10);
                    break;
               }
               case 2: {
                    //Serial.println("2+");
                    if (abs(robot::x) >(goalkeeper::R * 0.9)) 
                    {
                        state_goalkepeer = 1;
                        break;
                    }
                    line_goal_ball();
                    break;
                }
               }*/
               
               //line_goal_ball();
                if (abs(robot::x) >(goalkeeper::R * 0.9))// && abs(lead_to_degree_borders(goal::our::local_angle+180 - ball::angle) < 30)) 
                {
                    double x = 0, y = 0;
                    Point pcircle = findNearPoint(robot::x, robot::y, goalkeeper::line_ball_goal::x_center, goalkeeper::line_ball_goal::y_center, goalkeeper::R);
                    x = pcircle.x;
                    y  =constrain(pcircle.y, 0, goalkeeper::R);
                    a = constrain(a, -20, 20);
                    move_to_point(x - 10*abs(robot::x)/robot::x, y-10);
                    /*Serial.print(x);
                    Serial.print(' ');
                    Serial.println(y);*/
                }
                else line_goal_ball();
                
                if (abs(lead_to_degree_borders(ball::angle + robot::local_angle)) >  110) 
                {
                    //Serial.println(ball::distance);
                    //a = 0;
                    //a = lead_to_degree_borders(goal::our::local_angle + robot::local_angle + 180);
                    if (ball::distance <= 80) //&& (abs(lead_to_degree_borders(ball::angle)) >= 80 || abs(lead_to_degree_borders(ball::angle - goal::our::local_angle)) < 30)) 
                    {
                        goalkeeper::speed = 0;
                    }
                }
                if(abs(ball::angle) <= 5 && ball::distance == 0) 
                {
                    move_to_point(0, goalkeeper::R);
                    a = 0;
                }
                /*Serial.print(robot::x);
                    Serial.print(' ');
                    Serial.print(robot::y);
                    Serial.print(' ');
                    Serial.print(ball::angle);
                    Serial.print(' ');
                    Serial.print(ball::distance);
                    Serial.print(' ');
                   Serial.print (goalkeeper::angle);
                   Serial.print(' ');
                   Serial.println( goalkeeper::speed);*/             

                //if(if_ball_in_leadle1) kick();
                control_outs_goalkeeper(goalkeeper::angle, goalkeeper::speed);
                /*Serial.print(goalkeeper::angle);
                Serial.print(' ');
                Serial.println(goalkeeper::speed);*/
                break;
            }
            
            case 2: {
                if (abs(lead_to_degree_borders(ball::angle + robot::local_angle)) >  110) 
                {
                    //Serial.println(ball::distance);
                    //a = 0;
                    //a = lead_to_degree_borders(goal::our::local_angle + robot::local_angle + 180);
                    if (ball::distance <= 80) //&& (abs(lead_to_degree_borders(ball::angle)) >= 80 || abs(lead_to_degree_borders(ball::angle - goal::our::local_angle)) < 30)) 
                    {
                        goalkeeper::speed = 0;
                    }
                }
                timers::ball_state = millis();
                a = 0;
                control_outs_forward(180, 220);
                goalkeeper::angle = forward::angle;
                goalkeeper::speed =  forward::speed;
                break;
            }
        }
        
                /*Serial.print(robot::x);
                Serial.print(' ');
               Serial.print(goalkeeper::speed);
               Serial.print(' ');
               Serial.print(goalkeeper::angle);
               Serial.println(' ');*/
        a = constrain(a, -60, 60);
        move_angle_speed(goalkeeper::angle, goalkeeper::speed, a);
    }
//Serial.println(a);
/*Serial.print(a);
Serial.print(' ');
Serial.print(goalkeeper::angle);
Serial.print(' ');
Serial.println(goalkeeper::speed);*/
}