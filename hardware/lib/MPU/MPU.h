#ifndef _MPU_H
#define _MPU_H

#include <Wire.h>
#include <Adafruit_MPU6050.h>

class MPU {
  private:
    Adafruit_MPU6050 mpu;

  public:
    MPU();
    void setup();
    bool getMotionInterruptStatus();
    std::tuple<sensors_event_t, sensors_event_t> getAccelerometer();
    void getAcceleration(float *x, float *y, float *z);
    void getRotation(float *x, float *y, float *z);
};

#endif