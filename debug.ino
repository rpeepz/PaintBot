void debugEncoders() {
      Serial.print("Encoder right :");
      Serial.println(rightMotorEnc.read());
      Serial.print("Encoder left  :");
      Serial.println(leftMotorEnc.read());
}

void debugJoystick() {
      Serial.print("Joystick X :");
      Serial.println(analogRead(VRx));
      Serial.print("Joystick Y  :");
      Serial.println(analogRead(VRy));
}
