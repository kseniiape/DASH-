#pragma once

#include "Arduino.h"
#include "config.h"
#include "global.h"
#include "for_strategy.h"



void change_goal()
{
  if (digitalRead(BUT_ENTER) == 0)
  {
    //kick();
    delay(300);
    if (goal::our_color == 'Y')
    {
      goal::our_color = 'B';
      digitalWrite(LED_YELLOW, 0);
      digitalWrite(LED_BLUE, 1);
    }
    else
    {
      goal::our_color = 'Y';
      digitalWrite(LED_BLUE, 0);
      digitalWrite(LED_YELLOW, 1);
    }
    
  }
  
}


void but_motors ()
{
  static bool prev_button = 0;
  
  const bool button = !digitalRead(BUT_UP);

  const bool forward_front = prev_button == 0 && button == 1;
  const bool back_front = prev_button == 1 && button == 0;
  
  if(back_front){
    stop_motors = !stop_motors;
  }
 
  prev_button = button;    
}

void reset_imu()
{
  if (digitalRead(BUT_DOWN) == 0)
  {
    gyro::null_angle = gyro::angle;
    //Serial.println(gyro::null_angle);
  }
  
}
