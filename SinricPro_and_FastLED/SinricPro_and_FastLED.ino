/*
 * Title: SinricPro_and_FastLED
 * 
 * Description:
 *      - This sketch was created for controling a WS2812B LED light strip (or similar) using the FastLED library and SinricPro.
 *        Update the "User Parameters" section for your specific project before uploading sketch.
 *      
 * Author: Electriangle
 *      - Channel: https://www.youtube.com/@Electriangle
 *      
 * License: MIT License
 *      - Copyright (c) 2024 Electriangle
 *
 * Release Date: 5/18/2024
*/

/************************************************************/
//  Libraries
/************************************************************/

#ifdef ENABLE_DEBUG
  #define DEBUG_ESP_PORT Serial
  #define NODEBUG_WEBSOCKETS
  #define NDEBUG
#endif

#include <Arduino.h>
#ifdef ESP8266
  #include <ESP8266WiFi.h>
#endif
#ifdef ESP32
  #include <WiFi.h>
#endif

#include <SinricPro.h>
#include "Myleds.h"
#include <FastLED.h>


/************************************************************/
//  User Parameters
/************************************************************/

// Network Connection
#define APP_KEY    "YOUR APP_KEY"
#define APP_SECRET "YOUR APP_SECRET"
#define DEVICE_ID  "YOUR DEVICE_ID"
#define SSID       "YOUR_WIFI_SSID"
#define PASS       "YOUR_WIFI_PASS"

// Other
#define LED_TYPE          WS2812B
#define VOLTAGE           5         // Volts
#define MAX_CURRENT       1000      // MilliAmps
#define BAUD_RATE         9600
const int LED_PIN = 4;              // Pin # for the LEDs
const int NUM_LEDS = 150;           // Total number of LEDs


/************************************************************/
//  Global Variables
/************************************************************/

// PowerStateController
bool globalPowerState;

// ModeController
std::map<String, String> globalModes;

Myleds &myleds = SinricPro[DEVICE_ID];

// Configure FastLED pixel array
CRGB leds[NUM_LEDS];


/************************************************************/
//  SinricPro
/************************************************************/

/*************
 * Callbacks *
 *************/

// PowerStateController
bool onPowerState(const String &deviceId, bool &state) {
  Serial.printf("[Device: %s]: Powerstate changed to %s\r\n", deviceId.c_str(), state ? "on" : "off");
  globalPowerState = state;
  return true; // request handled properly
}

// ModeController
bool onSetMode(const String& deviceId, const String& instance, String &mode) {
  Serial.printf("[Device: %s]: Modesetting for \"%s\" set to mode %s\r\n", deviceId.c_str(), instance.c_str(), mode.c_str());
  globalModes[instance] = mode;

  return true;
}

/**********
 * Events *
 **********/

// PowerStateController
void updatePowerState(bool state) {
  myleds.sendPowerStateEvent(state);
}

// ModeController
void updateMode(String instance, String mode) {
  myleds.sendModeEvent(instance, mode, "PHYSICAL_INTERACTION");
}

/*******************
 * SinricPro Setup *
 *******************/

void setupSinricPro() {
  // PowerStateController
  myleds.onPowerState(onPowerState);
  // ModeController
  myleds.onSetMode("modeInstance1", onSetMode);

  SinricPro.onConnected([]{ Serial.printf("[SinricPro]: Connected\r\n"); });
  SinricPro.onDisconnected([]{ Serial.printf("[SinricPro]: Disconnected\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
};

void setupWiFi() {
  #if defined(ESP8266)
    WiFi.setSleepMode(WIFI_NONE_SLEEP); 
    WiFi.setAutoReconnect(true);
  #elif defined(ESP32)
    WiFi.setSleep(false); 
    WiFi.setAutoReconnect(true);
  #endif

  WiFi.begin(SSID, PASS);
  Serial.printf("[WiFi]: Connecting to %s", SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
  Serial.printf("connected\r\n");
}


/************************************************************/
//  Main Setup & Loop Functions
/************************************************************/

void setup() {
  Serial.begin(BAUD_RATE);
  setupWiFi();
  setupSinricPro();

  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  SinricPro.handle();

  // Modes
  // The following modes are provided as examples. Adjust or add your own modes here in the format below.
  //    - Enter the "Mode" with the same name of the mode you entered in SinricPro.
  //    - Enter the functionCall(); for the function you would like to activate.
  // FORMAT EXAMPLE:   if (globalModes["modeInstance1"] == "Mode") { functionCall(); }
  if (globalPowerState) {
    if (globalModes["modeInstance1"] == "Solid") { AllOn(0, 0, 255); }
    if (globalModes["modeInstance1"] == "Twinkle") { TwinklePixels(random(256), 255, 20, 50, 50); }
    if (globalModes["modeInstance1"] == "ShootingStar") { shootingStarAnimation(255, 255, 255, random(10, 60), random(5, 40), random(2000, 8000), 1); }
    if (globalModes["modeInstance1"] == "RainbowCycle") { rainbowCycle(20); }
    if (globalModes["modeInstance1"] == "Fade") { fadeAnimation(255, 255, 255); }
  }
  else {
    FastLED.clear();
    FastLED.show();
  }
}