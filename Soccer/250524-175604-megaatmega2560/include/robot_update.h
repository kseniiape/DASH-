#pragma once

#include "buttons.h"
#include "camera.h"
#include "config.h"
#include "gyro_and_angle.h"
#include "robot_update.h"
#include "strategy.h"
#include "tssop.h"
#include "gyro_and_angle.h"
#include "global.h"

void camera_data();
void detect_ball();
void but_motors();
void change_goal(); 
void reset_imu();

void robot_update()
{
  gyro_angle = gyro_data();
  robot_local_angle = lead_to_degree_borders(gyro_angle - null_angle);
  reset_imu();
  camera_data();
  detect_ball();
  but_motors();
  change_goal();
  if_notice_goal();
  if_sen_leadle();
  control_charge();
}
