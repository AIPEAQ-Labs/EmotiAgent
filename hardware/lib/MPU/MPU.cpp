#include "mpu.h"


MPU::MPU() {
  mpu = Adafruit_MPU6050();
}

void MPU::setup() {
  // Wire.begin(36, 35);
  Wire.begin(8, 9);

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(true);	// Keep it latched.  Will turn off when reinitialized.
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);
}


bool MPU::getMotionInterruptStatus() {
  return mpu.getMotionInterruptStatus();
}

std::tuple<sensors_event_t, sensors_event_t> MPU::getAccelerometer() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  return { a, g };
}
