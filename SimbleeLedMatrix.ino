/*
 * SimbleeLedMatrix: https://github.com/lumostuff/SimbleeLedMatrix
 * Copyright (C) 2016 Jason Coon & Jon Richings, LumoStuff
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <SimbleeForMobile.h>
#include <FastLED.h>
#include "GradientPalettes.h"
#include "Palettes.h"
#include "SpiralOut.h"

// Params for width and height
const uint8_t kMatrixWidth = 16;
const uint8_t kMatrixHeight = 16;

#define DATA_PIN    5
#define CLOCK_PIN   4
#define LED_TYPE    APA102
#define COLOR_ORDER BGR // RGB
#define NUM_LEDS    kMatrixWidth * kMatrixHeight

// ten seconds per color palette makes a good demo
// 20-120 is better for deployment
#define SECONDS_PER_PALETTE 1

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

FASTLED_USING_NAMESPACE

CRGB leds[NUM_LEDS];

uint8_t brightness = 16;

CRGB solidColor = CRGB(0, 0, 255);

uint8_t hue = 0; // rotating "base color" used by many of the patterns

// Current palette number from the 'playlist' of color palettes
uint8_t currentGradientPaletteIndex = 0;

CRGBPalette16 currentGradientPalette(gradientPalettes[0]);
CRGBPalette16 targetGradientPalette(gradientPalettes[0]);

const int paletteCount = ARRAY_SIZE(palettes);

int currentPaletteIndex = 0;
CRGBPalette16 currentPalette = palettes[0];

#include "XY.h"

void showSolidColor() {
  fill_solid(leds, NUM_LEDS, solidColor);
}

void off() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
}

void dimAll(byte value) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(value);
  }
}
#include "ColorWaves.h"
#include "Lightning.h"
#include "FastLedDemos.h"
#include "Noise.h"
#include "Wave.h"

// List of patterns to cycle through. Each is defined as a separate function below.
typedef void (*SimplePatternList[])();

SimplePatternList patterns = {
  colorwaves,
  lightning,
  rainbow,
  rainbowWithGlitter,
  confetti,
  sinelon,
  juggle,
  bpm,
  currentPaletteNoise,
  landscape,
  seascape,
  wave,
  showSolidColor,
  off,
};

uint8_t currentPatternIndex = 11;
uint8_t patternCount = ARRAY_SIZE(patterns);

void setup() {
  Serial.begin(57600);
//  delay(500); // 3 second delay for recovery

  SimbleeForMobile.deviceName = "LumoStuff";
  SimbleeForMobile.advertisementData = "Strip";
  SimbleeForMobile.domain = "Simblee.com";
  SimbleeForMobile.begin();

  FastLED.addLeds<LED_TYPE, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  //  FastLED.setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(brightness);
  FastLED.setDither(0);

  Serial.print("currentGradientPaletteIndex: ");
  Serial.println(currentGradientPaletteIndex);
}

void loop() {
  SimbleeForMobile.process();

//  EVERY_N_SECONDS(SECONDS_PER_PALETTE) {
//    currentGradientPaletteIndex = addmod8(currentGradientPaletteIndex, 1, gradientPaletteCount);
//
//    targetGradientPalette = gradientPalettes[currentGradientPaletteIndex];
//    Serial.print("currentGradientPaletteIndex: ");
//    Serial.println(currentGradientPaletteIndex);
//  }

  EVERY_N_MILLIS(30) {
    hue++;
  }

//  EVERY_N_MILLISECONDS(40) {
//    nblendPaletteTowardPalette(currentGradientPalette, targetGradientPalette, 16);
//  }

  patterns[currentPatternIndex]();

  FastLED.show();
}

// Simblee UI screens
#include "ScreenPatterns.h"
#include "ScreenColor.h"
#include "ScreenNoise.h"

void ui() {
  switch (SimbleeForMobile.screen) {
    case 1:
      patternSelectorScreen();
      break;

    case 2:
      colorSelectorScreen();
      break;

    case 3:
      noiseScreen();
      break;
  }
}

void ui_event(event_t &event) {
  Serial.print("screen: ");
  Serial.println(SimbleeForMobile.screen);
  Serial.print("event.id: ");
  Serial.println(event.id);

  switch (SimbleeForMobile.screen) {
    case 1:
      handlePatternScreenEvents(event);
      break;

    case 2:
      handleColorScreenEvents(event);
      break;

    case 3:
      handleNoiseScreenEvents(event);
      break;
  }
}
