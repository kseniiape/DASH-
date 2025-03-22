/*
   Плавное движение
*/
void soft_move_angle_speed (double angle, int speed_m) {
  static int timer_soft;
  if (timer_soft != millis())
  {

    /*if (x1 == 0 and y1 == 0) {
      x1 = speed_m * sin(angle / 57.3);
      y1 = speed_m * cos(angle / 57.3);
      move_angle_speed (angle, speed_m);

      }
      else
      {*/

    static float x2 = speed_m * sin(double(angle / 57.3));
    static float y2 = speed_m * cos(double(angle / 57.3));
    /*Serial.print(x1);
      Serial.print(" ");
      Serial.println(x2);*/
    if (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) ) > ds) {
      //Serial.println("+");
      double dx = x2 - x1;
      double dy = y2 - y1;

      double a = atan2(dx, dy);

      float xds = -1 * ds * sin(a);
      float yds = -1 * ds * cos(a);

      float y3 = y1 - yds;
      float x3 = x1 - xds;

      speed_new = sqrt(y3 * y3 + x3 * x3);
      angle_new = atan2(x3, y3) * (180 / 3.14);
     /* Serial.print(x3);
      Serial.print(" ");
      Serial.println(y3);*/
      move_angle_speed (angle_new, speed_new);
      /*Serial.print(speed_new);
      Serial.print(" ");
      Serial.println(angle_new);*/

      x1 = x3;
      y1 = y3;
    }
    else {
      move_angle_speed (angle, speed_m);
    }
    timer_soft = millis();
  }

}
//}



void move_angle_speed (double angle, int speed_m) {
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


void turn_angle (int angle) {
  //gyro_data();
  err_angle = angle - robot_local_angle;
  if (abs(err_angle) > 5) {
    turn (constrain(err_angle * kP, -255, 255));
  }
}


void turn (int power) {
  if (power < 0 ) {
    motor1 (-power);
    motor3 (power);
    motor2(power);
    motor4 (-power);
  }
  else {
    motor1 (-power);
    motor3 (power);
    motor2(power);
    motor4 (-power);
  }
}



void square() {
  move_angle_speed(0, 100);
  delay(1000);
  stop_m();
  delay(200);
  move_angle_speed(90, 100);
  delay(1000);
  stop_m();
  delay(200);
  move_angle_speed(180, 100);
  delay(1000);
  stop_m();
  delay(200);
  move_angle_speed(270, 100);
  delay(1000);
  stop_m();
  delay(200);
}
