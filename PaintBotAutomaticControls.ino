#include "Encoder.h"
#include "Motor.h"

#define WIDTH 85
#define HEIGHT 64
#define LEFT_ANCHOR_OFFSET_X -5
#define LEFT_ANCHOR_OFFSET_Y 5
#define RIGHT_ANCHOR_OFFSET_X 5
#define RIGHT_ANCHOR_OFFSET_Y 5
#define ROTATION_DISTANCE 2.65
#define MAX_VOLTAGE 180

#define MAX_WIDTH_SECONDS 15 //if center piece is 2 feet away from right beam, it takes 15 seconds to go horizontally to left beam
#define MAX_HEIGHT_SECONDS 10 //if center piece is ? feet away from top beam, it takes ?? seconds to go vertically to bottom beam 

const int VRx = A1; // Joystick x axis
const int VRy = A0; // Joystick y axis
const int JOYSTICK_SW = 13; //

struct vector {
  float x;
  float y;
};

struct vectorNode {
  struct vector point;
  bool spray;
  struct vectorNode *next;
};

struct vectorQueue {
  struct vectorNode *first;
  struct vectorNode *last;
};

// Dimensions of the structure
const float width = 85;
const float height = 67;

// Logic pins for encoders
const uint8_t encoderRightA = 20; // Green - pin 4 - Digital
const uint8_t encoderRightB = 21; // White - pin 5 - Digital
const uint8_t encoderLeftA = 18; // Green - pin 2 - Digital
const uint8_t encoderLeftB = 19; // White - pin 3 - Digital
long  encValL = 0;          
long  encValR = 0;

// Logic pins for motors
const int RPWMOutputRight = 10; // Arduino PWM output pin 9; connect to IBT-2 pin 1 (RPWM)
const int LPWMOutputRight = 11; // Arduino PWM output pin 10; connect to IBT-2 pin 2 (LPWM)
const int RPWMOutputLeft = 8; // Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM)
const int LPWMOutputLeft = 9; // Arduino PWM output pin 6; connect to IBT-2 pin 2 (LPWM)

struct vector origin = (struct vector){ width / 2, height / 2 };
struct vector topRight = (struct vector){ width, height };
struct vector topLeft = (struct vector){ 0, height };
struct vector start;
struct vector goTo;
struct vectorQueue *points = NULL;
bool done = false;

Encoder leftMotorEnc;
Encoder rightMotorEnc;

Motor leftMotor;
Motor rightMotor;


void setup() {
  
  Serial.begin(9600);

  leftMotorEnc.setup(encoderLeftA, encoderLeftB);
  rightMotorEnc.setup(encoderRightA, encoderRightB);
  
  leftMotorEnc.write(0);
  rightMotorEnc.write(0);
  
  pinMode(RPWMOutputLeft, OUTPUT);
  pinMode(LPWMOutputLeft, OUTPUT);
  pinMode(RPWMOutputRight, OUTPUT);
  pinMode(LPWMOutputRight, OUTPUT);

   //JOYSTICK//
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(JOYSTICK_SW, INPUT);
  digitalWrite(JOYSTICK_SW, HIGH);

  
  points = loadPoints();
  start = origin;
  goTo = vectorQueueDequeue(points);
}

void loop() {
//  Serial.print("Right encoder");
//  Serial.print(rightMotorEnc.read());
//  Serial.print("Left encoder");
//  Serial.println(leftMotorEnc.read());
  int turn = digitalRead(JOYSTICK_SW);
  if (turn)
    joystick(VRx, VRy);
  else {
    while (!done) {
      rightMotorEnc.write(0);
      bool rightMotorFinished = false;
      float rightChainCurrentLength = distanceBetweenVectors(topRight, start, RIGHT_ANCHOR_OFFSET_X, RIGHT_ANCHOR_OFFSET_Y);
      float rightChainNewLength = distanceBetweenVectors(topRight, goTo, RIGHT_ANCHOR_OFFSET_X, RIGHT_ANCHOR_OFFSET_Y);
      float rightMotorDistanceToTravel = fabs(rightChainCurrentLength - rightChainNewLength);
      bool rightMotorRotateClockwise = (rightChainNewLength < rightChainCurrentLength);

      leftMotorEnc.write(0);
      bool leftMotorFinished = false;
      float leftChainCurrentLength = distanceBetweenVectors(topLeft, start, LEFT_ANCHOR_OFFSET_X, LEFT_ANCHOR_OFFSET_Y);
      float leftChainNewLength = distanceBetweenVectors(topLeft, goTo, LEFT_ANCHOR_OFFSET_X, LEFT_ANCHOR_OFFSET_Y);
      float leftMotorDistanceToTravel = fabs(leftChainCurrentLength - leftChainNewLength);
      bool leftMotorRotateClockwise = (leftChainNewLength > leftChainCurrentLength);

      while (!rightMotorFinished || !leftMotorFinished) {
        float rightMotorDistanceTraveled = (fabs(rightMotorEnc.read() / (2400.0 * 8.0))) * ROTATION_DISTANCE; // ERROROROORORR
        float leftMotorDistanceTraveled = (fabs(leftMotorEnc.read() / (2400.0 * 8.0))) * ROTATION_DISTANCE; // Added divided by 8.0 because 8 rotations of the encoders is one rotation of the chain sprocket
        float rightMotorVoltagePercentage = (rightMotorDistanceToTravel - rightMotorDistanceTraveled) / max(leftMotorDistanceToTravel - leftMotorDistanceTraveled, rightMotorDistanceToTravel - rightMotorDistanceTraveled);
        float leftMotorVoltagePercentage = (leftMotorDistanceToTravel - leftMotorDistanceTraveled) / max(leftMotorDistanceToTravel - leftMotorDistanceTraveled, rightMotorDistanceToTravel - rightMotorDistanceTraveled);
        int leftMotorVoltage = leftMotorVoltagePercentage * MAX_VOLTAGE;
        int rightMotorVoltage = rightMotorVoltagePercentage * MAX_VOLTAGE;
//        Serial.print("Right motor distance traveled: ");
//        Serial.print(rightMotorDistanceTraveled);
//        Serial.print(" Left motor distance traveled: ");
//        Serial.println(leftMotorDistanceTraveled);
//        Serial.print("Right encoder rotations: ");
//        Serial.print(rightMotorEnc.read() / (2400.0 * 8.0) * ROTATION_DISTANCE);
//        Serial.print(" Left encoder rotations: ");
//        Serial.println(leftMotorEnc.read() / (2400.0 * 8.0) * ROTATION_DISTANCE);
        if (!rightMotorFinished)
        {
          if (rightMotorDistanceTraveled < rightMotorDistanceToTravel)
          {
            if (rightMotorRotateClockwise)
            {
              analogWrite(RPWMOutputRight, rightMotorVoltage);
              analogWrite(LPWMOutputRight, 0);
            }
            else
            {
              analogWrite(RPWMOutputRight, 0);
              analogWrite(LPWMOutputRight, rightMotorVoltage);
            }
          }
          else
          {
            Serial.println("Right motor finished");
            rightMotorFinished = true;
            analogWrite(RPWMOutputRight, 0);
            analogWrite(LPWMOutputRight, 0);
          }
        }
        // Left motor
        if (!leftMotorFinished)
        {
          if (leftMotorDistanceTraveled < leftMotorDistanceToTravel)
          {
            if (leftMotorRotateClockwise)
            {
              analogWrite(RPWMOutputLeft, leftMotorVoltage);
              analogWrite(LPWMOutputLeft, 0);
            }
            else
            {
              analogWrite(RPWMOutputLeft, 0);
              analogWrite(LPWMOutputLeft, leftMotorVoltage);
            }
          }
          else if (leftMotorFinished == false)
          {
            Serial.println("Left motor finished");
            leftMotorFinished = true;
            analogWrite(RPWMOutputLeft, 0);
            analogWrite(LPWMOutputLeft, 0);
          }
        }
      }
      if (isVectorQueueEmpty(points) == true)
        done = true;
      else
      {
        start = goTo;
        goTo = vectorQueueDequeue(points);
      }
    }
  }
}   
