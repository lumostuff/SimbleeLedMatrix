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

