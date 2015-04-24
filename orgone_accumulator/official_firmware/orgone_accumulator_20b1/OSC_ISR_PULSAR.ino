void FASTRUN outUpdateISR_PULSAR(void){
  
  //no FM or X modes yet
 
  
  oSQ.phase = oSQ.phase +  (uint32_t)oSQ.phase_increment; //square wave osc
  digitalWriteFast (oSQout,(oSQ.phase < oSQ.PW)); //pulse out   

      
    o1.phase = o1.phase + o1.phase_increment; 
     
    noiseTable[o1.phase>>23]= random(-32767,32767); //replace noise cells with random values.
    if (o1.phaseOld > o1.phase)o2.phase = o3.phase = 0;//check for sync reset osc in CZ mode.        
    o1.phaseOld = o1.phase;  
    if (o3.phase < 2147483647) {o3.phase = o3.phase + o3.phase_increment + (CZMix<<14);}    
    o2.phase = o2.phase +  o2.phase_increment; 
    o2.phaseRemain = (o2.phase<<9)>>17; //used for fake interpolation
    o1.phaseRemain = (o1.phase<<9)>>17;
    o3.phaseRemain = (o3.phase<<9)>>17;    
      
    //-----------------------------------------------------------------------
   
    
    o3.wave = (FMTable[o3.phase>>23]);    
    o3.nextwave =  (FMTable[(o3.phase+nextstep)>>23]);
        
   
    
    o2.wave = (((waveTableLink[o2.phase>>23]*mixHi)+(waveTable2Link[o2.phase>>23]*mixLo)+(waveTableMidLink[o2.phase>>23]*mixMid))>>4)>>11;
    o2.nextwave = (((waveTableLink[(o2.phase+nextstep)>>23]*mixHi)+(waveTable2Link[(o2.phase+nextstep)>>23]*mixLo)+(waveTableMidLink[(o2.phase+nextstep)>>23]*mixMid))>>4)>>11;
    
        
    o3.wave = o3.wave+((((o3.nextwave - o3.wave)) * o3.phaseRemain) >>15); 
    
    
    o2.wave = o2.wave +((((o2.nextwave - o2.wave))* o2.phaseRemain)>>15);
    //o4.wave = o4.wave +((((o4.nextwave - o4.wave))* o4.phaseRemain)>>15);
   

    
    o1.wave =   (o2.wave * o3.wave)>>14;    
    
      

  //  AGCtest = o1.wave >>13; 
   AGCtest = o1.wave;
      
    
    analogWrite(aout2,AGCtest+4000);
  
    
 //digitalWriteFast (oSQout,1);//temp testing OC 
}



