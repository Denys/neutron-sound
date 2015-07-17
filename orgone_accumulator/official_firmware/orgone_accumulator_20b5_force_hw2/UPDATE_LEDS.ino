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
    if (IsHW2 == 0){
  switch (ARC+1) {
    case 1:
    analogWrite(LED_Lo,(bitRead(FXi,0)*8000));
    break;
    case 2:
    analogWrite(LED_Mid,(bitRead(FXi,1)*8000));
    break;
    case 3:
    analogWrite(LED_Hi,(bitRead(FXi,2)*8000));
    break;
  
  }}}}
  
 
void UPDATE_prog_LEDS(){ 
  if (LED_MCD > 0){
 switch (ARC+1) {
    case 4:
    digitalWriteFast(SEL_LED_ARRAY[0],LOW);
    digitalWriteFast(SEL_LED_ARRAY[1],LOW);
    digitalWriteFast(SEL_LED_ARRAY[2],HIGH);//this LED is inverted because pin33 can not be grounded on boot.
    digitalWriteFast(SEL_LED_ARRAY[3],LOW);
    digitalWriteFast(SEL_LED_ARRAY[4],LOW);
    digitalWriteFast(SEL_LED_ARRAY[5],LOW);
    digitalWriteFast(SEL_LED_ARRAY[6],LOW);
    digitalWriteFast(SEL_LED_ARRAY[7],LOW);
    break;
    case 5:
    if (FXi == 2) digitalWriteFast(SEL_LED_ARRAY[FXi],LOW); 
 else   digitalWriteFast(SEL_LED_ARRAY[FXi],HIGH); 
    break;
    
}}

else{
switch (ARC +1) {
    case 1:
    digitalWriteFast(LED_TuneLock,tuneLockOn);
    break;
    case 2:
    digitalWriteFast(LED_LoSel,detuneLoOn);
    break;
    case 3:
     digitalWriteFast(LED_MidSel,!detuneMidOn);
    break;
    case 4:
    digitalWriteFast(LED_HiSel,detuneHiOn);
    break;
    case 5:
    digitalWriteFast(LED_FixSel,FMFixedOn);
    break;
    case 6:
    digitalWriteFast(LED_CZSel,CZmodeOn);
    break;
    case 7:
    digitalWriteFast(LED_xSel,xModeOn);
    break;
    case 8:
    digitalWriteFast(LED_FXSelDn,LOW);
    break;
    case 9:
    digitalWriteFast(LED_FXSelUp,LOW);
    break;

}
  } 
} 


