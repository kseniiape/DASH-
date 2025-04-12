void robot_update()
{
  gyro_angle = gyro_data();
  robot_local_angle = lead_to_degree_borders(gyro_angle - null_angle);
  reset_imu();
  camera_data();
  detect_ball();
  calibration_imu();
  but_motors();
}
