void SELECT_ISRS()
{
 buh = digitalReadFast(tuneLockSwitch);
    if (tuneLockOn != buh){
      tuneLockOn = buh;
      digitalWriteFast(LED_TuneLock,tuneLockOn);
      if (FX == 1) {
        if (tuneLockOn == 1) { 
          outUpdateTimer.end();
          outUpdateTimer.begin(outUpdateISR_CRUSH,ISRrate);
        }     
        else {
          outUpdateTimer.end();
          outUpdateTimer.begin(outUpdateISR_MAIN,ISRrate);     
        }
      }
    }     
}
