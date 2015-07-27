void WRITE2EEPROM(){
EEPROM.write(0, FXi);
EEPROM.write(1,detuneLoOn);
EEPROM.write(2,detuneMidOn);
EEPROM.write(3,detuneHiOn);
EEPROM.write(4,xModeOn);
EEPROM.write(5,CZmodeOn);
EEPROM.write(6,FMFixedOn);

}

void READ_POTS(){
   
if (IsHW2 == 0){ 
analogControls[ARC] = analogRead(potPinTable_DIY[ARC]);}//step through control knob readings one per cycle, humans are slow
else
{analogControls[ARC] = analogRead(potPinTable_ret[ARC]);}
}


void TUNELOCK_TOGGLE()
{
 if (IsHW2 == 0){ 
 buh = digitalReadFast(tuneLockSwitch);
    if (tuneLockOn != buh){
      tuneLockOn = buh;
      
      digitalWriteFast(LED_TuneLock,tuneLockOn);}}
      
 else{
   if (tuneLockButton.update()) {
   if (tuneLockButton.fallingEdge()){
     tuneLockOn = !tuneLockOn;
     
     }}     
 }   
    
  }
  
void FX_TOGGLES(){
if (IsHW2 == 0){
    detuneLoOn = digitalReadFast(detuneLoSwitch); 
    detuneMidOn = !digitalReadFast(detuneMidSwitch); 
    detuneHiOn = !digitalReadFast(detuneHiSwitch); }
else {

 if (detuneLoButton.update()) {
   if (detuneLoButton.fallingEdge()){     
     detuneLoOn = !detuneLoOn;
   
   }}     
     
 if (detuneMidButton.update()) {
   if (detuneMidButton.fallingEdge()){     
     detuneMidOn = !detuneMidOn;
  
   }}
 
 if (detuneHiButton.update()) {
   if (detuneHiButton.fallingEdge()){     
     detuneHiOn = !detuneHiOn;
   
   }}
   
 }
}

void OSC_MODE_TOGGLES(){
  if (IsHW2 == 0){
  FMFixedOn = digitalReadFast(FMFixedSwitch);
  oscMode = (!digitalReadFast(xModeSwitch)<<1)+ digitalReadFast(CZmodeSwitch);   
}

else{
  if (FMFixedButton.update()) {
   if (FMFixedButton.fallingEdge()){
     FMFixedOn = !FMFixedOn;
    
   }}
     
      if (CZmodeButton.update()) {
   if (CZmodeButton.fallingEdge()){
     CZmodeOn = !CZmodeOn;
   
  }}
     
      if (xModeButton.update()) {
   if (xModeButton.fallingEdge()){
     xModeOn = !xModeOn;
   
  }} 
     
     oscMode = ((xModeOn)<<1)+(!CZmodeOn);


}
}


void SELECT_ISRS(){

     LED_MCD = LED_MST;    
  
      switch (FX){
    case 0: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_MAIN,ISRrate);
      primeDetuneOn = 0;  
      break;
    case 1: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_MAIN,ISRrate); 
      primeDetuneOn =1; 
      break;
    case 2: 
       outUpdateTimer.end();
       outUpdateTimer.begin(outUpdateISR_DEL,ISRrate);
      break;
    case 3: 
      outUpdateTimer.end();
      o1.phase =        
      o2.phase =      
      o3.phase =     
      o4.phase =       
      o5.phase =       
      o6.phase =     
      o7.phase =       
      o8.phase =       
      o9.phase = 
      lfo.phase =      
      o10.phase = 0;
      outUpdateTimer.begin(outUpdateISR_PULSAR,ISRrate);
      break;
    case 4: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_CRUSH,ISRrate); 
      break;
      case 5: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_FOLD,ISRrate); 
      break; 
      case 6: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_MODMOD,ISRrate); 
      break; 
      case 7: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_CHORD,ISRrate); 
      break; 
      case 8: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_CHORD,ISRrate); 
      break; 
      case 9: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_ADT,ISRrate); 
      break; 
       case 10: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_SELF,ISRrate); 
      break; 
      case 11: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_DRUM,ISRrate); 
      break; 
      case 12: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_XOR,ISRrate); 
      break; 
      
}}

void GRADUALWAVE(){
  switch(oscMode){
  case 0:  
  GWTlo1 = FMWTselLo[analogControls[8]>>9]; //select "from" wave
  GWTlo2 = FMWTselLo[(((analogControls[8]>>9)+1)<<27)>>27]; //select "to" wave and modulo 16
  GremLo = (uint32_t)((uint32_t)((analogControls[8]<<23))>>23); //get remainder for mix amount
  
  GWTmid1 = FMWTselMid[analogControls[5]>>9];
  GWTmid2 = FMWTselMid[(((analogControls[5]>>9)+1)<<27)>>27];
  GremMid = (uint32_t)((uint32_t)((analogControls[5]<<23))>>23);
  
  GWThi1 = FMWTselHi[analogControls[4]>>9];
  GWThi2 = FMWTselHi[(((analogControls[4]>>9)+1)<<27)>>27];
  GremHi = (uint32_t)((uint32_t)((analogControls[4]<<23))>>23);
  
  break;
  case 2:  
  GWTlo1 = FMAltWTselLo[analogControls[8]>>9];
  GWTlo2 = FMAltWTselLo[(((analogControls[8]>>9)+1)<<27)>>27];
  GremLo = (uint32_t)((uint32_t)((analogControls[8]<<23))>>23);
  
  GWTmid1 = FMAltWTselMid[analogControls[5]>>9];
  GWTmid2 = FMAltWTselMid[(((analogControls[5]>>9)+1)<<27)>>27];
  GremMid = (uint32_t)((uint32_t)((analogControls[5]<<23))>>23); 
  break;
  
  case 1:  
  GWTlo1 = CZWTselLo[analogControls[8]>>9];
  GWTlo2 = CZWTselLo[(((analogControls[8]>>9)+1)<<27)>>27];
  GremLo = (uint32_t)((uint32_t)((analogControls[8]<<23))>>23);
  
  GWTmid1 = CZWTselMid[analogControls[5]>>9];
  GWTmid2 = CZWTselMid[(((analogControls[5]>>9)+1)<<27)>>27]; 
  GremMid = (uint32_t)((uint32_t)((analogControls[5]<<23))>>23);
  
  GWThi1 = CZWTselHi[analogControls[4]>>9];
  GWThi2 = CZWTselHi[(((analogControls[4]>>9)+1)<<27)>>27];
  GremHi = (uint32_t)((uint32_t)((analogControls[4]<<23))>>23);
  
  break;
   case 3:  
  GWTlo1 = CZAltWTselLo[analogControls[8]>>9];
  GWTlo2 = CZAltWTselLo[(((analogControls[8]>>9)+1)<<27)>>27];
  GremLo = (uint32_t)((uint32_t)((analogControls[8]<<23))>>23);
  
  GWTmid1 = CZAltWTselMid[analogControls[5]>>9];
  GWTmid2 = CZAltWTselMid[(((analogControls[5]>>9)+1)<<27)>>27];
  GremMid = (uint32_t)((uint32_t)((analogControls[5]<<23))>>23);
  
 
  
  break;
  }
}

void GRADUALWAVE_M(){ //same as above but wavetable is modulated by effects cv. effect control is range for CV.

  uint32_t loWM = analogControls[8] + (detuneLoOn *(((4095 - aInDetuneReading)*analogControls[2])>>13));
  uint32_t loWM15 = (((loWM>>9)<<28)>>28);
  uint32_t loWM16 = (((loWM15 + 1)<<28)>>28);
  uint32_t midWM = analogControls[5] + (detuneMidOn *(((4095 - aInDetuneReading)*analogControls[2])>>13));
  uint32_t midWM15 = (((midWM>>9)<<28)>>28);
  uint32_t midWM16 = (((midWM15 + 1)<<28)>>28);
  uint32_t hiWM = analogControls[4] + (detuneHiOn *(((4095 - aInDetuneReading)*analogControls[2])>>13));
  uint32_t hiWM15 = (((hiWM>>9)<<28)>>28);
  uint32_t hiWM16 = (((hiWM15 + 1)<<28)>>28);
  switch(oscMode){
  case 0:  
  GWTlo1 = FMWTselLo[loWM15];
  GWTlo2 = FMWTselLo[loWM16]; 
  GremLo = (uint32_t)((uint32_t)((loWM<<23))>>23); //get remainder for mix amount
  
  GWTmid1 = FMWTselMid[midWM15];
  GWTmid2 = FMWTselMid[midWM16];
  GremMid = (uint32_t)((uint32_t)((midWM<<23))>>23);
  
  GWThi1 = FMWTselHi[hiWM15];
  GWThi2 = FMWTselHi[hiWM16];
  GremHi = (uint32_t)((uint32_t)((hiWM<<23))>>23);
  
  break;
  case 2:  
  GWTlo1 = FMAltWTselLo[loWM15];
  GWTlo2 = FMAltWTselLo[loWM16];
  GremLo = (uint32_t)((uint32_t)((loWM<<23))>>23);
  
  GWTmid1 = FMAltWTselMid[midWM15];
  GWTmid2 = FMAltWTselMid[midWM16];
  GremMid = (uint32_t)((uint32_t)((midWM<<23))>>23); 
  break;
  
  case 1:  
  GWTlo1 = CZWTselLo[loWM15];
  GWTlo2 = CZWTselLo[loWM16];
  GremLo = (uint32_t)((uint32_t)((loWM<<23))>>23);
  
  GWTmid1 = CZWTselMid[midWM15];
  GWTmid2 = CZWTselMid[midWM16]; 
  GremMid = (uint32_t)((uint32_t)((midWM<<23))>>23);
  
  GWThi1 = CZWTselHi[hiWM15];
  GWThi2 = CZWTselHi[hiWM16];
  GremHi = (uint32_t)((uint32_t)((hiWM<<23))>>23);
  
  break;
   case 3:  
  GWTlo1 = CZAltWTselLo[loWM15];
  GWTlo2 = CZAltWTselLo[loWM16];
  GremLo = (uint32_t)((uint32_t)((loWM<<23))>>23);
  
  GWTmid1 = CZAltWTselMid[midWM15];
  GWTmid2 = CZAltWTselMid[midWM16];
  GremMid = (uint32_t)((uint32_t)((midWM<<23))>>23);
  
 
  
  break;
  }
//zorro  Serial.println(loWM15);
}




