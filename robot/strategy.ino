/*void coordinates_robot (int local_angle, int b_l_a, int y_l_a, int b_d, int y_d)
{
  int b_a = b_l_a + local_angle;
  int y_a = y_l_a + local_angle;
  int x_b = blue_goal_x + b_d * sin((b_a - 90) / (3.14 / 180));
  int y_b = blue_goal_y + b_d * cos((b_a - 90) / (3.14 / 180));
  int x_y = yellow_goal_x + y_d * sin((y_a - 90) / (3.14 / 180));
  int y_y = yellow_goal_y + y_d * cos((y_a - 90) / (3.14 / 180));
  //float k_b = b_d/(yellow_goal_y - blue_goal_y);
  //float k_y = (-y_d /(yellow_goal_y - blue_goal_y)) + 1;
  float k = (b_d - y_d + yellow_goal_y - blue_goal_y) / (2 * (yellow_goal_y - blue_goal_y));
  y_robot = (1 - k) * y_b + k * y_y;
  x_robot = (1 - k) * x_b + k * x_y;
}*/


void ball_capture ()
{
  if (ball_distance < min_dist_to_ball)
    move_angle_speed (ball_angle, v_capture);
  else
  {
    if (abs(ball_angle) < 30)
      move_angle_speed(ball_angle, v_capture);
    else
  {
    if (ball_angle > 0)
      move_angle_speed(ball_angle + 90, v_capture);
    else
      move_angle_speed(ball_angle - 90, v_capture);
  }
 }
 //move_angle_speed (ball_angle, v_capture);
}

 int if_sen_leadle()
{
  if (digitalRead(SEN_LEADLE) == 1) return 0;
  else return 1;
}
