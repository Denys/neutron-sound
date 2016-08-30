void UPDATE_LEDS(){

  
    analogWrite(LED_Lo,LEDToggle*8000);
    
    analogWrite(LED_Mid,LEDToggle*8000);
    
    analogWrite(LED_Hi,LEDToggle*8000);
    
    digitalWriteFast(LED_TuneLock,LEDToggle);
    
  
}
