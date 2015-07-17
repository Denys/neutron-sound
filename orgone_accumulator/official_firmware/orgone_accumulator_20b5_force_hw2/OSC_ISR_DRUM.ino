void FASTRUN outUpdateISR_DRUM(void){
 //noInterrupts();  

 //digitalWriteFast (oSQout,0);//temp testing OC
 
  
  oSQ.phase = oSQ.phase +  (uint32_t)oSQ.phase_increment; //square wave osc
  digitalWriteFast (oSQout,(oSQ.phase < oSQ.PW)); //pulse out 
  
  if (declickRampOut > 0) declickRampOut = (declickRampOut - declick);
  else declickRampOut = 0;
  declickValue = (declickValue * declickRampOut)>>12;
  declickRampIn = abs(4095 - declickRampOut);
  
 ditherbit = random(0,2);
  
   noiseTable3[0]=noiseTable3[1]=(noiseTable3[0]+NT3Rate);
    noiseTable[o1.phase>>23]= random(-32767,32767); //replace noise cells with random values.  
    
    
   //envs
   if (drum_envStep[0] == 0) 
   {drum_envVal[0] = drum_envVal[0] + drum_a;
   if (drum_envVal[0] >= (( 2047-CZMix)<<19)) {drum_envVal[0] = (( 2047-CZMix)<<19); drum_envStep[0] = 1;}}
   
   else if (drum_envStep[0] == 1) {
   drum_envTemp[0] = drum_envVal[0] >> 14;
   int32_t tempt = drum_envTemp[0] * drum_d >> 10;
   drum_envVal[0] = drum_envVal[0] - tempt;
   
   if (drum_envVal[0] <= 16390) drum_envStep[0] = 2;}
   
   if (drum_envStep[0] == 2) drum_envVal[0] = 0;
   
   
   if (drum_envStep[1] == 0) 
   {drum_envVal[1] = drum_envVal[1] + drum_a;
   if (drum_envVal[1] >= CZMix<<19) {drum_envVal[1] = CZMix<<19; drum_envStep[1] = 1;}}
   
   else if (drum_envStep[1] == 1) {
   drum_envTemp[1] = drum_envVal[1] >> 14;
   int32_t tempr = drum_envTemp[1] * drum_d2 >> 10;
   drum_envVal[1] = drum_envVal[1] - tempr;
   
   if (drum_envVal[1] <= 16390) drum_envStep[1] = 2;}
   
   if (drum_envStep[1] == 2) drum_envVal[1] = 0;


   
   //oscs
    o1.phase = o1.phase + o1.phase_increment + ((envVal * drum_envTemp[0])>>2); 
    o1.phaseRemain = (o1.phase<<9)>>17;    
    o1.wave = (waveTableMidLink[o1.phase>>WTShift]);
    o1.nextwave =  (waveTableMidLink[(o1.phase+nextstep)>>WTShift]);
    o1.wave = o1.wave+((((o1.nextwave - o1.wave)) * o1.phaseRemain) >>15);
//    if (o1.phaseOld > o1.phase) o1.index = drum_envTemp[0];//zero crossing change level.   
//    o1.phaseOld = o1.phase; 
    o1.wave = ((o1.wave + ditherbit)* drum_envTemp[0])>>15;
 
 o2.phase = o2.phase + o2.phase_increment+ ((envVal * drum_envTemp[1])>>2); 
    o2.phaseRemain = (o2.phase<<9)>>17;    
    o2.wave = (waveTableMidLink[o2.phase>>WTShift]);
    o2.nextwave =  (waveTableMidLink[(o2.phase+nextstep)>>WTShift]);
    o2.wave = o2.wave+((((o2.nextwave - o2.wave)) * o2.phaseRemain) >>15);
   o2.wave = o2.wave * (drum_envVal[1]>>14)>>15; 
    
 o3.phase = o3.phase + o3.phase_increment+ ((envVal * drum_envTemp[1])>>2); 
    o3.phaseRemain = (o3.phase<<9)>>17;    
    o3.wave = (waveTableMidLink[o3.phase>>WTShift]);
    o3.nextwave =  (waveTableMidLink[(o3.phase+nextstep)>>WTShift]);
    o3.wave = o3.wave+((((o3.nextwave - o3.wave)) * o3.phaseRemain) >>15); 
    o3.wave = o3.wave * (drum_envVal[1]>>14)>>15;
    
 o4.phase = o4.phase + o4.phase_increment+ ((envVal * drum_envTemp[1])>>2); 
    o4.phaseRemain = (o4.phase<<9)>>17;    
    o4.wave = (waveTableMidLink[o4.phase>>WTShift]);
    o4.nextwave =  (waveTableMidLink[(o4.phase+nextstep)>>WTShift]);
    o4.wave = o4.wave+((((o4.nextwave - o4.wave)) * o4.phaseRemain) >>15);  
    o4.wave = (o4.wave + ditherbit) * (drum_envVal[1]>>14)>>15;

o5.phase = o5.phase + o5.phase_increment+ ((envVal * drum_envTemp[1])>>2); 
    o5.phaseRemain = (o5.phase<<9)>>17;    
    o5.wave = (waveTableMidLink[o5.phase>>WTShift]);
    o5.nextwave =  (waveTableMidLink[(o5.phase+nextstep)>>WTShift]);
    o5.wave = o5.wave+((((o5.nextwave - o5.wave)) * o5.phaseRemain) >>15); 
o5.wave = o5.wave * (drum_envVal[1]>>14)>>15;    
        
    
   
    
    
    

    AGCtest = ((o5.wave + o2.wave + o3.wave + o4.wave)>>6)  + ((o1.wave+ditherbit)>>4);
    AGCtest = declickValue + ((AGCtest*declickRampIn)>>12);
    analogWrite(aout2,AGCtest+4000);
 

}



