CRGB w(85, 85, 85), W(CRGB::White);
CRGBPalette16 snowColors = CRGBPalette16( W, W, W, W, w, w, w, w, w, w, w, w, w, w, w, w );

CRGB l(0xE1A024);
CRGBPalette16 incandescentColors = CRGBPalette16( l, l, l, l, l, l, l, l, l, l, l, l, l, l, l, l );

CRGBPalette16 blackAndWhiteStripedPalette;

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( blackAndWhiteStripedPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  blackAndWhiteStripedPalette[0] = CRGB::White;
  blackAndWhiteStripedPalette[4] = CRGB::White;
  blackAndWhiteStripedPalette[8] = CRGB::White;
  blackAndWhiteStripedPalette[12] = CRGB::White;
}

CRGBPalette16 blackAndBlueStripedPalette;

// This function sets up a palette of black and blue stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndBlueStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( blackAndBlueStripedPalette, 16, CRGB::Black);

  for (uint8_t i = 0; i < 6; i++) {
    blackAndBlueStripedPalette[i] = CRGB::Blue;
  }
}

const CRGBPalette16 palettes[] = {
  RainbowColors_p,
  RainbowStripeColors_p,
  OceanColors_p,
  CloudColors_p,
  ForestColors_p,
  PartyColors_p,
  HeatColors_p,
  LavaColors_p,
  snowColors,
  incandescentColors,
  blackAndWhiteStripedPalette,
  blackAndBlueStripedPalette,
};
