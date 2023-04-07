/*
  Test Me: This program is configured to test all the sensors and modules together
  Note that this program does not check Bluetooth connectivity

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

#include <Adafruit_NeoPixel.h>
#include "src/IRstepI/IRstepI.h"
#include "config.h"

#define PIXEL_COUNT 2  // Number of RGB LED's
Adafruit_NeoPixel strip(PIXEL_COUNT, RGB, NEO_RGB + NEO_KHZ800);

#define POWER  0x1FE48B7
#define MODE  0x1FE58A7
#define MUTE  0x1FE7887
#define PLAY  0x1FE807F
#define REWIND  0x1FE40BF
#define FORWARD 0x1FEC03F
#define EQUIL 0x1FE20DF
#define VOLUMEM 0x1FEA05F
#define VOLUMEP 0x1FE609F
#define ZER0  0x1FEE01F
#define REPT  0x1FE10EF
#define USD   0x1FE906F
#define ONE   0x1FE50AF
#define TWO   0x1FED827
#define THREE 0x1FEF807
#define FOUR  0x1FE30CF
#define FIVE  0x1FEB04F
#define SIX   0x1FE708F
#define SEVEN 0x1FE00FF
#define EIGHT 0x1FEF00F
#define NINE  0x1FE9867

IRrecv irrecv(IRRX);
decode_results results;
unsigned long irCode = 0;

void setup()
{
  Serial.begin(9600);   // Set up serial communication
  pinMode(LED_BUILTIN, OUTPUT);
  irrecv.enableIRIn();  // Start the receiver

  strip.begin();  // Start RGB
  strip.show();

  pinMode(TRIG, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHO, INPUT); // Sets the echoPin as an Input

  pinMode(EN1, OUTPUT);  // sets motor pins as output
  pinMode(EN2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  Serial.println();
  Serial.println("Use IR Remote to check various sensors by pressing buttons 1 through 9");
  Serial.println("For Bluetooth, upload Bluetooth Program");
}

void loop()
{
  if (irrecv.decode(&results))
  {
    irCode = results.value;
    if (irCode != 0xFFFFFFFF) {
      translateIR();
    }
    irrecv.resume(); // wait for the next value
  }
}

void blink_led() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(1000);              // wait for a second
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);               // wait for a second
  }
  Serial.println(" - Stopped Blinking. Try next");
}

/*---------------------------------------------------------------------*/

void buzzer_tone() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZ, HIGH);
    delay(1000);
    digitalWrite(BUZZ, LOW);
    delay(1000);
  }
  Serial.println(" - Stopped making Noise. Try next");
}

/*---------------------------------------------------------------------*/
int brightness = 0;
int fadeAmount = 5;

void fade_led() {
  for (int i = 0; i < 50; i++) {
    analogWrite(LED_BUILTIN, brightness);
    brightness = brightness + fadeAmount;
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
    delay(30);
  }
  Serial.println(" - Stopped Fading LED. Try next");
}

/*---------------------------------------------------------------------*/
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void theaterChaseRainbow(int wait) {
  uint16_t i, j;
  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
  for (i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
  }
  strip.show();
  Serial.println(" - RGB Lights Off. Try next");
}

/*---------------------------------------------------------------------*/

int ldr1Reading = 0;      // to store analog value of LDR1
int ldr2Reading = 0;      // to store analog value of LDR2

void displayLDRValues() {
  Serial.println("Move your hand in front of Light Sensors. Runs for 10 Seconds");
  for (int i = 0; i < 20; i++) {
    ldr1Reading = analogRead(LDR1);    // Reading LDR1 value
    ldr2Reading = analogRead(LDR2);    // Reading LDR2 value
    Serial.println((String)"LDR1:" + ldr1Reading + " LDR2:" + ldr2Reading); // Printing to serial monitor
    delay(500);
  }
  Serial.println(" - LDR Sensor checked. Try next");
}

/*---------------------------------------------------------------------*/

float batteryVoltage = 0.00;
float R1 = 10000.0;        // R1 and R2 value in Ohms
float R2 = 2000.0;
float ref_voltage = 5.0;  // Float for Reference Voltage
int analogPinValue = 0;
float adc_voltage = 0.0;
float calibration_factor = 0.05;  // check the deviation % using a multimeter

void displayBatteryVolatage() {
  // read battery pin analog value
  analogPinValue = analogRead(BV);
  adc_voltage  = analogPinValue * (ref_voltage / 1024.0);

  batteryVoltage = adc_voltage / (R2 / (R1 + R2));
  batteryVoltage = batteryVoltage + (batteryVoltage * calibration_factor);
  Serial.print("Battery Voltage = " );
  Serial.print(batteryVoltage );
  Serial.println(" - Try Next" );
}

/*---------------------------------------------------------------------*/

int s1, s2, s3;
void readLFRSensors() {
  Serial.println("Move your hand in front the Line Following Sensors");
  for (int i = 0; i < 20; i++) {
    s1 = analogRead(LF1); // Right
    s2 = analogRead(LF2); // Center
    s3 = analogRead(LF3); // Left
    Serial.println((String)"Right Sensor :" + s1 + " | Center Sensor :" + s2 + " | Left Sensor :" + s3); // Print to serial monitor
    delay(500);
  }
  Serial.println(" - Done reading Line Sensors. Try Next" );
}

/*---------------------------------------------------------------------*/

long duration;  // duration of sound wave travel
int distance;   // distance measurement

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

void readSonar() {
  Serial.println("The reading runs for 10 Seconds. Move your hand in front of Sonar");
  for (int i = 0; i < 20; i++) {
    int obdistance = pingInCm();
    Serial.print("Distance in CM : ");
    if (obdistance > 40) Serial.println("Out of bound");
    else Serial.println(obdistance);
    delay(500);
  }
  Serial.println(" - Sonar Reading Complete. Try Next");
}

/*---------------------------------------------------------------------*/

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

void controlMotors() {
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

  Serial.println(" - Motor Checking Complete. Try Next");
}

/*---------------------------------------------------------------------*/

void translateIR()
{
  switch (irCode)
  {
    case POWER:
      Serial.println("POWER");
      break;
    case MODE:
      Serial.println("MODE");
      break;
    case MUTE:
      Serial.println("MUTE");
      break;
    case PLAY:
      Serial.println("PLAY");
      break;
    case REWIND:
      Serial.println("REWIND");
      break;
    case FORWARD:
      Serial.println("FORWARD");
      break;
    case EQUIL:
      Serial.println("EQUILISER");
      break;
    case VOLUMEM:
      Serial.println("VOLUME MINUS");
      break;
    case VOLUMEP:
      Serial.println("VOLUME PLUS");
      break;
    case ZER0:
      Serial.println("ZERO");
      break;
    case REPT:
      Serial.println("REPEAT");
      break;
    case USD:
      Serial.println("US/D");
      break;
    case ONE:
      Serial.println("Blink! Blink! Blink!");
      blink_led();
      break;
    case TWO:
      Serial.println("Lets make some noise");
      buzzer_tone();
      break;
    case THREE:
      Serial.println("LED Fade Effect. Press twice to see the effect");
      fade_led();
      break;
    case FOUR:
      Serial.println("Enjoy the Colours");
      theaterChaseRainbow(50);
      break;
    case FIVE:
      Serial.println("How bright is it outside?");
      displayLDRValues();
      break;
    case SIX:
      Serial.println("Checking Battery Voltage!");
      displayBatteryVolatage();
      break;
    case SEVEN:
      Serial.println("Let's Follow the Lane");
      readLFRSensors();
      break;
    case EIGHT:
      Serial.println("Checking if there is an obstacle");
      readSonar();
      break;
    case NINE:
      Serial.println("Run, Run, Run the Motors");
      controlMotors();
      break;
    default:
      Serial.println(" #NOT MAPPED  ");
  }
  delay(30);          // Software debouncing
}
