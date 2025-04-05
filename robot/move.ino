void move_angle_speed (double angle, int speed_m) 

{
  double angle1 = angle + 45;
  double angle3 = angle + 45;
  double angle2 = angle - 45;
  double angle4 = angle - 45;

  int speed1 = speed_m * cos(angle1 / 57.3);
  int speed3 = speed_m * cos(angle3 / 57.3);
  int speed2 = speed_m * cos(angle2 / 57.3);
  int speed4 = speed_m * cos(angle4 / 57.3);

  motor1(speed1);
  motor3(speed3);
  motor2(speed2);
  motor4(speed4);
}
