void FASTRUN outUpdateISR_MODMOD(void){
 //noInterrupts();  

 //digitalWriteFast (oSQout,0);//temp testing OC
 
  
  oSQ.phase = oSQ.phase +  (uint32_t)oSQ.phase_increment; //square wave osc
  digitalWriteFast (oSQout,(oSQ.phase < oSQ.PW)); //pulse out 
  
  

  switch(oscMode){
    
  //-----------------------------------------------FM MODE OSCILLATORS-----------------------------------------------
  case 0:
  
   noiseTable3[0]=noiseTable3[1]=(noiseTable3[0]+NT3Rate);
    noiseTable[o1.phase>>23]= random(-32767,32767); //replace noise cells with random values.  

    //main oscillator
    o1.phase = o1.phase + o1.phase_increment; 
    o1.phaseRemain = (o1.phase<<9)>>17; 
    
    //mix mod waves with FX controls
   
    o1.wave = ((int32_t)(FMTable[o1.phase>>WTShift]*(2047-o1.amp))>>11) +  ((int32_t)(FMTableMM[o1.phase>>WTShift]*(o1.amp))>>11)  ;
   o1.nextwave =  ((int32_t)(FMTable[(o1.phase+nextstep)>>WTShift]*(2047-o1.amp))>>11)    +     ((int32_t)(FMTableMM[(o1.phase+nextstep)>>WTShift]*(o1.amp))>>11);
//    
    
    o1.wave = o1.wave+((((o1.nextwave - o1.wave)) * o1.phaseRemain) >>15);    
    o1.index = (FMIndex * o1.wave);   
    o2.phase = o2.phase +  (o2.phase_increment+o1.index);
    o2.phaseRemain = (o2.phase<<9)>>17;    
  
    o2.wave = (((waveTableLink[o2.phase>>23]*mixHi)+(waveTable2Link[o2.phase>>23]*mixLo)+(waveTableMidLink[o2.phase>>23]*mixMid)))>>11;
    
    o2.nextwave = (((waveTableLink[(o2.phase + nextstep)>>23]*mixHi)+(waveTable2Link[(o2.phase + nextstep)>>23]*mixLo)+(waveTableMidLink[(o2.phase + nextstep)>>23]*mixMid)))>>11;
    
    o2.wave = o2.wave+((((o2.nextwave - o2.wave)) * o2.phaseRemain) >>15); 
    
    AGCtest = o2.wave>>3; //main out and mix detune
    
    analogWrite(aout2,AGCtest+4000);
    
    
    break;  
    
    //-----------------------------------------------ALT FM MODE OSCILLATORS-----------------------------------------------
  case 2:
  
  
noiseTable3[0]=noiseTable3[1]=(noiseTable3[0]+NT3Rate);
    noiseTable[o1.phase>>23]= random(-32767,32767); //replace noise cells with random values.  

    //main oscillator
    o1.phase = o1.phase + o1.phase_increment; 
    o1.phaseRemain = (o1.phase<<9)>>17; 
    
    //mix mod waves with FX controls
   
    o1.wave = ((int32_t)(FMTable[o1.phase>>WTShift]*(2047-mixDetune))>>11) +  ((int32_t)(FMTableMM[o1.phase>>WTShift]*(mixDetune))>>11)  ;
   o1.nextwave =  ((int32_t)(FMTable[(o1.phase+nextstep)>>WTShift]*(2047-mixDetune))>>11)    +     ((int32_t)(FMTableMM[(o1.phase+nextstep)>>WTShift]*(mixDetune))>>11);
//    
    
    o1.wave = o1.wave+((((o1.nextwave - o1.wave)) * o1.phaseRemain) >>15);    
    o1.index = (FMIndex * o1.wave);   
    o2.phase = o2.phase +  (o2.phase_increment+o1.index);
    o2.phaseRemain = (o2.phase<<9)>>17;  
      

    o2.wave = (((waveTable2Link[o2.phase>>23]*mixLo)+(waveTableMidLink[o2.phase>>23]*(mixMid+mixHi))))>>11;
     
  
    o2.nextwave = (((waveTable2Link[(o2.phase + nextstep)>>23]*mixLo)+(waveTableMidLink[(o2.phase + nextstep)>>23]*(mixMid+mixHi))))>>11;
    
    o2.wave = o2.wave+((((o2.nextwave - o2.wave)) * o2.phaseRemain) >>15); 
    

    AGCtest = o2.wave>>3; //main out and mix detune
            
    analogWrite(aout2,AGCtest+4000);     
   
        
    break;  
     
    
  case 1://-------------------------------------------CZ MODE OSCILLATORS-----------------------------------------------

    
    o1.phase = o1.phase + o1.phase_increment; 
    noiseTable[o1.phase>>23]= random(-32767,32767); //replace noise cells with random values.
    if (o1.phaseOld > o1.phase)o2.phase = 0; //check for sync reset osc in CZ mode.        
    o1.phaseOld = o1.phase;       
    o2.phase = o2.phase +  o2.phase_increment; 
    o2.phaseRemain = (o2.phase<<9)>>17; //used for fake interpolation
    o1.phaseRemain = (o1.phase<<9)>>17;    
   
   
    o2.wave = FMTable[o2.phase>>WTShift];
   o2.nextwave =  FMTable[(o2.phase+nextstep)>>WTShift];
//    
    
    o1.wave = (int32_t)(((waveTableLink[o1.phase>>23]*mixHi)+(waveTable2Link[o1.phase>>23]*mixLo)+(waveTableMidLink[o1.phase>>23]*mixMid))>>14);    
    o1.nextwave = (int32_t)(((waveTableLink[(o1.phase+nextstep)>>23]*mixHi)+(waveTable2Link[(o1.phase+nextstep)>>23]*mixLo)+(waveTableMidLink[(o1.phase+nextstep)>>23]*mixMid))>>14);
   
    o3.wave = (int32_t)(FMTableMM[o1.phase>>23])>>3;
    o3.nextwave = (int32_t)(FMTableMM[(o1.phase+nextstep)>>23])>>3;
    
        
    o1.wave = o1.wave+((((o1.nextwave - o1.wave)) * o1.phaseRemain) >>15);    
    o2.wave = o2.wave +((((o2.nextwave - o2.wave))* o2.phaseRemain)>>15);
    o3.wave = o3.wave +((((o3.nextwave - o3.wave))* o1.phaseRemain)>>15);
    
    o1.wave = ((o1.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o1.wave) * ((o2.wave*CZMix)>>11))>>15)); 
    o3.wave = ((o3.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o3.wave) * ((o2.wave*CZMix)>>11))>>15)); 
    
    mixDetuneUpTMp = (int32_t)(mixDetuneUp * (8191 - aInDetuneReading))>>12;
    mixDetuneDnTMp = 2047 - mixDetuneUpTMp;
    
    o1.wave = ((o3.wave * ((int)mixDetuneUpTMp))>>11)  +  (((o1.wave *((int)mixDetuneDnTMp))>>11));
    
    analogWrite(aout2,o1.wave+4000);
  
  
  break;
  
 
  
    //----------------------------------------------ALT CZ mode-----------------------------------------
    case 3: 

   lfo.phase = lfo.phase + lfo.phase_increment;
    lfo.wave = FMTableAMX[lfo.phase>>23];    
    
    o1.phaseOffset = (FMX_HiOffset * lfo.wave);
    o1.phase = o1.phase + (o1.phase_increment + o1.phaseOffset); 
    noiseTable[o1.phase>>23]= random(-32767,32767); //replace noise cells with random values.
    if (o1.phaseOld > o1.phase)o2.phase = 0; //check for sync reset osc in CZ mode.        
    o1.phaseOld = o1.phase;       
    o2.phase = o2.phase +  o2.phase_increment; 
    o2.phaseRemain = (o2.phase<<9)>>17; //used for fake interpolation
    o1.phaseRemain = (o1.phase<<9)>>17;
    
    
    o2.wave = ((int32_t)(FMTable[o2.phase>>WTShift]*(2047-mixDetune))>>11) +  ((int32_t)(FMTableMM[o2.phase>>WTShift]*(mixDetune))>>11)  ;
   o2.nextwave =  ((int32_t)(FMTable[(o2.phase+nextstep)>>WTShift]*(2047-mixDetune))>>11)    +     ((int32_t)(FMTableMM[(o2.phase+nextstep)>>WTShift]*(mixDetune))>>11);
    
    o1.wave = (((waveTable2Link[o1.phase>>23]*mixLo)+(waveTableMidLink[o1.phase>>23]*(mixMid+mixHi)))>>4)>>10;
    o1.nextwave = (((waveTable2Link[(o1.phase+nextstep)>>23]*mixLo)+(waveTableMidLink[(o1.phase+nextstep)>>23]*(mixMid+mixHi)))>>4)>>10;
    
    
        
    o1.wave = o1.wave+((((o1.nextwave - o1.wave)) * o1.phaseRemain) >>15);     
    o2.wave = o2.wave +((((o2.nextwave - o2.wave))* o2.phaseRemain)>>15);   

    
    o1.wave = ((o1.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o1.wave) * ((o2.wave*CZMix)>>11))>>15));    
   

  //  AGCtest = o1.wave >>13; 
   AGCtest = ((((o9.wave+o7.wave+o5.wave+o3.wave+o1.wave)>>2)*((int)mixDetuneUp))>>10)  +  (((o1.wave *((int)mixDetuneDn))>>10)); //main out and mix detune
      
    
    analogWrite(aout2,AGCtest+4000);
  
    break;   
  
  }
   
 //digitalWriteFast (oSQout,1);//temp testing OC 
}



