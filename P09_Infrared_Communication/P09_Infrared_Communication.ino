/*
  Ultrasonic Sensor: Sends a ping and calculates distance to obstacle in cms

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

long duration;  // duration of sound wave travel
int distance;   // distance measurement

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHO, INPUT); // Sets the echoPin as an Input
}

void loop() {
  int obdistance = pingInCm();
  Serial.print("Distance in CM : ");
  if (obdistance > 40) Serial.println("Out of bound");
  else Serial.println(obdistance);
  delay(300);
}

int pingInCm() {
  // Clears the trigPin condition
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (to and fro)
  return distance;
}