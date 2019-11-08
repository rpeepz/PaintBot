///////////////////////////////////////////////////////////////// MOVEMENTS ///////////////////////////////////////////////////////
void goUp(int vol)
{
  if (vol >= 255)
    vol = 255;
    analogWrite(RPWMOutputLeft, vol);
    analogWrite(LPWMOutputLeft, 0);
    
    analogWrite(RPWMOutputRight, 0);
    analogWrite(LPWMOutputRight, vol);
}

void goUp_v2(int volL, int volR)
{
  if (volL >= 255)
    volL = 255;
  if (volR >= 255)
    volR = 255;
    analogWrite(RPWMOutputLeft, volL);
    analogWrite(LPWMOutputLeft, 0);
    
    analogWrite(RPWMOutputRight, 0);
    analogWrite(LPWMOutputRight, volR);
}

void goDown(int vol)
{
  if (vol >= 255)
    vol = 255;
    analogWrite(RPWMOutputLeft, 0);
    analogWrite(LPWMOutputLeft, vol);
    
    analogWrite(RPWMOutputRight, vol);
    analogWrite(LPWMOutputRight, 0);
}

void goDown_v2(int volL, int volR)
{
  if (volL >= 255)
    volL = 255;
  if (volR >= 255)
    volR = 255;
    analogWrite(RPWMOutputLeft, 0);
    analogWrite(LPWMOutputLeft, volL);
    
    analogWrite(RPWMOutputRight, volR);
    analogWrite(LPWMOutputRight, 0);
}

void goRight(int vol)
{
  if (vol >= 255)
    vol = 255;
    analogWrite(RPWMOutputLeft, vol);
    analogWrite(LPWMOutputLeft, 0);
    
    analogWrite(RPWMOutputRight, vol);
    analogWrite(LPWMOutputRight, 0);
}

void goRight_v2(int volL, int volR)
{
  if (volL >= 255)
    volL = 255;
  if (volR >= 255)
    volR = 255;
    analogWrite(RPWMOutputLeft, volL);
    analogWrite(LPWMOutputLeft, 0);
    
    analogWrite(RPWMOutputRight, volR);
    analogWrite(LPWMOutputRight, 0);
}

void goLeft(int vol)
{
  if (vol >= 255)
    vol = 255;    
    analogWrite(RPWMOutputLeft, 0);
    analogWrite(LPWMOutputLeft, vol);
    
    analogWrite(RPWMOutputRight, 0);
    analogWrite(LPWMOutputRight, vol);
}

void goLeft_v2(int volL, int volR)
{
  if (volL >= 255)
    volL = 255;
  if (volR >= 255)
    volR = 255;
    analogWrite(RPWMOutputLeft, 0);
    analogWrite(LPWMOutputLeft, volL);
    
    analogWrite(RPWMOutputRight, 0);
    analogWrite(LPWMOutputRight, volR);
}

void goUpRight(int vol)
{
    if (vol >= 255)
    vol = 255;
    analogWrite(RPWMOutputRight, vol);
    analogWrite(LPWMOutputRight, 0);
}

void goDownLeft(int vol)
{
    if (vol >= 255)
    vol = 255;
    analogWrite(RPWMOutputRight, 0);
    analogWrite(LPWMOutputRight, vol);
}

void goUpLeft(int vol)
{
    if (vol >= 255)
    vol = 255;
    analogWrite(RPWMOutputLeft, 0);
    analogWrite(LPWMOutputLeft, vol);
}

void goDownRight(int vol)
{
    if (vol >= 255)
    vol = 255;
    analogWrite(RPWMOutputLeft, vol);
    analogWrite(LPWMOutputLeft, 0);
}

void doStop()
{
    analogWrite(RPWMOutputLeft, 0);
    analogWrite(LPWMOutputLeft, 0);
    
    analogWrite(RPWMOutputRight, 0);
    analogWrite(LPWMOutputRight, 0);
}
