#pragma once

#include "Arduino.h"
#include "config.h"
#include "global.h"
#include "for_strategy.h"
#include "motors.h"
#include "gyro.h"
#include "function_for_angle.h"

int turn_angle (int angle) {

  float err_angle = lead_to_degree_borders(angle - robot::local_angle) ;
  static float err_old_angle = err_angle;
  int u = err_angle * kP_turn_angle + (err_angle - err_old_angle)*kD_turn_angle;
  #if ROLE == 2
  u = constrain(u, -30, 30); 
  #else
  u =constrain(u, -50, 50); 
  #endif
  err_old_angle = err_angle;
  
  
  return u;
}



void turn(int num)
{
  motor1(num);
  motor2(-num);
  motor3(num);
  motor4(-num);
}

void move_angle_speed (double angle, int speed_m, double angle_turn)
{
  #if ROLE == 1
    double angle1 = angle + 45;
    double angle3 = angle - 135;
    double angle2 = angle - 45;
    double angle4 = angle + 135;
    int a = turn_angle(angle_turn);

    int speed1 = -speed_m * cos(angle1 / 57.3) + a;
    int speed3 = -speed_m * cos(angle3 / 57.3)+ a;
    int speed2 = -speed_m * cos(angle2 / 57.3)- a;
    int speed4 = -speed_m * cos(angle4 / 57.3)- a;
    
   /*Serial.print(angle1);
    Serial.print(' ');
    Serial.print(speed1);
        Serial.print(' ');
    Serial.print(angle2);
    Serial.print(' ');
    Serial.print(speed2);
        Serial.print(' ');
     Serial.print(angle3);
    Serial.print(' ');
    Serial.print(speed3);
        Serial.print(' ');
            Serial.print(angle4);
    Serial.print(' ');
    Serial.print(speed4);
        Serial.println(' ');*/

    motor1(speed1);
    motor3(speed3);
    motor2(speed2);
    motor4(speed4);


  #else if ROLE == 2
    double angle1 = angle + 45;
    double angle3 = angle - 135;
    double angle2 = angle - 45;
    double angle4 = angle + 135;

    int a = turn_angle(angle_turn);
    int speed1 = speed_m * cos(angle1 / 57.3) - a;
    int speed3 = -speed_m * cos(angle3 / 57.3) + a;
    int speed2 = speed_m * cos(angle2 / 57.3) + a;
    int speed4 = speed_m * cos(angle4 / 57.3) + a;
    
    motor1(speed1);
    motor3(speed3);
    motor2(speed2);
    motor4(speed4);
  
  #endif
}


void move_to_point(int x_point, int y_point) 

{//int y = sqrt(((pow(goalkeeper::line_ball_goal::major_semi_axis,2) *pow(goalkeeper::line_ball_goal::minor_axis, 2)) - pow(goalkeeper::line_ball_goal::y_center,2) - (pow(goalkeeper::line_ball_goal::minor_axis, 2)) * (pow(robot::x - goalkeeper::line_ball_goal::x_center, 2))/(pow(goalkeeper::line_ball_goal::major_semi_axis,2) - 2*pow(goalkeeper::line_ball_goal::major_semi_axis,2)*goalkeeper::line_ball_goal::y_center)));
    //int y = (goalkeeper::line_ball_goal::major_semi_axis/goalkeeper::line_ball_goal::minor_axis)*sqrt(pow(goalkeeper::line_ball_goal::major_semi_axis,2) - pow(robot::x - goalkeeper::line_ball_goal::x_center, 2));
    //int y = sqrt((goalkeeper::R * goalkeeper::R ) - ((robot::x - goal::our::x) * (robot::x - goal::our::x))) + goal::our::y;
    int err_y = y_point - robot::y;
    static int err_old_y = err_y, err_i_y = err_y;
    int u_y = err_y*goalkeeper::k::y::kP + (err_y - err_old_y)*goalkeeper::k::y::kD+ err_i_y;
    u_y = constrain(u_y, -goalkeeper::constrain_y, goalkeeper::constrain_y);

    /*Serial.print(u_y);
    Serial.print(' ');*/

    //int err_x = lead_to_degree_borders(lead_to_degree_borders((ball::angle + robot::local_angle)) - (lead_to_degree_borders(goal::our::local_angle + robot::local_angle + 180)));
    int err_x = -(x_point - robot::x);


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
    xy = constrain(xy, -110, 110);

    /*Serial.print(' ');    
    Serial.println(xy_angle);*/

    
    err_old_y = err_y;
    err_i_y += goalkeeper::k::y::kI*err_y;
    err_old_x = err_x;
    err_i_x += goalkeeper::k::x::kI*err_x;
 
  forward::angle = xy_angle;
  forward::speed = xy;

    //move_angle_speed(forward::angle, forward::speed, 0);

}






