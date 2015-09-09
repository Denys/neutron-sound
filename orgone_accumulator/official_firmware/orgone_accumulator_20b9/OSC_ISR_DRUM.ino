void FASTRUN outUpdateISR_DRUM(void) {
  //noInterrupts();

  //digitalWriteFast (oSQout,0);//temp testing OC


  oSQ.phase = oSQ.phase +  (uint32_t)oSQ.phase_increment; //square wave osc
  digitalWriteFast (oSQout, (oSQ.phase < oSQ.PW)); //pulse out

  if (declickRampOut > 0) declickRampOut = (declickRampOut - declick);
  else declickRampOut = 0;
  declickValue = (declickValue * declickRampOut) >> 12;
  declickRampIn = abs(4095 - declickRampOut);

  ditherbit = random(0, 2);

  noiseTable3[0] = noiseTable3[1] = (noiseTable3[0] + NT3Rate);
  noiseTable[o1.phase >> 23] = random(-32767, 32767); //replace noise cells with random values.


  //envs

  //--------------------first osc envelope---------------------

  o7.phase_increment += o8.phase_increment;

  if (drum_envStep[0] == 0) {
    if (drum_st == 0) {
      drum_envVal[0] = drum_envVal[2] = o6.wave << 14; //use front of wave as attack
      drum_envTemp[2] =drum_envTemp[0] = drum_envVal[0] >> 14;
      o7.phase_increment = 0;
    }
    else {      
        drum_envVal[0] = drum_envVal[2] = 1 << 30;
        drum_envTemp[2] = drum_envTemp[0] = drum_envVal[0] >> 14;
        drum_envStep[0] = 1;
      
    }
  }

  else if (drum_envStep[0] == 1) {

    
    int32_t tempt = multiply_32x32_rshift32(drum_envVal[0], drum_d<<1);
    drum_envVal[0] = drum_envVal[0] - tempt;
    drum_envTemp[0] = drum_envVal[0] >> 14;

    if (o7.phase_increment > drum_a && drum_envStep[2] == 0)drum_envStep[2] = 1;

    if (drum_envVal[0] <= 16390) drum_envStep[0] = 2;
  }

  if (drum_envStep[0] == 2) {
    drum_envVal[0] = 0;
    
    if (o7.phase_increment > drum_a && drum_envStep[2] == 0)drum_envStep[2] = 1;//o7 phase counts up the hold on the amplitude envelope.
  }

  //-----------------second half of ahd amplitude. h is by time

  if (drum_envStep[2] == 1) {

    
    int32_t temph = multiply_32x32_rshift32(drum_envVal[2], drum_d);
    drum_envVal[2] = drum_envVal[2] - temph;
    drum_envTemp[2] = drum_envVal[2] >> 14;

    if (drum_envVal[2] <= 16390) drum_envStep[2] = 2;
  }

  if (drum_envStep[2] == 2) drum_envVal[2] = 0;



  //--------------detuned drums envelope------------


  if (drum_envStep[1] == 0) {
    if (drum_st == 0) {
      drum_envVal[1] = o6.wave << 14;
      drum_envTemp[1] = drum_envVal[1] >> 14;
    }
    else {
      drum_envVal[1] = 1 << 30;
      drum_envTemp[1] = drum_envVal[1] >> 14;
      drum_envStep[1] = 1;      
    }
  }

  else if (drum_envStep[1] == 1) {
    drum_envTemp[1] = drum_envVal[1] >> 14;
    int32_t tempr = multiply_32x32_rshift32(drum_envVal[1], drum_d2);
    drum_envVal[1] = drum_envVal[1] - tempr;
    drum_envTemp[1] = drum_envVal[1] >> 14;

    if (drum_envVal[1] <= 16390) drum_envStep[1] = 2;
  }

  if (drum_envStep[1] == 2) drum_envVal[1] = 0;

  
   
  //oscs
  o1.phase = o1.phase + o1.phase_increment + o10.phase + (o1.amp * drum_envTemp[0]) + o10.phase_increment;
  o1.phaseRemain = (o1.phase << 9) >> 17;
  o6.wave = (waveTableMidLink[o1.phase >> WTShift]);
  o6.nextwave =  (waveTableMidLink[(o1.phase + nextstep) >> WTShift]);
  if (o6.wave > 30000) drum_st = 1;//trigger decay styat at peak of wave 1
  o1.wave = multiply_32x32_rshift32(drum_envVal[2], o6.wave);
  o1.nextwave =  (waveTableMidLink[(o1.phase + nextstep) >> WTShift]);
  o1.nextwave = multiply_32x32_rshift32(drum_envVal[2], o1.nextwave);
  o1.wave = o1.wave + ((((o1.nextwave - o1.wave)) * o1.phaseRemain) >> 15);
  o6.wave = o6.wave + ((((o6.nextwave - o6.wave)) * o1.phaseRemain) >> 15);
  //o1.wave = o1.wave * (drum_envVal[0] >> 14) >> 15;

  if (detuneLoOn) o10.phase_increment = ((int32_t)(drum_envTemp[2]* o6.wave))>>8;//a bit of selfmod osc for osc1 via hold env
  o6.phase =  detuneHiOn * ((envVal * drum_envTemp[1]) >> 2); //borrowed unused osc 6 variable for drum pitch. turns on env 2 > pitch > oscs 2
  o7.phase = detuneMidOn * ((envVal * drum_envTemp[0]) >> 2); // turns on ev1 > pitch > oscs2
  
  if (FMmodeOn) o9.phase_increment = multiply_32x32_rshift32(drum_envVal[1], (o6.phase_increment<<2));
  else o9.phase_increment = o6.phase_increment;

  //oscs 2------------------------------------------

  o2.phase = o2.phase + o2.phase_increment + o6.phase + o7.phase +(o9.phase_increment * o6.wave);
  o2.phaseRemain = (o2.phase << 9) >> 17;
  o8.wave = (waveTableMidLink[o2.phase >> WTShift]);
  o2.wave = multiply_32x32_rshift32(drum_envVal[1], o8.wave);
  o2.nextwave =  (waveTableMidLink[(o2.phase + nextstep) >> WTShift]);
  o2.nextwave = multiply_32x32_rshift32(drum_envVal[1], o2.nextwave);
  o2.wave = o2.wave + ((((o2.nextwave - o2.wave)) * o2.phaseRemain) >> 15);


  o3.phase = o3.phase + o3.phase_increment + o6.phase + o7.phase+(o9.phase_increment * o8.wave);
  o3.phaseRemain = (o3.phase << 9) >> 17;
  o9.wave = (waveTableMidLink[o3.phase >> WTShift]);
  o3.wave = multiply_32x32_rshift32(drum_envVal[1], o9.wave);
  o3.nextwave =  (waveTableMidLink[(o3.phase + nextstep) >> WTShift]);
  o3.nextwave = multiply_32x32_rshift32(drum_envVal[1], o3.nextwave);
  o3.wave = o3.wave + ((((o3.nextwave - o3.wave)) * o3.phaseRemain) >> 15);


  o4.phase = o4.phase + o4.phase_increment + o6.phase +  o7.phase+(o9.phase_increment * o9.wave);
  o4.phaseRemain = (o4.phase << 9) >> 17;
  o10.wave = (waveTableMidLink[o4.phase >> WTShift]);
  o4.wave = multiply_32x32_rshift32(drum_envVal[1], o10.wave);
  o4.nextwave =  (waveTableMidLink[(o4.phase + nextstep) >> WTShift]);
  o4.nextwave = multiply_32x32_rshift32(drum_envVal[1], o4.nextwave);
  o4.wave = o4.wave + ((((o4.nextwave - o4.wave)) * o4.phaseRemain) >> 15);


  o5.phase = o5.phase + o5.phase_increment + o6.phase + o7.phase +(o9.phase_increment * o10.wave);
  o5.phaseRemain = (o5.phase << 9) >> 17;
  o7.wave = (waveTableMidLink[o5.phase >> WTShift]);
  if (o7.wave > 30000) drum_st2 = 1; //start envelope at top of wave, o5 is the highest pitch so will get there first..
  o5.wave = multiply_32x32_rshift32(drum_envVal[1], o7.wave);
  o5.nextwave =  (waveTableMidLink[(o5.phase + nextstep) >> WTShift]);
  o5.nextwave = multiply_32x32_rshift32(drum_envVal[1], o5.nextwave);
  o5.wave = o5.wave + ((((o5.nextwave - o5.wave)) * o5.phaseRemain) >> 15);



  o8.wave = ((o5.wave + o2.wave + o3.wave + o4.wave) >> 2);

  if (pulsarOn) o8.wave = (o8.wave * o6.wave)>>15; //turn on AM osc1 oscs 2
  if (xModeOn) o8.wave = o8.wave * (8191 - abs(o1.wave))>>13; 


  FinalOut = (((o1.wave * (2047 - CZMix))) >> 12) + ((o8.wave * CZMix) >> 12);
  //if (FinalOut > 3900) drum_st = 1;
  FinalOut = declickValue + ((FinalOut * declickRampIn) >> 12);
  analogWrite(aout2, FinalOut + 4000);


}



