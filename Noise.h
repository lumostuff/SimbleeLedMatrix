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

#define MAX_DIMENSION ((kMatrixWidth > kMatrixHeight) ? kMatrixWidth : kMatrixHeight)

// The 16 bit version of our coordinates
static uint16_t noisex;
static uint16_t noisey;
static uint16_t noisez;

// A second set of coordinates, for split-screen noise
static uint16_t noisex2;
static uint16_t noisey2;
static uint16_t noisez2;

// We're using the x/y dimensions to map to the x/y pixels on the matrix.  We'll
// use the z-axis for "time".  speed determines how fast time moves forward.  Try
// 1 for a very slow moving effect, or 60 for something that ends up looking like
// water.
uint32_t noisespeedx = 9;
uint32_t noisespeedy = 0;
uint32_t noisespeedz = 0;

// Scale determines how far apart the pixels in our noise matrix are.  Try
// changing these values around to see how it affects the motion of the display.  The
// higher the value of scale, the more "zoomed out" the noise will be.  A value
// of 1 will be so zoomed in, you'll mostly see solid colors.
uint16_t noisescale = 30; // scale is set dynamically once we've started up

// This is the array that we keep our computed noise values in
uint8_t noise[MAX_DIMENSION][MAX_DIMENSION];

uint8_t colorLoop = 0;

uint8_t hueReduce = 0;

uint8_t currentNoisePaletteIndex = 0;

CRGBPalette16 currentNoisePalette(palettes[0]);

boolean initialized = false;

// Fill the x/y array of 8-bit noise values using the inoise8 function.
void fillnoise8(uint8_t set, uint8_t startY, uint8_t endY) {

  if (!initialized) {
    initialized = true;
    // Initialize our coordinates to some random values
    noisex = random16();
    noisey = random16();
    noisez = random16();

    noisex2 = random16();
    noisey2 = random16();
    noisez2 = random16();

    SetupBlackAndWhiteStripedPalette();
    SetupBlackAndBlueStripedPalette();
  }

  // If we're runing at a low "speed", some 8-bit artifacts become visible
  // from frame-to-frame.  In order to reduce this, we can do some fast data-smoothing.
  // The amount of data smoothing we're doing depends on "speed".
  uint8_t dataSmoothing = 0;
  uint16_t lowestNoise = noisespeedx < noisespeedy ? noisespeedx : noisespeedy;
  lowestNoise = lowestNoise < noisespeedz ? lowestNoise : noisespeedz;
  if ( lowestNoise < 8) {
    dataSmoothing = 200 - (lowestNoise * 4);
  }

  for (int i = 0; i < MAX_DIMENSION; i++) {
    int ioffset = noisescale * i;
    for (int j = startY; j < endY; j++) {
      int joffset = noisescale * j;

      uint8_t data = 0;

      if (set == 1)
        data = inoise8(noisex2 + ioffset, noisey2 + joffset, noisez2);
      else
        data = inoise8(noisex + ioffset, noisey + joffset, noisez);

      // The range of the inoise8 function is roughly 16-238.
      // These two operations expand those values out to roughly 0..255
      // You can comment them out if you want the raw noise data.
      data = qsub8(data, 16);
      data = qadd8(data, scale8(data, 39));

      if ( dataSmoothing ) {
        uint8_t olddata = noise[i][j];
        uint8_t newdata = scale8( olddata, dataSmoothing) + scale8( data, 256 - dataSmoothing);
        data = newdata;
      }

      noise[i][j] = data;
    }
  }

  if (set == 1)
  {
    noisex2 += noisespeedx;
    noisey2 += noisespeedy;
    noisez2 += noisespeedz;
  }
  else
  {
    noisex += noisespeedx;
    noisey += noisespeedy;
    noisez += noisespeedz;
  }
}

void mapNoiseToLEDsUsingPalette(CRGBPalette16 palette, uint8_t startY, uint8_t endY)
{
  static uint8_t ihue = 0;

  for (int i = 0; i < kMatrixWidth; i++) {
    for (int j = startY; j < endY; j++) {
      // We use the value at the (i,j) coordinate in the noise
      // array for our brightness, and the flipped value from (j,i)
      // for our pixel's index into the color palette.

      uint8_t index = noise[i][j];
      //      uint8_t bri =   noise[i][j];

      // if this palette is a 'loop', add a slowly-changing base value
      if ( colorLoop) {
        index += ihue;
      }

      //      // brighten up, as the color palette itself often contains the
      //      // light/dark dynamic range desired
      //      if ( bri > 127 ) {
      //        bri = 255;
      //      } else {
      //        bri = dim8_raw( bri * 2);
      //      }

      if (hueReduce > 0) {
        if (index < hueReduce) index = 0;
        else index -= hueReduce;
      }

      CRGB color = ColorFromPalette( palette, index, 255);
      uint16_t n = XY(i, j);

      leds[n] = color;
    }
  }

  ihue += 1;
}

void drawNoise(CRGBPalette16 palette) {
  //  Serial.print("noisex: ");
  //  Serial.println(noisex);

  // generate noise data
  fillnoise8(0, 0, kMatrixHeight);

  // convert the noise data to colors in the LED array
  // using the current palette
  mapNoiseToLEDsUsingPalette(palette, 0, kMatrixHeight);
}

void drawHorizon() {
  // start at the middle, then work up & down, darkening a bit less as we go

  uint8_t value = 14;
  uint8_t y = kMatrixHeight / 2;

  // clear the middle
  for (uint8_t x = 0; x < kMatrixWidth; x++) {
      leds[XY(x, y)].nscale8(value);
  }

  value = 16;

  // middle up
  for (y = kMatrixHeight / 2 + 1; y < kMatrixHeight; y++) {
    for (uint8_t x = 0; x < kMatrixWidth; x++) {
      leds[XY(x, y)].nscale8(value);
    }
    if (value >= 128)
      break;
    value *= 2;
  }

  value = 16;

  for (y = kMatrixHeight / 2 - 1; y >= 0; y--) {
    for (uint8_t x = 0; x < kMatrixWidth; x++) {
      leds[XY(x, y)].nscale8(value);
    }
    if (value >= 128)
      break;
    value *= 2;
  }
}

void landscape() {
  // ground
  noisespeedx = 1;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 120;
  colorLoop = 0;
  hueReduce = 0;
  fillnoise8(0, kMatrixHeight / 2, kMatrixHeight);
  mapNoiseToLEDsUsingPalette(ForestColors_p, kMatrixHeight / 2, kMatrixHeight);

  // sky
  noisespeedx = -1;
  noisespeedy = -1;
  noisespeedz = 0;
  noisescale = 60;
  colorLoop = 0;
  hueReduce = 0;
  fillnoise8(1, 0, kMatrixHeight / 2);
  mapNoiseToLEDsUsingPalette(CloudColors_p, 0, kMatrixHeight / 2);

  drawHorizon();
}

void seascape() {
  // ocean
  noisespeedx = 1;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 90;
  colorLoop = 0;
  hueReduce = 0;
  fillnoise8(0, kMatrixHeight / 2, kMatrixHeight);
  mapNoiseToLEDsUsingPalette(OceanColors_p, kMatrixHeight / 2, kMatrixHeight);

  // sky
  noisespeedx = -1;
  noisespeedy = -1;
  noisespeedz = 0;
  noisescale = 60;
  colorLoop = 0;
  hueReduce = 0;
  fillnoise8(1, 0, kMatrixHeight / 2);
  mapNoiseToLEDsUsingPalette(CloudColors_p, 0, kMatrixHeight / 2);

  drawHorizon();
}

void currentPaletteNoise() {
  drawNoise(currentNoisePalette);
}

void rainbowNoise() {
  noisespeedx = 9;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 20;
  colorLoop = 0;
  hueReduce = 0;
  currentNoisePaletteIndex = 0;
  currentNoisePalette = RainbowColors_p;
}

void rainbowStripeNoise() {
  noisespeedx = 9;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 20;
  colorLoop = 0;
  hueReduce = 0;
  currentNoisePaletteIndex = 1;
  currentNoisePalette = RainbowStripeColors_p;
}

uint16_t oceanNoise() {
  noisespeedx = 9;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 90;
  colorLoop = 0;
  hueReduce = 0;
  currentNoisePaletteIndex = 2;
  currentNoisePalette = OceanColors_p;
}

uint16_t cloudNoise() {
  noisespeedx = -9;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 30;
  colorLoop = 0;
  hueReduce = 0;
  currentNoisePaletteIndex = 3;
  currentNoisePalette = CloudColors_p;
}

uint16_t forestNoise() {
  noisespeedx = 9;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 120;
  colorLoop = 0;
  hueReduce = 0;
  currentNoisePaletteIndex = 4;
  currentNoisePalette = ForestColors_p;
}

uint16_t partyNoise() {
  noisespeedx = 9;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 30;
  colorLoop = 0;
  hueReduce = 0;
  currentNoisePaletteIndex = 5;
  currentNoisePalette = PartyColors_p;
}

uint16_t fireNoise() {
  noisespeedx = 0;
  noisespeedy = -24;
  noisespeedz = 8;
  noisescale = 50;
  colorLoop = 0;
  hueReduce = 45;
  currentNoisePaletteIndex = 6;
  currentNoisePalette = HeatColors_p;
}

uint16_t lavaNoise() {
  noisespeedx = -32;
  noisespeedy = 0;
  noisespeedz = 16;
  noisescale = 50;
  colorLoop = 0;
  hueReduce = 0;
  currentNoisePaletteIndex = 7;
  currentNoisePalette = LavaColors_p;
}

uint16_t blackAndWhiteNoise() {
  noisespeedx = 9;
  noisespeedy = 0;
  noisespeedz = 0;
  noisescale = 30;
  colorLoop = 0;
  hueReduce = 0;
  currentNoisePaletteIndex = 10;
  currentNoisePalette = blackAndWhiteStripedPalette;
}

uint16_t blackAndBlueNoise() {
  SetupBlackAndBlueStripedPalette();
  noisespeedx = 0;
  noisespeedy = -1;
  noisespeedz = 1;
  noisescale = 30;
  colorLoop = 0;
  hueReduce = 0;
  currentNoisePaletteIndex = 11;
  currentNoisePalette = blackAndBlueStripedPalette;
}
