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
    /*Serial.print((goalkeeper::R * goalkeeper::R ) - ((robot::x - goal::our::x) * (robot::x - goal::our::x)));
    Serial.print(' ');
    Serial.print((robot::x - goal::our::x) * (robot::x - goal::our::x));
    Serial.print(' ');
    Serial.print(robot::x);
    Serial.print(' ');
    Serial.println(goal::our::x);*/
    /*Serial.print(' ');
    Serial.print(y);
    Serial.print(' ');
    Serial.print(robot::y);
    //Serial.println(robot::y);*/
    static double err_old_y = err_y, err_i_y = err_y;
    double u_y = err_y*goalkeeper::k::y::kP + (err_y - err_old_y)*goalkeeper::k::y::kD+ err_i_y;
    //u_y = constrain(u_y, -goalkeeper::constrain_y, goalkeeper::constrain_y);

    // Serial.print(' ');

    /*Serial.print(err_y);
    Serial.print(' ');
    Serial.print(u_y);
    Serial.print(' ');*/
    

    double err_x = lead_to_degree_borders((ball::angle - (goal::our::local_angle + 180)));
    /*Serial.print(ball::angle);
    Serial.print(' ');
    Serial.println(goal::our::local_angle + 180);*/
    //int err_x = lead_to_degree_borders(lead_to_degree_borders((ball::angle)) - (lead_to_degree_borders(goal::our::local_angle+180)));


    static double err_old_x = err_x, err_i_x = err_x;
    double u_x = err_x*goalkeeper::k::x::kP + (err_x - err_old_x)*goalkeeper::k::x::kD+ err_i_x;
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

    double xy_angle = lead_to_degree_borders((90 - (atan2(u_y, u_x)* 180/3.14)));
    int xy = sqrt(pow(u_y, 2) + pow(u_x, 2));
    xy = constrain(xy, -230, 230);

    /*Serial.print(u_y);
    Serial.print(' '); */
    //Serial.print(u_x);
        //Serial.print(' ');    


    
    err_old_y = err_y;
    err_i_y += goalkeeper::k::y::kI*err_y;
    err_old_x = err_x;
    err_i_x += goalkeeper::k::x::kI*err_x;

    goalkeeper::angle = xy_angle - robot::local_angle;
    goalkeeper::speed = xy;
    //Serial.println(goalkeeper::speed);
    //Serial.print(' ');    
    //Serial.println(goalkeeper::angle);
    //move_angle_speed(goalkeeper::angle, goalkeeper::speed, a);
    //move_angle_speed(goalkeeper::angle, goalkeeper::speed, a);
    /*Serial.print(' ');
    Serial.print(goalkeeper::speed);
    Serial.print(' ');    
    Serial.println(goalkeeper::angle);*/
    double a = ball::angle + robot::local_angle;
    //move_angle_speed(goalkeeper::angle,  goalkeeper::speed, a);
}

void control_outs_goalkeeper(double angle, int speed)
{
    /*if (robot::y > 170) 
    {
        forward::outs::left_far_point::x =   forward::outs::left_far_point::x - 5;
        forward::outs::right_near_point::x = forward::outs::right_near_point::x+  5;
    }*/
    angle = lead_to_degree_borders(angle);
    double absolute_angle = lead_to_degree_borders(angle + robot::local_angle);
    if(robot::x < goalkeeper::outs::right_point::x)
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
    if (robot::x < goalkeeper::outs::right_point::x + goalkeeper::outs::dist_slowdown) speed = constrain(speed, -speed_constrain, speed_constrain);
    else if (robot::x > goalkeeper::outs::left_point::x)
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
    if (robot::x > goalkeeper::outs::left_point::x - goalkeeper::outs::dist_slowdown) speed = constrain(speed, -speed_constrain, speed_constrain);


    if(robot::y < goalkeeper::outs::right_point::y)
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
    if(robot::y < goalkeeper::outs::right_point::y + goalkeeper::outs::dist_slowdown) speed = constrain(speed, -speed_constrain, speed_constrain);
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
   if (millis() - timers::ball_state >= 8000) 
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
        static int state = 1;
        if (robot::y >= 80) state = 2;
        else state = 1;
        switch (state)
        {
            case 1:
                if (abs(ball_angle_pre - ball::angle) < 10 && abs(ball_distance_pre - ball::distance) < 1.5);
                else 
                {
                    timers::ball_state = millis();
                    ball_angle_pre = ball::angle;
                    ball_distance_pre = ball::distance;
                }
                if (abs(robot::x) >(goalkeeper::R))// && abs(lead_to_degree_borders(goal::our::local_angle+180 - ball::angle) < 30)) 
                {
                    double x = 0, y = 0;
                    Point pcircle = findNearPoint(robot::x, robot::y,goal::our::x, goal::our::y, goalkeeper::R);
                    x = pcircle.x;
                    y  = pcircle.y;
                    move_to_point(x-10, y);
                    /*Serial.print(x);
                    Serial.print(' ');
                    Serial.println(y);*/
                }
                else line_goal_ball();
                if (abs(lead_to_degree_borders(ball::angle + robot::local_angle)) > 150) 
                {
                    //a = 0;
                    a = lead_to_degree_borders(goal::our::local_angle + robot::local_angle + 180);
                    if (ball::distance >= 7 && (abs(lead_to_degree_borders(ball::angle)) >= 80 || abs(lead_to_degree_borders(ball::angle - goal::our::local_angle)) < 30)) 
                    {
                        goalkeeper::speed = 0;
                    }
                }
                

                if(if_ball_in_leadle1) kick();
                control_outs_goalkeeper(goalkeeper::angle, goalkeeper::speed);
                /*Serial.print(goalkeeper::angle);
                Serial.print(' ');
                Serial.println(goalkeeper::speed);*/
                break;
            
            case 2:
                timers::ball_state = millis();
                a = 0;
                control_outs_forward(180, 220);
                goalkeeper::angle = forward::angle;
                goalkeeper::speed =  forward::speed;
                break;
        }
        if(abs(lead_to_degree_borders(ball::angle + robot::local_angle)) <= 10) 
        {
            move_to_point(0, goalkeeper::line_ball_goal::minor_axis);
            a = 0;
        }
        a = constrain(a, -70, 70);
        move_angle_speed(goalkeeper::angle, goalkeeper::speed, a);
    }
//Serial.println(a);
/*Serial.print(a);
Serial.print(' ');
Serial.print(goalkeeper::angle);
Serial.print(' ');
Serial.println(goalkeeper::speed);*/
}