void update()
{
  robot_local_angle = lead_to_degree_borders(gyro_data());
  //move_robot (robot_angle, robot_speed);
  camera_data();
  detect_ball();
}

/*void move_robot (int angle, int speed_m)
{
  robot_speed = constrain(speed_m, -255, 255);
  angle = abs(angle);
  local_angle = lead_to_degree_borders(angle);
}*/
