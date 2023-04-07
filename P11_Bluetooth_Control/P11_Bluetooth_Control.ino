/*
  Bluetooth Control: Use a bluetooth module to wirelessly control the board

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

#include <SoftwareSerial.h>
#include "config.h"

SoftwareSerial btSerial(3, 2); // RX, TX
char cmd = 0;                //Variable for storing received data

void setup() {
  Serial.begin(9600);   // initialize serial connection
  btSerial.begin(9600); // initialize bluetooth connection
}

void loop() {
  decodeserialcommand();
}

void decodeserialcommand() {
  if (btSerial.available() > 0)   {
    cmd = btSerial.read();      //Read the incoming data and store it into variable data
    Serial.println(cmd);        //Print Value inside data in Serial monitor
    switch (cmd) {
      case 'W':
        Serial.println("Up Button");
        break;
      case 'X':
        Serial.println("Down Button");
        break;
      case 'A':
        Serial.println("Left Button");
        break;
      case 'D':
        Serial.println("Right Button");
        break;
      case 'Q':
        Serial.println("Top Left Button");
        break;
      case 'E':
        Serial.println("Top Right Button");
        break;
      case 'Z':
        Serial.println("Bottom Left Button");
        break;
      case 'C':
        Serial.println("Bottom Right Button");
        break;
      case 'S':
        Serial.println("Stop/Center Button");
        break;
      case 'T':
        Serial.println("Down Arrow");
        break;
      case 'Y':
        Serial.println("Up Arrow");
        break;
      case 'R':
        Serial.println("Red Button");
        break;
      case 'G':
        Serial.println("Blue Button");
        break;
      case 'B':
        Serial.println("Green Button");
        break;
      case 'O':
        Serial.println("White Button");
        break;
      case 'L':
        Serial.println("Gray Button");
        break;
      case 'M':
        Serial.println("Buzzer Button");
        break;
      case '1':
        Serial.println("Manual Key");
        break;
      case '2':
        Serial.println("Autonomous Key");
        break;
      case '3':
        Serial.println("Line Follower Key");
        break;
      default:
        break;
    }
  }
}