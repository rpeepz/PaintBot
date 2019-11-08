///////////////////////////////////////////////////////////////// SPRAY ///////////////////////////////////////////////////////
void spray() {

//    EEPROM.write(sprayStatusCacheAddr, 1);  
    analogWrite(ZMOTOR_A_Output, 0);
    analogWrite(ZMOTOR_B_Output, SRPAY_MAX_VOLTAGE);
    
    delay(spraySwitchDistance);
    
    analogWrite(ZMOTOR_A_Output, 0);
    analogWrite(ZMOTOR_B_Output, 0);
}

int stopSpraying() {

//    EEPROM.write(sprayStatusCacheAddr, 0);  
    analogWrite(ZMOTOR_A_Output, SRPAY_MAX_VOLTAGE);
    analogWrite(ZMOTOR_B_Output, 0);

    delay(spraySwitchDistance * 0.8);

    analogWrite(ZMOTOR_A_Output, 0);
    analogWrite(ZMOTOR_B_Output, 0);

    return (1);
}
