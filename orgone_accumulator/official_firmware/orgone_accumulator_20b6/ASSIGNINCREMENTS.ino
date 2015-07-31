void ASSIGNINCREMENTS() { //--------------------------------------------------------default



  switch (oscMode) { //switches which oscs get changed by FM and how much multiplier ;
    case 0://break intentionally ommited

      UPDATECONTROLS_FM();




      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);

      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) + (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * (inputVOct / 4.0))));

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095.0) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 0.7; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97;


      if (FMFixedOn) {
        avgcubing = (float)(averageratio / 500.0); //change to adjust "LFO" in fm fixed
        FMMult = ((((float)(avgcubing * avgcubing * avgcubing))) + 0.001) * (aInModRatio * 8.0); //FM+fixed mult control
        //Serial.println(FMMult);
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        o2.phase_increment = inputConverter * osc_mult[1]  ;
        o4.phase_increment = inputConverter * osc_mult[1] + detune[2];
        o6.phase_increment = inputConverter * osc_mult[1] - detune[3];
        o8.phase_increment = inputConverter * osc_mult[1] + detune[0];
        o10.phase_increment = inputConverter * osc_mult[1] - detune[1];
        o1.phase_increment = inputConverterF * osc_mult[0] ;
        o3.phase_increment = inputConverterF * osc_mult[0] - detune[2];
        o5.phase_increment = inputConverterF * osc_mult[0] + detune[3];
        o7.phase_increment = inputConverterF * osc_mult[0] - detune[0];
        o9.phase_increment = inputConverterF * osc_mult[0] + detune[1];
      }
      else {
        FMMult = ((int)((averageratio >> 9) + 1)) * aInModRatio; //FM + free
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        o2.phase_increment = inputConverter * osc_mult[1] ;
        o4.phase_increment = inputConverter * osc_mult[1] + detune[2];
        o6.phase_increment = inputConverter * osc_mult[1] - detune[3];
        o8.phase_increment = inputConverter * osc_mult[1] + detune[0];
        o10.phase_increment = inputConverter * osc_mult[1] - detune[1];
        o1.phase_increment = inputConverter * osc_mult[0] ;
        o3.phase_increment = inputConverter * osc_mult[0] - detune[2];
        o5.phase_increment = inputConverter * osc_mult[0] + detune[3];
        o7.phase_increment = inputConverter * osc_mult[0] + detune[0];
        o9.phase_increment = inputConverter * osc_mult[0] - detune[1];
      }
      break;



    case 2://fm mode with x button pressed allows pitch bending on hi position and FM is LFO in fixed (no auto get freq).


      UPDATECONTROLS_FMALT();

      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);

      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) + (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * (inputVOct / 4.0))));

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 512.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 0.78; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97; //keep away from "rails"


      if (FMFixedOn) {
        float avgcubing = averageratio / 500.0; //change to adjust "LFO" in fm fixed
        FMMult = ((((float)(avgcubing * avgcubing * avgcubing))) + 0.001) * (aInModRatio * 8.0); //FM+fixed mult control
        osc_mult[0] = FMMult;
        osc_mult[1] = 4;
        FMX_HiOffset = mixHi * FMX_HiOffsetCont;
        o2.phase_increment = inputConverter * osc_mult[1] + FMX_HiOffset ;
        o4.phase_increment = inputConverter * osc_mult[1] + detune[2] + FMX_HiOffset;
        o6.phase_increment = inputConverter * osc_mult[1] - detune[3] + FMX_HiOffset;
        o8.phase_increment = inputConverter * osc_mult[1] + detune[0] + FMX_HiOffset;
        o10.phase_increment = inputConverter * osc_mult[1] - detune[1] + FMX_HiOffset;
        o1.phase_increment = inputConverterF * osc_mult[0] ;
        o3.phase_increment = inputConverterF * osc_mult[0] ;
        o5.phase_increment = inputConverterF * osc_mult[0] ;
        o7.phase_increment = inputConverterF * osc_mult[0] ;
        o9.phase_increment = inputConverterF * osc_mult[0] ;
      }
      else {
        FMMult = ((int)((averageratio >> 9) + 1)) * aInModRatio; //FM + free
        osc_mult[0] = FMMult;
        osc_mult[1] = 4;
        FMX_HiOffset = mixHi * FMX_HiOffsetCont;
        o2.phase_increment = inputConverter * osc_mult[1] + FMX_HiOffset ;
        o4.phase_increment = inputConverter * osc_mult[1] + detune[2] + FMX_HiOffset;
        o6.phase_increment = inputConverter * osc_mult[1] - detune[3] + FMX_HiOffset;
        o8.phase_increment = inputConverter * osc_mult[1] + detune[1] + FMX_HiOffset;
        o10.phase_increment = inputConverter * osc_mult[1] - detune[0] + FMX_HiOffset;
        o1.phase_increment = inputConverter * osc_mult[0] ;
        o3.phase_increment = inputConverter * osc_mult[0] - detune[2];
        o5.phase_increment = inputConverter * osc_mult[0] + detune[3];
        o7.phase_increment = inputConverter * osc_mult[0] + detune[0];
        o9.phase_increment = inputConverter * osc_mult[0] - detune[1];
      }
      break;
    case 1://cz

      UPDATECONTROLS_CZ();


      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);


      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97;



      if (FMFixedOn) {
        FMMult = (float)((((averageratio >> 4) / 1.1)) + 1.0) * aInModRatio; //CZ + fixed + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o2.phase_increment = inputConverterF * osc_mult[1];
        o4.phase_increment = inputConverterF * osc_mult[1];
        o6.phase_increment = inputConverterF * osc_mult[1];
        o8.phase_increment = inputConverterF * osc_mult[1];
        o10.phase_increment = inputConverterF * osc_mult[1];
        o1.phase_increment = inputConverter * osc_mult[0];
        o3.phase_increment = inputConverter * osc_mult[0] + detune[3];
        o5.phase_increment = inputConverter * osc_mult[0] - detune[2];
        o7.phase_increment = inputConverter * osc_mult[0] + detune[1];
        o9.phase_increment = inputConverter * osc_mult[0] - detune[0];
      }
      else {
        FMMult = (float)((((averageratio >> 5) / 7.0)) + 1.0) * aInModRatio; //CZ + free + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o2.phase_increment = inputConverter * osc_mult[1];
        o4.phase_increment = inputConverter * osc_mult[1] + detune[3];
        o6.phase_increment = inputConverter * osc_mult[1] - detune[2];
        o8.phase_increment = inputConverter * osc_mult[1] + detune[1];
        o10.phase_increment = inputConverter * osc_mult[1] - detune[0];
        o1.phase_increment = inputConverter * osc_mult[0];
        o3.phase_increment = inputConverter * osc_mult[0] + detune[3];
        o5.phase_increment = inputConverter * osc_mult[0] - detune[2];
        o7.phase_increment = inputConverter * osc_mult[0] + detune[1];
        o9.phase_increment = inputConverter * osc_mult[0] - detune[0];
      }
      break;


    case 3://ALT CZ


      UPDATECONTROLS_CZALT();


      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);
      //CZMix = (CZMix *((mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn)))>>11;  //mixing index with detune buttons.


      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97;




      if (FMFixedOn) {
        FMMult = (float)((((averageratio >> 2) + 1) / 3.0) * aInModRatio); //CZ + fixed + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        FMX_HiOffset = int32_t(mixHi * FMX_HiOffsetCont) >> 10;
        o2.phase_increment = inputConverterF * osc_mult[1]; //modulation not detuned
        o4.phase_increment = inputConverterF * osc_mult[1] + detune[2];
        o6.phase_increment = inputConverterF * osc_mult[1] - detune[3];
        o8.phase_increment = inputConverterF * osc_mult[1] + detune[0];
        o10.phase_increment = inputConverterF * osc_mult[1] - detune[1];
        o1.phase_increment = inputConverter * osc_mult[0] ;
        o3.phase_increment = inputConverter * osc_mult[0] + detune[3];
        o5.phase_increment = inputConverter * osc_mult[0] - detune[2];
        o7.phase_increment = inputConverter * osc_mult[0] + detune[1];
        o9.phase_increment = inputConverter * osc_mult[0] - detune[0];
        lfo.phase_increment = inputConverterF * (osc_mult[1] / 8.0);
      }
      else {
        FMMult = (float)((((averageratio >> 5) / 7.0)) + 1.0) * aInModRatio; //CZ + free + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        FMX_HiOffset = int32_t(mixHi * FMX_HiOffsetCont) >> 10;
        o2.phase_increment = inputConverter * osc_mult[1];
        o4.phase_increment = inputConverter * osc_mult[1] + detune[3];;
        o6.phase_increment = inputConverter * osc_mult[1] - detune[2];;
        o8.phase_increment = inputConverter * osc_mult[1] + detune[1];;
        o10.phase_increment = inputConverter * osc_mult[1] - detune[0];;
        o1.phase_increment = inputConverter * osc_mult[0];
        o3.phase_increment = inputConverter * osc_mult[0] + detune[3];
        o5.phase_increment = inputConverter * osc_mult[0] - detune[2];
        o7.phase_increment = inputConverter * osc_mult[0] + detune[1];
        o9.phase_increment = inputConverter * osc_mult[0] - detune[0];
        lfo.phase_increment = inputConverter * (osc_mult[1] / 2.0);
      }

      break;

  }




  oSQ.phase_increment = (inputConverter / PWM_Div) * 4;
  if (PWM_Cont == 0) {
    oSQ.PW = (PWM_Min << 20) + ((envVal * (4095 - (PWM_Min << 1))) << 8); //scale the pwm so it only reaches min/max set by PWM_MINIMUM in config
  }
  else {
    oSQ.PW = (PWM_Min << 20) + (((constrain(((2048 + FMIndexCont) + (int(2048 - averageaInIAv))), 0, 4095))    *    (4095 - (PWM_Min << 1))) << 8);
  }

  //BSFfreq = min((o2.phase_increment>>16),2047);

}

void ASSIGNINCREMENTS_A() { //--------------------------------------------------------default



  switch (oscMode) { //switches which oscs get changed by FM and how much multiplier ;
    case 0://break intentionally ommited

      UPDATECONTROLS_FM();




      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);

      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) + (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * (inputVOct / 4.0))));

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095.0) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97;


      if (FMFixedOn) {
        avgcubing = (float)(averageratio / 500.0); //change to adjust "LFO" in fm fixed
        FMMult = ((((float)(avgcubing * avgcubing * avgcubing))) + 0.001) * (aInModRatio * 8.0); //FM+fixed mult control
        //Serial.println(FMMult);
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        o2.phase_increment = inputConverter * osc_mult[1]  ;
        o4.phase_increment = inputConverter * osc_mult[1] + detune[2];
        o6.phase_increment = inputConverter * osc_mult[1] - detune[3];
        ;
        o1.phase_increment = inputConverterF * osc_mult[0] ;
        o3.phase_increment = inputConverterF * osc_mult[0] - detune[2];
        o5.phase_increment = inputConverterF * osc_mult[0] + detune[3];

        o7.phase_increment = random(6000, 13000) ;
        o8.phase_increment = random(7000, 12000) ;

      }
      else {
        FMMult = ((int)((averageratio >> 9) + 1)) * aInModRatio; //FM + free
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        o2.phase_increment = inputConverter * osc_mult[1] ;
        o4.phase_increment = inputConverter * osc_mult[1] + detune[2];
        o6.phase_increment = inputConverter * osc_mult[1] - detune[3];

        o1.phase_increment = inputConverter * osc_mult[0] ;
        o3.phase_increment = inputConverter * osc_mult[0] - detune[2];
        o5.phase_increment = inputConverter * osc_mult[0] + detune[3];

        o7.phase_increment = random(0, 13000) ;
        o8.phase_increment = random(0, 12000) ;
      }
      break;



    case 2://fm mode with x button pressed allows pitch bending on hi position and FM is LFO in fixed (no auto get freq).


      UPDATECONTROLS_FMALT();

      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);

      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) + (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * (inputVOct / 4.0))));

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 512.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97; //keep away from "rails"


      if (FMFixedOn) {
        float avgcubing = averageratio / 500.0; //change to adjust "LFO" in fm fixed
        FMMult = ((((float)(avgcubing * avgcubing * avgcubing))) + 0.001) * (aInModRatio * 8.0); //FM+fixed mult control
        osc_mult[0] = FMMult;
        osc_mult[1] = 4;
        FMX_HiOffset = mixHi * FMX_HiOffsetCont;
        o2.phase_increment = inputConverter * osc_mult[1] + FMX_HiOffset ;
        o4.phase_increment = inputConverter * osc_mult[1] + detune[2] + FMX_HiOffset;
        o6.phase_increment = inputConverter * osc_mult[1] - detune[3] + FMX_HiOffset;
        o8.phase_increment = inputConverter * osc_mult[1] + detune[0] + FMX_HiOffset;
        o10.phase_increment = inputConverter * osc_mult[1] - detune[1] + FMX_HiOffset;
        o1.phase_increment = inputConverterF * osc_mult[0] ;
        o3.phase_increment = inputConverterF * osc_mult[0] ;
        o5.phase_increment = inputConverterF * osc_mult[0] ;
        o7.phase_increment = inputConverterF * osc_mult[0] ;
        o9.phase_increment = inputConverterF * osc_mult[0] ;
      }
      else {
        FMMult = ((int)((averageratio >> 9) + 1)) * aInModRatio; //FM + free
        osc_mult[0] = FMMult;
        osc_mult[1] = 4;
        FMX_HiOffset = mixHi * FMX_HiOffsetCont;
        o2.phase_increment = inputConverter * osc_mult[1] + FMX_HiOffset ;
        o4.phase_increment = inputConverter * osc_mult[1] + detune[2] + FMX_HiOffset;
        o6.phase_increment = inputConverter * osc_mult[1] - detune[3] + FMX_HiOffset;
        o8.phase_increment = inputConverter * osc_mult[1] + detune[1] + FMX_HiOffset;
        o10.phase_increment = inputConverter * osc_mult[1] - detune[0] + FMX_HiOffset;
        o1.phase_increment = inputConverter * osc_mult[0] ;
        o3.phase_increment = inputConverter * osc_mult[0] - detune[2];
        o5.phase_increment = inputConverter * osc_mult[0] + detune[3];
        o7.phase_increment = inputConverter * osc_mult[0] + detune[0];
        o9.phase_increment = inputConverter * osc_mult[0] - detune[1];
      }
      break;
    case 1://cz

      UPDATECONTROLS_CZ();


      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);


      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97;



      if (FMFixedOn) {
        FMMult = (float)((((averageratio >> 4) / 1.1)) + 1.0) * aInModRatio; //CZ + fixed + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o2.phase_increment = inputConverterF * osc_mult[1];
        o4.phase_increment = inputConverterF * osc_mult[1];
        o6.phase_increment = inputConverterF * osc_mult[1];
        o8.phase_increment = inputConverterF * osc_mult[1];
        o10.phase_increment = inputConverterF * osc_mult[1];
        o1.phase_increment = inputConverter * osc_mult[0];
        o3.phase_increment = inputConverter * osc_mult[0] + detune[3];
        o5.phase_increment = inputConverter * osc_mult[0] - detune[2];
        o7.phase_increment = inputConverter * osc_mult[0] + detune[1];
        o9.phase_increment = inputConverter * osc_mult[0] - detune[0];
      }
      else {
        FMMult = (float)((((averageratio >> 5) / 7.0)) + 1.0) * aInModRatio; //CZ + free + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o2.phase_increment = inputConverter * osc_mult[1];
        o4.phase_increment = inputConverter * osc_mult[1] + detune[3];
        o6.phase_increment = inputConverter * osc_mult[1] - detune[2];
        o8.phase_increment = inputConverter * osc_mult[1] + detune[1];
        o10.phase_increment = inputConverter * osc_mult[1] - detune[0];
        o1.phase_increment = inputConverter * osc_mult[0];
        o3.phase_increment = inputConverter * osc_mult[0] + detune[3];
        o5.phase_increment = inputConverter * osc_mult[0] - detune[2];
        o7.phase_increment = inputConverter * osc_mult[0] + detune[1];
        o9.phase_increment = inputConverter * osc_mult[0] - detune[0];
      }
      break;


    case 3://ALT CZ


      UPDATECONTROLS_CZALT();


      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);
      //CZMix = (CZMix *((mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn)))>>11;  //mixing index with detune buttons.


      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97;




      if (FMFixedOn) {
        FMMult = (float)((((averageratio >> 2) + 1) / 3.0) * aInModRatio); //CZ + fixed + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        FMX_HiOffset = int32_t(mixHi * FMX_HiOffsetCont) >> 10;
        o2.phase_increment = inputConverterF * osc_mult[1]; //modulation not detuned
        o4.phase_increment = inputConverterF * osc_mult[1] + detune[2];
        o6.phase_increment = inputConverterF * osc_mult[1] - detune[3];
        o8.phase_increment = inputConverterF * osc_mult[1] + detune[0];
        o10.phase_increment = inputConverterF * osc_mult[1] - detune[1];
        o1.phase_increment = inputConverter * osc_mult[0] ;
        o3.phase_increment = inputConverter * osc_mult[0] + detune[3];
        o5.phase_increment = inputConverter * osc_mult[0] - detune[2];
        o7.phase_increment = inputConverter * osc_mult[0] + detune[1];
        o9.phase_increment = inputConverter * osc_mult[0] - detune[0];
        lfo.phase_increment = inputConverterF * (osc_mult[1] / 8.0);
      }
      else {
        FMMult = (float)((((averageratio >> 5) / 7.0)) + 1.0) * aInModRatio; //CZ + free + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        FMX_HiOffset = int32_t(mixHi * FMX_HiOffsetCont) >> 10;
        o2.phase_increment = inputConverter * osc_mult[1];
        o4.phase_increment = inputConverter * osc_mult[1] + detune[3];;
        o6.phase_increment = inputConverter * osc_mult[1] - detune[2];;
        o8.phase_increment = inputConverter * osc_mult[1] + detune[1];;
        o10.phase_increment = inputConverter * osc_mult[1] - detune[0];;
        o1.phase_increment = inputConverter * osc_mult[0];
        o3.phase_increment = inputConverter * osc_mult[0] + detune[3];
        o5.phase_increment = inputConverter * osc_mult[0] - detune[2];
        o7.phase_increment = inputConverter * osc_mult[0] + detune[1];
        o9.phase_increment = inputConverter * osc_mult[0] - detune[0];
        lfo.phase_increment = inputConverter * (osc_mult[1] / 2.0);
      }

      break;

  }




  oSQ.phase_increment = (inputConverter / PWM_Div) * 4;
  if (PWM_Cont == 0) {
    oSQ.PW = (PWM_Min << 20) + ((envVal * (4095 - (PWM_Min << 1))) << 8); //scale the pwm so it only reaches min/max set by PWM_MINIMUM in config
  }
  else {
    oSQ.PW = (PWM_Min << 20) + (((constrain(((2048 + FMIndexCont) + (int(2048 - averageaInIAv))), 0, 4095))    *    (4095 - (PWM_Min << 1))) << 8);
  }

  //BSFfreq = min((o2.phase_increment>>16),2047);

}




void ASSIGNINCREMENTS_C() { //----------------------------------------------for chord

  int chordArrayOffset = ((constrain(((4095 - aInDetuneReading) + (analogControls[2])), 0, 8190)) >> 10) * 3;

  if (FX == 7) {
    for (int i = 0; i <= 2; i++) {
      detune[i] = inputConverter * (equalTemprementTable[chordTable[i + chordArrayOffset]]);
    }
  }
  if (FX == 8) {
    for (int i = 0; i <= 2; i++) {
      detune[i] = inputConverter * (justTable[chordTable[i + chordArrayOffset]]);
    }
  }

  switch (oscMode) { //switches which oscs get changed by FM and how much multiplier ;


    case 0:

      UPDATECONTROLS_FM();

      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);

      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) + (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * (inputVOct / 4.0))));

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095.0) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 1.1; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97;


      if (FMFixedOn) {
        avgcubing = (float)(averageratio / 500.0); //change to adjust "LFO" in fm fixed
        FMMult = ((((float)(avgcubing * avgcubing * avgcubing))) + 0.001) * (aInModRatio * 8.0); //FM+fixed mult control
        //Serial.println(FMMult);
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        o2.phase_increment = inputConverter * osc_mult[1]  ;
        o4.phase_increment = detune[0] * osc_mult[1];
        o6.phase_increment = detune[1] * osc_mult[1];
        o8.phase_increment = detune[2] * osc_mult[1];
        o10.phase_increment = inputConverter * osc_mult[1];
        o1.phase_increment = inputConverterF * osc_mult[0] ;
        o3.phase_increment = inputConverterF * osc_mult[0];
        o5.phase_increment = inputConverterF * osc_mult[0];
        o7.phase_increment = inputConverterF * osc_mult[0];
        o9.phase_increment = inputConverterF * osc_mult[0];
      }
      else {
        FMMult = ((int)((averageratio >> 9) + 1)) * aInModRatio; //FM + free
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        o2.phase_increment = inputConverter * osc_mult[1] ;
        o4.phase_increment = detune[0] * osc_mult[1];
        o6.phase_increment = detune[1] * osc_mult[1];
        o8.phase_increment = detune[2] * osc_mult[1];
        o10.phase_increment = inputConverter * osc_mult[1] - detune[1];
        o1.phase_increment = inputConverter * osc_mult[0] ;
        o3.phase_increment = detune[0] * osc_mult[0];
        o5.phase_increment = detune[1] * osc_mult[0];
        o7.phase_increment = detune[2] * osc_mult[0];
        o9.phase_increment = inputConverter * osc_mult[0] - detune[1];
      }
      break;



    case 2://fm mode with x button pressed allows pitch bending on hi position and FM is LFO in fixed (no auto get freq).


      UPDATECONTROLS_FMALT();

      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);

      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) + (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * (inputVOct / 4.0))));

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 512.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 1.1; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97; //keep away from "rails"


      if (FMFixedOn) {
        float avgcubing = averageratio / 500.0; //change to adjust "LFO" in fm fixed
        FMMult = ((((float)(avgcubing * avgcubing * avgcubing))) + 0.001) * (aInModRatio * 8.0); //FM+fixed mult control
        osc_mult[0] = FMMult;
        osc_mult[1] = 4;
        FMX_HiOffset = mixHi * FMX_HiOffsetCont;
        o2.phase_increment = inputConverter * osc_mult[1] + FMX_HiOffset ;
        o4.phase_increment = detune[0] * osc_mult[1] + FMX_HiOffset;
        o6.phase_increment = detune[1] * osc_mult[1] + FMX_HiOffset;
        o8.phase_increment = detune[2] * osc_mult[1] + FMX_HiOffset;
        o10.phase_increment = inputConverter * osc_mult[1] - detune[1] + FMX_HiOffset;
        o1.phase_increment = inputConverterF * osc_mult[0] ;
        o3.phase_increment = inputConverterF * osc_mult[0] ;
        o5.phase_increment = inputConverterF * osc_mult[0] ;
        o7.phase_increment = inputConverterF * osc_mult[0] ;
        o9.phase_increment = inputConverterF * osc_mult[0] ;
      }
      else {
        FMMult = ((int)((averageratio >> 9) + 1)) * aInModRatio; //FM + free
        osc_mult[0] = FMMult;
        osc_mult[1] = 4;
        FMX_HiOffset = mixHi * FMX_HiOffsetCont;
        o2.phase_increment = inputConverter * osc_mult[1] + FMX_HiOffset ;
        o4.phase_increment = detune[0] * osc_mult[1] + FMX_HiOffset;
        o6.phase_increment = detune[1] * osc_mult[1] + FMX_HiOffset;
        o8.phase_increment = detune[2] * osc_mult[1] + FMX_HiOffset;
        o10.phase_increment = inputConverter * osc_mult[1] + FMX_HiOffset;
        o1.phase_increment = inputConverter * osc_mult[0] ;
        o3.phase_increment = detune[0] * osc_mult[0];
        o5.phase_increment = detune[1] * osc_mult[0];
        o7.phase_increment = detune[2] * osc_mult[0];
        o9.phase_increment = inputConverter * osc_mult[0];
      }
      break;
    case 1://cz

      UPDATECONTROLS_CZ();

      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 1.1; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97;

      if (FMFixedOn) {
        FMMult = (float)((((averageratio >> 4) / 1.1)) + 1.0) * aInModRatio; //CZ + fixed + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o2.phase_increment = inputConverterF * osc_mult[1];
        o4.phase_increment = inputConverterF * osc_mult[1];
        o6.phase_increment = inputConverterF * osc_mult[1];
        o8.phase_increment = inputConverterF * osc_mult[1];
        o10.phase_increment = inputConverterF * osc_mult[1];
        o1.phase_increment = inputConverter * osc_mult[0];
        o3.phase_increment = detune[0] * osc_mult[0];
        o5.phase_increment = detune[1] * osc_mult[0];
        o7.phase_increment = detune[2] * osc_mult[0];
        o9.phase_increment = inputConverter * osc_mult[0];
      }
      else {
        FMMult = (float)((((averageratio >> 5) / 7.0)) + 1.0) * aInModRatio; //CZ + free + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o2.phase_increment = inputConverter * osc_mult[1];
        o4.phase_increment = detune[0] * osc_mult[1];
        o6.phase_increment = detune[1] * osc_mult[1];
        o8.phase_increment = detune[2] * osc_mult[1];
        o10.phase_increment = inputConverter * osc_mult[1] - detune[0];
        o1.phase_increment = inputConverter * osc_mult[0];
        o3.phase_increment = detune[0] * osc_mult[0];
        o5.phase_increment = detune[1] * osc_mult[0];
        o7.phase_increment = detune[2] * osc_mult[0];
        o9.phase_increment = inputConverter * osc_mult[0];
      }
      break;


    case 3://ALT CZ


      UPDATECONTROLS_CZALT();


      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);
      //CZMix = (CZMix *((mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn)))>>11;  //mixing index with detune buttons.


      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 1.1; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97;



      if (FMFixedOn) {
        FMMult = (float)((((averageratio >> 2) + 1) / 3.0) * aInModRatio); //CZ + fixed + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        FMX_HiOffset = int32_t(mixHi * FMX_HiOffsetCont) >> 10;
        o2.phase_increment = inputConverterF * osc_mult[1] + FMX_HiOffset; //modulation not detuned
        o4.phase_increment = inputConverterF * osc_mult[1] + FMX_HiOffset;
        o6.phase_increment = inputConverterF * osc_mult[1] + FMX_HiOffset;
        o8.phase_increment = inputConverterF * osc_mult[1] + FMX_HiOffset;
        o10.phase_increment = inputConverterF * osc_mult[1] + FMX_HiOffset;
        o1.phase_increment = inputConverter * osc_mult[0] ;
        o3.phase_increment = detune[0] * osc_mult[0];
        o5.phase_increment = detune[1] * osc_mult[0];
        o7.phase_increment = detune[2] * osc_mult[0];
        o9.phase_increment = inputConverter * osc_mult[0];
        lfo.phase_increment = inputConverterF * (osc_mult[1] / 8.0);
      }
      else {
        FMMult = (float)((((averageratio >> 5) / 7.0)) + 1.0) * aInModRatio; //CZ + free + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        FMX_HiOffset = int32_t(mixHi * FMX_HiOffsetCont) >> 10;
        o2.phase_increment = inputConverter * osc_mult[1] + FMX_HiOffset;
        o4.phase_increment = detune[0] * osc_mult[1] + FMX_HiOffset;
        o6.phase_increment = detune[1] * osc_mult[1] + FMX_HiOffset;
        o8.phase_increment = detune[2] * osc_mult[1] + FMX_HiOffset;
        o10.phase_increment = inputConverter * osc_mult[1] + FMX_HiOffset;
        o1.phase_increment = inputConverter * osc_mult[0];
        o3.phase_increment = detune[0] * osc_mult[0];
        o5.phase_increment = detune[1] * osc_mult[0];
        o7.phase_increment = detune[2] * osc_mult[0];
        o9.phase_increment = inputConverter * osc_mult[0];
        lfo.phase_increment = inputConverter * (osc_mult[1] / 2.0);
      }

      break;

  }




  oSQ.phase_increment = (inputConverter / PWM_Div) * 4;
  if (PWM_Cont == 0) {
    oSQ.PW = (PWM_Min << 20) + ((envVal * (4095 - (PWM_Min << 1))) << 8); //scale the pwm so it only reaches min/max set by PWM_MINIMUM in config
  }
  else {
    oSQ.PW = (PWM_Min << 20) + (((constrain(((2048 + FMIndexCont) + (int(2048 - averageaInIAv))), 0, 4095))    *    (4095 - (PWM_Min << 1))) << 8);
  }

  //BSFfreq = min((o2.phase_increment>>16),2047);

}

void ASSIGNINCREMENTS_P() { //--------------------------------------------for pulsar

  PENV = PulsarEnv[analogControls[3] >> 9];

  switch (oscMode) { //switches which oscs get changed by FM and how much multiplier ;

    case 0:

      UPDATECONTROLS_FM();

      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);

      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) + (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * (inputVOct / 4.0))));

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095.0) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97;


      if (FMFixedOn) {
        FMMult = (float)((((averageratio) / 1.1)) + 1.0) * aInModRatio;
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o2.phase_increment = inputConverterF * osc_mult[1];
        o1.phase_increment = inputConverter * osc_mult[0];
        o3.phase_increment = inputConverter * osc_mult[0];

      }
      else {
        FMMult = (float)((((averageratio >> 4) / 1.1)) + 1.0) * aInModRatio;
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o2.phase_increment = inputConverter * osc_mult[1];
        o1.phase_increment = inputConverter * osc_mult[0];
        o3.phase_increment = inputConverter * osc_mult[0];
      }
      break;



    case 2://fm mode with x button pressed allows pitch bending on hi position and FM is LFO in fixed (no auto get freq).


      UPDATECONTROLS_FMALT();

      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);

      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) + (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * (inputVOct / 4.0))));

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 512.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97; //keep away from "rails"

      FMX_HiOffset = mixHi * FMX_HiOffsetCont;

      if (FMFixedOn) {
        FMMult = (float)((((averageratio) / 1.1)) + 1.0) * aInModRatio;
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o2.phase_increment = inputConverterF * osc_mult[1];
        o1.phase_increment = inputConverter * osc_mult[0] + FMX_HiOffset;
        o3.phase_increment = inputConverter * osc_mult[0];

      }
      else {
        FMMult = (float)((((averageratio >> 4) / 1.1)) + 1.0) * aInModRatio;
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o2.phase_increment = inputConverter * osc_mult[1];
        o1.phase_increment = inputConverter * osc_mult[0] + FMX_HiOffset;
        o3.phase_increment = inputConverter * osc_mult[0];
      }
      break;
    case 1://cz

      UPDATECONTROLS_CZ();


      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);


      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97;



      if (FMFixedOn) {
        FMMult = (float)((((averageratio >> 4) / 1.1)) + 1.0) * aInModRatio; //CZ + fixed + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o2.phase_increment = inputConverterF * osc_mult[1];
        o1.phase_increment = inputConverter * osc_mult[0];
        o3.phase_increment = inputConverterF * osc_mult[0];

      }
      else {
        FMMult = (float)((((averageratio >> 5) / 7.0)) + 1.0) * aInModRatio; //CZ + free + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o2.phase_increment = inputConverter * osc_mult[1];
        o1.phase_increment = inputConverter * osc_mult[0];
        o3.phase_increment = inputConverterF * osc_mult[0];
      }
      break;
    case 3://ALT CZ


      UPDATECONTROLS_CZALT();


      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);
      //CZMix = (CZMix *((mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn)))>>11;  //mixing index with detune buttons.


      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97;

      FMX_HiOffset = int32_t(mixHi * FMX_HiOffsetCont) >> 10;

      if (FMFixedOn) {
        FMMult = (float)((((averageratio >> 4) / 1.1)) + 1.0) * aInModRatio; //CZ + fixed + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o2.phase_increment = inputConverterF * osc_mult[1];
        o1.phase_increment = inputConverter * osc_mult[0];
        o3.phase_increment = inputConverterF * osc_mult[0];
        lfo.phase_increment = inputConverterF * (osc_mult[1] / 8.0);
      }
      else {
        FMMult = (float)((((averageratio >> 5) / 7.0)) + 1.0) * aInModRatio; //CZ + free + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o2.phase_increment = inputConverter * osc_mult[1];
        o1.phase_increment = inputConverter * osc_mult[0];
        o3.phase_increment = inputConverterF * osc_mult[0];
        lfo.phase_increment = inputConverter * (osc_mult[1] / 2.0);
      }

      break;

  }




  oSQ.phase_increment = (inputConverter / PWM_Div) * 4;
  if (PWM_Cont == 0) {
    oSQ.PW = (PWM_Min << 20) + ((envVal * (4095 - (PWM_Min << 1))) << 8); //scale the pwm so it only reaches min/max set by PWM_MINIMUM in config
  }
  else {
    oSQ.PW = (PWM_Min << 20) + (((constrain(((2048 + FMIndexCont) + (int(2048 - averageaInIAv))), 0, 4095))    *    (4095 - (PWM_Min << 1))) << 8);
  }

  //BSFfreq = min((o2.phase_increment>>16),2047);

}

void ASSIGNINCREMENTS_D() { //--------------------------------------------------------delay



  switch (oscMode) { //switches which oscs get changed by FM and how much multiplier ;
    case 0://break intentionally ommited

      UPDATECONTROLS_FM();


      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);

      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) + (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * (inputVOct / 4.0))));

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095.0) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97;


      if (FMFixedOn) {
        avgcubing = (float)(analogControls[3] / 500.0); //change to adjust "LFO" in fm fixed
        FMMult = ((((float)(avgcubing * avgcubing * avgcubing))) + 0.001); //FM+fixed mult control
        //Serial.println(FMMult);
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        o2.phase_increment = inputConverter * osc_mult[1]  ;

        o1.phase_increment = inputConverterF * osc_mult[0] ;




      }
      else {
        FMMult = ((int)((analogControls[3] >> 9) + 1)); //FM + free
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        o2.phase_increment = inputConverter * osc_mult[1] ;

        o1.phase_increment = inputConverter * osc_mult[0] ;



      }
      break;



    case 2://fm mode with x button pressed allows pitch bending on hi position and FM is LFO in fixed (no auto get freq).


      UPDATECONTROLS_FMALT();

      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);

      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) + (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * (inputVOct / 4.0))));

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 512.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97; //keep away from "rails"

      //FMX_HiOffset=int32_t(mixHi*FMX_HiOffsetCont)>>10;
      if (FMFixedOn) {
        float avgcubing = analogControls[3] / 500.0; //change to adjust "LFO" in fm fixed
        FMMult = ((((float)(avgcubing * avgcubing * avgcubing))) + 0.001); //FM+fixed mult control
        osc_mult[0] = FMMult;
        osc_mult[1] = 4;
        FMX_HiOffset = mixHi * FMX_HiOffsetCont;
        o2.phase_increment = inputConverter * osc_mult[1] + FMX_HiOffset ;

        o1.phase_increment = inputConverterF * osc_mult[0] ;

      }
      else {
        FMMult = ((int)((analogControls[3] >> 9) + 1)); //FM + free
        osc_mult[0] = FMMult;
        osc_mult[1] = 4;
        FMX_HiOffset = mixHi * FMX_HiOffsetCont;
        o2.phase_increment = inputConverter * osc_mult[1] + FMX_HiOffset ;

        o1.phase_increment = inputConverter * osc_mult[0] ;

      }
      break;
    case 1://cz

      UPDATECONTROLS_CZ();


      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);


      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97;



      if (FMFixedOn) {
        FMMult = (float)((((analogControls[3] >> 4) / 1.1)) + 1.0); //CZ + fixed + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o2.phase_increment = inputConverterF * osc_mult[1];

        o1.phase_increment = inputConverter * osc_mult[0];

      }
      else {
        FMMult = (float)((((analogControls[3] >> 5))) + 1.0); //CZ + free + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o2.phase_increment = inputConverter * osc_mult[1];

        o1.phase_increment = inputConverter * osc_mult[0];

      }
      break;


    case 3://ALT CZ


      UPDATECONTROLS_CZALT();


      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);
      //CZMix = (CZMix *((mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn)))>>11;  //mixing index with detune buttons.


      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
      mixDetuneUp = mixDetune * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixDetuneDn =  (2047 - mixDetune) * 0.97;




      if (FMFixedOn) {
        FMMult = (float)((((analogControls[3] >> 2) + 1) / 3.0)); //CZ + fixed + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        FMX_HiOffset = int32_t(mixHi * FMX_HiOffsetCont) >> 10;
        o2.phase_increment = inputConverterF * osc_mult[1]; //modulation not detuned

        o1.phase_increment = inputConverter * osc_mult[0] ;

        lfo.phase_increment = inputConverterF * (osc_mult[1] / 8.0);
      }
      else {
        FMMult = (float)((((analogControls[3] >> 5))) + 1.0); //CZ + free + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        FMX_HiOffset = int32_t(mixHi * FMX_HiOffsetCont) >> 10;
        o2.phase_increment = inputConverter * osc_mult[1];

        o1.phase_increment = inputConverter * osc_mult[0];

        lfo.phase_increment = inputConverter * (osc_mult[1] / 2.0);
      }

      break;

  }




  oSQ.phase_increment = (inputConverter / PWM_Div) * 4;
  if (PWM_Cont == 0) {
    oSQ.PW = (PWM_Min << 20) + ((envVal * (4095 - (PWM_Min << 1))) << 8); //scale the pwm so it only reaches min/max set by PWM_MINIMUM in config
  }
  else {
    oSQ.PW = (PWM_Min << 20) + (((constrain(((2048 + FMIndexCont) + (int(2048 - averageaInIAv))), 0, 4095))    *    (4095 - (PWM_Min << 1))) << 8);
  }

  //BSFfreq = min((o2.phase_increment>>16),2047);

}

void ASSIGNINCREMENTS_DRUM() { //--------------------------------------------------------drum effect

  UPDATECONTROLS_DRUM();
  //    Serial.print   (CZMix);
  //    Serial.print   ("      ");
  //Serial.println(inputConverter);

  CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2))), 0, 2047);
  CZMixDn = constrain(((4095 - FMIndexCont) - (2047 - (averageaInIAv / 2))), 0, 2047);

  mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);
  mixDetuneUp = mixDetune * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
  mixDetuneDn =  (2047 - mixDetune) * 0.97;
  o8.phase_increment =  ((uint32_t)(inputConverter)) >> 10; //borrow this for pitch>hold time

  if (FMFixedOn) {
    osc_mult[0] = 4.0;
    osc_mult[1] = 4.0;
    o1.phase_increment = inputConverter * osc_mult[1]  ;
    o2.phase_increment = inputConverterF + detune[0];
    o3.phase_increment = inputConverterF + detune[1];
    o4.phase_increment = inputConverterF + detune[2];
    o5.phase_increment = inputConverterF + detune[3];


  }
  else {
    FMMult = ((int)((averageratio >> 9) + 1)) * aInModRatio; //FM + free
    osc_mult[0] = FMMult;
    osc_mult[1] = 4.0;
    o1.phase_increment = inputConverter * osc_mult[1]  ;
    o2.phase_increment = inputConverter * osc_mult[1] + detune[0];
    o3.phase_increment = inputConverter * osc_mult[1] + detune[1];
    o4.phase_increment = inputConverter * osc_mult[1] + detune[2];
    o5.phase_increment = inputConverter * osc_mult[1] + detune[3];
  }




  oSQ.phase_increment = (inputConverter / PWM_Div) * 4;
  if (PWM_Cont == 0) {
    oSQ.PW = (PWM_Min << 20) + ((envVal * (4095 - (PWM_Min << 1))) << 8); //scale the pwm so it only reaches min/max set by PWM_MINIMUM in config
  }
  else {
    oSQ.PW = (PWM_Min << 20) + (((constrain(((2048 + FMIndexCont) + (int(2048 - averageaInIAv))), 0, 4095))    *    (4095 - (PWM_Min << 1))) << 8);
  }

  //BSFfreq = min((o2.phase_increment>>16),2047);

}

void ASSIGNINCREMENTS_SPECTRUM() { //--------------------------------------------------------



  switch (oscMode) { //switches which oscs get changed by FM and how much multiplier ;
    case 0://break intentionally ommited

      UPDATECONTROLS_FM();


      o2.index = (((HARM_LEVELS[Lbuh]) * mixLo) + ((HARM_LEVELS[Mbuh]) * mixMid) + ((HARM_LEVELS[Hbuh]) * mixHi)) >> 11;
      o3.index = (((HARM_LEVELS[1 + Lbuh]) * mixLo) + ((HARM_LEVELS[1 + Mbuh]) * mixMid) + ((HARM_LEVELS[1 + Hbuh]) * mixHi)) >> 11;
      o4.index = (((HARM_LEVELS[2 + Lbuh]) * mixLo) + ((HARM_LEVELS[2 + Mbuh]) * mixMid) + ((HARM_LEVELS[2 + Hbuh]) * mixHi)) >> 11;
      o5.index = (((HARM_LEVELS[3 + Lbuh]) * mixLo) + ((HARM_LEVELS[3 + Mbuh]) * mixMid) + ((HARM_LEVELS[3 + Hbuh]) * mixHi)) >> 11;
      o6.index = (((HARM_LEVELS[4 + Lbuh]) * mixLo) + ((HARM_LEVELS[4 + Mbuh]) * mixMid) + ((HARM_LEVELS[4 + Hbuh]) * mixHi)) >> 11;
      o7.index = (((HARM_LEVELS[5 + Lbuh]) * mixLo) + ((HARM_LEVELS[5 + Mbuh]) * mixMid) + ((HARM_LEVELS[5 + Hbuh]) * mixHi)) >> 11;
      o8.index = (((HARM_LEVELS[6 + Lbuh]) * mixLo) + ((HARM_LEVELS[6 + Mbuh]) * mixMid) + ((HARM_LEVELS[6 + Hbuh]) * mixHi)) >> 11;
      o9.index = (((HARM_LEVELS[7 + Lbuh]) * mixLo) + ((HARM_LEVELS[7 + Mbuh]) * mixMid) + ((HARM_LEVELS[7 + Hbuh]) * mixHi)) >> 11;
      o10.index = (((HARM_LEVELS[8 + Lbuh]) * mixLo) + ((HARM_LEVELS[8 + Mbuh]) * mixMid) + ((HARM_LEVELS[8 + Hbuh]) * mixHi)) >> 11;


      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);

      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) + (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * (inputVOct / 4.0))));

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095.0) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);

      if (FMFixedOn) {
        avgcubing = (float)(averageratio / 500.0); //change to adjust "LFO" in fm fixed
        FMMult = ((((float)(avgcubing * avgcubing * avgcubing))) + 0.001) * (aInModRatio * 8.0); //FM+fixed mult control
        //Serial.println(FMMult);
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        o1.phase_increment = inputConverterF * osc_mult[0] ;
        o2.phase_increment = inputConverter * osc_mult[1] ;
        o3.phase_increment = inputConverter * 6.0 + (detuneScaler * o3.index );
        o4.phase_increment = inputConverter * 8.0 + (detuneScaler * o4.index );
        o5.phase_increment = inputConverter * 12.0 + (detuneScaler * o5.index );
        o6.phase_increment = inputConverter * 16.0 + (detuneScaler * o6.index );
        o7.phase_increment = inputConverter * 20.0 + (detuneScaler * o7.index );
        o8.phase_increment = inputConverter * 24.0 + (detuneScaler * o8.index );
        o9.phase_increment = inputConverter * 28.0 + (detuneScaler * o9.index );
        o10.phase_increment = inputConverter * 32.0 + (detuneScaler * o10.index );
      }
      else {
        FMMult = ((int)((averageratio >> 9) + 1)) * aInModRatio; //FM + free
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        o1.phase_increment = inputConverter * osc_mult[0] ;
        o2.phase_increment = inputConverter * osc_mult[1] ;
        o3.phase_increment = inputConverter * 6.0 + (detuneScaler * o3.index );
        o4.phase_increment = inputConverter * 8.0 + (detuneScaler * o4.index );
        o5.phase_increment = inputConverter * 12.0 + (detuneScaler * o5.index );
        o6.phase_increment = inputConverter * 16.0 + (detuneScaler * o6.index );
        o7.phase_increment = inputConverter * 20.0 + (detuneScaler * o7.index );
        o8.phase_increment = inputConverter * 24.0 + (detuneScaler * o8.index );
        o9.phase_increment = inputConverter * 28.0 + (detuneScaler * o9.index );
        o10.phase_increment = inputConverter * 32.0 + (detuneScaler * o10.index );





      }
      break;



    case 2://fm mode with x button pressed allows pitch bending on hi position and FM is LFO in fixed (no auto get freq).


      UPDATECONTROLS_FMALT();


      o2.index = (((HARM_LEVELS[Lbuh]) * mixLo) + ((HARM_LEVELS[Mbuh]) * (mixMid + mixHi))) >> 11;
      o3.index = (((HARM_LEVELS[1 + Lbuh]) * mixLo) + ((HARM_LEVELS[1 + Mbuh]) * (mixMid + mixHi))) >> 11;
      o4.index = (((HARM_LEVELS[2 + Lbuh]) * mixLo) + ((HARM_LEVELS[2 + Mbuh]) * (mixMid + mixHi))) >> 11;
      o5.index = (((HARM_LEVELS[3 + Lbuh]) * mixLo) + ((HARM_LEVELS[3 + Mbuh]) * (mixMid + mixHi))) >> 11;
      o6.index = (((HARM_LEVELS[4 + Lbuh]) * mixLo) + ((HARM_LEVELS[4 + Mbuh]) * (mixMid + mixHi))) >> 11;
      o7.index = (((HARM_LEVELS[5 + Lbuh]) * mixLo) + ((HARM_LEVELS[5 + Mbuh]) * (mixMid + mixHi))) >> 11;
      o8.index = (((HARM_LEVELS[6 + Lbuh]) * mixLo) + ((HARM_LEVELS[6 + Mbuh]) * (mixMid + mixHi))) >> 11;
      o9.index = (((HARM_LEVELS[7 + Lbuh]) * mixLo) + ((HARM_LEVELS[7 + Mbuh]) * (mixMid + mixHi))) >> 11;
      o10.index = (((HARM_LEVELS[8 + Lbuh]) * mixLo) + ((HARM_LEVELS[8 + Mbuh]) * (mixMid + mixHi))) >> 11;

      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);

      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) + (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * (inputVOct / 4.0))));

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 512.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen


      if (FMFixedOn) {
        float avgcubing = averageratio / 500.0; //change to adjust "LFO" in fm fixed
        FMMult = ((((float)(avgcubing * avgcubing * avgcubing))) + 0.001) * (aInModRatio * 8.0); //FM+fixed mult control
        osc_mult[0] = FMMult;
        osc_mult[1] = 4;
        FMX_HiOffset = mixHi * FMX_HiOffsetCont;
        o1.phase_increment = inputConverterF * osc_mult[0] ;
        o2.phase_increment = inputConverter * osc_mult[1] + FMX_HiOffset ;
        o3.phase_increment = inputConverter * 6.0 + (detuneScaler * o3.index ) + FMX_HiOffset;
        o4.phase_increment = inputConverter * 8.0 + (detuneScaler * o4.index ) + FMX_HiOffset;
        o5.phase_increment = inputConverter * 12.0 + (detuneScaler * o5.index ) + FMX_HiOffset;
        o6.phase_increment = inputConverter * 16.0 + (detuneScaler * o6.index ) + FMX_HiOffset;
        o7.phase_increment = inputConverter * 20.0 + (detuneScaler * o7.index ) + FMX_HiOffset;
        o8.phase_increment = inputConverter * 24.0 + (detuneScaler * o8.index ) + FMX_HiOffset;
        o9.phase_increment = inputConverter * 28.0 + (detuneScaler * o9.index ) + FMX_HiOffset;
        o10.phase_increment = inputConverter * 32.0 + (detuneScaler * o10.index ) + FMX_HiOffset;
      }
      else {
        FMMult = ((int)((averageratio >> 9) + 1)) * aInModRatio; //FM + free
        osc_mult[0] = FMMult;
        osc_mult[1] = 4;
        FMX_HiOffset = mixHi * FMX_HiOffsetCont;
        o1.phase_increment = inputConverter * osc_mult[0] ;
        o2.phase_increment = inputConverter * osc_mult[1] + FMX_HiOffset ;
        o3.phase_increment = inputConverter * 6.0 + (detuneScaler * o3.index ) + FMX_HiOffset;
        o4.phase_increment = inputConverter * 8.0 + (detuneScaler * o4.index ) + FMX_HiOffset;
        o5.phase_increment = inputConverter * 12.0 + (detuneScaler * o5.index ) + FMX_HiOffset;
        o6.phase_increment = inputConverter * 16.0 + (detuneScaler * o6.index ) + FMX_HiOffset;
        o7.phase_increment = inputConverter * 20.0 + (detuneScaler * o7.index ) + FMX_HiOffset;
        o8.phase_increment = inputConverter * 24.0 + (detuneScaler * o8.index ) + FMX_HiOffset;
        o9.phase_increment = inputConverter * 28.0 + (detuneScaler * o9.index ) + FMX_HiOffset;
        o10.phase_increment = inputConverter * 32.0 + (detuneScaler * o10.index ) + FMX_HiOffset;
      }
      break;
    case 1://cz

      UPDATECONTROLS_CZ();

      o2.index = (((HARM_LEVELS[Lbuh]) * mixLo) + ((HARM_LEVELS[Mbuh]) * mixMid) + ((HARM_LEVELS[Hbuh]) * mixHi)) >> 11;
      o3.index = (((HARM_LEVELS[1 + Lbuh]) * mixLo) + ((HARM_LEVELS[1 + Mbuh]) * mixMid) + ((HARM_LEVELS[1 + Hbuh]) * mixHi)) >> 11;
      o4.index = (((HARM_LEVELS[2 + Lbuh]) * mixLo) + ((HARM_LEVELS[2 + Mbuh]) * mixMid) + ((HARM_LEVELS[2 + Hbuh]) * mixHi)) >> 11;
      o5.index = (((HARM_LEVELS[3 + Lbuh]) * mixLo) + ((HARM_LEVELS[3 + Mbuh]) * mixMid) + ((HARM_LEVELS[3 + Hbuh]) * mixHi)) >> 11;
      o6.index = (((HARM_LEVELS[4 + Lbuh]) * mixLo) + ((HARM_LEVELS[4 + Mbuh]) * mixMid) + ((HARM_LEVELS[4 + Hbuh]) * mixHi)) >> 11;
      o7.index = (((HARM_LEVELS[5 + Lbuh]) * mixLo) + ((HARM_LEVELS[5 + Mbuh]) * mixMid) + ((HARM_LEVELS[5 + Hbuh]) * mixHi)) >> 11;
      o8.index = (((HARM_LEVELS[6 + Lbuh]) * mixLo) + ((HARM_LEVELS[6 + Mbuh]) * mixMid) + ((HARM_LEVELS[6 + Hbuh]) * mixHi)) >> 11;
      o9.index = (((HARM_LEVELS[7 + Lbuh]) * mixLo) + ((HARM_LEVELS[7 + Mbuh]) * mixMid) + ((HARM_LEVELS[7 + Hbuh]) * mixHi)) >> 11;
      o10.index = (((HARM_LEVELS[8 + Lbuh]) * mixLo) + ((HARM_LEVELS[8 + Mbuh]) * mixMid) + ((HARM_LEVELS[8 + Hbuh]) * mixHi)) >> 11;

      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen


      if (FMFixedOn) {
        FMMult = (float)((((averageratio >> 4) / 1.1)) + 1.0) * aInModRatio; //CZ + fixed + free
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        o1.phase_increment = inputConverterF * osc_mult[0] ;
        o2.phase_increment = inputConverter * osc_mult[1] ;
        o3.phase_increment = inputConverter * 6.0 + (detuneScaler * o3.index );
        o4.phase_increment = inputConverter * 8.0 + (detuneScaler * o4.index );
        o5.phase_increment = inputConverter * 12.0 + (detuneScaler * o5.index );
        o6.phase_increment = inputConverter * 16.0 + (detuneScaler * o6.index );
        o7.phase_increment = inputConverter * 20.0 + (detuneScaler * o7.index );
        o8.phase_increment = inputConverter * 24.0 + (detuneScaler * o8.index );
        o9.phase_increment = inputConverter * 28.0 + (detuneScaler * o9.index );
        o10.phase_increment = inputConverter * 32.0 + (detuneScaler * o10.index );
      }
      else {
        FMMult = (float)((((averageratio >> 4) / 5.1)) + 1.0) * aInModRatio;
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        o1.phase_increment = inputConverter * osc_mult[0] ;
        o2.phase_increment = inputConverter * osc_mult[1] ;
        o3.phase_increment = inputConverter * 6.0 + (detuneScaler * o3.index );
        o4.phase_increment = inputConverter * 8.0 + (detuneScaler * o4.index );
        o5.phase_increment = inputConverter * 12.0 + (detuneScaler * o5.index );
        o6.phase_increment = inputConverter * 16.0 + (detuneScaler * o6.index );
        o7.phase_increment = inputConverter * 20.0 + (detuneScaler * o7.index );
        o8.phase_increment = inputConverter * 24.0 + (detuneScaler * o8.index );
        o9.phase_increment = inputConverter * 28.0 + (detuneScaler * o9.index );
        o10.phase_increment = inputConverter * 32.0 + (detuneScaler * o10.index );
      }


      break;


    case 3://ALT CZ


      UPDATECONTROLS_CZALT();

      o2.index = (((HARM_LEVELS[Lbuh]) * mixLo) + ((HARM_LEVELS[Mbuh]) * (mixMid + mixHi))) >> 11;
      o3.index = (((HARM_LEVELS[1 + Lbuh]) * mixLo) + ((HARM_LEVELS[1 + Mbuh]) * (mixMid + mixHi))) >> 11;
      o4.index = (((HARM_LEVELS[2 + Lbuh]) * mixLo) + ((HARM_LEVELS[2 + Mbuh]) * (mixMid + mixHi))) >> 11;
      o5.index = (((HARM_LEVELS[3 + Lbuh]) * mixLo) + ((HARM_LEVELS[3 + Mbuh]) * (mixMid + mixHi))) >> 11;
      o6.index = (((HARM_LEVELS[4 + Lbuh]) * mixLo) + ((HARM_LEVELS[4 + Mbuh]) * (mixMid + mixHi))) >> 11;
      o7.index = (((HARM_LEVELS[5 + Lbuh]) * mixLo) + ((HARM_LEVELS[5 + Mbuh]) * (mixMid + mixHi))) >> 11;
      o8.index = (((HARM_LEVELS[6 + Lbuh]) * mixLo) + ((HARM_LEVELS[6 + Mbuh]) * (mixMid + mixHi))) >> 11;
      o9.index = (((HARM_LEVELS[7 + Lbuh]) * mixLo) + ((HARM_LEVELS[7 + Mbuh]) * (mixMid + mixHi))) >> 11;
      o10.index = (((HARM_LEVELS[8 + Lbuh]) * mixLo) + ((HARM_LEVELS[8 + Mbuh]) * (mixMid + mixHi))) >> 11;


      CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);

      mixDetune = (mixLo * detuneLoOn) + (mixMid * detuneMidOn) + (mixHi * detuneHiOn);

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen


      if (FMFixedOn) {
        FMMult = (float)((((averageratio >> 4) / 1.1)) + 1.0) * aInModRatio; //CZ + fixed + free
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        FMX_HiOffset = mixHi * FMX_HiOffsetCont<<6;
        o1.phase_increment = inputConverterF * osc_mult[0] ;
        o2.phase_increment = inputConverter * osc_mult[1] + FMX_HiOffset ;
        o3.phase_increment = inputConverter * 6.0 + (detuneScaler * o3.index ) + FMX_HiOffset;
        o4.phase_increment = inputConverter * 8.0 + (detuneScaler * o4.index ) + FMX_HiOffset;
        o5.phase_increment = inputConverter * 12.0 + (detuneScaler * o5.index ) + FMX_HiOffset;
        o6.phase_increment = inputConverter * 16.0 + (detuneScaler * o6.index ) + FMX_HiOffset;
        o7.phase_increment = inputConverter * 20.0 + (detuneScaler * o7.index ) + FMX_HiOffset;
        o8.phase_increment = inputConverter * 24.0 + (detuneScaler * o8.index ) + FMX_HiOffset;
        o9.phase_increment = inputConverter * 28.0 + (detuneScaler * o9.index ) + FMX_HiOffset;
        o10.phase_increment = inputConverter * 32.0 + (detuneScaler * o10.index ) + FMX_HiOffset;
      }
      else {
        FMMult = (float)((((averageratio >> 4) / 5.1)) + 1.0) * aInModRatio;
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        FMX_HiOffset = mixHi * FMX_HiOffsetCont<<6;
        o1.phase_increment = inputConverter * osc_mult[0] ;
        o2.phase_increment = inputConverter * osc_mult[1] + FMX_HiOffset ;
        o3.phase_increment = inputConverter * 6.0 + (detuneScaler * o3.index ) + FMX_HiOffset;
        o4.phase_increment = inputConverter * 8.0 + (detuneScaler * o4.index ) + FMX_HiOffset;
        o5.phase_increment = inputConverter * 12.0 + (detuneScaler * o5.index ) + FMX_HiOffset;
        o6.phase_increment = inputConverter * 16.0 + (detuneScaler * o6.index ) + FMX_HiOffset;
        o7.phase_increment = inputConverter * 20.0 + (detuneScaler * o7.index ) + FMX_HiOffset;
        o8.phase_increment = inputConverter * 24.0 + (detuneScaler * o8.index ) + FMX_HiOffset;
        o9.phase_increment = inputConverter * 28.0 + (detuneScaler * o9.index ) + FMX_HiOffset;
        o10.phase_increment = inputConverter * 32.0 + (detuneScaler * o10.index ) + FMX_HiOffset;
      }
      break;

  }



  oSQ.phase_increment = (inputConverter / PWM_Div) * 4;
  if (PWM_Cont == 0) {
    oSQ.PW = (PWM_Min << 20) + ((envVal * (4095 - (PWM_Min << 1))) << 8); //scale the pwm so it only reaches min/max set by PWM_MINIMUM in config
  }
  else {
    oSQ.PW = (PWM_Min << 20) + (((constrain(((2048 + FMIndexCont) + (int(2048 - averageaInIAv))), 0, 4095))    *    (4095 - (PWM_Min << 1))) << 8);
  }

  //BSFfreq = min((o2.phase_increment>>16),2047);

}
