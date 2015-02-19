void DODETUNING(){

  aInModDetuneCubing = max((aInModDetune+detuneAmountCont),0)/64.0;
  aInModDetune = ((aInModDetuneCubing*aInModDetuneCubing*aInModDetuneCubing)/8.0);
  //switches between prime and even spaced detune modes.  
  if (primeDetuneOn){   //Detune does not follow pitch 
    detuneScaler = aInModDetune * mixDetune ;
    for (int i=0; i <= 3; i++){  
      detune[i] = (uint32_t)((detuneScaler/300000.0) * primes[i]);
    }
  }
  else{  //detune follows pitch, detune up to "hoover"
    detuneScaler = aInModDetune;
    detune[1] = detune[3]=(uint32_t)((detuneScaler/32768.0)*(inputConverter));
    detune[2] = detune[0]=(uint32_t)((detuneScaler/16384.0)*(inputConverter)) ;     
  }
}









