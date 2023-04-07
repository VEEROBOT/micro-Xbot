/*
  Voltage Reading: This program reads analog voltage and converts it to battery voltage

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

float batteryVoltage = 0.00;
float R1 = 10000.0;        // R1 and R2 value in Ohms
float R2 = 2000.0;
float ref_voltage = 5.0;  // Float for Reference Voltage
int analogPinValue = 0;
float adc_voltage = 0.0;
float calibration_factor = 0.05;  // check the deviation % using a multimeter

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read battery pin analog value
  analogPinValue = analogRead(BV);
  adc_voltage  = analogPinValue * (ref_voltage / 1024.0);

  batteryVoltage = adc_voltage / (R2 / (R1 + R2));
  batteryVoltage = batteryVoltage + (batteryVoltage * calibration_factor);
  Serial.print("Battery Voltage = " );
  Serial.println(batteryVoltage );
  delay(300);
}