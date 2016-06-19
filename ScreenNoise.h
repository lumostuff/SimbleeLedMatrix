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

// noise screen controls
uint8_t ui_buttonNoiseBack;

uint8_t ui_stepperNoisePalette;
uint8_t ui_textNoisePalette;

uint8_t ui_stepperNoiseScale;
uint8_t ui_textNoiseScale;

uint8_t ui_stepperNoiseSpeedX;
uint8_t ui_textNoiseSpeedX;

uint8_t ui_stepperNoiseSpeedY;
uint8_t ui_textNoiseSpeedY;

uint8_t ui_stepperNoiseSpeedZ;
uint8_t ui_textNoiseSpeedZ;

// noise preset buttons
uint8_t ui_buttonNoisePreset1;
uint8_t ui_buttonNoisePreset2;
uint8_t ui_buttonNoisePreset3;
uint8_t ui_buttonNoisePreset4;
uint8_t ui_buttonNoisePreset5;
uint8_t ui_buttonNoisePreset6;
uint8_t ui_buttonNoisePreset7;
uint8_t ui_buttonNoisePreset8;
uint8_t ui_buttonNoisePreset9;
uint8_t ui_buttonNoisePreset10;

void noiseScreen() {
  SimbleeForMobile.beginScreen(WHITE);

  SimbleeForMobile.drawText(85, 30, "LumoStuff Noise", BLUE);

  uint16_t margin = 10;
  uint16_t height = 40;
  uint16_t y = 70;
  uint16_t width = SimbleeForMobile.screenWidth / 2;
  uint16_t width4 = SimbleeForMobile.screenWidth / 4;
  width -= margin * 1.5;
  width4 -= margin * 1.5;

  ui_buttonNoiseBack = SimbleeForMobile.drawButton(margin, y, width, "Back");

  y += height;
  ui_buttonNoisePreset1  = SimbleeForMobile.drawButton(margin, y, width, "Rainbow");
  ui_buttonNoisePreset2  = SimbleeForMobile.drawButton(margin * 2 + width, y, width, "Rainbow Stripe");

  y += height;
  ui_buttonNoisePreset3  = SimbleeForMobile.drawButton(margin, y, width, "Ocean");
  ui_buttonNoisePreset4  = SimbleeForMobile.drawButton(margin * 2 + width, y, width, "Cloud");

  y += height;
  ui_buttonNoisePreset5  = SimbleeForMobile.drawButton(margin, y, width, "Forest");
  ui_buttonNoisePreset6  = SimbleeForMobile.drawButton(margin * 2 + width, y, width, "Party");

  y += height;
  ui_buttonNoisePreset7  = SimbleeForMobile.drawButton(margin, y, width, "Fire");
  ui_buttonNoisePreset8  = SimbleeForMobile.drawButton(margin * 2 + width, y, width, "Lava");

  y += height;
  ui_buttonNoisePreset9  = SimbleeForMobile.drawButton(margin, y, width, "Black & White");
  ui_buttonNoisePreset10  = SimbleeForMobile.drawButton(margin * 2 + width, y, width, "Black & Blue");

  y += height + margin;
  SimbleeForMobile.drawText(margin, y, "Palette:", BLUE);
  ui_textNoisePalette = SimbleeForMobile.drawText(margin * 2 + width4, y, width, currentPaletteIndex);
  ui_stepperNoisePalette = SimbleeForMobile.drawStepper(margin * 3 + width4 * 2, y, width, 0, paletteCount - 1);

  y += height + margin;
  SimbleeForMobile.drawText(margin, y, "Scale:", BLUE);
  ui_textNoiseScale = SimbleeForMobile.drawText(margin * 2 + width4, y, width, noisescale);
  ui_stepperNoiseScale = SimbleeForMobile.drawStepper(margin * 3 + width4 * 2, y, width, 0, 255);

  y += height + margin;
  SimbleeForMobile.drawText(margin, y, "Speed X:", BLUE);
  ui_textNoiseSpeedX = SimbleeForMobile.drawText(margin * 2 + width4, y, width, noisespeedx);
  ui_stepperNoiseSpeedX = SimbleeForMobile.drawStepper(margin * 3 + width4 * 2, y, width, -255, 255);

  y += height + margin;
  SimbleeForMobile.drawText(margin, y, "Speed Y:", BLUE);
  ui_textNoiseSpeedY = SimbleeForMobile.drawText(margin * 2 + width4, y, width, noisespeedy);
  ui_stepperNoiseSpeedY = SimbleeForMobile.drawStepper(margin * 3 + width4 * 2, y, width, -255, 255);

  y += height + margin;
  SimbleeForMobile.drawText(margin, y, "Speed Z:", BLUE);
  ui_textNoiseSpeedZ = SimbleeForMobile.drawText(margin * 2 + width4, y, width, noisespeedz);
  ui_stepperNoiseSpeedZ = SimbleeForMobile.drawStepper(margin * 3 + width4 * 2, y, width, -255, 255);

  SimbleeForMobile.endScreen();
}

void handleNoiseScreenEvents(event_t &event) {
  bool updateAll = false;

  if (event.id == ui_buttonNoiseBack) {
    SimbleeForMobile.showScreen(1);
  }
  else if (event.id == ui_stepperNoisePalette) {
    currentNoisePaletteIndex = event.value;
    if (currentNoisePaletteIndex < paletteCount)
      currentNoisePalette = palettes[currentNoisePaletteIndex];
//    else if (currentNoisePaletteIndex - paletteCount < gradientPaletteCount)
//      currentNoisePalette = gradientPalettes[currentNoisePaletteIndex - paletteCount];
    SimbleeForMobile.updateValue(ui_textNoisePalette, currentNoisePaletteIndex);
  }
  else if (event.id == ui_stepperNoiseScale) {
    noisescale = event.value;
    SimbleeForMobile.updateValue(ui_textNoiseScale, noisescale);
  }
  else if (event.id == ui_stepperNoiseSpeedX) {
    noisespeedx = event.value;
    SimbleeForMobile.updateValue(ui_textNoiseSpeedX, noisespeedx);
  }
  else if (event.id == ui_stepperNoiseSpeedY) {
    noisespeedy = event.value;
    SimbleeForMobile.updateValue(ui_textNoiseSpeedY, noisespeedy);
  }
  else if (event.id == ui_stepperNoiseSpeedZ) {
    noisespeedz = event.value;
    SimbleeForMobile.updateValue(ui_textNoiseSpeedZ, noisespeedz);
  }
  else if (event.id == ui_buttonNoisePreset1) {
    rainbowNoise();
    updateAll = true;
  }
  else if (event.id == ui_buttonNoisePreset2) {
    rainbowStripeNoise();
    updateAll = true;
  }
  else if (event.id == ui_buttonNoisePreset3) {
    oceanNoise();
    updateAll = true;
  }
  else if (event.id == ui_buttonNoisePreset4) {
    cloudNoise();
    updateAll = true;
  }
  else if (event.id == ui_buttonNoisePreset5) {
    forestNoise();
    updateAll = true;
  }
  else if (event.id == ui_buttonNoisePreset6) {
    partyNoise();
    updateAll = true;
  }
  else if (event.id == ui_buttonNoisePreset7) {
    fireNoise();
    updateAll = true;
  }
  else if (event.id == ui_buttonNoisePreset8) {
    lavaNoise();
    updateAll = true;
  }
  else if (event.id == ui_buttonNoisePreset9) {
    blackAndWhiteNoise();
    updateAll = true;
  }
  else if (event.id == ui_buttonNoisePreset10) {
    blackAndBlueNoise();
    updateAll = true;
  }

  if(updateAll) {
    SimbleeForMobile.updateValue(ui_textNoisePalette, currentNoisePaletteIndex);
    SimbleeForMobile.updateValue(ui_textNoiseScale, noisescale);
    SimbleeForMobile.updateValue(ui_textNoiseSpeedX, noisespeedx);
    SimbleeForMobile.updateValue(ui_textNoiseSpeedY, noisespeedy);
    SimbleeForMobile.updateValue(ui_textNoiseSpeedZ, noisespeedz);
  }
}
