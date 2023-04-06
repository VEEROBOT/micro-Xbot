/*
* RGB LED: The program controls two programmable LED's from a single pin
*
* At VEEROBOT, we invest time and resources providing this open source code,
* Please support VEEROBOT and open-source hardware by purchasing products
* from us @ http://veerobot.com
* -----------------------------------------------------------------------------
* You are free to redistribute it and/or modify it under the terms of the GNU
* Lesser General Public License as  published by the Free Software Foundation,
* either version 3 of the License, or (at your option) any later version.
*
* This Code is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* See <http://www.gnu.org/licenses/>
*/

#include <Adafruit_NeoPixel.h>
#include "config.h"

#define PIXEL_COUNT 2  // Number of RGB LED's

Adafruit_NeoPixel strip(PIXEL_COUNT, RGB, NEO_RGB + NEO_KHZ800);

void setup() {
  strip.begin();  // Initialize RGB LED strip object (REQUIRED)
  strip.show();   // Initialize all LED's to 'off'
}

void loop() {
  colorWipe(strip.Color(255, 0, 0), 50);  // Red
  delay(1000);
  colorWipe(strip.Color(0, 255, 0), 50);  // Green
  delay(1000);
  colorWipe(strip.Color(0, 0, 255), 50);  // Blue
  delay(1000);
  rainbow(5);
  colorWipe(strip.Color(255, 255, 255), 50);  // White
  delay(1000);  
  theaterChaseRainbow(50);
  colorWipe(strip.Color(0, 0, 0), 50);  // Off
  delay(3000);
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {  // For each pixel in strip...
    strip.setPixelColor(i, color);               //  Set pixel's color (in RAM)
    strip.show();                                //  Update strip to match
    delay(wait);                                 //  Pause for a moment
  }
}

void theaterChase(uint32_t color, int wait) {
  for (int a = 0; a < 10; a++) {   // Repeat 10 times...
    for (int b = 0; b < 3; b++) {  //  'b' counts from 0 to 2...
      strip.clear();               //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for (int c = b; c < strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color);  // Set pixel 'c' to value 'color'
      }
      strip.show();  // Update strip with new contents
      delay(wait);   // Pause for a moment
    }
  }
}

void rainbow(int wait) {
  for (long firstPixelHue = 0; firstPixelHue < 3 * 65536; firstPixelHue += 256) {
    for (int i = 0; i < strip.numPixels(); i++) {  // For each pixel in strip...
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();  // Update strip with new contents
    delay(wait);   // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;           // First pixel starts at red (hue 0)
  for (int a = 0; a < 30; a++) {   // Repeat 30 times...
    for (int b = 0; b < 3; b++) {  //  'b' counts from 0 to 2...
      strip.clear();               //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for (int c = b; c < strip.numPixels(); c += 3) {
        int hue = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue));  // hue -> RGB
        strip.setPixelColor(c, color);                        // Set pixel 'c' to value 'color'
      }
      strip.show();                 // Update strip with new contents
      delay(wait);                  // Pause for a moment
      firstPixelHue += 65536 / 90;  // One cycle of color wheel over 90 frames
    }
  }
}