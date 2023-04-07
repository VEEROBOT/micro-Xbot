/*
  Light Detecting: This program controls LED brightness depending on the amount of Light it detects

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
int ldr1Reading = 0;      // to store analog value of LDR1
int ldr2Reading = 0;      // to store analog value of LDR2
int LEDBrightness = 0;    // to store the value of LED Brightness
int threshold_val = 50;   // Add a threshold to control on and off of LED

void setup() {
  Serial.begin(9600);     // initializing serial communication.
  pinMode(LED_BUILTIN, OUTPUT);   // Defining LED pin as output
}

void loop() {
  ldr1Reading = analogRead(LDR1);    // Reading LDR1 value
  ldr2Reading = analogRead(LDR2);    // Reading LDR2 value
  Serial.println((String)"LDR1:" + ldr1Reading + " LDR2:" + ldr2Reading); // Printing to serial monitor

  if (ldr1Reading > threshold_val) {                 // Condition to make LED ON.
    LEDBrightness = map(ldr1Reading, 0, 1023, 0, 255); // Converting LDR to LED Brightness.
    analogWrite(LED_BUILTIN, LEDBrightness); // Writing Brightness to LED.
  }
  else {
    analogWrite(LED_BUILTIN, 0);             // If LDR is below threshold make LED OFF.
  }
  delay(300);                               // delay to make output readable on serial monitor.
}