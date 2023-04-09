/*
* Fading LED: The program below fades an LED from On to Off to On continuously. 
* LED is connected to pin 10
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

#include "config.h"

int brightness = 0;  // how bright the LED is
int fadeAmount = 5;  // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 10 to be an output:
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // set the brightness of pin 10:
  analogWrite(LED_BUILTIN, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}