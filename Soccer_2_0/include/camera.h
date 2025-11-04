#pragma once

#include "Arduino.h"
#include "global.h"
#include "function_for_angle.h"



uint8_t crc8(uint8_t* data, int len)
{
    uint8_t crc = 0xFF, i, j;
    for (i = 0; i < len; i++) {
        crc ^= data[i];
        for (j = 0; j < 8; j++) {
            if (crc & 0x80) crc = (char)((crc << 1) ^ 0x31);
            else crc <<= 1;
        }
    }
    
    return crc;
}

void camera_data() {
    
  if (Serial2.available() >= 6)
  {
    byte prev_sense = Serial2.read();
    if (prev_sense == 255)
    {
      byte data_camera[5];

      for (int i = 0; i < 5; i++)
      {
        data_camera[i] = Serial2.read();

      }
      byte crc = crc8(data_camera, 4);
      if (crc == data_camera[4])
      {
        if(goal::our_color == 'Y')
        {
          goal::our::local_angle = lead_to_degree_borders(data_camera[0] * 3);
          goal::our::distance = data_camera[1] * 2;
          goal::enemy::local_angle = lead_to_degree_borders(data_camera[2] * 3);
          goal::enemy::distance = data_camera[3] * 2;

          digitalWrite(LED_YELLOW, 1);
          digitalWrite(LED_BLUE, 0);

        }
        else
        {
          goal::enemy::local_angle = lead_to_degree_borders(data_camera[0] * 3);
          goal::enemy::distance = data_camera[1] * 2;
          goal::our::local_angle = lead_to_degree_borders(data_camera[2] * 3);
          goal::our::distance = data_camera[3] * 2;
          digitalWrite(LED_YELLOW, 0);
          digitalWrite(LED_BLUE, 1);
        }
      }
    }
   /*Serial.print(goal::enemy::local_angle);
    Serial.print(' ');
    Serial.print(goal::enemy::distance);
    Serial.print(' ');
    Serial.print(goal::our::local_angle);
    Serial.print(' ');
    Serial.print(goal::our::distance);
    Serial.println(' ');*/

  }
}
