void UPDATE_LEDS(){

  if (LED_MCD == 0)  {
  switch (ARC+1) {
    case 1:
    analogWrite(LED_Lo,(mixLo<<2)-conf_LED_comp);
    break;
    case 2:
    analogWrite(LED_Mid,(mixMid<<2)-conf_LED_comp);
    break;
    case 3:
    analogWrite(LED_Hi,(mixHi<<2)-conf_LED_comp);
    break;
    //case 4:
    //analogWrite(LED_PWM,min(8191,((oSQ.PW>>19)+LED_comp)));
    //break;
  }}
  
  else{
  switch (ARC+1) {
    case 1:
    analogWrite(LED_Lo,(bitRead(FX,0)*8000));
    break;
    case 2:
    analogWrite(LED_Mid,(bitRead(FX,1)*8000));
    break;
    case 3:
    analogWrite(LED_Hi,(bitRead(FX,2)*8000));
    break;
  
  }}
}
