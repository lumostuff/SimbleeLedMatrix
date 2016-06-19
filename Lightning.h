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

// Based on Lightning2014 by Daniel Wilson, 2014
// https://github.com/fibonacci162/LEDs

void lightning() {
  // The first "flash" in a bolt of lightning is the "leader." The leader
  // is usually duller and has a longer delay until the next flash. Subsequent
  // flashes, the "strokes," are brighter and happen at shorter intervals.

  const uint8_t frequency = 50; // controls the interval between strikes
  const uint8_t flashes = 8;    // the upper limit of flashes per strike

  static uint8_t dimmer = 1;
  static uint8_t flashCount = flashes;
  static uint8_t flashCounter = 0;

  static uint32_t delayMillis = 0;
  static uint32_t delayStart = 0;

  static bool flashing = true;

  // bail, if we haven't waited long enough
  if (millis() < delayMillis + delayStart)
    return;

  flashing = !flashing;

  if (flashCounter >= flashCount) // if we've finished the current set of flashes, clear the display and wait a bit
  {
    flashCounter = 0;
    fill_solid(leds, NUM_LEDS, CRGB::Black); // clear the display
    delayMillis = random8(frequency) * 100;
    delayStart = millis();
    return;
  }

  if (flashCounter == 0) dimmer = 5; // the brightness of the leader is scaled down by a factor of 5
  else dimmer = random8(1, 3);      // return strokes are brighter than the leader

  if (flashing)
  {
    fill_solid(leds, NUM_LEDS, CHSV(255, 0, 255 / dimmer));
    delayMillis = random8(4, 10);
    delayStart = millis();
  }
  else
  {
    fill_solid(leds, NUM_LEDS, CRGB::Black); // clear the display
    delayMillis = 50 + random8(100);
    if (flashCount == 0) delayMillis += 150; // longer delay until next flash after the leader
  }

  flashCounter++;
}
