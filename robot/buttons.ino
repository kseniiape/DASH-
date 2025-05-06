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
    delay(500);
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


void but_motors ()
{
  if (digitalRead(BUT_UP) == 0) 
  {
    if (stop_motor == true) stop_motor = false;
    else 
    {
      stop_motor = true;
      stop_m ();
    }
    delay(500);
  }
}

void reset_imu()
{
  if (digitalRead(BUT_DOWN) == 0) null_angle = gyro_angle;
}
