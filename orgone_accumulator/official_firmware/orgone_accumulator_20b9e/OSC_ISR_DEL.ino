void FASTRUN outUpdateISR_WAVE_DELAY(void) {

  delayCounter = delayCounter + 16;
  delayCounterShift = delayCounter >> 4 ;
  delayTimeShift = uint16_t(delayCounter - ((8192 - delayTime) << 3)) >> 4;


  oSQ.phase = oSQ.phase +  (uint32_t)oSQ.phase_increment; //square wave osc
  digitalWriteFast (oSQout, (oSQ.phase < oSQ.PW)); //pulse out

  if (declickRampOut > 0) declickRampOut = (declickRampOut - declick);
  else declickRampOut = 0;
  declickValue = (declickValue * declickRampOut) >> 12;
  declickRampIn = abs(4095 - declickRampOut);


  switch (oscMode) {

    //-----------------------------------------------FM MODE OSCILLATORS-----------------------------------------------
    case 0:

      noiseTable3[0] = noiseTable3[1] = (noiseTable3[0] + NT3Rate);
      noiseTable[o1.phase >> 23] = random(-32767, 32767); //replace noise cells with random values.

      //main oscillator
      o1.phase = o1.phase + o1.phase_increment;
      o1.phaseRemain = (o1.phase << 9) >> 17;
      o1.wave = (sinTable[o1.phase >> WTShiftFM]);
      o1.nextwave =  (sinTable[(o1.phase + nextstep) >> WTShiftFM]);
      o1.wave = o1.wave + ((((o1.nextwave - o1.wave)) * o1.phaseRemain) >> 15);
      o1.index = (FMIndex * o1.wave);
      o2.phase = o2.phase +  (o2.phase_increment + o1.index);
      o2.phaseRemain = (o2.phase << 9) >> 17;

     

      //-----------------------------------------------------------------------

      o2.wave = (
                  (((int32_t)(((GWThi1[o2.phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o2.phase >> 23] * (GremHi)) >> 9))) * mixHi) +
                  (((int32_t)(((GWTlo1[o2.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o2.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o2.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o2.phase >> 23] * (GremMid)) >> 9))) * mixMid)) >> 11;

      o2.nextwave = (
                      (((int32_t)(((GWThi1[(o2.phase + nextstep) >> 23] * (511 - GremHi)) >> 9)  +  ((GWThi2[(o2.phase + nextstep) >> 23] * (GremHi)) >> 9))) * mixHi) +
                      (((int32_t)(((GWTlo1[(o2.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o2.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o2.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o2.phase + nextstep) >> 23] * (GremMid)) >> 9))) * mixMid)) >> 11;

     
      o2.wave = (o2.wave + ((((o2.nextwave - o2.wave)) * o2.phaseRemain) >> 15)) >> 4;
      

      o2.wave = declickValue + ((o2.wave * declickRampIn) >> 12);

      o4.wave = ((o2.wave * (2047 - delayFeedback)) >> 11)  +  ((o3.wave * delayFeedback) >> 11) + o2.wave;


      delayTable[delayCounterShift] = o4.wave >> 1;

      o3.wave = (int32_t)(delayTable[delayTimeShift] << 1);




      //  FinalOut = o1.wave >>13;
      FinalOut = ((((o3.wave + o2.wave) >> 1) * ((int)mixEffectUp)) >> 10)  +  (((o2.wave * ((int)mixEffectDn)) >> 10)); //main out and mix detune



      analogWrite(aout2, FinalOut + 4000);


      break;

    //-----------------------------------------------ALT FM MODE OSCILLATORS-----------------------------------------------
    case 2:


      noiseTable3[0] = noiseTable3[1] = (noiseTable3[0] + NT3Rate);
      noiseTable[o1.phase >> 23] = random(-32767, 32767); //replace noise cells with random values.

      //main oscillator
      o1.phase = o1.phase + o1.phase_increment;       
      o1.phaseRemain = (o1.phase << 9) >> 17;
      o1.wave = (sinTable[o1.phase >> WTShiftFM]);
      o1.nextwave =  (sinTable[(o1.phase + nextstep) >> WTShiftFM]);
      o1.wave = o1.wave + ((((o1.nextwave - o1.wave)) * o1.phaseRemain) >> 15);
      o1.index = (FMIndex * o1.wave);
      o2.phase = o2.phase +  (o2.phase_increment + o1.index);
      o2.phaseRemain = (o2.phase << 9) >> 17;

     


      //-----------------------------------------------------------------------

      o2.wave = (

                  (((int32_t)(((GWTlo1[o2.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o2.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o2.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o2.phase >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 11;

      o2.nextwave = (

                      (((int32_t)(((GWTlo1[(o2.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o2.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o2.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o2.phase + nextstep) >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 11;

     

      o2.wave = (o2.wave + ((((o2.nextwave - o2.wave)) * o2.phaseRemain) >> 15)) >> 4;
      
      o2.wave = declickValue + ((o2.wave * declickRampIn) >> 12);

      o4.wave = ((o2.wave * (2047 - delayFeedback)) >> 11)  +  ((o3.wave * delayFeedback) >> 11) + o2.wave;


      delayTable[delayCounterShift] = o4.wave >> 1;

      o3.wave = (int32_t)(delayTable[delayTimeShift] << 1);


      //  FinalOut = o1.wave >>13;
      FinalOut = ((((o3.wave + o2.wave) >> 1) * ((int)mixEffectUp)) >> 10)  +  (((o2.wave * ((int)mixEffectDn)) >> 10)); //main out and mix detune

      analogWrite(aout2, FinalOut + 4000);

      break;


    case 1://-------------------------------------------CZ MODE OSCILLATORS-----------------------------------------------


      o1.phase = o1.phase + o1.phase_increment;
      noiseTable[o1.phase >> 23] = random(-32767, 32767); //replace noise cells with random values.
      if (o1.phaseOld > o1.phase)o2.phase = 0; //check for sync reset osc in CZ mode.
      o1.phaseOld = o1.phase;
      o2.phase = o2.phase +  o2.phase_increment;
      o2.phaseRemain = (o2.phase << 9) >> 17; //used for fake interpolation
      o1.phaseRemain = (o1.phase << 9) >> 17;

     


      //-----------------------------------------------------------------------

      o2.wave = (sawTable[o2.phase >> 23]);
      o2.nextwave =  (sawTable[(o2.phase + nextstep) >> 23]);


      o1.wave = ((
                   (((int32_t)(((GWThi1[o1.phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o1.phase >> 23] * (GremHi)) >> 9))) * mixHi)   +
                   (((int32_t)(((GWTlo1[o1.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o1.phase >> 23] * (GremLo)) >> 9))) * mixLo)   +
                   (((int32_t)(((GWTmid1[o1.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o1.phase >> 23] * (GremMid)) >> 9))) * mixMid)
                 ) >> 4) >> 11;

      o1.nextwave = ((
                       (((int32_t)(((GWThi1[(o1.phase + nextstep) >> 23] * (511 - GremHi)) >> 9)  +  ((GWThi2[(o1.phase + nextstep) >> 23] * (GremHi)) >> 9))) * mixHi)   +
                       (((int32_t)(((GWTlo1[(o1.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o1.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo)   +
                       (((int32_t)(((GWTmid1[(o1.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o1.phase + nextstep) >> 23] * (GremMid)) >> 9))) * mixMid)
                     ) >> 4) >> 11;
    

      o1.wave = o1.wave + ((((o1.nextwave - o1.wave)) * o1.phaseRemain) >> 15);
      o2.wave = o2.wave + ((((o2.nextwave - o2.wave)) * o2.phaseRemain) >> 15);
      
      o1.wave = ((o1.wave * (2047 - CZMix)) >> 11)  +  ((int32_t)(((o1.wave) * ((o2.wave * CZMix) >> 11)) >> 15));

      o1.wave = declickValue + ((o1.wave * declickRampIn) >> 12);

      o4.wave = ((o1.wave * (2047 - delayFeedback)) >> 11)  +  ((o3.wave * delayFeedback) >> 11) + o1.wave;

      delayTable[delayCounterShift] = o4.wave >> 1;

      o3.wave = (int32_t)(delayTable[delayTimeShift] << 1);

      FinalOut = ((((o3.wave + o1.wave) >> 1) * ((int)mixEffectUp)) >> 10)  +  (((o1.wave * ((int)mixEffectDn)) >> 10)); //main out and mix detune


      analogWrite(aout2, FinalOut + 4000);


      break;



    //----------------------------------------------ALT CZ mode-----------------------------------------
    case 3:

      lfo.phase = lfo.phase + lfo.phase_increment;
      lfo.wave = sinTable[(lfo.phase+o3.phaseOffset) >> 23];

      o3.phaseOffset = (FMX_HiOffset * lfo.wave);
      o1.phase = o1.phase + (o1.phase_increment + o3.phaseOffset);
      noiseTable[o1.phase >> 23] = random(-32767, 32767); //replace noise cells with random values.
      if (o1.phaseOld > o1.phase)o2.phase = 0; //check for sync reset osc in CZ mode.
      o1.phaseOld = o1.phase;
      o2.phase = o2.phase +  o2.phase_increment;
      o2.phaseRemain = (o2.phase << 9) >> 17; //used for fake interpolation
      o1.phaseRemain = (o1.phase << 9) >> 17;

      //-----------------------------------------------------------------------

      o2.wave = (sawTable[o2.phase >> 23]);
      o2.nextwave =  (sawTable[(o2.phase + nextstep) >> 23]);



      o1.wave = ((

                   (((int32_t)(((GWTlo1[o1.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o1.phase >> 23] * (GremLo)) >> 9))) * mixLo)   +
                   (((int32_t)(((GWTmid1[o1.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o1.phase >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))
                 ) >> 4) >> 11;

      o1.nextwave = ((

                       (((int32_t)(((GWTlo1[(o1.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o1.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo)   +
                       (((int32_t)(((GWTmid1[(o1.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o1.phase + nextstep) >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))
                     ) >> 4) >> 11;

      


      o1.wave = o1.wave + ((((o1.nextwave - o1.wave)) * o1.phaseRemain) >> 15);
      o2.wave = o2.wave + ((((o2.nextwave - o2.wave)) * o2.phaseRemain) >> 15);
      
      o1.wave = ((o1.wave * (2047 - CZMix)) >> 11)  +  ((int32_t)(((o1.wave) * ((o2.wave * CZMix) >> 11)) >> 15));

      o1.wave = declickValue + ((o1.wave * declickRampIn) >> 12);

      o4.wave = (((o1.wave * (2047 - delayFeedback)) >> 11)  +  ((o3.wave * delayFeedback) >> 11) + o1.wave) >>1;

      delayTable[delayCounterShift] = o4.wave>>1;

      o3.wave = (int32_t)(delayTable[delayTimeShift] << 1);

      o3.wave = ((((o3.wave + o1.wave) >> 1) * ((int)mixEffectUp)) >> 10)  +  (((o1.wave * ((int)mixEffectDn)) >> 10)); //main out and mix detune
      
      
      FinalOut = declickValue + ((o3.wave * declickRampIn) >> 12);


      analogWrite(aout2, FinalOut + 4000);

      break;
  }   
}

void FASTRUN outUpdateISR_PULSAR_DELAY(void) {

  delayCounter = delayCounter + 16;
  delayCounterShift = delayCounter >> 4 ;
  delayTimeShift = uint16_t(delayCounter - ((8192 - delayTime) << 3)) >> 4;

  
  oSQ.phase = oSQ.phase +  (uint32_t)oSQ.phase_increment; //square wave osc
  digitalWriteFast (oSQout, (oSQ.phase < oSQ.PW)); //pulse out

  if (declickRampOut > 0) declickRampOut = (declickRampOut - declick);
  else declickRampOut = 0;
  declickValue = (declickValue * declickRampOut) >> 12;
  declickRampIn = abs(4095 - declickRampOut);

  

      noiseTable[o1.phase >> 23] = random(-32767, 32767); //replace noise cells with random values.

      o1.phase = o1.phase + o1.phase_increment;
      
      o10.phase = o10.phase + o10.phase_increment;//"fm" button sub osc
      o10.phaseRemain = (o10.phase << 9) >> 17;
      o10.wave = (sinTable[o6.phase >> 23]);
      o10.nextwave = (sinTable[(o6.phase + nextstep)>> 23]);
      o10.wave = o10.wave + ((((o10.nextwave - o10.wave)) * o10.phaseRemain) >> 15);  
      
         
      if (o1.phaseOld > o1.phase) {
        o2.phase = o3.phase = 0; //check for sync reset osc in CZ mode.
      }     
      o1.phaseOld = o1.phase;
      

      o2.phase = o2.phase +  o2.phase_increment + ((o10.wave<<10) * FMmodeOn);
      o2.phaseRemain = (o2.phase << 9) >> 17; //used for fake interpolation
     

      if (o3.phase >> 31 == 0) {
        o3.phase = o3.phase + o3.phase_increment ;
        o3.wave = (sinTable[o3.phase >> 23]);
        o3.nextwave =  (sinTable[(o3.phase + nextstep) >> 23]);
      }
      else {
        o3.wave = 0;
        o3.nextwave =  0;
      }

      o3.phaseRemain = (o3.phase << 9) >> 17;
     

  switch (oscMode) {

    //-----------------------------------------------FM MODE OSCILLATORS-----------------------------------------------
    case 0:
    

      o2.wave = (
                  (((int32_t)(((GWThi1[o2.phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o2.phase >> 23] * (GremHi)) >> 9))) * mixHi) +
                  (((int32_t)(((GWTlo1[o2.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o2.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o2.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o2.phase >> 23] * (GremMid)) >> 9))) * mixMid)) >> 15;

      o2.nextwave = (
                      (((int32_t)(((GWThi1[(o2.phase + nextstep) >> 23] * (511 - GremHi)) >> 9)  +  ((GWThi2[(o2.phase + nextstep) >> 23] * (GremHi)) >> 9))) * mixHi) +
                      (((int32_t)(((GWTlo1[(o2.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o2.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o2.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o2.phase + nextstep) >> 23] * (GremMid)) >> 9))) * mixMid)) >> 15;

     

      break;

    //-----------------------------------------------ALT FM MODE OSCILLATORS-----------------------------------------------
    case 2:

       o2.wave = (

                  (((int32_t)(((GWTlo1[o2.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o2.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o2.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o2.phase >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 15;

      o2.nextwave = (

                      (((int32_t)(((GWTlo1[(o2.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o2.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o2.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o2.phase + nextstep) >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 15;

     
      break;

    //-----------------------------------------------CZ MODE OSCILLATORS-----------------------------------------------
    case 1:



      o2.wave = (
                  (((int32_t)(((GWThi1[o2.phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o2.phase >> 23] * (GremHi)) >> 9))) * mixHi) +
                  (((int32_t)(((GWTlo1[o2.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o2.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o2.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o2.phase >> 23] * (GremMid)) >> 9))) * mixMid)) >> 15;

      o2.nextwave = (
                      (((int32_t)(((GWThi1[(o2.phase + nextstep) >> 23] * (511 - GremHi)) >> 9)  +  ((GWThi2[(o2.phase + nextstep) >> 23] * (GremHi)) >> 9))) * mixHi) +
                      (((int32_t)(((GWTlo1[(o2.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o2.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o2.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o2.phase + nextstep) >> 23] * (GremMid)) >> 9))) * mixMid)) >> 15;

     

       
      break;

    //-----------------------------------------------ALT CZ MODE OSCILLATORS-----------------------------------------------
    case 3:

        o2.wave = (

                  (((int32_t)(((GWTlo1[o2.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o2.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o2.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o2.phase >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 15;

      o2.nextwave = (

                      (((int32_t)(((GWTlo1[(o2.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o2.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o2.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o2.phase + nextstep) >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 15;

     
      break;

  }
  
      o2.wave = o2.wave + ((((o2.nextwave - o2.wave)) * o2.phaseRemain) >> 15);
      o3.wave = o3.wave + ((((o3.nextwave - o3.wave)) * o3.phaseRemain) >> 15);      

      o1.wave =   (o2.wave * o3.wave) >> 13;          

      o1.wave = declickValue + ((o1.wave * declickRampIn) >> 12);

      o4.wave = ((int32_t)(o1.wave * (2047 - delayFeedback)) >> 11)  +  (int32_t)((o5.wave * delayFeedback) >> 9) + o1.wave;

      delayTable[delayCounterShift] = o4.wave>>2;

      o5.wave = (int32_t)(delayTable[delayTimeShift])<<1;

      o5.wave = ((((o5.wave + o1.wave) >> 1) * ((int)mixEffectUp)) >> 11)  +  (((o1.wave * ((int)mixEffectDn)) >> 11)); //main out and mix detune

      FinalOut = declickValue + ((o5.wave * declickRampIn) >> 12);
      
      analogWrite(aout2, FinalOut + 4000);
}




