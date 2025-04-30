void forward()
{
  if (if_ball_in_leadle == false) ball_capture(150, e_a);
  else
  {
   if (y_robot > 120) 
   {
    if(abs(e_a - robot_local_angle) < 30) kick();
    else turn_angle(e_a);
   }
   else move_angle_speed(e_a, 150, e_a);  
  }
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



void ball_capture (int v_capture, int angle)
{
  /*if (ball_distance < min_dist_to_ball)
    move_angle_speed (ball_angle, v_capture, angle);
  else
  {*/
    if (abs(ball_angle) < 30)
      move_angle_speed(ball_angle, v_capture, angle);
    else
    {
      if (ball_angle > 0)
        move_angle_speed(ball_angle + 90, v_capture, angle);
      else
        move_angle_speed(ball_angle - 90, v_capture, angle);
    //}
  }
}
//move_angle_speed (ball_angle, v_capture);
//}

void if_sen_leadle()
{
  if (analogRead(SEN_LEADLE) >  400) if_ball_in_leadle = false;
  else if_ball_in_leadle = true;
}

void change_goal()
{
  if (digitalRead(BUT_ENTER) == 0)
  {
    kick();
    if (our_goal == 'Y')
    {
      our_goal = 'B';
      digitalWrite(LED_YELLOW, 0);
      digitalWrite(LED_BLUE, 1);
    }
    else
    {
      our_goal = 'Y';
      digitalWrite(LED_BLUE, 0);
      digitalWrite(LED_YELLOW, 1);
    }
    delay(10);
  }
  if (our_goal == 'Y')
  {
    our_distance = yellow_distance;
    our_local_angle = yellow_local_angle;
    enemy_distance = blue_distance;
    enemy_local_angle = blue_local_angle;
    digitalWrite(LED_YELLOW, 1);
  }
  else
  {
    enemy_distance = yellow_distance;
    enemy_local_angle = yellow_local_angle;
    our_distance = blue_distance;
    our_local_angle = blue_local_angle;
    digitalWrite(LED_BLUE, 1);
  }
}
