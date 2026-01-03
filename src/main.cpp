#include <Arduino.h>
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include "credentials.h"

// LED strip configuration
#define LED_PIN D4  // GPIO2 on NodeMCU
#define NUM_LEDS 40 // 40 WS2811 ICs (40 groups × 6 LEDs = 240 total LEDs)
#define LED_TYPE WS2811
#define COLOR_ORDER RGB
#define BRIGHTNESS 64 // 25% brightness (0-255)

CRGB leds[NUM_LEDS];

void setup()
{
  Serial.begin(9600);
  delay(1000);

  Serial.println("\n\nStarting up...");

  // Initialize LED strip
  Serial.println("Initializing LED strip...");
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.println("LED strip ready!");

  // Connect to WiFi
  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED && attempt < 20)
  {
    delay(500);
    Serial.print(".");
    attempt++;
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("\nWiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Signal strength (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  }
  else
  {
    Serial.println("\nWiFi connection failed!");
    Serial.println("Continuing with LED animation anyway...");
  }
}

void loop()
{
  // Set all LEDs to white
  fill_solid(leds, NUM_LEDS, CRGB::White);

  // Show the LEDs
  FastLED.show();

  // No need for frequent updates when showing static color
  delay(100);
}