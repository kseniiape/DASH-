void forward()
{
  if (if_ball_in_leadle == true)
  {
    if (abs(e_a) < 60) {
      if (enemy_distance < 160) kick();
      ball_capture(190);
    }
  }
  else ball_capture(190);
  angle_forward = control_outs(angle_forward, speed_forward);
  //Serial.println(if_ball_in_leadle);
  if (if_notice_enemy == true) move_angle_speed(angle_forward, speed_forward, e_a);
  else move_angle_speed (angle_forward, speed_forward, 0);
  //Serial.println('-');
}

double control_outs (double angle, int speed_r)
{
  angle = lead_to_degree_borders(angle);
  if ((x_robot > out1_x)  or (x_robot < out2_x))
  {
    if (x_robot > out1_x)
    {
      if ((lead_to_degree_borders(angle + robot_local_angle)) < 20 or (lead_to_degree_borders(angle + robot_local_angle)) > 160)
      {
        if ((lead_to_degree_borders(angle + robot_local_angle)) < -90 or (lead_to_degree_borders(angle + robot_local_angle)) > 160) angle = 160 - robot_local_angle;
        else angle = 20 - robot_local_angle;
      }
    }
    else
    {
      if ((lead_to_degree_borders(angle + robot_local_angle)) > -20 or (lead_to_degree_borders(angle + robot_local_angle)) < -160)
      {
        if ((lead_to_degree_borders(angle + robot_local_angle)) > 90 or (lead_to_degree_borders(angle + robot_local_angle)) < -160) angle = -160 - robot_local_angle;
        else angle = -20 - robot_local_angle;
      }
    }
  }

  if ((x_robot > out1_x2))
  {
    if ((lead_to_degree_borders(angle + robot_local_angle)) < 20 or (lead_to_degree_borders(angle + robot_local_angle)) > 160) speed_forward = constrain(speed_r, -120, 120);

  }

  if ((x_robot < out2_x2))
  {
    if ((lead_to_degree_borders(angle + robot_local_angle)) > -20 or (lead_to_degree_borders(angle + robot_local_angle)) < -160) speed_forward = constrain(speed_r, -120, 120);
  }

  if ((y_robot > out1_y)  or (y_robot < out3_y))
  {
    if (y_robot > out1_y)
    {
      if (abs(lead_to_degree_borders(angle + robot_local_angle)) < 120)
      {
        if ((lead_to_degree_borders(angle + robot_local_angle)) > 0) angle = 120 - robot_local_angle;
        else angle = -120 - robot_local_angle;
      }
    }

    else
    {
      if (abs(angle + robot_local_angle) > 60)
      {
        if ((lead_to_degree_borders(angle + robot_local_angle)) > 0) angle = 60 - robot_local_angle;
        else angle = -60 - robot_local_angle;
      }
    }
  }

  if ((y_robot > out1_y2))
  {
    if (abs(lead_to_degree_borders(angle + robot_local_angle)) < 120) speed_forward = constrain(speed_r, -120, 120);
  }

  if (y_robot < out3_y2)
  {
    if (abs(lead_to_degree_borders(angle + robot_local_angle)) > 60)speed_forward = constrain(speed_r, -120, 120);
  }

  angle = lead_to_degree_borders(angle);
  return angle;
}

void goalkeeper()
{
  if (y_robot < 100)
  {
    /*if((abs(lead_to_degree_borders(ball_angle + robot_local_angle)) <= 5) and ball_distance > 4)
      {
      move_angle_speed(0, 200, 0);
      delay(600);
      move_angle_speed(180, 200, 0);
      delay(600);
      }*/
    //Serial.println('-');
    line_goal_ball();
    /*Serial.print(angle_goalkeeper);
       Serial.print(' ');
      Serial.println(speed_goalkeeper);*/
    angle_goalkeeper = control_outs_g(angle_goalkeeper, speed_goalkeeper);
    if (abs(lead_to_degree_borders(ball_angle)) <= 120) move_angle_speed(angle_goalkeeper, speed_goalkeeper, ball_angle);
    else
    {
      if (ball_distance >= 7)move_angle_speed(0, 0, 0);
      else move_angle_speed(angle_goalkeeper, angle_goalkeeper, lead_to_degree_borders(o_a + 180));
    }
  }
  else
  {
    //Serial.println('+');
    angle_goalkeeper = control_outs(180, 200);
    speed_goalkeeper = speed_forward;
    //move_angle_speed(angle_goalkeeper, angle_goalkeeper, 0);
    if ((ball_distance >= 6) and abs(lead_to_degree_borders(ball_angle + robot_local_angle)) >= 170) move_angle_speed(0, 0, 0);
    else move_angle_speed(angle_goalkeeper, speed_goalkeeper, 0);
  }
  //move_angle_speed(angle_goalkeeper,speed_goalkeeper, angle_rout_goalkeeper)
}


double control_outs_g (double angle, int speed_r)
{
  angle = lead_to_degree_borders(angle);
  if (y_robot < out1_y_g)
  {
    if (abs(lead_to_degree_borders(angle + robot_local_angle)) > 60)
    {
      if ((lead_to_degree_borders(angle + robot_local_angle)) > 0) angle = 60 - robot_local_angle;
      else angle = -60 - robot_local_angle;
    }
  }

  if (y_robot < out1_y2_g)
  {
    if (abs(lead_to_degree_borders(angle + robot_local_angle)) > 60)speed_goalkeeper = constrain(speed_r, -100, 100);
  }



  if ((x_robot > out1_x_g)  or (x_robot < out2_x_g))
  {
    if (x_robot > out1_x_g)
    {
      if ((lead_to_degree_borders(angle + robot_local_angle) < 20) or (lead_to_degree_borders(angle + robot_local_angle) > 160))
      {
        if ((lead_to_degree_borders(angle + robot_local_angle) < -90) or (lead_to_degree_borders(angle + robot_local_angle) > 160)) angle = 160 - robot_local_angle;
        else angle = 20 - robot_local_angle;
      }
    }
    else
    {
      if ((lead_to_degree_borders(angle + robot_local_angle) > -20) or (lead_to_degree_borders(angle + robot_local_angle) < -160))
      {
        if ((lead_to_degree_borders(angle + robot_local_angle) > 90) or  (lead_to_degree_borders(angle + robot_local_angle) < -160)) angle = -160 - robot_local_angle;
        else angle = -20 - robot_local_angle;
      }
    }
  }

  if ((x_robot > out1_x2_g))
  {
    if ((lead_to_degree_borders(angle + robot_local_angle)) < 20 or (lead_to_degree_borders(angle + robot_local_angle)) > 160) speed_goalkeeper = constrain(speed_r, -100, 100);

  }

  if ((x_robot < out2_x2_g))
  {
    if ((lead_to_degree_borders(angle + robot_local_angle)) > -20 or (lead_to_degree_borders(angle + robot_local_angle)) < -160)speed_goalkeeper = constrain(speed_r, -100, 100);
  }
  angle = lead_to_degree_borders(angle);
  return angle;
}

void line_goal_ball()
{

  /*if (x_robot <= x1 and x_robot >= x2)
    {*/
  int y_goalkepeer = sqrt((R * R) - ((x_robot - our_goal_x) * (x_robot - our_goal_x))) + our_goal_y;

  err_y = y_goalkepeer - y_robot;
  //if (abs(err_y) < 3) err_y = 0;
  if (err_y < 0)
  {
    angle_y = 180;
    u_y = -(err_y * Kp_line_goal + (err_y - err_old_y) * Kd_line_goal + err_i_y);
  }
  else
  {
    angle_y = 0;
    u_y = err_y * Kp_line_goal + (err_y - err_old_y) * Kd_line_goal + err_i_y;
  }
  /*if (err_y < 0)
    {
    angle_y = 180;
    u_y = -(err_y * Kp_line_goal + (err_y - err_old_y) * Kd_line_goal + err_i_y);
    }
    else
    {
    angle_y = 0;
    u_y = err_y * Kp_line_goal + (err_y - err_old_y) * Kd_line_goal + err_i_y;
    }
    //angle_y = 0;
    u_y = err_y * Kp_line_goal + (err_y - err_old_y) * Kd_line_goal + err_i_y;*/

  err_x = lead_to_degree_borders(lead_to_degree_borders((ball_angle + robot_local_angle)) - (lead_to_degree_borders(o_a + 180)));
  //if (abs(err_x) < 3) err_x = 0;
  if (err_x > 0)
  {
    angle_x = 90;
    u_x = Kp_line_goal_ball * err_x + (err_x - err_old_x) * Kd_line_goal_ball + err_i_x;
  }
  else
  {
    angle_x = -90;
    u_x = -(Kp_line_goal_ball * err_x + (err_x - err_old_x) * Kd_line_goal_ball + err_i_x);
  }
  //u_x = Kp_line_goal_ball * err_x + (err_x - err_old_x) * Kd_line_goal_ball + err_i_x;
  //angle_x =lead_to_degree_borders(angle_y + 90*sign(u_x)) ;
  xy = sqrt(u_y * u_y + u_x * u_x);
  xy = constrain(xy, -180, 180);
  if (angle_y == 0) angle_xy = lead_to_degree_borders(sign(angle_x) * lead_to_degree_borders(90 - (atan2(u_y, u_x) * 57.3)) - robot_local_angle);
  else angle_xy = lead_to_degree_borders(sign(angle_x) * lead_to_degree_borders((atan2(u_y, u_x) * 57.3) + 90));
  //angle_xy = lead_to_degree_borders(90 - atan2(u_y, u_x) * 57.3);
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
  err_i_y  += Ki_line_goal * err_y;
  err_i_x += Ki_line_goal_ball * err_x;
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
  angle_goalkeeper = angle_xy;
  speed_goalkeeper = xy;
  //move_angle_speed(angle_xy, xy, ball_angle);
}

float sign (float num)
{
  if (num >= 0) return 1;
  else return -1;
}
void kick()
{
  if ((millis() - timer_kick) > 700)
  {
    digitalWrite(KICK_PIN1, 0);
    digitalWrite(KICK_PIN1, 1);
    delay(4);
    digitalWrite(KICK_PIN1, 0);
    timer_kick = millis();
  }
}

void coordinates_robot()
{
  o_a = lead_to_degree_borders(our_local_angle + robot_local_angle);
  e_a = lead_to_degree_borders(enemy_local_angle + robot_local_angle);
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
  x_soft_c = k_coordinates * x_robot + x_soft_c * (1 - k_coordinates);
  y_soft_c = k_coordinates * y_robot + y_soft_c * (1 - k_coordinates);
}



void if_notice_goal()
{
  if (our_distance == 0) if_notice_our = false;
  else if_notice_our = true;
  if (enemy_distance == 0) if_notice_enemy = false;
  else if_notice_enemy = true;
}



double convert_dist(double max_dist, double dist)
{
  double _data = (dist - max_dist) / max_dist + 1;

  if (_data > 1)
    _data = 1;
  else if (_data < 0)
    _data = 0;

  return _data;
}

int16_t exponential_detour(double ball_angle, double distance, double k1_angle, double k2_angle, double k1_dist, double k2_dist)
{
  angK = k1_angle * pow(ec, double(k2_angle * abs(ball_angle)));

  if (angK > 90)
    angK = 90;

  distance = convert_dist(min_dist_to_ball, distance);

  distK = k1_dist * pow(ec, double(k2_dist * distance));

  if (distK > 1)
    distK = 1;

  if (ball_angle > 0)
    _data = angK * distK;
  else
    _data = -angK * distK;

  return _data;
}

void ball_capture(int v_capture)  {
  angle_forward = ball_angle + exponential_detour(ball_angle, ball_distance, 0.05, 0.2, 0.4, 18);
  speed_forward = v_capture;
}

/*void ball_capture (int v_capture)
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
  }*/

void if_sen_leadle()
{
  if (analogRead(SEN_LEADLE) >  700) if_ball_in_leadle = true;
  else if_ball_in_leadle = false;
}

void control_charge()
{
  float bat_charge = 4.3 * analogRead(CHARGE_PIN) / ((4.3 * 1023) / 5);
  //Serial.println(analogRead(CHARGE_PIN));
  if (bat_charge < 3.6) digitalWrite(CHARGE_LED_PIN, 1);
}
