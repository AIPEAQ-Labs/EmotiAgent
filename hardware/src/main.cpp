#include <SPI.h>
#include <ESP.h>
#include <MPU.h>
#include <esp_system.h>
#include <esp_heap_caps.h>
#include <OTA.h>
#include <BluetoothWifiConnector.h>
#include <Preferences.h>
#include <SerialNumber.h>
#include <TFT_eSPI.h>
#include <MQTT.h>
#include <SPIFFSHandler.h>
#include <User_Setup.h>

#define I2S_WS 15
#define I2S_SD 18
#define I2S_SCK 2
#define I2S_PORT I2S_NUM_0
#define I2S_AUDIO_DOUT 42
#define I2S_AUDIO_BCLK 41
#define I2S_AUDIO_LRC 40

// Constants and Configuration
// Threshold value for capacitive touch sensing - higher values mean less sensitive
#define TOUCH_THRESHOLD 100000

// Base URL for the update server
#define BASE_URL "http://192.168.1.100:8080"

// Current firmware version
#define VERSION "0.0.1"

// Full URL endpoint for checking firmware updates
#define JSON_URL BASE_URL "/checkForUpdate"

// MQTT broker connection details
#define MQTT_SERVER "192.168.1.100"  // MQTT broker IP address
#define MQTT_USER "aipeaq"           // MQTT authentication username
#define MQTT_PASSWORD "aipeaq"       // MQTT authentication password
#define MQTT_PORT 1883              // Default MQTT port

// Threshold for ambient noise detection in arbitrary units
#define NOISE_THRESHOLD 500

// Standard gravitational acceleration in meters per second squared (m/s²)
#define GRAVITY 9.81

// Add new constants for happiness calculation
#define TOUCH_WINDOW 60000  // 1 minute window for touch frequency
#define NOISE_WINDOW 60000 // 10 second window for noise
#define MOTION_WINDOW 30000 // 30 second window for motion metrics
#define W1 0.4  // Weight for touch frequency
#define W2 0.4  // Weight for acceleration
#define W3 0.2  // Weight for rotation
// #define W4 0.2  // Weight for noise


MPU mpu;
// InterICSound interICSound = InterICSound(I2S_PORT, I2S_WS, I2S_SD, I2S_SCK, 64);
TFT_eSPI tft = TFT_eSPI(TFT_WIDTH, TFT_HEIGHT);
Preferences preferences;
BluetoothWifiConnector bluetoothWifiConnector = BluetoothWifiConnector(preferences);
OTA ota;
MQTT mqtt = MQTT(Config::MQTT_SERVER, Config::MQTT_USER, Config::MQTT_PASSWORD, Config::MQTT_PORT);

#include <ScreenDisplay.h>

// Add tracking variables
unsigned long touchEvents[10];  // Circular buffer for touch timestamps
unsigned short touchIndex = 0;
float avgAcceleration = 0.0;
float totalRotation = 0.0;
unsigned long lastMetricUpdate = 0;

// Happiness Management
float happinessRate = 50.0;  // Starts at neutral 50%
const float HAPPINESS_INCREMENT = 5.0;
unsigned long lastPublish = 0;
unsigned long lastHappinessIncrease = 0;
unsigned short randomHappinessThreshold = random(50, 300);

// API and Task Management
unsigned long lastMqtt = 0;

enum ACTION_TYPE {
  TOUCH,
  MOTION
};

// OTA
bool otaChecked = false;

// Track current animation
int currentAnimation = 0;
unsigned long eventTimer = 0;

// Structure to hold API call parameters
// Function declarations
void printSystemStats();
void callAction(ACTION_TYPE actionType);
void updateHappinessRate();

#define bufferLen 64
int16_t sBuffer[bufferLen];

ScreenDisplay screenDisplay;  // Add this instance

void setup() {

  Serial.begin(115200);
  delay(200);
  while (!Serial) {
    delay(100);
  }
  // Print chip info
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);
  Serial.printf("Model: %d\n", chip_info.model);
  Serial.printf("Features: 0x%08x\n", chip_info.features);

  // Print ESP32 information
  Serial.printf("ESP32 Chip Revision: %d\n", ESP.getChipRevision());
  Serial.printf("ESP32 SDK Version: %s\n", ESP.getSdkVersion());

  pinMode(TFT_BL,OUTPUT);
  digitalWrite(TFT_BL,HIGH);
  
  // Check if PSRAM is actually available in hardware
  if (psramFound()) {
      Serial.println("PSRAM is available");
      Serial.printf("Total PSRAM: %d bytes\n", ESP.getPsramSize());
  } else {
      Serial.println("PSRAM is NOT available");
  }

  Serial.println("setup");
  Serial.flush();

  preferences.begin("aipeaq", false);

  // Initialize the Bluetooth and WiFi
  bluetoothWifiConnector.setup();
  // Initialize the OTA
  ota.setup();

  // Initialize the MPU
  mpu.setup();

  // Initialize the InterICSound
//   interICSound.setup();

  // Initialize the MQTT
  mqtt.setup();
  // Initialize the display
  screenDisplay.setup();
}

bool lastCheck = false;

void loop() {
  mqtt.loop();

  ota.loop(JSON_URL, VERSION);
  screenDisplay.loop(happinessRate);
  // Handle happiness decay every second
  if (millis() - lastPublish > 15000) {
    printSystemStats();

    Serial.printf("Happiness rate: %.1f%%\n", happinessRate);

    mqtt.publishHappiness(happinessRate);

    lastPublish = millis();
  }

  if (touchRead(4) > TOUCH_THRESHOLD) {
    touchEvents[touchIndex] = millis();
    touchIndex = (touchIndex + 1) % 10;
  }

  updateHappinessRate();
}

void printSystemStats() {
  // Get free heap memory
  uint32_t freeHeap = ESP.getFreeHeap();
  uint32_t totalHeap = ESP.getHeapSize();
  float heapPercentage = ((float)freeHeap / totalHeap) * 100;

  // Get CPU frequency
  uint32_t cpuFreq = ESP.getCpuFreqMHz();

  Serial.printf("Free Heap: %d bytes (%.1f%%)\n", freeHeap, heapPercentage);
  Serial.printf("CPU Frequency: %d MHz\n", cpuFreq);
}

// Update the happiness calculation function
void updateHappinessRate() {
    // Calculate touch frequency
    unsigned short touchCount = 0;
    unsigned long currentTime = millis();
    for (int i = 0; i < 10; i++) {
        if (currentTime - touchEvents[i] < TOUCH_WINDOW) {
            touchCount++;
        }
    }
    float touchFrequency = (float)touchCount / 10.0;  // Normalize to 0-1

    // Get motion metrics from MPU
    std::tuple<sensors_event_t, sensors_event_t> sensorData = mpu.getAccelerometer();
    sensors_event_t accel = std::get<0>(sensorData);
    sensors_event_t gyro = std::get<1>(sensorData);
    
    
    // Update average acceleration
    float currentAccel = sqrt(accel.acceleration.x * accel.acceleration.x + 
                            accel.acceleration.y * accel.acceleration.y + 
                            accel.acceleration.z * accel.acceleration.z) / GRAVITY; // Normalize by gravity constant (m/s^2)
    avgAcceleration = (avgAcceleration * 0.8) + (currentAccel * 0.2); // Moving average

    // Update total rotation
    float currentRotation = sqrt(gyro.gyro.x * gyro.gyro.x + 
                               gyro.gyro.y * gyro.gyro.y + 
                               gyro.gyro.z * gyro.gyro.z);
    totalRotation = (totalRotation * 0.8) + (currentRotation * 0.2); // Moving average

    Serial.printf("Touch frequency: %.1f\n", touchFrequency);
    Serial.printf("Average acceleration: %.1f\n", avgAcceleration);
    Serial.printf("Total rotation: %.1f\n", totalRotation);

    // Calculate final happiness with all factors
    float newHappiness = ((W1 * touchFrequency + 
                          W2 * avgAcceleration + 
                          W3 * totalRotation) / 
                         (W1 + W2 + W3)) * 100.0;
    
    // Smooth the transition
    happinessRate = happinessRate * 0.2 + newHappiness * 0.8;

    // Ensure bounds
    happinessRate = constrain(happinessRate, 0.0, 100.0);

    Serial.printf("Happiness: %.1f%%\n", happinessRate);
}

// optional
void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info){  //id3 metadata
    Serial.print("id3data     ");Serial.println(info);
}
void audio_eof_mp3(const char *info){  //end of file
    Serial.print("eof_mp3     ");Serial.println(info);
}
void audio_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}
void audio_showstreamtitle(const char *info){
    Serial.print("streamtitle ");Serial.println(info);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    Serial.print("commercial  ");Serial.println(info);
}
void audio_icyurl(const char *info){  //homepage
    Serial.print("icyurl      ");Serial.println(info);
}
void audio_lasthost(const char *info){  //stream URL played
    Serial.print("lasthost    ");Serial.println(info);
}
void audio_eof_speech(const char *info){
    Serial.print("eof_speech  ");Serial.println(info);
}