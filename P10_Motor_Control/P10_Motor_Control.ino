/*
  Motor Controller: Controls the direction and speed of two motors on either side

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
  Serial.begin(9600);    // begin serial communication

  pinMode(EN1, OUTPUT);  // sets motor pins as output
  pinMode(EN2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);  
  testMotors();          // run this function once
}

void loop() {
// we do not have anything to run in the loop
}


void testMotors() {
  LeftMotor(100, false);  // both motors forward
  RightMotor(100, false);
  delay(2500);

  LeftMotor(0, true);    // both motors stopped
  RightMotor(0, true);
  delay(500);

  LeftMotor(150, true);  // both motors reverse
  RightMotor(150, true);
  delay(2500);

  LeftMotor(0, true);    // both motors stopped
  RightMotor(0, true);
  delay(500);

  LeftMotor(125, true);  // Left forward and Right Backward
  RightMotor(200, false);
  delay(2500);

  LeftMotor(0, true);    // both motors stopped
  RightMotor(0, true);
  delay(500);

  LeftMotor(150, false);  // Left backward and Right forward
  RightMotor(75, true);
  delay(2500);

  LeftMotor(0, true);      // both motors stopped
  RightMotor(0, true);
  delay(500);
}

void LeftMotor(int pwm, boolean reverse) // left motor
{
  analogWrite(EN1, pwm); //set pwm control, 0 for stop, and 255 for maximum speed
  if (reverse)
  {
    digitalWrite(IN1, HIGH);
  }
  else
  {
    digitalWrite(IN1, LOW);
  }
}

void RightMotor(int pwm, boolean reverse) // right motor
{
  analogWrite(EN2, pwm);
  if (reverse)
  {
    digitalWrite(IN2, HIGH);
  }
  else
  {
    digitalWrite(IN2, LOW);
  }
}