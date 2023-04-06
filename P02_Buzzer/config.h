/*
* config.h : A configuration file to map pinouts in micro:Xbot
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

#ifndef _CONFIG_H
#define _CONFIG_H

#define STX D2           // Software Serial Tx Pin
#define SRX D3           // Software Serial Rx Pin

#define EN1 5            // Motor 1 PWM Pin
#define EN2 6            // Motor 2 PWM  Pin
#define IN1 4            // Motor 1 Direction Pin
#define IN2 7            // Motor 2 Direction Pin

#define LDR1 A6          // Right LDR Sensor
#define LDR2 A7          // Left LDR Sensor

#define IRRX 8           // IR Receiver

#define BUZZ 9           // Buzzer Output

#define LED_BUILTIN 10   // LED Pin

#define TRIG 11          // Trigger Pin for Sonar
#define ECHO 12          // Echo Pin for Sonar

#define RGB 13     	 // RGB LED Output

#define LF1 A0   	 // Right IRRX Module
#define LF2 A1   	 // Center IRRX Module
#define LF3 A2   	 // Left IRRX Module
#define BV A3    	 // Battery Voltage Pin
#define SDA_PIN A4   	 // Right LDR Sensor
#define SCL_PIN A5   	 // Left LDR Sensor

#define MAX_DISTANCE 500 // We will use this for maximum Sonar distance

// We will use the below enum to define different RGB Colours
enum RGBColor { UNDEF, RED, ORANGE, YELLOW, GREEN,  BLUE, PURPLE, WHITE, BLACK };

#endif //_CONFIG_H
