void TUNELOCK_TOGGLE()
{
 buh = digitalReadFast(tuneLockSwitch);
    if (tuneLockOn != buh){
      tuneLockOn = buh;
      digitalWriteFast(LED_TuneLock,tuneLockOn);}}


void SELECT_ISRS(){

     LED_MCD = LED_MST;    
  
      switch (FX){//select middle wavetable
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
      
}}
