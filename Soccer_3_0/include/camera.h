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
  // Ищем маркер начала пакета (255) и выравниваем поток
  while (Serial2.available() > 0 && Serial2.peek() != 255) {
    Serial2.read(); // Сбрасываем байты-мусор до стартового
  }

  // В буфере должен быть маркер (1 байт) + полезные данные (7 байт)
  if (Serial2.available() >= 8) {
    byte start_byte = Serial2.read(); // Считываем 255

    if (start_byte == 255) {
      byte data_camera[7];
      
      // Читаем все 7 байт за один вызов
      Serial2.readBytes(data_camera, 7);

      // Проверяем контрольную сумму
      if (crc8(data_camera, 6) == data_camera[6]) {
        
        if (goal::our_color == 'Y') {
          goal::our::local_angle   = lead_to_degree_borders(data_camera[0] * 3);
          goal::our::distance      = data_camera[1] * 2;
          goal::enemy::local_angle = lead_to_degree_borders(data_camera[2] * 3);
          goal::enemy::distance    = data_camera[3] * 2;
          
          digitalWrite(LED_YELLOW, HIGH);
          digitalWrite(LED_BLUE, LOW);
        } 
        else {
          goal::enemy::local_angle = lead_to_degree_borders(data_camera[0] * 3);
          goal::enemy::distance    = data_camera[1] * 2;
          goal::our::local_angle   = lead_to_degree_borders(data_camera[2] * 3);
          goal::our::distance      = data_camera[3] * 2;
          
          digitalWrite(LED_YELLOW, LOW);
          digitalWrite(LED_BLUE, HIGH);
        }

        // Данные мяча (исправлен индекс с 4 на 5)
        ball::angle_camera    = lead_to_degree_borders(data_camera[4] * 3);
        ball::distance_camera = data_camera[5] * 2; 
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
