void DODETUNING(){

    
  aInModDetuneCubing = max((aInModDetune+detuneAmountCont),0)/64.0;
  aInModDetune = ((aInModDetuneCubing*aInModDetuneCubing*aInModDetuneCubing)/8.0);  
  //switches between prime and even spaced detune modes. 
 
 
 switch (FX){//select middle wavetable
    case 0: 
      detuneScaler = aInModDetune;
    detune[1] = detune[3]=(uint32_t)((detuneScaler/32768.0)*(inputConverter));
    detune[2] = detune[0]=(uint32_t)((detuneScaler/16384.0)*(inputConverter)) ;
      break;
    case 1: 
      detuneScaler = aInModDetune * mixDetune ;
    for (int i=0; i <= 3; i++){  
      detune[i] = (uint32_t)((detuneScaler * primes[i])/3000000.0) ;
    }
      break;
    case 2: 
       delayTime = analogControls[0];//For Feedback altFX ratio knob
  delayFeedback = (constrain(((analogControls[2]>>2)+(2047-(aInDetuneReading>>1))),0,2047));//detune become feedback  
      break;
    case 3: 
      
      break;
    case 4: 
      CRUSHBITS = int(constrain((aInModDetune+detuneAmountCont),0,8191)/1365)+7;//for bitcrush altFX
      break;
  
  
}}









