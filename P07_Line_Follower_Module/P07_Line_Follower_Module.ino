/*
  Line Follower Module: Reads values from three different infrared modules and suggests actions

  At VEEROBOT, we invest time and resources providing this open source code,
  Please support VEEROBOT and open-source hardware by purchasing products
  from us @ http://veerobot.com
  -----------------------------------------------------------------------------
  You are free to redistribute it and/or modify it under the terms of the GNU
  Lesser General Public License as  published by the Free Software Foundation,
  either version 3 of the License, or (at your option) any later version.

  This Code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  See <http://www.gnu.org/licenses/>
*/

#include "config.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  byte linecolor_threshold = 100; // tune this value measuring against the lines
  int s1, s2, s3;
  s1 = analogRead(LF1); // Right
  s2 = analogRead(LF2); // Center
  s3 = analogRead(LF3); // Left
  Serial.print((String)"Right Sensor :" + s1 + " | Center Sensor :" + s2 + " | Left Sensor :" + s3); // Print to serial monitor

/* 
 *  There are eight different possibilities from three sensors
 *  0 - 0 - 0
 *  0 - 0 - 1
 *  0 - 1 - 0
 *  0 - 1 - 1
 *  1 - 0 - 0
 *  1 - 0 - 1
 *  1 - 1 - 0
 *  1 - 1 - 1
 */

  // 0 is black and 1 is white
  if ((s1 < linecolor_threshold) && (s2 < linecolor_threshold) && (s3 < linecolor_threshold))       Serial.println(" | 0 - 0 - 0 : Go Straight");
  else if ((s1 < linecolor_threshold) && (s2 < linecolor_threshold) && (s3 > linecolor_threshold))  Serial.println(" | 0 - 0 - 1 : Slow Right");
  else if ((s1 < linecolor_threshold) && (s2 > linecolor_threshold) && (s3 < linecolor_threshold))  Serial.println(" | 0 - 1 - 0 : Split Lines");
  else if ((s1 < linecolor_threshold) && (s2 > linecolor_threshold) && (s3 > linecolor_threshold))  Serial.println(" | 0 - 1 - 1 : Turn Right");
  else if ((s1 > linecolor_threshold) && (s2 < linecolor_threshold) && (s3 < linecolor_threshold))  Serial.println(" | 1 - 0 - 0 : Slow Left");
  else if ((s1 > linecolor_threshold) && (s2 < linecolor_threshold) && (s3 > linecolor_threshold))  Serial.println(" | 1 - 0 - 1 : Go Straight");
  else if ((s1 > linecolor_threshold) && (s2 > linecolor_threshold) && (s3 < linecolor_threshold))  Serial.println(" | 1 - 1 - 0 : Turn Left");
  else if ((s1 > linecolor_threshold) && (s2 > linecolor_threshold) && (s3 > linecolor_threshold))  Serial.println(" | 1 - 1 - 1 : Stop");
  delay(300);
}