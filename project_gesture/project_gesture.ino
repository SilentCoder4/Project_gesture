#include <Wire.h>
#include <MPU6050.h>
#include <ESP32_BLE_Mouse.h>

// Replace with your own ESP32 Bluetooth address
#define BLE_MOUSE_ADDRESS "Mouse Address"

MPU6050 mpu;
BLEMouse bleMouse;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();

  // Initialize Bluetooth
  bleMouse.begin(BLE_MOUSE_ADDRESS);

  Serial.println("Bluetooth Mouse Initialized");
}

void loop() {
  // Read accelerometer data from MPU6050
  int16_t ax, ay, az;
  mpu.getAcceleration(&ax, &ay, &az);

  // Adjust the sensitivity based on your preference
  int sensitivity = 2;

  // Map the accelerometer values to mouse movements
  int dx = map(ax, -32768, 32767, -sensitivity, sensitivity);
  int dy = map(ay, -32768, 32767, -sensitivity, sensitivity);

  // Send mouse movements over Bluetooth
  bleMouse.move(dx, dy, 0);

  delay(50); // Adjust the delay based on your preference
}
