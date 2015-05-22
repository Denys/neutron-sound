void FASTRUN outUpdateISR_PULSAR(void){
  
 
 
  
  oSQ.phase = oSQ.phase +  (uint32_t)oSQ.phase_increment; //square wave osc
  digitalWriteFast (oSQout,(oSQ.phase < oSQ.PW)); //pulse out   

  
   switch(oscMode){
     
      //-----------------------------------------------FM MODE OSCILLATORS-----------------------------------------------
  case 0:
      
    o1.phase = o1.phase + o1.phase_increment; 
     
    noiseTable[o1.phase>>23]= random(-32767,32767); //replace noise cells with random values.
    if (o1.phaseOld > o1.phase)o2.phase = o3.phase = 0;//check for sync reset osc in CZ mode.        
    o1.phaseOld = o1.phase;  
        
    o2.phase = o2.phase +  o2.phase_increment; 
    o2.phaseRemain = (o2.phase<<9)>>17; //used for fake interpolation
    o1.phaseRemain = (o1.phase<<9)>>17;
      
      
    //-----------------------------------------------------------------------
   
    
    if (o3.phase < 2147483647) {o3.phase = o3.phase + o3.phase_increment + (CZMix<<14);
    o3.wave = (FMTable[o3.phase>>23]);    
    o3.nextwave =  (FMTable[(o3.phase+nextstep)>>23]);}
    else {
    o3.wave = 0;    
    o3.nextwave =  0;}
    o3.phaseRemain = (o3.phase<<9)>>17;  
        
   
    
    o2.wave = (((waveTableLink[o2.phase>>23]*mixHi)+(waveTable2Link[o2.phase>>23]*mixLo)+(waveTableMidLink[o2.phase>>23]*mixMid))>>4)>>11;
    o2.nextwave = (((waveTableLink[(o2.phase+nextstep)>>23]*mixHi)+(waveTable2Link[(o2.phase+nextstep)>>23]*mixLo)+(waveTableMidLink[(o2.phase+nextstep)>>23]*mixMid))>>4)>>11;
    
        
    o3.wave = o3.wave+((((o3.nextwave - o3.wave)) * o3.phaseRemain) >>15); 
    
    
    o2.wave = o2.wave +((((o2.nextwave - o2.wave))* o2.phaseRemain)>>15);
    //o4.wave = o4.wave +((((o4.nextwave - o4.wave))* o4.phaseRemain)>>15);
   

    
    o1.wave =   (o2.wave * o3.wave)>>11;  
  
  
    o3.wave = (((((o1.wave * o1.amp)>>8) * ((int)mixDetuneUp))>>14) + o1.wave)>>3; //main out and mix detune
    
    o4.wave = (o3.wave<<19)>>19;
      
   if (o3.wave > 0){
   if((((o3.wave)>>12)& 0x01) == 0) o4.wave = -o4.wave; } 
   else {
   if((((o3.wave)>>12)& 0x01) == 1) o4.wave = -o4.wave; }    
    
    analogWrite(aout2,o4.wave+4000);
    
      

  //  AGCtest = o1.wave >>13; 
   AGCtest = o1.wave;
   
   
   
   
   break;
   
   //-----------------------------------------------ALT FM MODE OSCILLATORS-----------------------------------------------
  case 2:
      
    o1.phase = o1.phase + o1.phase_increment; 
     
    noiseTable[o1.phase>>23]= random(-32767,32767); //replace noise cells with random values.
    if (o1.phaseOld > o1.phase)o2.phase = o3.phase = 0;//check for sync reset osc in CZ mode.        
    o1.phaseOld = o1.phase;  
        
    o2.phase = o2.phase +  o2.phase_increment; 
    o2.phaseRemain = (o2.phase<<9)>>17; //used for fake interpolation
    o1.phaseRemain = (o1.phase<<9)>>17;
      
      
    //-----------------------------------------------------------------------
   
    
    if (o3.phase < 2147483647) {o3.phase = o3.phase + o3.phase_increment + (CZMix<<14);
    o3.wave = (FMTable[o3.phase>>23]);    
    o3.nextwave =  (FMTable[(o3.phase+nextstep)>>23]);}
    else {
    o3.wave = 0;    
    o3.nextwave =  0;}
    
    o3.phaseRemain = (o3.phase<<9)>>17;  
        
   
    
    o2.wave = (((waveTable2Link[o2.phase>>23]*mixLo)+(waveTableMidLink[o2.phase>>23]*(mixMid+mixHi)))>>4)>>11;
    o2.nextwave = (((waveTable2Link[(o2.phase+nextstep)>>23]*mixLo)+(waveTableMidLink[(o2.phase+nextstep)>>23]*(mixMid+mixHi)))>>4)>>11;
    
        
    o3.wave = o3.wave+((((o3.nextwave - o3.wave)) * o3.phaseRemain) >>15); 
    
    
    o2.wave = o2.wave +((((o2.nextwave - o2.wave))* o2.phaseRemain)>>15);
    //o4.wave = o4.wave +((((o4.nextwave - o4.wave))* o4.phaseRemain)>>15);
   

    
    o1.wave =   (o2.wave * o3.wave)>>11;  
  
  
    o3.wave = (((((o1.wave * o1.amp)>>8) * ((int)mixDetuneUp))>>14) + o1.wave)>>3; //main out and mix detune
    
    o4.wave = (o3.wave<<19)>>19;
      
   if (o3.wave > 0){
   if((((o3.wave)>>12)& 0x01) == 0) o4.wave = -o4.wave; } 
   else {
   if((((o3.wave)>>12)& 0x01) == 1) o4.wave = -o4.wave; }    
    
    analogWrite(aout2,o4.wave+4000);
    
      

  //  AGCtest = o1.wave >>13; 
   AGCtest = o1.wave;
   
   
   
   
   break;
    
  //-----------------------------------------------CZ MODE OSCILLATORS-----------------------------------------------
  case 1:
      
    o1.phase = o1.phase + o1.phase_increment; 
     
    noiseTable[o1.phase>>23]= random(-32767,32767); //replace noise cells with random values.
    if (o1.phaseOld > o1.phase)o2.phase = o3.phase = 0;//check for sync reset osc in CZ mode.        
    o1.phaseOld = o1.phase;         
    o2.phase = o2.phase +  o2.phase_increment; 
    o2.phaseRemain = (o2.phase<<9)>>17; //used for fake interpolation
    o1.phaseRemain = (o1.phase<<9)>>17;
      
      
    //-----------------------------------------------------------------------
   
    if (o3.phase < 2147483647) {o3.phase = o3.phase + o3.phase_increment + (CZMix<<14);
    o3.wave = (FMTable[o3.phase>>23]);    
    o3.nextwave =  (FMTable[(o3.phase+nextstep)>>23]);}
    else {
    o3.wave = 0;    
    o3.nextwave =  0;}
    
    o3.phaseRemain = (o3.phase<<9)>>17;  
        
   
    
    o2.wave = (((waveTableLink[o2.phase>>23]*mixHi)+(waveTable2Link[o2.phase>>23]*mixLo)+(waveTableMidLink[o2.phase>>23]*mixMid))>>4)>>11;
    o2.nextwave = (((waveTableLink[(o2.phase+nextstep)>>23]*mixHi)+(waveTable2Link[(o2.phase+nextstep)>>23]*mixLo)+(waveTableMidLink[(o2.phase+nextstep)>>23]*mixMid))>>4)>>11;
    
        
    o3.wave = o3.wave+((((o3.nextwave - o3.wave)) * o3.phaseRemain) >>15); 
    
    
    o2.wave = o2.wave +((((o2.nextwave - o2.wave))* o2.phaseRemain)>>15);
    //o4.wave = o4.wave +((((o4.nextwave - o4.wave))* o4.phaseRemain)>>15);
   

    
    o1.wave =   (o2.wave * o3.wave)>>11;  
  
  
    o3.wave = (((((o1.wave * o1.amp)>>8) * ((int)mixDetuneUp))>>14) + o1.wave)>>3; //main out and mix detune
    
    o4.wave = (o3.wave<<19)>>19;
      
   if (o3.wave > 0){
   if((((o3.wave)>>12)& 0x01) == 0) o4.wave = -o4.wave; } 
   else {
   if((((o3.wave)>>12)& 0x01) == 1) o4.wave = -o4.wave; }    
    
    analogWrite(aout2,o4.wave+4000);
    
      

  //  AGCtest = o1.wave >>13; 
   AGCtest = o1.wave;
   
   
   break; 

//-----------------------------------------------ALT FM MODE OSCILLATORS-----------------------------------------------
  case 3:
  
     lfo.phase = lfo.phase + lfo.phase_increment;
    lfo.wave = FMTableAMX[lfo.phase>>23];    
    
    o1.phaseOffset = (FMX_HiOffset * lfo.wave);  
    o1.phase = o1.phase + o1.phase_increment + o1.phaseOffset; 
     
    noiseTable[o1.phase>>23]= random(-32767,32767); //replace noise cells with random values.
    if (o1.phaseOld > o1.phase)o2.phase = o3.phase = 0;//check for sync reset osc in CZ mode.        
    o1.phaseOld = o1.phase;  
        
    o2.phase = o2.phase +  o2.phase_increment; 
    o2.phaseRemain = (o2.phase<<9)>>17; //used for fake interpolation
    o1.phaseRemain = (o1.phase<<9)>>17;
     
      
    //-----------------------------------------------------------------------
   
    
    if (o3.phase < 2147483647) {o3.phase = o3.phase + o3.phase_increment + (CZMix<<14);
    o3.wave = (FMTable[o3.phase>>23]);    
    o3.nextwave =  (FMTable[(o3.phase+nextstep)>>23]);}
    else {
    o3.wave = 0;    
    o3.nextwave =  0;}
    
    o3.phaseRemain = (o3.phase<<9)>>17;   
        
   
    
    o2.wave = (((waveTable2Link[o2.phase>>23]*mixLo)+(waveTableMidLink[o2.phase>>23]*(mixMid+mixHi)))>>4)>>11;
    o2.nextwave = (((waveTable2Link[(o2.phase+nextstep)>>23]*mixLo)+(waveTableMidLink[(o2.phase+nextstep)>>23]*(mixMid+mixHi)))>>4)>>11;
    
        
    o3.wave = o3.wave+((((o3.nextwave - o3.wave)) * o3.phaseRemain) >>15); 
    
    
    o2.wave = o2.wave +((((o2.nextwave - o2.wave))* o2.phaseRemain)>>15);
    //o4.wave = o4.wave +((((o4.nextwave - o4.wave))* o4.phaseRemain)>>15);
   

    
    o1.wave =   (o2.wave * o3.wave)>>11;  
  
  
    o3.wave = (((((o1.wave * o1.amp)>>8) * ((int)mixDetuneUp))>>14) + o1.wave)>>3; //main out and mix detune
    
    o4.wave = (o3.wave<<19)>>19;
      
   if (o3.wave > 0){
   if((((o3.wave)>>12)& 0x01) == 0) o4.wave = -o4.wave; } 
   else {
   if((((o3.wave)>>12)& 0x01) == 1) o4.wave = -o4.wave; }    
    
    analogWrite(aout2,o4.wave+4000);
    
      

  //  AGCtest = o1.wave >>13; 
   AGCtest = o1.wave;
   
   
   
   
   break;   
    
   }
}



