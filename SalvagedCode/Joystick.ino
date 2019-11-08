bool joystick(const int VRx, const int VRy, int encoderLeft, int encoderRight, int vol)
{
    readX = analogRead(VRx);
    readY = analogRead(VRy);
    Serial.print("X-axis: ");
    Serial.println(readX);
    Serial.print("Y-axis: ");
    Serial.println(readY);
    Serial.print(encoderLeft);
    Serial.print(" - ");
    Serial.println(encoderRight);
    Serial.print("\n\n");

    while (readX < 300 && readY > 600)
    {
      goDownRight(vol);
      readX = analogRead(VRx);
      readY = analogRead(VRy);
    }
    doStop();
    while (readY > 600 && readX < 300)
    {
      goUpRight(vol);
      readX = analogRead(VRx);
      readY = analogRead(VRy);
    }
    doStop();
    while (readY < 300 && readX < 300)
    {
      goDownRight(vol);
      readX = analogRead(VRx);
      readY = analogRead(VRy);
    }
    doStop();
    while (readY > 600 && readX > 600)
    {
      goUpLeft(vol);
      readX = analogRead(VRx);
      readY = analogRead(VRy);
    }
    doStop();
    while (readX < 300)
    {
//      goRight_v2(140, 200);
      goRight(vol);
      readX = analogRead(VRx);
      readY = analogRead(VRy);
    }
    doStop();
    while (readX > 700)
    {
//      goLeft_v2(150, 165);
      goLeft(vol);
      readX = analogRead(VRx);
      readY = analogRead(VRy);
    }
    doStop();
    while (readY < 300)
    {
//      goDown_v2(145, 200);
      goDown(vol);
      readX = analogRead(VRx);
      readY = analogRead(VRy);
    }
    doStop();
    while (readY > 700)
    {
//      goUp_v2(145, 200);
      goUp(vol);
      readX = analogRead(VRx);
      readY = analogRead(VRy);
    }
    doStop();
}
