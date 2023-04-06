/*
* Blinking LED: The program below turns an LED on for one second, 
* then off for one second, and continuous endlessly. LED is connected to pin 10
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

void setup() 
{
  // Initialize digital pin as output
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second
}
