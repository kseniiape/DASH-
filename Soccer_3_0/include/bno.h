#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

static Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);

bool initBNO() {
  if (!bno.begin()) {
    return false;
  }
  bno.setExtCrystalUse(true);
  return true;
}

float getYaw() {
  sensors_event_t orientationData;
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  
  return orientationData.orientation.x;
}