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
#include "IRstepI/IRstepI.h"

// Hex values of each button on remote control. These are 
// specific for the remote controller provided with thie kit.
// In case you have a different remote control, all you need to 
// do is uncomment Serial.print("Hex Value = "); and find 
// appropriate Hex value which can be later mapped to buttons.

#define POWER	0xF61E2A57//power//0x1FE48B7
#define MODE	0x1AD1ED61//menu//0x1FE58A7
#define MUTE	0x1FE7887
#define PLAY	0x1FE807F
#define REWIND	0x81930A09//down//0x1FE40BF
#define FORWARD	0xC20370A1//up//0x1FEC03F
#define EQUIL	0x1FE20DF
#define VOLUMEM	0x983AB4C1//left//0x1FEA05F
#define VOLUMEP	0x21035431//right//0x1FE609F
#define ZER0	0x1FEE01F
#define REPT	0x1FE10EF
#define USD		0x1FE906F
#define ONE		0x1FE50AF
#define TWO		0x1FED827
#define THREE	0x1FEF807
#define FOUR	0x1FE30CF
#define FIVE	0x1FEB04F
#define SIX		0x1FE708F
#define SEVEN	0x1FE00FF
#define EIGHT	0x1FEF00F
#define NINE	0x1FE9867

int remoteValue = 50;
IRrecv irrecv(IRRX);
decode_results results;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);   // Set up serial communication
  irrecv.enableIRIn();	// Start the receiver
}

void loop()
{
  if (irrecv.decode(&results))
  {
    Serial.print("Hex Value = ");
    Serial.print(results.value, HEX);  // print raw values
    translateIR(); 
    irrecv.resume(); // wait for the next value
  }
	controlComponents();
}

void translateIR()
{
  Serial.print(" : Button = ");
  switch(results.value)
  {
 case POWER:
    Serial.print(" POWER		");
	powerBoard();		// turn on circuit
    break;
 case MODE:
    Serial.print(" MODE			"); 
	break;
 case MUTE:
    Serial.print(" MUTE			");
    break;
 case PLAY:
    Serial.print(" PLAY			");
    break;
 case REWIND:
    Serial.print(" REWIND		");
	remoteValue = remoteValue - 10;
    break;
 case FORWARD:
    Serial.print(" FORWARD		");
	remoteValue = remoteValue + 10;
    break;
 case EQUIL:
    Serial.print(" EQUILISER	");
    break;
  case VOLUMEM:  
    Serial.print(" VOLUME MINUS	"); 
    break;
  case VOLUMEP:  
    Serial.print(" VOLUME PLUS	"); 
    break;
  case ZER0:  
    Serial.print(" ZERO			"); 
    break;
  case REPT:  
    Serial.print(" REPEAT		"); 
    break;
  case USD:  
    Serial.print(" US/D			"); 
    break;
  case ONE:  
    Serial.print(" ONE			"); 
    break;
  case TWO:  
    Serial.print(" TWO			"); 
    break;
  case THREE:  
    Serial.print(" THREE		"); 
    break;
  case FOUR:  
    Serial.print(" FOUR			"); 
    break;
  case FIVE:  
    Serial.print(" FIVE			"); 
    break;
  case SIX:  
    Serial.print(" SIX			"); 
    break;
  case SEVEN:  
    Serial.print(" SEVEN		"); 
    break;
  case EIGHT:  
    Serial.print(" EIGHT		"); 
    break;
  case NINE:  
    Serial.print(" NINE			"); 
    break;
  default: 
    Serial.print(" #NOT MAPPED	");
  }
  Serial.println();
  //delay(500);					// avoid multiple presses
}

// This is the main logic function. Any additional components
// can be attached here and extended.
void controlComponents(){
	if(powerStatus == 1)		// checks if power button is on
	{
		controlMotor();
	}
	else{
		digitalWrite(motorPin, LOW);    // sets motor off
	}
}