#define SRPAY_MAX_VOLTAGE 255
#define MOTOR_VOLTAGE 255

#include "Encoder.h"
//bool swState = false;
int readX = 500;
int readY = 500;

//const int encoderRightA = 2; // Green - pin 4 - Digital
//const int encoderRightB = 3; // White - pin 5 - Digital
//const int encoderLeftA = 18; // Green - pin 2 - Digital
//const int encoderLeftB = 19; // White - pin 3 - Digital
//const int RPWMOutputRight = 10; // Arduino PWM output pin 9; connect to IBT-2 pin 1 (RPWM)
//const int LPWMOutputRight = 11; // Arduino PWM output pin 10; connect to IBT-2 pin 2 (LPWM)
//const int RPWMOutputLeft = 8; // Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM)
//const int LPWMOutputLeft = 9; // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM)
const int ZMOTOR_A_Output = 12; // Arduino PWM output pin 7; connect to IBT-2 pin 1 (RPWM)
const int ZMOTOR_B_Output = 13; // Arduino PWM output pin 8; connect to IBT-2 pin 2 (LPWM)
/////////////////////////////////////////////////////////////////////////////////////// PINS //////////////////////////////////////////////////////////////////////////////
const int VRx = A1; // Joystick x axis
const int VRy = A0; // Joystick y axis
const int JOYSTICK_SW = 13; // Joystick click

// Logic pins for encoders - Must use interrupt pins
const uint8_t encoderRightA = 20; // Green - Digital
const uint8_t encoderRightB = 21; // White - Digital
const uint8_t encoderLeftA = 18; // Green - Digital
const uint8_t encoderLeftB = 19; // White - Digital
long  encValL = 0;
long  encValR = 0;

// Logic pins for motors - Must use PWM pins
const int RPWMOutputRight = 10;
const int LPWMOutputRight = 11;
const int RPWMOutputLeft = 8;
const int LPWMOutputLeft = 9;
/////////////////////////////////////////////////////////////////////////////////////// Globals //////////////////////////////////////////////////////////////////////////////

int spraySwitchDistance = 600;

long encoderLeft = 0;
long encoderRight = 0;
bool done = false;
long encL = 8000L * 6;
long encR = 6000L * 8;
long encLprev = 0L;
long encRprev = 0L;

//void callibrate(     callibrate(100, "FORWARD");
Encoder leftMotorEnc;
Encoder rightMotorEnc;

///////////////////////////////////////////////////////////////// SETUP ///////////////////////////////////////////////////////
void setup() {
  
  Serial.begin(9600);

  //MOVEMENT MOTORS//
  pinMode(encoderLeftA, INPUT_PULLUP);
  pinMode(encoderLeftB, INPUT_PULLUP);
  pinMode(encoderRightA, INPUT_PULLUP);
  pinMode(encoderRightB, INPUT_PULLUP);
  pinMode(RPWMOutputLeft, OUTPUT);
  pinMode(LPWMOutputLeft, OUTPUT);
  pinMode(RPWMOutputRight, OUTPUT);
  pinMode(LPWMOutputRight, OUTPUT);

  //JOYSTICK//
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(JOYSTICK_SW, INPUT);
  digitalWrite(JOYSTICK_SW, HIGH);

  //MOVEMENT ENCODERS//
  attachInterrupt(digitalPinToInterrupt(encoderLeftA), encoderLeftPinChangeA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderLeftB), encoderLeftPinChangeB, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderRightA), encoderRightPinChangeA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderRightB), encoderRightPinChangeB, CHANGE);

  //SPRAY//
//  pinMode(encoderZA, INPUT_PULLUP);
//  pinMode(encoderZB, INPUT_PULLUP);
  //Check if Spray nozzle is engaged and set it off
//  spraying = EEPROM.read(sprayStatusCacheAddr);
//  if (spraying) {
//    stopSpraying();
//  }
}

void loop() {
  int turn = digitalRead(JOYSTICK_SW);
  if (turn)
    joystick(VRx, VRy, encoderLeft, encoderRight, MOTOR_VOLTAGE);
  else
  {
    while (!done)
    {
      encoderLeft = 0;
      encoderRight = 0;
      delay(100);
      encoderLeft = 0;
      encoderRight = 0;
      square_v2();
//      spray();
//      delay(400);
//      stopSpraying();
    Serial.print("Encoder Left = ");
    Serial.println(encoderLeft);
    Serial.print("Encoder Right = ");
    Serial.println(encoderRight);
    Serial.println("start left");
//      goRight_v2(180, 250);
      delay(1000);
      break ;
    }
  }
}

// Reading the encoder inputs
//  Left encoder
void encoderLeftPinChangeA() {
  encoderLeft += digitalRead(encoderLeftA) == digitalRead(encoderLeftB) ? -1 : 1;
}

void encoderLeftPinChangeB() {
  encoderLeft += digitalRead(encoderLeftA) != digitalRead(encoderLeftB) ? -1 : 1;
}

//  Right encoder
void encoderRightPinChangeA() {
  encoderRight += digitalRead(encoderRightA) == digitalRead(encoderRightB) ? -1 : 1;
}

void encoderRightPinChangeB() {
  encoderRight += digitalRead(encoderRightA) != digitalRead(encoderRightB) ? -1 : 1;
}
