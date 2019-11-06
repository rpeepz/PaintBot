int readX = 500;
int readY = 500;

int neutral = 500;
int jsDeadZone = 30;

int joystickPower = 150;

void updateJoystick() {
   readX = analogRead(VRx);
   readY = analogRead(VRy);
}

bool joystickIsActive() {
  return (
    readX <= neutral - jsDeadZone ||
    readX >= neutral + jsDeadZone ||
    readY <= neutral - jsDeadZone ||
    readY >= neutral + jsDeadZone
   );
}

bool joystick(const int VRx, const int VRy) {
    updateJoystick();
    while (joystickIsActive()) {
      //DEBUG:
//      debugEncoders();
//      debugJoystick();
      if (readX < 300) {
        goRight(joystickPower);
      } else if (readX > 700) {
        goLeft(joystickPower);
      } else if (readY < 300) {
        goUp_v2(joystickPower, joystickPower);
      } else if (readY > 700) {
        goDown_v2(joystickPower, joystickPower);
      }
      updateJoystick();
    }
    doStop();
}
