void detect_ball()
{
  for (int i = 0; i < 16; i++)
  {
    digitalWrite(ADDR_P1, ir_addr[i][0]);
    digitalWrite(ADDR_P2, ir_addr[i][1]);
    digitalWrite(ADDR_P3, ir_addr[i][2]);
    digitalWrite(ADDR_P4, ir_addr[i][3]);
    delayMicroseconds(10);
    ball_data[i] = 1 - digitalRead(BALL_SEN_SIGNAL_1);
  }

  for (int i = 0; i < 16; i++)
  {
    digitalWrite(ADDR_P1, ir_addr[i][0]);
    digitalWrite(ADDR_P2, ir_addr[i][1]);
    digitalWrite(ADDR_P3, ir_addr[i][2]);
    digitalWrite(ADDR_P4, ir_addr[i][3]);
    delayMicroseconds(10);
    ball_data[i + 16] = 1 - digitalRead(BALL_SEN_SIGNAL_2);
  }

  double x = 0;
  double y = 0;
  for (int i = 0; i < 32; i++)
  {
    x += ball_data[i] * sin((d_alpha * i) / 57.3);
    y += ball_data[i] * cos((d_alpha * i) / 57.3);
  }
  ball_angle = -1*lead_to_degree_borders(atan2(x, y) * 57.3);
  ball_distance = sqrt(x * x + y * y);
}
