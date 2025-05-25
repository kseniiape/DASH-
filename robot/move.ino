void move_angle_speed (double angle, int speed_m, double angle_turn)
{
  if (robot_role == 'F')
  {
    double angle1 = angle - 135;
    double angle3 = angle + 135;
    double angle2 = angle - 45;
    double angle4 = angle + 45;

    int speed1 = -speed_m * cos(angle1 / 57.3) + turn_angle(angle_turn);
    int speed3 = -speed_m * cos(angle3 / 57.3) - turn_angle(angle_turn);
    int speed2 = -speed_m * cos(angle2 / 57.3) - turn_angle(angle_turn);
    int speed4 = speed_m * cos(angle4 / 57.3) - turn_angle(angle_turn);
    
    motor1(speed1);
    motor3(speed3);
    motor2(speed2);
    motor4(speed4);
  }

  else
  {
    double angle1 = angle - 135;
    double angle3 = angle + 135;
    double angle2 = angle - 45;
    double angle4 = angle + 45;

    int speed1 = -speed_m * cos(angle1 / 57.3) + turn_angle(angle_turn);
    int speed3 = speed_m * cos(angle3 / 57.3) + turn_angle(angle_turn);
    int speed2 = speed_m * cos(angle2 / 57.3) + turn_angle(angle_turn);
    int speed4 = speed_m * cos(angle4 / 57.3) - turn_angle(angle_turn);
    
    motor1(speed1);
    motor3(speed3);
    motor2(speed2);
    motor4(speed4);
  }


}
