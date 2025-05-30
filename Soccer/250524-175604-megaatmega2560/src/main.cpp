#include "motors.h"
#include "buttons.h"
#include "camera.h"
#include "config.h"
#include "gyro_and_angle.h"
#include "robot_update.h"
#include "tssop.h"
#include "gyro_and_angle.h"

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);

  pinMode(M1_P1, OUTPUT);
  pinMode(M1_P2, OUTPUT);

  pinMode(M2_P1, OUTPUT);
  pinMode(M2_P2, OUTPUT);

  pinMode(M3_P1, OUTPUT);
  pinMode(M3_P2, OUTPUT);

  pinMode(M4_P1, OUTPUT);
  pinMode(M4_P2, OUTPUT);

  pinMode(ADDR_P1, OUTPUT);
  pinMode(ADDR_P2, OUTPUT);
  pinMode(ADDR_P3, OUTPUT);
  pinMode(ADDR_P4, OUTPUT);
  pinMode(BALL_SEN_SIGNAL_1, INPUT_PULLUP);
  pinMode(BALL_SEN_SIGNAL_2, INPUT_PULLUP);

  pinMode(SEN_LEADLE, INPUT);

  pinMode(BUT_DOWN, INPUT);
  pinMode(BUT_UP, INPUT);
  pinMode(BUT_ENTER, INPUT);

  pinMode(LED_CALIBRATION, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  pinMode(KICK_PIN1, OUTPUT);

  pinMode(CHARGE_PIN, INPUT);
  pinMode(CHARGE_LED_PIN, OUTPUT);

  timer = millis();
  timer_kick = millis();
  timer_ball = millis();

  // calibration_imu();
}

void loop()
{
  // Serial.println(abs(lead_to_degree_borders(ball_angle + robot_local_angle)));
  robot_update();
  coordinates_robot();
  /*Serial.print(x_soft_c);
  Serial.print(" ");
  Serial.println(y_soft_c);*/
  /*Serial.print(enemy_distance);
    Serial.print(" ");
    Serial.print(our_distance);
    Serial.print(" ");
    Serial.print(x_soft_c);
    Serial.print(" ");
    Serial.print(y_soft_c);
    Serial.print(" ");
    Serial.print(if_notice_our);
    Serial.print(" ");
    Serial.print(if_notice_enemy);
    Serial.print(" ");
    //Serial.print(k);
    Serial.println(" ");*/
  /*Serial.print(x_robot);
    Serial.print(" ");
    Serial.print(y_robot);
    Serial.println(" ");*/
  /*Serial.print(x_robot);
    Serial.print(" ");
    Serial.print(y_robot);
    Serial.print(" ");
    Serial.print(ball_distance);
    Serial.print(" ");
    Serial.println(angle_forward);*/
  // Serial.println(sign(2));
  // Serial.println(analogRead(SEN_LEADLE));
  // Serial.println(x_robot);
  //Serial.println(ball_angle);
  if (stop_motor == false)
  {
    if (robot_role == 'G')
      goalkeeper();
    else
      forward();
    // move_angle_speed(0, 0, 0);
    // forward();
  }
  else
    stop_m();
  /*Serial.print(enemy_distance);
    Serial.print(" ");
    Serial.print(our_distance);
    Serial.print(" ");
    Serial.print(x_robot);
    Serial.print(" ");
    Serial.print(y_robot);
    Serial.println(" ");*/

  /*Serial.println(" ");
     for (int i = 0; i < 32; i++)
     {
     Serial.print(ball_data[i]);
     Serial.print(" ");
     }
     Serial.println(" ");
     Serial.print(ball_distance);
     Serial.print(" ");
     Serial.println(ball_angle);*/
}
