// From ColorWavesWithPalettes by Mark Kriegsman: https://gist.github.com/kriegsman/8281905786e8b2632aeb
// This function draws color waves with an ever-changing,
// widely-varying set of parameters, using a color palette.
//void colorwaves() {
//  static uint16_t sPseudotime = 0;
//  static uint16_t sLastMillis = 0;
//  static uint16_t sHue16 = 0;
//
//  uint8_t sat8 = beatsin88(87, 220, 250);
//  uint8_t brightdepth = beatsin88(341, 96, 224);
//  uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
//  uint8_t msmultiplier = beatsin88(147, 23, 60);
//
//  uint16_t hue16 = sHue16;//gHue * 256;
//  uint16_t hueinc16 = beatsin88(113, 300, 1500);
//
//  uint16_t ms = millis();
//  uint16_t deltams = ms - sLastMillis ;
//  sLastMillis  = ms;
//  sPseudotime += deltams * msmultiplier;
//  sHue16 += deltams * beatsin88(400, 5, 9);
//  uint16_t brightnesstheta16 = sPseudotime;
//
//  for (uint16_t i = 0 ; i < NUM_LEDS; i++) {
//    hue16 += hueinc16;
//    uint8_t hue8 = hue16 / 256;
//    uint16_t h16_128 = hue16 >> 7;
//    if (h16_128 & 0x100) {
//      hue8 = 255 - (h16_128 >> 1);
//    } else {
//      hue8 = h16_128 >> 1;
//    }
//
//    brightnesstheta16  += brightnessthetainc16;
//    uint16_t b16 = sin16(brightnesstheta16) + 32768;
//
//    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
//    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
//    bri8 += (255 - brightdepth);
//
//    uint8_t index = hue8;
//    //index = triwave8(index);
//    index = scale8(index, 240);
//
//    CRGB newcolor = ColorFromPalette(currentGradientPalette, index, bri8);
//
//    uint16_t pixelnumber = i;
//    pixelnumber = (NUM_LEDS - 1) - pixelnumber;
//
//    nblend(leds[pixelnumber], newcolor, 128);
//  }
//}

// variation by Jason Coon that spirals out from the center of a matrix
void colorwaves() {  
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;

  uint8_t sat8 = beatsin88(87, 220, 250);
  uint8_t brightdepth = beatsin88(341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 300, 1500);

  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88(400, 5, 9);
  uint16_t brightnesstheta16 = sPseudotime;

  SpiralOut spiralOut;
  
  for (uint16_t i = 0 ; i < NUM_LEDS; i++) {    
    uint8_t x = spiralOut.x + kMatrixWidth / 2 - 1;
    uint8_t y = spiralOut.y + kMatrixHeight / 2 - 1;
    
    spiralOut.goNext();
    
    if(x >= kMatrixWidth || y >= kMatrixHeight)
      continue;

    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;
    uint16_t h16_128 = hue16 >> 7;
    if (h16_128 & 0x100) {
      hue8 = 255 - (h16_128 >> 1);
    } else {
      hue8 = h16_128 >> 1;
    }

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16(brightnesstheta16) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);

    uint8_t index = hue8;
    //index = triwave8(index);
    index = scale8(index, 240);

    CRGB newcolor = ColorFromPalette(currentGradientPalette, index, bri8);

    nblend(leds[XY(x, y)], newcolor, 128);
  }
}
