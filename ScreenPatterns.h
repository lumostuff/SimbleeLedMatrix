/*
 * SimbleeLed: https://github.com/lumostuff/SimbleeLed
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

// pattern screen controls
uint8_t ui_buttonOff;
uint8_t ui_buttonColor;
uint8_t ui_buttonColorWaves;
uint8_t ui_buttonLightning;
uint8_t ui_buttonRainbow;
uint8_t ui_buttonRainbowWithGlitter;
uint8_t ui_buttonConfetti;
uint8_t ui_buttonSinelon;
uint8_t ui_buttonBeat;
uint8_t ui_buttonJuggle;
uint8_t ui_buttonNoise;
uint8_t ui_buttonLandscape;
uint8_t ui_buttonSeascape;
uint8_t ui_buttonWave;

uint8_t ui_sliderBrightness;

void patternSelectorScreen() {
  SimbleeForMobile.beginScreen(WHITE);

  SimbleeForMobile.drawText(85, 30, "LumoStuff Patterns", BLUE);

  uint16_t margin = 10;
  uint16_t height = 40;
  uint16_t y = 70;
  uint16_t width = SimbleeForMobile.screenWidth / 2;
  width -= margin * 1.5;

  ui_buttonOff                = SimbleeForMobile.drawButton(margin, y, width, "Off");
  ui_buttonColor              = SimbleeForMobile.drawButton(margin * 2 + width, y, width, "Color");

  y += height;
  ui_buttonColorWaves         = SimbleeForMobile.drawButton(margin, y, width, "ColorWaves");
  ui_buttonLightning          = SimbleeForMobile.drawButton(margin * 2 + width, y, width, "Lightning");

  y += height;
  ui_buttonRainbow            = SimbleeForMobile.drawButton(margin, y, width, "Rainbow");
  ui_buttonRainbowWithGlitter = SimbleeForMobile.drawButton(margin * 2 + width, y, width, "Rainbow w Glitter");

  y += height;
  ui_buttonConfetti           = SimbleeForMobile.drawButton(margin, y, width, "Confetti");
  ui_buttonSinelon            = SimbleeForMobile.drawButton(margin * 2 + width, y, width, "Sinelon");

  y += height;
  ui_buttonJuggle             = SimbleeForMobile.drawButton(margin, y, width, "Juggle");
  ui_buttonBeat               = SimbleeForMobile.drawButton(margin * 2 + width, y, width, "Beat");

  y += height;
  ui_buttonNoise              = SimbleeForMobile.drawButton(margin, y, width, "Noise");
  ui_buttonLandscape          = SimbleeForMobile.drawButton(margin * 2 + width, y, width, "Landscape");

  y += height;
  ui_buttonSeascape           = SimbleeForMobile.drawButton(margin, y, width, "Seascape");
  ui_buttonWave               = SimbleeForMobile.drawButton(margin * 2 + width, y, width, "Wave");

  y += height;
  SimbleeForMobile.drawButton(margin, y, width, "");
  SimbleeForMobile.drawButton(margin * 2 + width, y, width, "");

  y += height;
  SimbleeForMobile.drawText(margin, y, "Brightness:", BLUE);

  y += height / 2;
  width = SimbleeForMobile.screenWidth - margin * 2;
  ui_sliderBrightness = SimbleeForMobile.drawSlider(margin, y, width, 0, 255);
  SimbleeForMobile.setEvents(ui_sliderBrightness, EVENT_DRAG | EVENT_RELEASE);
  SimbleeForMobile.updateValue(ui_sliderBrightness, brightness);

  SimbleeForMobile.endScreen();
}

void handlePatternScreenEvents(event_t &event) {
  if (event.id == ui_buttonColor) {
    currentPatternIndex = patternCount - 2; // solid color is always the second to last 'pattern'
    SimbleeForMobile.showScreen(2);
  }
  else if (event.id == ui_buttonOff) {
    currentPatternIndex = patternCount - 1; // off is always the last 'pattern'
  }
  else if (event.id == ui_sliderBrightness) {
    brightness = event.value;
    FastLED.setBrightness(brightness);
  }
  else if (event.id == ui_buttonColorWaves) {
    currentPatternIndex = 0;
  }
  else if (event.id == ui_buttonLightning) {
    currentPatternIndex = 1;
  }
  else if (event.id == ui_buttonRainbow) {
    currentPatternIndex = 2;
  }
  else if (event.id == ui_buttonRainbowWithGlitter) {
    currentPatternIndex = 3;
  }
  else if (event.id == ui_buttonConfetti) {
    currentPatternIndex = 4;
  }
  else if (event.id == ui_buttonSinelon) {
    currentPatternIndex = 5;
  }
  else if (event.id == ui_buttonJuggle) {
    currentPatternIndex = 6;
  }
  else if (event.id == ui_buttonBeat) {
    currentPatternIndex = 7;
  }
  else if (event.id == ui_buttonNoise) {
    currentPatternIndex = 8;
    SimbleeForMobile.showScreen(3);
  }
  else if (event.id == ui_buttonLandscape) {
    currentPatternIndex = 9;
  }
  else if (event.id == ui_buttonSeascape) {
    currentPatternIndex = 10;
  }
  else if (event.id == ui_buttonWave) {
    currentPatternIndex = 11;
  }
}
