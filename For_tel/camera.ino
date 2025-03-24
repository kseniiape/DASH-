void camera_data() {
  if (Serial3.available() >= 6)
  {
    byte prev_sense = Serial3.read();
    //Serial.println(Serial1.read());
    if (prev_sense == 255)
    {

      for (int i = 0; i < 5; i++)
      {
        data_camera[i] = Serial3.read();

      }
      byte crc = crc8(data_camera, 4);
      if (crc == data_camera[4])
      {
        yellow_local_angle = lead_to_degree_borders(data_camera[0] * 4);
        yellow_distance = data_camera[1] * 4;
        blue_local_angle = lead_to_degree_borders(data_camera[2] * 4);
        blue_distance = data_camera[3] * 4;
      }
    }
  }
}

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
