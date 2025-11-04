#pragma once
#include "Arduino.h"
#include "global.h"
#include "move.h"
#include "math.h"
#include "forward.h"

void line_goal_ball()
{
   int y = (goalkeeper::line_ball_goal::major_semi_axis/goalkeeper::line_ball_goal::minor_axis)*sqrt(pow(goalkeeper::line_ball_goal::major_semi_axis,2) - pow(robot::x - goalkeeper::line_ball_goal::x_center, 2));
    //int y = sqrt((goalkeeper::R * goalkeeper::R ) - ((robot::x - goal::our::x) * (robot::x - goal::our::x))) + goal::our::y;
    int err_y = y - robot::y;
    static int err_old_y = err_y, err_i_y = err_y;
    int u_y = err_y*goalkeeper::k::y::kP + (err_y - err_old_y)*goalkeeper::k::y::kD+ err_i_y;
    u_y = constrain(u_y, -goalkeeper::constrain_y, goalkeeper::constrain_y);

    /*Serial.print(u_y);
    Serial.print(' ');*/

    int err_x = lead_to_degree_borders(lead_to_degree_borders((ball::angle + robot::local_angle)) - (lead_to_degree_borders(goal::our::local_angle + robot::local_angle + 180)));
    //int err_x = lead_to_degree_borders(lead_to_degree_borders((ball::angle)) - (lead_to_degree_borders(goal::our::local_angle+180)));


    static int err_old_x = err_x, err_i_x = err_x;
    int u_x = err_x*goalkeeper::k::x::kP + (err_x - err_old_x)*goalkeeper::k::x::kD+ err_i_x;
    u_x = constrain(u_x, -goalkeeper::constrain_x, goalkeeper::constrain_x);
    /*Serial.print(u_x);
    Serial.print(' ');*/

    /*Serial.print(lead_to_degree_borders((ball::angle + robot::local_angle)));
    Serial.print(' ');
    Serial.print(lead_to_degree_borders(goal::our::local_angle + robot::local_angle + 180));*/

    int xy_angle = lead_to_degree_borders(90 - (atan2(u_y, u_x)* 180/3.14));
    int xy = sqrt(pow(u_y, 2) + pow(u_x, 2));
    xy = constrain(xy, -230, 230);

    /*Serial.print(' ');    
    Serial.println(xy_angle);*/

    
    err_old_y = err_y;
    err_i_y += goalkeeper::k::y::kI*err_y;
    err_old_x = err_x;
    err_i_x += goalkeeper::k::x::kI*err_x;

    goalkeeper::angle = xy_angle - robot::local_angle;
    goalkeeper::speed = xy;

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
    else if (robot::x < goalkeeper::outs::right_point::x + goalkeeper::outs::dist_slowdown) speed = constrain(speed, -speed_constrain, speed_constrain);
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
    else if (robot::x > goalkeeper::outs::left_point::x - goalkeeper::outs::dist_slowdown) speed = constrain(speed, -speed_constrain, speed_constrain);


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
    else if(robot::y < goalkeeper::outs::right_point::y + goalkeeper::outs::dist_slowdown) speed = constrain(speed, -speed_constrain, speed_constrain);
/*Serial.print(forward::angle);
Serial.print(' ');
Serial.println(forward::speed);*/

    goalkeeper::angle = angle;
    goalkeeper::speed = speed;

}


void goalkeeper_s()
{
   static double ball_angle_pre = ball::angle;
    static int ball_distance_pre = ball::distance;
    double a = lead_to_degree_borders(ball::angle + robot::local_angle);
    if (millis() - timers::ball_state >= 7000) 
    {
        timers::forward_state = millis();
        while (millis() - timers::forward_state <= 10000)
        {
            robot_update(); 
            coordinates_robot();
            if (stop_motors) {
                stop_m();
                //dribler_power(1000);
            }
            else forward();
        }
        timers::ball_state = millis();
    }
    else
    {
        static int state = 1;
        if (robot::y >= 100) state = 2;
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
            line_goal_ball();
            if (abs(ball::angle) >= 160) 
            {
                //a = lead_to_degree_borders(goal::our::local_angle + robot::local_angle + 180);
                a = 0;
                if (ball::distance >= 9 && abs(ball::angle) >= 170) goalkeeper::speed = 0;
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
        
    a = constrain(a, -90, 90);
    move_angle_speed(goalkeeper::angle, goalkeeper::speed, a);
    }
//Serial.println(a);
/*Serial.print(a);
Serial.print(' ');
Serial.print(goalkeeper::angle);
Serial.print(' ');
Serial.println(goalkeeper::speed);*/
}