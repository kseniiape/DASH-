void forward()
{
  ball_capture(150);
  angle_forward = control_outs(angle_forward);
  move_angle_speed(angle_forward, speed_forward, e_a);
}

double control_outs (double angle)
{
  angle = lead_to_degree_borders(angle);
  if ((x_robot > out1_x)  or (x_robot < out2_x))
  {
    if (x_robot > out1_x)
    {
      if ((angle + robot_local_angle) < 20 or (angle + robot_local_angle) > 160)
      {
        if ((angle + robot_local_angle) < -90 or ((angle + robot_local_angle) > 160 and (angle + robot_local_angle) < 180)) angle = 160 - robot_local_angle;
        else angle = 20 - robot_local_angle;
      }
    
    }

    else
    {
      if ((angle + robot_local_angle) > -20 or (angle + robot_local_angle) < -160)
      {
        if ((angle + robot_local_angle) > 90 or ((angle + robot_local_angle) > -180 and (angle + robot_local_angle) < -160)) angle = -160 - robot_local_angle;
        else angle = -20 - robot_local_angle;
      }
    }
  }

  if ((y_robot > out1_y)  or (y_robot < out3_y))
  {
    if (y_robot > out1_y)
    {
      if (abs(angle + robot_local_angle) < 120)
      {
        if ((angle + robot_local_angle) > 0) angle = 120 - robot_local_angle;
        else angle = -120 - robot_local_angle;
      }
    }

    else
    {
      if (abs(angle + robot_local_angle) > 60)
      {
        if ((angle + robot_local_angle) > 0) angle = 60 - robot_local_angle;
        else angle = -60 - robot_local_angle;
      }
    }
  }
  angle = lead_to_degree_borders(angle);
  return angle;
}

void goalkeeper()
{
  line_goal_ball();
}

void line_goal_ball()
{

  /*if (x_robot <= x1 and x_robot >= x2)
    {*/
  int y_goalkepeer = sqrt((R * R) - ((x_robot - our_goal_x) * (x_robot - our_goal_x))) + our_goal_y;

  err_y = y_goalkepeer - y_robot;
  if (err_y < 0)
  {
    angle_y = 180;
    u_y = -(err_y * Kp_line_goal + (err_y - err_old_y) * Kd_line_goal + Ki_line_goal * err_y + err_i_y);
  }
  else
  {
    angle_y = 0;
    u_y = err_y * Kp_line_goal + (err_y - err_old_y) * Kd_line_goal + Ki_line_goal * err_y + err_i_y;
  }
  err_x = lead_to_degree_borders(lead_to_degree_borders((ball_angle)) - (lead_to_degree_borders(our_local_angle + 180)));
  if (err_x > 0)
  {
    angle_x = 90;
    u_x = Kp_line_goal_ball * err_x + (err_x - err_old_x) * Kd_line_goal_ball + Ki_line_goal_ball * err_x + err_i_x;
  }
  else
  {
    angle_x = -90;
    u_x = -(Kp_line_goal_ball * err_x + (err_x - err_old_x) * Kd_line_goal_ball + Ki_line_goal_ball * err_x + err_i_x);
  }
  xy = sqrt(u_y * u_y + u_x * u_x);
  if (angle_y == 0) angle_xy = sign(angle_x) * lead_to_degree_borders(90 - (atan2(u_y, u_x) * 57.3));
  else angle_xy = lead_to_degree_borders(sign(angle_x) * lead_to_degree_borders((atan2(u_y, u_x) * 57.3) + 90));
  //}

  /* else
    {
     if (x_robot > x1) x_goalkepeer = x1;
     else x_goalkepeer = x2;
     err_x = x_goalkepeer - x_robot;
     if (err_x < 0)
     {
       angle_x = 90;
       u_x = -(Kp_line_goal_ball * err_x + (err_x - err_old_x) * Kd_line_goal_ball + Ki_line_goal_ball * err_x + err_i_x);
     }
     else
     {
       angle_x = -90;
       u_x = Kp_line_goal_ball * err_x + (err_x - err_old_x) * Kd_line_goal_ball + Ki_line_goal_ball * err_x + err_i_x;
     }
     err_y = lead_to_degree_borders(lead_to_degree_borders((ball_angle + robot_local_angle)) - (lead_to_degree_borders(o_a + 180)));
     if (err_y > 0)
     {
       angle_x = 180;
       u_y = err_y * Kp_line_goal + (err_y - err_old_y) * Kd_line_goal + Ki_line_goal * err_y + err_i_y;
     }
     else
     {
       angle_y = 0;
       u_y = -(err_y * Kp_line_goal + (err_y - err_old_y) * Kd_line_goal + Ki_line_goal * err_y + err_i_y);
     }
     if (angle_y == 0) angle_xy = sign(angle_x) * lead_to_degree_borders(90 - (atan2(u_y, u_x) * 57.3));
    else angle_xy = lead_to_degree_borders(sign(angle_x) * lead_to_degree_borders((atan2(u_y, u_x) * 57.3) + 90));
    }
    xy = sqrt(u_y * u_y + u_x * u_x);*/



  /*if (x_robot > x1)x_robot_point1 = x_robot - x1;
    else x_robot_point1 = x2 - x_robot;
    int y_robot_point1 = y_robot - y1;
    int r_robot_point1 = sqrt( x_robot_point1 * x_robot_point1 + y_robot_point1 * y_robot_point1);
    int angle_robot_point2 = lead_to_degree_borders(90 - asin(x_robot_point1 / r_robot_point1) * 57.3);
    angle2_robot_point2 = 180 - angle_robot_point2 - (180 - 45);
    int r_robot_line = (r_robot_point1 / sin((180 - 45) / 57.3)) * sin(angle2_robot_point2 / 57.3);
    int r_robot_point2 = r_robot_line * sin(45 / 57.3);
    y_goalkepeer = y_robot - (r_robot_point2 * cos(45 / 57.3));*/
  // if (x_robot < x2)angle_xy + 90;
  //else if (x_robot > x1)angle_xy - 90;

  err_old_y = err_y;
  err_old_x = err_x;
  err_i_y  = Ki_line_goal * err_y;
  err_i_x = err_x * Ki_line_goal_ball * err_x;
  /*Serial.print(err_y);
    Serial.print(" ");
    Serial.print(err_x);
    Serial.print(" ");
    Serial.print(u_y);
    Serial.print(" ");
    Serial.print(u_x);
    Serial.print(" ");
    //Serial.print(sq_x + sq_y);
    Serial.print(" ");
    Serial.print(angle_xy);
    Serial.print(" ");
    Serial.print(xy);
    Serial.println(" ");*/
  move_angle_speed(angle_xy, xy, ball_angle);
}

float sign (float num)
{
  if (num >= 0) return 1;
  else return -1;
}
void kick()
{
  //if ((millis() - timer_kick) > 3000)
  //{
  digitalWrite(KICK_PIN1, 1);
  delay(10);
  digitalWrite(KICK_PIN1, 0);
  timer_kick = millis();
  //}
}

void coordinates_robot()
{
  o_a = our_local_angle + robot_local_angle;
  e_a = enemy_local_angle + robot_local_angle;
  x_o = our_goal_x + our_distance * sin((180 - o_a) * 3.14 / 180.0);
  y_o = our_goal_y + our_distance * cos((180 - o_a) * 3.14 / 180.0);
  x_e = enemy_goal_x + enemy_distance * sin(e_a * 3.14 / 180.0);
  y_e = enemy_goal_y - enemy_distance * cos(e_a * 3.14 / 180.0);

  //float k_b = b_d/(yellow_goal_y - blue_goal_y);
  //float k_y = (-y_d /(yellow_goal_y - blue_goal_y)) + 1;
  if (if_notice_our == true and if_notice_enemy == true)
  {
    float k = (our_distance - enemy_distance + enemy_goal_y - our_goal_y) / (2 * (enemy_goal_y - our_goal_y));
    //Serial.println(k);
    y_robot = (1 - k) * y_o + k * y_e;
    x_robot = (1 - k) * x_o + k * x_e;
  }
  else
  {
    if (if_notice_our == true)
    {
      y_robot = y_o;
      x_robot = x_o;
    }
    else
    {
      y_robot = y_e;
      x_robot = x_e;
    }
  }
}



void if_notice_goal()
{
  if (our_distance == 0) if_notice_our = false;
  else if_notice_our = true;
  if (enemy_distance == 0) if_notice_enemy = false;
  else if_notice_enemy = true;
}



void ball_capture (int v_capture)
{
  if (ball_distance < min_dist_to_ball) angle_forward = ball_angle;
  //move_angle_speed (ball_angle, v_capture, angle);

  else
  {
    if (abs(ball_angle) < 30)angle_forward = ball_angle;
    //move_angle_speed(ball_angle, v_capture, angle);

    else
    {
      if (ball_angle > 0) angle_forward = ball_angle + 90;
      //move_angle_speed(ball_angle + 90, v_capture, angle);

      else angle_forward = ball_angle - 90;
      //move_angle_speed(ball_angle - 90, v_capture, angle);
      //}

    }
  }
  speed_forward = v_capture;
  //move_angle_speed (ball_angle, v_capture);
}

void if_sen_leadle()
{
  if (analogRead(SEN_LEADLE) >  400) if_ball_in_leadle = false;
  else if_ball_in_leadle = true;
}
