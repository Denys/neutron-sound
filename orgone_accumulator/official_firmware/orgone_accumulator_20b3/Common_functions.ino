void TUNELOCK_TOGGLE()
{
 buh = digitalReadFast(tuneLockSwitch);
    if (tuneLockOn != buh){
      tuneLockOn = buh;
      LED_MCD = LED_MST;
      digitalWriteFast(LED_TuneLock,tuneLockOn);}}


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
      
}}
