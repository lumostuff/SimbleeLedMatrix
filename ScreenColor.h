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

// color screen controls
uint8_t ui_buttonColorBack;
uint8_t ui_rectSwatch;
uint8_t ui_imageColorWheel;

void colorSelectorScreen() {
  SimbleeForMobile.beginScreen(WHITE);

  SimbleeForMobile.drawText(85, 30, "LumoStuff Color", BLUE);

  uint16_t margin = 10;
  uint16_t height = 40;
  uint16_t y = 70;
  uint16_t width = SimbleeForMobile.screenWidth / 2;
  width -= margin * 1.5;

  ui_buttonColorBack = SimbleeForMobile.drawButton(10, y, width, "Back");

  width = SimbleeForMobile.screenWidth;
  width -= margin * 2;

  // border
  SimbleeForMobile.drawRect(margin, 120, width, height, BLACK);
  ui_rectSwatch = SimbleeForMobile.drawRect(margin + 1, 121, width - 2, height - 2, WHITE);

  ui_imageColorWheel = SimbleeForMobile.drawImage(COLOR_WHEEL, margin, 170);

  SimbleeForMobile.setEvents(ui_imageColorWheel, EVENT_COLOR);

  SimbleeForMobile.endScreen();
}

void handleColorScreenEvents(event_t &event) {
  if (event.id == ui_buttonColorBack) {
    SimbleeForMobile.showScreen(1);
  }
  else if (event.id == ui_imageColorWheel) {
    Serial.print("R,G,B: ");
    Serial.print(event.red);
    Serial.print(",");
    Serial.print(event.green);
    Serial.print(",");
    Serial.println(event.blue);

    solidColor.r = event.red;
    solidColor.g = event.green;
    solidColor.b = event.blue;
    SimbleeForMobile.updateColor(ui_rectSwatch, rgb(solidColor.r, solidColor.g, solidColor.b));
  }
}
