void DODETUNING(){
  

pcounter = micros() - pcounterOld;
pcounterOld = micros();

 

  aInModDetuneCubing = max((aInModDetune+detuneAmountCont),0)/64.0;
  aInModDetune = ((aInModDetuneCubing*aInModDetuneCubing*aInModDetuneCubing)/8.0);  
  //switches between prime and even spaced detune modes. 


  switch (FX){//select middle wavetable
  case 0: //symetrical detune
    detuneScaler = aInModDetune;
    detune[1] = detune[2]=(uint32_t)((detuneScaler/32768.0)*(inputConverter));
    detune[3] = detune[0]=(uint32_t)((detuneScaler/16384.0)*(inputConverter)) ;
    break;


  case 1: //prime detune
    detuneScaler = aInModDetune * mixDetune ;
    for (int i=0; i <= 3; i++){  
      detune[i] = (uint32_t)((detuneScaler * primes[i])/3000000.0) ;
    }
    break;

  case 2: //delay
    GRADUALWAVE();  
    delayTime = constrain(((averageaInRAv-4065)+averageratio),1,8190);//For Feedback altFX ratio knob
    delayFeedback = (constrain(((analogControls[2]>>2)+(2047-(aInDetuneReading>>1))),0,2047));//detune become feedback  
    break;
  case 3: //pulsar with folding
    GRADUALWAVE();
    o1.amp = (constrain(((4095 - aInDetuneReading)+(analogControls[2])),0,8190));
    detune[3]=(uint32_t)((detuneScaler/32768.0)*(inputConverter));      
    break;
  case 4: //crush
    CRUSHBITS = ((constrain(((4095 - aInDetuneReading)+(analogControls[2])),0,8190))>>10)+9;//
    CRUSH_Remain = (uint32_t)(((constrain((((uint32_t)(4095 - aInDetuneReading))+(analogControls[2])),0,8190))<<22)>>22); //remainder used for mix
    GRADUALWAVE();    
    break;
  case 5: //wave folding
    o1.amp = (constrain(((4095 - aInDetuneReading)+(analogControls[2])),0,8190));
    GRADUALWAVE();
    break;
  case 6: //modmod
    //o1.amp = (constrain((((4095 - aInDetuneReading)*mixDetune)>>13),0,8190));
    GRADUALWAVE_M();
    break;
  case 7: 
   
    break;
    case 10: //self mod
    o1.amp = (constrain(((4095 - aInDetuneReading)+(analogControls[2])),0,8190));
    GRADUALWAVE();
    break;
    case 11: //drum voice 
 detuneScaler = aInModDetune;   
    detune[0] =(uint32_t)((detuneScaler/32768.0)*(inputConverter));
    detune[1] =(uint32_t)((detuneScaler/16384.0)*(inputConverter));
    detune[2] =(uint32_t)((detuneScaler/8192.0)*(inputConverter));
    detune[3] =(uint32_t)((detuneScaler/4096.0)*(inputConverter));
    
    o1.amp = (constrain(((4095 - aInDetuneReading)+(analogControls[2])),0,8190));
    
    break;
  
}}










