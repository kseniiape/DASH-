#pragma once
#include "Arduino.h"

#include "motors.h"
#include "buttons.h"
#include "camera.h"
#include "config.h"
#include "tssop.h"
#include "function_for_angle.h"
#include "global.h"
#include "dribler.h"
#include "for_strategy.h"
#include "gyro.h"
#include "robot_update.h"
#include "forward.h"
#include "goalkeeper.h"


void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);

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

  pinMode(SEN_LEADLE1, INPUT);
  pinMode(SEN_LEADLE2, INPUT);

  pinMode(BUT_DOWN, INPUT);
  pinMode(BUT_UP, INPUT);
  pinMode(BUT_ENTER, INPUT);

  pinMode(LED_CALIBRATION, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);

  pinMode(KICK_PIN1, OUTPUT);

  pinMode(CHARGE_PIN, INPUT);
  pinMode(CHARGE_LED_PIN, OUTPUT);

  

  timers::kick = millis();
  timers::leadle1 =  millis();
  timers::leadle2 =  millis();
  timers::ball_capture = millis();
  timers::ball_state = millis();
  timers::forward_state = millis();
  timers::d_capture = millis();
  
  if(robot::role == 2) dribler = false;
  dribler_config();

}

void loop()
{
  robot_update(); 
  coordinates_robot();
  //dribler_power(1400);
  //move_angle_speed(0, 0, 0);

  /*digitalWrite(LED_YELLOW, 1);
  digitalWrite(LED_BLUE, 1);*/
//Serial.println(ball::angle);
  //Serial.println(if_ball_in_leadle1);
  //Serial.println(goal::our_color);
  /*Serial.print(robot::x);
  Serial.print(' ');
  Serial.print(robot::y);
  Serial.println('.');*/
  //Serial.println(robot::local_angle);
  /*motor1(200);
  motor2(200);
  motor3(200);
  motor4(200);*/
  if (!stop_motors)
  {
    //ball_capture();
    #if ROLE == 1
    //goalkeeper_s();
    forward();
    #else
    //forward();
    goalkeeper_s();
    #endif
    
    //goalkeeper_s();
    //move_to_point(0, 140);
    //move_angle_speed(0, 0, 0);
    //Serial.println(robot::local_angle);
    //move_angle_speed(0, 150, ball::angle+robot::local_angle);
    //goalkeeper_s();
    //dribler_power(1500);
    //move_angle_speed(0, 0, 0);
    //turn(200);
    
  }
  else
  {
    timers::ball_state = millis();
    dribler_power(1000);
    stop_m();
  }
  
}
