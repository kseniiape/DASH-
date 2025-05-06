int16_t lead_to_degree_borders(int angle)
{
  if (angle > 180) angle -= 360;
  else if (angle < -180) angle += 360;
  return angle;

}

int gyro_data() {
  if (Serial1.available() >= 2)
  {
    byte prev_sense = Serial1.read();
    byte sense = Serial1.read();
    if (prev_sense == 255)
    {
      int angle_gyro = lead_to_degree_borders((byte)sense * 2);
      return angle_gyro;
    }
  }
}

int turn_angle (int angle) {
  //gyro_data();
  int err_angle = angle - robot_local_angle;
  int u = err_angle * kP;
  return u;
}




void calibration_imu()
{
  for (; (millis() - timer) < 10000;);
  digitalWrite(LED_CALIBRATION, 1);
}
