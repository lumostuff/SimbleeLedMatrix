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

void wave() {
  static uint8_t theta = 0;
  static uint8_t rotation = 0;

  static uint8_t waveCount = 1;

  const uint8_t scale = 256 / kMatrixWidth;

  int n = 0;

  switch (rotation) {
    case 0:
      for (int x = 0; x < kMatrixWidth; x++) {
        n = quadwave8(x * 2 + theta) / scale;
        leds[XY(x, n)] = ColorFromPalette(currentGradientPalette, x + hue);
        if (waveCount == 2)
          leds[XY(x, maxY - n)] = ColorFromPalette(currentGradientPalette, x + hue);
      }
      break;

    case 1:
      for (int y = 0; y < kMatrixHeight; y++) {
        n = quadwave8(y * 2 + theta) / scale;
        leds[XY(n, y)] = ColorFromPalette(currentGradientPalette, y + hue);
        if (waveCount == 2)
          leds[XY(maxX - n, y)] = ColorFromPalette(currentGradientPalette, y + hue);
      }
      break;

    case 2:
      for (int x = 0; x < kMatrixWidth; x++) {
        n = quadwave8(x * 2 - theta) / scale;
        leds[XY(x, n)] = ColorFromPalette(currentGradientPalette, x + hue);
        if (waveCount == 2)
          leds[XY(x, maxY - n)] = ColorFromPalette(currentGradientPalette, x + hue);
      }
      break;

    case 3:
      for (int y = 0; y < kMatrixHeight; y++) {
        n = quadwave8(y * 2 - theta) / scale;
        leds[XY(n, y)] = ColorFromPalette(currentGradientPalette, y + hue);
        if (waveCount == 2)
          leds[XY(maxX - n, y)] = ColorFromPalette(currentGradientPalette, y + hue);
      }
      break;
  }

  dimAll(254);

  EVERY_N_MILLIS(8) {
    theta++;
  }

  EVERY_N_SECONDS(10) {
    rotation = random(0, 4);
    waveCount = random(1, 3);
  }
}

