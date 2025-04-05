void ball_capture ()
{
  if (ball_distance < min_dist_to_ball)
    move_angle_speed (ball_angle, 150);
  else
  {
    if (abs(ball_angle) < 30)
      move_angle_speed(ball_angle, 150);
    else
  {
    if (ball_angle > 0)
      move_angle_speed(ball_angle + 90, 150);
    else
      move_angle_speed(ball_angle - 90, 150);
  }
 }
}
