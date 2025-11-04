#pragma once
#include "Arduino.h"

#include "buttons.h"
#include "camera.h"
#include "config.h"
#include "gyro.h"
#include "function_for_angle.h"
#include "tssop.h"
#include "for_strategy.h"


#include "global.h"

void camera_data();
void detect_ball();
void but_motors();
void change_goal(); 
void reset_imu();
void if_notice_goal();
void coordinates_robot();
void if_sen_leadle1();
void if_sen_leadle2();

void robot_update()
{
  gyro::angle = gyro_data();//
  
  robot::local_angle= lead_to_degree_borders(gyro::angle - gyro::null_angle);//
  if_sen_leadle2();
  camera_data();
  if_sen_leadle1();//
  detect_ball();//
  but_motors();//
  reset_imu();//
  change_goal();//
  if_notice_goal();

}
