void ASSIGNINCREMENTS(){//--------------------------------------------------------default
  
  Serial.println(declickRampOut);

  switch(oscMode){ //switches which oscs get changed by FM and how much multiplier ;
  case 0://break intentionally ommited
    
    UPDATECONTROLS_FM();  
    
   
 
     
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);   
    
    FMIndexContCubing = FMIndexCont/256.0;  
    FMIndex= (uint32_t((float)(((FMIndexContCubing*FMIndexContCubing*FMIndexContCubing)+(averageaInIAvCubing*averageaInIAvCubing*averageaInIAvCubing))*(inputVOct/4.0))));
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095.0)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);  
    mixDetuneUp = mixDetune*0.7;//because there are 5 oscillators being mixed in the detune mix of ISR
    mixDetuneDn =  (2047-mixDetune)*0.97; 


    if (FMFixedOn){
      avgcubing = (float)(averageratio/500.0); //change to adjust "LFO" in fm fixed
      FMMult = ((((float)(avgcubing*avgcubing*avgcubing)))+0.001)*(aInModRatio*8.0);  //FM+fixed mult control 
      //Serial.println(FMMult);
      osc_mult[0]=FMMult;
      osc_mult[1]=4.0;
      o2.phase_increment = inputConverter*osc_mult[1]  ;
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[2];
      o6.phase_increment = inputConverter*osc_mult[1]- detune[3];
      o8.phase_increment = inputConverter*osc_mult[1]+ detune[0];
      o10.phase_increment = inputConverter*osc_mult[1] - detune[1];
      o1.phase_increment = inputConverterF*osc_mult[0] ;
      o3.phase_increment = inputConverterF*osc_mult[0]- detune[2];
      o5.phase_increment = inputConverterF*osc_mult[0]+ detune[3];
      o7.phase_increment = inputConverterF*osc_mult[0]- detune[0];
      o9.phase_increment = inputConverterF*osc_mult[0]+ detune[1];   
    }
    else {
      FMMult = ((int)((averageratio>>9)+1))*aInModRatio; //FM + free 
      osc_mult[0]=FMMult;
      osc_mult[1]=4.0;
      o2.phase_increment = inputConverter*osc_mult[1] ;
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[2];
      o6.phase_increment = inputConverter*osc_mult[1]- detune[3];
      o8.phase_increment = inputConverter*osc_mult[1]+ detune[0];
      o10.phase_increment = inputConverter*osc_mult[1] - detune[1];
      o1.phase_increment = inputConverter*osc_mult[0] ;
      o3.phase_increment = inputConverter*osc_mult[0]- detune[2];
      o5.phase_increment = inputConverter*osc_mult[0]+ detune[3];
      o7.phase_increment = inputConverter*osc_mult[0]+ detune[0];
      o9.phase_increment = inputConverter*osc_mult[0] - detune[1];
    }
    break; 


  
  case 2://fm mode with x button pressed allows pitch bending on hi position and FM is LFO in fixed (no auto get freq).
   

    UPDATECONTROLS_FMALT();     
  
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);   
    
    FMIndexContCubing = FMIndexCont/256.0;  
    FMIndex= (uint32_t((float)(((FMIndexContCubing*FMIndexContCubing*FMIndexContCubing)+(averageaInIAvCubing*averageaInIAvCubing*averageaInIAvCubing))*(inputVOct/4.0))));
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/512.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn); 
    mixDetuneUp = mixDetune*0.78;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97; //keep away from "rails"


    if (FMFixedOn){
      float avgcubing = averageratio/500.0; //change to adjust "LFO" in fm fixed
      FMMult = ((((float)(avgcubing*avgcubing*avgcubing)))+0.001)*(aInModRatio*8.0);  //FM+fixed mult control 
      osc_mult[0]=FMMult;
      osc_mult[1]=4;
      FMX_HiOffset=mixHi*FMX_HiOffsetCont;
      o2.phase_increment = inputConverter*osc_mult[1] + FMX_HiOffset ;
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[2]+ FMX_HiOffset;
      o6.phase_increment = inputConverter*osc_mult[1]- detune[3]+ FMX_HiOffset;
      o8.phase_increment = inputConverter*osc_mult[1]+ detune[0]+ FMX_HiOffset;
      o10.phase_increment = inputConverter*osc_mult[1] - detune[1]+ FMX_HiOffset;
      o1.phase_increment = inputConverterF*osc_mult[0] ;
      o3.phase_increment = inputConverterF*osc_mult[0] ;
      o5.phase_increment = inputConverterF*osc_mult[0] ;
      o7.phase_increment = inputConverterF*osc_mult[0] ;
      o9.phase_increment = inputConverterF*osc_mult[0] ;   
    }
    else {
      FMMult = ((int)((averageratio>>9)+1))*aInModRatio; //FM + free 
      osc_mult[0]=FMMult;
      osc_mult[1]=4;
      FMX_HiOffset=mixHi*FMX_HiOffsetCont;
      o2.phase_increment = inputConverter*osc_mult[1]+ FMX_HiOffset ;
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[2]+ FMX_HiOffset;
      o6.phase_increment = inputConverter*osc_mult[1]- detune[3]+ FMX_HiOffset;
      o8.phase_increment = inputConverter*osc_mult[1]+ detune[1]+ FMX_HiOffset;
      o10.phase_increment = inputConverter*osc_mult[1] - detune[0]+ FMX_HiOffset;
      o1.phase_increment = inputConverter*osc_mult[0] ;
      o3.phase_increment = inputConverter*osc_mult[0]- detune[2];
      o5.phase_increment = inputConverter*osc_mult[0]+ detune[3];
      o7.phase_increment = inputConverter*osc_mult[0]+ detune[0];
      o9.phase_increment = inputConverter*osc_mult[0] - detune[1];
    }
    break; 
case 1://cz

    UPDATECONTROLS_CZ();    
  
    
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);    
    
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);  
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97; 


    
    if (FMFixedOn){
      FMMult = (float)((((averageratio>>4)/1.1))+1.0)*aInModRatio; //CZ + fixed + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverterF*osc_mult[1]; 
      o4.phase_increment = inputConverterF*osc_mult[1];
      o6.phase_increment = inputConverterF*osc_mult[1];
      o8.phase_increment = inputConverterF*osc_mult[1];
      o10.phase_increment = inputConverterF*osc_mult[1];
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0]+ detune[3];
      o5.phase_increment = inputConverter*osc_mult[0]- detune[2];
      o7.phase_increment = inputConverter*osc_mult[0]+ detune[1];
      o9.phase_increment = inputConverter*osc_mult[0] - detune[0];
    }
    else{
      FMMult = (float)((((averageratio>>5)/7.0))+1.0)*aInModRatio; //CZ + free + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverter*osc_mult[1];
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[3];
      o6.phase_increment = inputConverter*osc_mult[1]- detune[2];
      o8.phase_increment = inputConverter*osc_mult[1]+ detune[1];
      o10.phase_increment = inputConverter*osc_mult[1] - detune[0];
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0]+ detune[3];
      o5.phase_increment = inputConverter*osc_mult[0]- detune[2];
      o7.phase_increment = inputConverter*osc_mult[0]+ detune[1];
      o9.phase_increment = inputConverter*osc_mult[0] - detune[0];
    }
    break; 


  case 3://ALT CZ  
  

    UPDATECONTROLS_CZALT();    
  

    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047); 
    //CZMix = (CZMix *((mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn)))>>11;  //mixing index with detune buttons.  

    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97; 

   

    
    if (FMFixedOn){
      FMMult = (float)((((averageratio>>2)+1)/3.0)*aInModRatio); //CZ + fixed + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
    FMX_HiOffset=int32_t(mixHi*FMX_HiOffsetCont)>>10;
      o2.phase_increment = inputConverterF*osc_mult[1]; //modulation not detuned 
      o4.phase_increment = inputConverterF*osc_mult[1]+detune[2];
      o6.phase_increment = inputConverterF*osc_mult[1]-detune[3];
      o8.phase_increment = inputConverterF*osc_mult[1]+detune[0];
      o10.phase_increment = inputConverterF*osc_mult[1]-detune[1];
      o1.phase_increment = inputConverter*osc_mult[0] ;
      o3.phase_increment = inputConverter*osc_mult[0]+ detune[3];
      o5.phase_increment = inputConverter*osc_mult[0]- detune[2];
      o7.phase_increment = inputConverter*osc_mult[0]+ detune[1];
      o9.phase_increment = inputConverter*osc_mult[0]- detune[0];
      lfo.phase_increment = inputConverterF*(osc_mult[1]/8.0);
    }
    else{
      FMMult = (float)((((averageratio>>5)/7.0))+1.0)*aInModRatio; //CZ + free + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
    FMX_HiOffset=int32_t(mixHi*FMX_HiOffsetCont)>>10;
      o2.phase_increment = inputConverter*osc_mult[1];
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[3];;
      o6.phase_increment = inputConverter*osc_mult[1]- detune[2];;
      o8.phase_increment = inputConverter*osc_mult[1]+ detune[1];;
      o10.phase_increment = inputConverter*osc_mult[1]- detune[0];;
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0]+ detune[3];
      o5.phase_increment = inputConverter*osc_mult[0]- detune[2];
      o7.phase_increment = inputConverter*osc_mult[0]+ detune[1];
      o9.phase_increment = inputConverter*osc_mult[0]- detune[0];
      lfo.phase_increment = inputConverter*(osc_mult[1]/2.0);
    }

    break; 
   
  }
  
  
  
 
  oSQ.phase_increment = (inputConverter/PWM_Div)*4;
  if (PWM_Cont == 0){oSQ.PW = (PWM_Min<<20) + ((envVal*(4095 - (PWM_Min<<1)))<<8);}  //scale the pwm so it only reaches min/max set by PWM_MINIMUM in config 
  else {oSQ.PW = (PWM_Min<<20) + (((constrain(((2048+FMIndexCont)+(int(2048-averageaInIAv))),0,4095))    *    (4095 - (PWM_Min<<1)))<<8);}

  //BSFfreq = min((o2.phase_increment>>16),2047); 

}

void ASSIGNINCREMENTS_A(){//--------------------------------------------------------default
  
  

  switch(oscMode){ //switches which oscs get changed by FM and how much multiplier ;
  case 0://break intentionally ommited
    
    UPDATECONTROLS_FM();  
    
   
 
     
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);   
    
    FMIndexContCubing = FMIndexCont/256.0;  
    FMIndex= (uint32_t((float)(((FMIndexContCubing*FMIndexContCubing*FMIndexContCubing)+(averageaInIAvCubing*averageaInIAvCubing*averageaInIAvCubing))*(inputVOct/4.0))));
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095.0)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);  
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR
    mixDetuneDn =  (2047-mixDetune)*0.97; 


    if (FMFixedOn){
      avgcubing = (float)(averageratio/500.0); //change to adjust "LFO" in fm fixed
      FMMult = ((((float)(avgcubing*avgcubing*avgcubing)))+0.001)*(aInModRatio*8.0);  //FM+fixed mult control 
      //Serial.println(FMMult);
      osc_mult[0]=FMMult;
      osc_mult[1]=4.0;
      o2.phase_increment = inputConverter*osc_mult[1]  ;
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[2];
      o6.phase_increment = inputConverter*osc_mult[1]- detune[3];
      ;
      o1.phase_increment = inputConverterF*osc_mult[0] ;
      o3.phase_increment = inputConverterF*osc_mult[0]- detune[2];
      o5.phase_increment = inputConverterF*osc_mult[0]+ detune[3];
     
     o7.phase_increment = random(6000,13000) ;
      o8.phase_increment = random(7000,12000) ;
     
    }
    else {
      FMMult = ((int)((averageratio>>9)+1))*aInModRatio; //FM + free 
      osc_mult[0]=FMMult;
      osc_mult[1]=4.0;
      o2.phase_increment = inputConverter*osc_mult[1] ;
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[2];
      o6.phase_increment = inputConverter*osc_mult[1]- detune[3];
      
      o1.phase_increment = inputConverter*osc_mult[0] ;
      o3.phase_increment = inputConverter*osc_mult[0]- detune[2];
      o5.phase_increment = inputConverter*osc_mult[0]+ detune[3];
     
     o7.phase_increment = random(0,13000) ;
      o8.phase_increment = random(0,12000) ;
    }
    break; 


  
  case 2://fm mode with x button pressed allows pitch bending on hi position and FM is LFO in fixed (no auto get freq).
   

    UPDATECONTROLS_FMALT();     
  
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);   
    
    FMIndexContCubing = FMIndexCont/256.0;  
    FMIndex= (uint32_t((float)(((FMIndexContCubing*FMIndexContCubing*FMIndexContCubing)+(averageaInIAvCubing*averageaInIAvCubing*averageaInIAvCubing))*(inputVOct/4.0))));
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/512.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn); 
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97; //keep away from "rails"


    if (FMFixedOn){
      float avgcubing = averageratio/500.0; //change to adjust "LFO" in fm fixed
      FMMult = ((((float)(avgcubing*avgcubing*avgcubing)))+0.001)*(aInModRatio*8.0);  //FM+fixed mult control 
      osc_mult[0]=FMMult;
      osc_mult[1]=4;
      FMX_HiOffset=mixHi*FMX_HiOffsetCont;
      o2.phase_increment = inputConverter*osc_mult[1] + FMX_HiOffset ;
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[2]+ FMX_HiOffset;
      o6.phase_increment = inputConverter*osc_mult[1]- detune[3]+ FMX_HiOffset;
      o8.phase_increment = inputConverter*osc_mult[1]+ detune[0]+ FMX_HiOffset;
      o10.phase_increment = inputConverter*osc_mult[1] - detune[1]+ FMX_HiOffset;
      o1.phase_increment = inputConverterF*osc_mult[0] ;
      o3.phase_increment = inputConverterF*osc_mult[0] ;
      o5.phase_increment = inputConverterF*osc_mult[0] ;
      o7.phase_increment = inputConverterF*osc_mult[0] ;
      o9.phase_increment = inputConverterF*osc_mult[0] ;   
    }
    else {
      FMMult = ((int)((averageratio>>9)+1))*aInModRatio; //FM + free 
      osc_mult[0]=FMMult;
      osc_mult[1]=4;
      FMX_HiOffset=mixHi*FMX_HiOffsetCont;
      o2.phase_increment = inputConverter*osc_mult[1]+ FMX_HiOffset ;
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[2]+ FMX_HiOffset;
      o6.phase_increment = inputConverter*osc_mult[1]- detune[3]+ FMX_HiOffset;
      o8.phase_increment = inputConverter*osc_mult[1]+ detune[1]+ FMX_HiOffset;
      o10.phase_increment = inputConverter*osc_mult[1] - detune[0]+ FMX_HiOffset;
      o1.phase_increment = inputConverter*osc_mult[0] ;
      o3.phase_increment = inputConverter*osc_mult[0]- detune[2];
      o5.phase_increment = inputConverter*osc_mult[0]+ detune[3];
      o7.phase_increment = inputConverter*osc_mult[0]+ detune[0];
      o9.phase_increment = inputConverter*osc_mult[0] - detune[1];
    }
    break; 
case 1://cz

    UPDATECONTROLS_CZ();    
  
    
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);    
    
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);  
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97; 


    
    if (FMFixedOn){
      FMMult = (float)((((averageratio>>4)/1.1))+1.0)*aInModRatio; //CZ + fixed + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverterF*osc_mult[1]; 
      o4.phase_increment = inputConverterF*osc_mult[1];
      o6.phase_increment = inputConverterF*osc_mult[1];
      o8.phase_increment = inputConverterF*osc_mult[1];
      o10.phase_increment = inputConverterF*osc_mult[1];
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0]+ detune[3];
      o5.phase_increment = inputConverter*osc_mult[0]- detune[2];
      o7.phase_increment = inputConverter*osc_mult[0]+ detune[1];
      o9.phase_increment = inputConverter*osc_mult[0] - detune[0];
    }
    else{
      FMMult = (float)((((averageratio>>5)/7.0))+1.0)*aInModRatio; //CZ + free + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverter*osc_mult[1];
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[3];
      o6.phase_increment = inputConverter*osc_mult[1]- detune[2];
      o8.phase_increment = inputConverter*osc_mult[1]+ detune[1];
      o10.phase_increment = inputConverter*osc_mult[1] - detune[0];
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0]+ detune[3];
      o5.phase_increment = inputConverter*osc_mult[0]- detune[2];
      o7.phase_increment = inputConverter*osc_mult[0]+ detune[1];
      o9.phase_increment = inputConverter*osc_mult[0] - detune[0];
    }
    break; 


  case 3://ALT CZ  
  

    UPDATECONTROLS_CZALT();    
  

    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047); 
    //CZMix = (CZMix *((mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn)))>>11;  //mixing index with detune buttons.  

    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97; 

   

    
    if (FMFixedOn){
      FMMult = (float)((((averageratio>>2)+1)/3.0)*aInModRatio); //CZ + fixed + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
    FMX_HiOffset=int32_t(mixHi*FMX_HiOffsetCont)>>10;
      o2.phase_increment = inputConverterF*osc_mult[1]; //modulation not detuned 
      o4.phase_increment = inputConverterF*osc_mult[1]+detune[2];
      o6.phase_increment = inputConverterF*osc_mult[1]-detune[3];
      o8.phase_increment = inputConverterF*osc_mult[1]+detune[0];
      o10.phase_increment = inputConverterF*osc_mult[1]-detune[1];
      o1.phase_increment = inputConverter*osc_mult[0] ;
      o3.phase_increment = inputConverter*osc_mult[0]+ detune[3];
      o5.phase_increment = inputConverter*osc_mult[0]- detune[2];
      o7.phase_increment = inputConverter*osc_mult[0]+ detune[1];
      o9.phase_increment = inputConverter*osc_mult[0]- detune[0];
      lfo.phase_increment = inputConverterF*(osc_mult[1]/8.0);
    }
    else{
      FMMult = (float)((((averageratio>>5)/7.0))+1.0)*aInModRatio; //CZ + free + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
    FMX_HiOffset=int32_t(mixHi*FMX_HiOffsetCont)>>10;
      o2.phase_increment = inputConverter*osc_mult[1];
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[3];;
      o6.phase_increment = inputConverter*osc_mult[1]- detune[2];;
      o8.phase_increment = inputConverter*osc_mult[1]+ detune[1];;
      o10.phase_increment = inputConverter*osc_mult[1]- detune[0];;
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0]+ detune[3];
      o5.phase_increment = inputConverter*osc_mult[0]- detune[2];
      o7.phase_increment = inputConverter*osc_mult[0]+ detune[1];
      o9.phase_increment = inputConverter*osc_mult[0]- detune[0];
      lfo.phase_increment = inputConverter*(osc_mult[1]/2.0);
    }

    break; 
   
  }
  
  
  
 
  oSQ.phase_increment = (inputConverter/PWM_Div)*4;
  if (PWM_Cont == 0){oSQ.PW = (PWM_Min<<20) + ((envVal*(4095 - (PWM_Min<<1)))<<8);}  //scale the pwm so it only reaches min/max set by PWM_MINIMUM in config 
  else {oSQ.PW = (PWM_Min<<20) + (((constrain(((2048+FMIndexCont)+(int(2048-averageaInIAv))),0,4095))    *    (4095 - (PWM_Min<<1)))<<8);}

  //BSFfreq = min((o2.phase_increment>>16),2047); 

}




void ASSIGNINCREMENTS_C(){//----------------------------------------------for chord
  
  int chordArrayOffset = ((constrain(((4095 - aInDetuneReading)+(analogControls[2])),0,8190))>>10)*3;
  
  if (FX==7){
  for (int i=0; i <= 2; i++){
    detune[i]= inputConverter*(equalTemprementTable[chordTable[i + chordArrayOffset]]);
  }}
  if (FX==8){
  for (int i=0; i <= 2; i++){
    detune[i]= inputConverter*(justTable[chordTable[i + chordArrayOffset]]);
  }}

  switch(oscMode){ //switches which oscs get changed by FM and how much multiplier ;
  

  case 0:
    
    UPDATECONTROLS_FM();  
     
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);   
    
    FMIndexContCubing = FMIndexCont/256.0;  
    FMIndex= (uint32_t((float)(((FMIndexContCubing*FMIndexContCubing*FMIndexContCubing)+(averageaInIAvCubing*averageaInIAvCubing*averageaInIAvCubing))*(inputVOct/4.0))));
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095.0)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);  
    mixDetuneUp = mixDetune*1.1;//because there are 5 oscillators being mixed in the detune mix of ISR
    mixDetuneDn =  (2047-mixDetune)*0.97; 


    if (FMFixedOn){
      avgcubing = (float)(averageratio/500.0); //change to adjust "LFO" in fm fixed
      FMMult = ((((float)(avgcubing*avgcubing*avgcubing)))+0.001)*(aInModRatio*8.0);  //FM+fixed mult control 
      //Serial.println(FMMult);
      osc_mult[0]=FMMult;
      osc_mult[1]=4.0;
      o2.phase_increment = inputConverter*osc_mult[1]  ;
      o4.phase_increment = detune[0]*osc_mult[1];
      o6.phase_increment = detune[1]*osc_mult[1];
      o8.phase_increment = detune[2]*osc_mult[1];
      o10.phase_increment = inputConverter*osc_mult[1];
      o1.phase_increment = inputConverterF*osc_mult[0] ;
      o3.phase_increment = inputConverterF*osc_mult[0];
      o5.phase_increment = inputConverterF*osc_mult[0];
      o7.phase_increment = inputConverterF*osc_mult[0];
      o9.phase_increment = inputConverterF*osc_mult[0];   
    }
    else {
      FMMult = ((int)((averageratio>>9)+1))*aInModRatio; //FM + free 
      osc_mult[0]=FMMult;
      osc_mult[1]=4.0;
      o2.phase_increment = inputConverter*osc_mult[1] ;
      o4.phase_increment = detune[0]*osc_mult[1];
      o6.phase_increment = detune[1]*osc_mult[1];
      o8.phase_increment = detune[2]*osc_mult[1];
      o10.phase_increment = inputConverter*osc_mult[1] - detune[1];
      o1.phase_increment = inputConverter*osc_mult[0] ;
      o3.phase_increment = detune[0]*osc_mult[0];
      o5.phase_increment = detune[1]*osc_mult[0];
      o7.phase_increment = detune[2]*osc_mult[0];
      o9.phase_increment = inputConverter*osc_mult[0] - detune[1];
    }
    break; 


  
  case 2://fm mode with x button pressed allows pitch bending on hi position and FM is LFO in fixed (no auto get freq).
   

    UPDATECONTROLS_FMALT();     
  
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);   
    
    FMIndexContCubing = FMIndexCont/256.0;  
    FMIndex= (uint32_t((float)(((FMIndexContCubing*FMIndexContCubing*FMIndexContCubing)+(averageaInIAvCubing*averageaInIAvCubing*averageaInIAvCubing))*(inputVOct/4.0))));
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/512.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn); 
    mixDetuneUp = mixDetune*1.1;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97; //keep away from "rails"


    if (FMFixedOn){
      float avgcubing = averageratio/500.0; //change to adjust "LFO" in fm fixed
      FMMult = ((((float)(avgcubing*avgcubing*avgcubing)))+0.001)*(aInModRatio*8.0);  //FM+fixed mult control 
      osc_mult[0]=FMMult;
      osc_mult[1]=4;
      FMX_HiOffset=mixHi*FMX_HiOffsetCont;
      o2.phase_increment = inputConverter*osc_mult[1] + FMX_HiOffset ;
      o4.phase_increment = detune[0]*osc_mult[1]+ FMX_HiOffset;
      o6.phase_increment = detune[1]*osc_mult[1]+ FMX_HiOffset;
      o8.phase_increment = detune[2]*osc_mult[1]+ FMX_HiOffset;
      o10.phase_increment = inputConverter*osc_mult[1] - detune[1]+ FMX_HiOffset;
      o1.phase_increment = inputConverterF*osc_mult[0] ;
      o3.phase_increment = inputConverterF*osc_mult[0] ;
      o5.phase_increment = inputConverterF*osc_mult[0] ;
      o7.phase_increment = inputConverterF*osc_mult[0] ;
      o9.phase_increment = inputConverterF*osc_mult[0] ;   
    }
    else {
      FMMult = ((int)((averageratio>>9)+1))*aInModRatio; //FM + free 
      osc_mult[0]=FMMult;
      osc_mult[1]=4;
      FMX_HiOffset=mixHi*FMX_HiOffsetCont;
      o2.phase_increment = inputConverter*osc_mult[1]+ FMX_HiOffset ;
      o4.phase_increment = detune[0]*osc_mult[1]+ FMX_HiOffset;
      o6.phase_increment = detune[1]*osc_mult[1]+ FMX_HiOffset;
      o8.phase_increment = detune[2]*osc_mult[1]+ FMX_HiOffset;
      o10.phase_increment = inputConverter*osc_mult[1]+ FMX_HiOffset;
      o1.phase_increment = inputConverter*osc_mult[0] ;
      o3.phase_increment = detune[0]*osc_mult[0];
      o5.phase_increment = detune[1]*osc_mult[0];
      o7.phase_increment = detune[2]*osc_mult[0];
      o9.phase_increment = inputConverter*osc_mult[0];
    }
    break; 
case 1://cz

    UPDATECONTROLS_CZ();  
    
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);    
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);  
    mixDetuneUp = mixDetune*1.1;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97;
    
    if (FMFixedOn){
      FMMult = (float)((((averageratio>>4)/1.1))+1.0)*aInModRatio; //CZ + fixed + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverterF*osc_mult[1]; 
      o4.phase_increment = inputConverterF*osc_mult[1];
      o6.phase_increment = inputConverterF*osc_mult[1];
      o8.phase_increment = inputConverterF*osc_mult[1];
      o10.phase_increment = inputConverterF*osc_mult[1];
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = detune[0]*osc_mult[0];
      o5.phase_increment = detune[1]*osc_mult[0];
      o7.phase_increment = detune[2]*osc_mult[0];
      o9.phase_increment = inputConverter*osc_mult[0];
    }
    else{
      FMMult = (float)((((averageratio>>5)/7.0))+1.0)*aInModRatio; //CZ + free + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverter*osc_mult[1];
      o4.phase_increment = detune[0]*osc_mult[1];
      o6.phase_increment = detune[1]*osc_mult[1];
      o8.phase_increment = detune[2]*osc_mult[1];
      o10.phase_increment = inputConverter*osc_mult[1] - detune[0];
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = detune[0]*osc_mult[0];
      o5.phase_increment = detune[1]*osc_mult[0];
      o7.phase_increment = detune[2]*osc_mult[0];
      o9.phase_increment = inputConverter*osc_mult[0];
    }
    break; 


  case 3://ALT CZ  
  

    UPDATECONTROLS_CZALT();    
  

    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047); 
    //CZMix = (CZMix *((mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn)))>>11;  //mixing index with detune buttons.  

    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);
    mixDetuneUp = mixDetune*1.1;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97; 


    
    if (FMFixedOn){
      FMMult = (float)((((averageratio>>2)+1)/3.0)*aInModRatio); //CZ + fixed + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
    FMX_HiOffset=int32_t(mixHi*FMX_HiOffsetCont)>>10;
      o2.phase_increment = inputConverterF*osc_mult[1]+ FMX_HiOffset; //modulation not detuned 
      o4.phase_increment = inputConverterF*osc_mult[1]+ FMX_HiOffset;
      o6.phase_increment = inputConverterF*osc_mult[1]+ FMX_HiOffset;
      o8.phase_increment = inputConverterF*osc_mult[1]+ FMX_HiOffset;
      o10.phase_increment = inputConverterF*osc_mult[1]+ FMX_HiOffset;
      o1.phase_increment = inputConverter*osc_mult[0] ;
      o3.phase_increment = detune[0]*osc_mult[0];
      o5.phase_increment = detune[1]*osc_mult[0];
      o7.phase_increment = detune[2]*osc_mult[0];
      o9.phase_increment = inputConverter*osc_mult[0];
      lfo.phase_increment = inputConverterF*(osc_mult[1]/8.0);
    }
    else{
      FMMult = (float)((((averageratio>>5)/7.0))+1.0)*aInModRatio; //CZ + free + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
    FMX_HiOffset=int32_t(mixHi*FMX_HiOffsetCont)>>10;
      o2.phase_increment = inputConverter*osc_mult[1]+ FMX_HiOffset;
      o4.phase_increment = detune[0]*osc_mult[1]+ FMX_HiOffset;
      o6.phase_increment = detune[1]*osc_mult[1]+ FMX_HiOffset;
      o8.phase_increment = detune[2]*osc_mult[1]+ FMX_HiOffset;
      o10.phase_increment = inputConverter*osc_mult[1]+ FMX_HiOffset;
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = detune[0]*osc_mult[0];
      o5.phase_increment = detune[1]*osc_mult[0];
      o7.phase_increment = detune[2]*osc_mult[0];
      o9.phase_increment = inputConverter*osc_mult[0];
      lfo.phase_increment = inputConverter*(osc_mult[1]/2.0);
    }

    break; 
   
  }
  
  
  
 
  oSQ.phase_increment = (inputConverter/PWM_Div)*4;
  if (PWM_Cont == 0){oSQ.PW = (PWM_Min<<20) + ((envVal*(4095 - (PWM_Min<<1)))<<8);}  //scale the pwm so it only reaches min/max set by PWM_MINIMUM in config 
  else {oSQ.PW = (PWM_Min<<20) + (((constrain(((2048+FMIndexCont)+(int(2048-averageaInIAv))),0,4095))    *    (4095 - (PWM_Min<<1)))<<8);}

  //BSFfreq = min((o2.phase_increment>>16),2047); 

}

void ASSIGNINCREMENTS_P(){//--------------------------------------------for pulsar
  
  PENV = PulsarEnv[analogControls[3]>>9];

  switch(oscMode){ //switches which oscs get changed by FM and how much multiplier ;

  case 0:
    
    UPDATECONTROLS_FM();  
     
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);   
    
    FMIndexContCubing = FMIndexCont/256.0;  
    FMIndex= (uint32_t((float)(((FMIndexContCubing*FMIndexContCubing*FMIndexContCubing)+(averageaInIAvCubing*averageaInIAvCubing*averageaInIAvCubing))*(inputVOct/4.0))));
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095.0)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);  
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR
    mixDetuneDn =  (2047-mixDetune)*0.97; 


    if (FMFixedOn){
      FMMult = (float)((((averageratio)/1.1))+1.0)*aInModRatio; 
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverterF*osc_mult[1];      
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0];
      
    }
    else{
      FMMult = (float)((((averageratio>>4)/1.1))+1.0)*aInModRatio;    
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverter*osc_mult[1];      
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverter*osc_mult[0];      
    }
    break; 


  
  case 2://fm mode with x button pressed allows pitch bending on hi position and FM is LFO in fixed (no auto get freq).
   

    UPDATECONTROLS_FMALT();     
  
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);   
    
    FMIndexContCubing = FMIndexCont/256.0;  
    FMIndex= (uint32_t((float)(((FMIndexContCubing*FMIndexContCubing*FMIndexContCubing)+(averageaInIAvCubing*averageaInIAvCubing*averageaInIAvCubing))*(inputVOct/4.0))));
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/512.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn); 
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97; //keep away from "rails"
    
    FMX_HiOffset=mixHi*FMX_HiOffsetCont;

    if (FMFixedOn){
      FMMult = (float)((((averageratio)/1.1))+1.0)*aInModRatio;     
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverterF*osc_mult[1];      
      o1.phase_increment = inputConverter*osc_mult[0]+FMX_HiOffset;
      o3.phase_increment = inputConverter*osc_mult[0];
      
    }
    else{
      FMMult = (float)((((averageratio>>4)/1.1))+1.0)*aInModRatio;        
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverter*osc_mult[1];      
      o1.phase_increment = inputConverter*osc_mult[0]+FMX_HiOffset;
      o3.phase_increment = inputConverter*osc_mult[0];      
    }
    break; 
case 1://cz

    UPDATECONTROLS_CZ();    
  
    
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);    
    
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);  
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97; 


    
    if (FMFixedOn){
      FMMult = (float)((((averageratio>>4)/1.1))+1.0)*aInModRatio; //CZ + fixed + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverterF*osc_mult[1];      
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverterF*osc_mult[0];
      
    }
    else{
      FMMult = (float)((((averageratio>>5)/7.0))+1.0)*aInModRatio; //CZ + free + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverter*osc_mult[1];      
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverterF*osc_mult[0];      
    }
break;
  case 3://ALT CZ  
  

    UPDATECONTROLS_CZALT();    
  

    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047); 
    //CZMix = (CZMix *((mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn)))>>11;  //mixing index with detune buttons.  

    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97; 

FMX_HiOffset=int32_t(mixHi*FMX_HiOffsetCont)>>10;
    
    if (FMFixedOn){
      FMMult = (float)((((averageratio>>4)/1.1))+1.0)*aInModRatio; //CZ + fixed + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverterF*osc_mult[1];      
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverterF*osc_mult[0];
      lfo.phase_increment = inputConverterF*(osc_mult[1]/8.0);
    }
    else{
     FMMult = (float)((((averageratio>>5)/7.0))+1.0)*aInModRatio; //CZ + free + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverter*osc_mult[1];      
      o1.phase_increment = inputConverter*osc_mult[0];
      o3.phase_increment = inputConverterF*osc_mult[0];    
      lfo.phase_increment = inputConverter*(osc_mult[1]/2.0);
    }

    break; 
   
  }
  
  
  
 
  oSQ.phase_increment = (inputConverter/PWM_Div)*4;
  if (PWM_Cont == 0){oSQ.PW = (PWM_Min<<20) + ((envVal*(4095 - (PWM_Min<<1)))<<8);}  //scale the pwm so it only reaches min/max set by PWM_MINIMUM in config 
  else {oSQ.PW = (PWM_Min<<20) + (((constrain(((2048+FMIndexCont)+(int(2048-averageaInIAv))),0,4095))    *    (4095 - (PWM_Min<<1)))<<8);}

  //BSFfreq = min((o2.phase_increment>>16),2047); 

}

void ASSIGNINCREMENTS_D(){//--------------------------------------------------------delay
  
  

  switch(oscMode){ //switches which oscs get changed by FM and how much multiplier ;
  case 0://break intentionally ommited
    
    UPDATECONTROLS_FM();    
 
     
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);   
    
    FMIndexContCubing = FMIndexCont/256.0;  
    FMIndex= (uint32_t((float)(((FMIndexContCubing*FMIndexContCubing*FMIndexContCubing)+(averageaInIAvCubing*averageaInIAvCubing*averageaInIAvCubing))*(inputVOct/4.0))));
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095.0)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);  
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR
    mixDetuneDn =  (2047-mixDetune)*0.97; 


    if (FMFixedOn){
      avgcubing = (float)(analogControls[3]/500.0); //change to adjust "LFO" in fm fixed
      FMMult = ((((float)(avgcubing*avgcubing*avgcubing)))+0.001);  //FM+fixed mult control 
      //Serial.println(FMMult);
      osc_mult[0]=FMMult;
      osc_mult[1]=4.0;
      o2.phase_increment = inputConverter*osc_mult[1]  ;
      
      o1.phase_increment = inputConverterF*osc_mult[0] ;
      
      
      
      
    }
    else {
      FMMult = ((int)((analogControls[3]>>9)+1)); //FM + free 
      osc_mult[0]=FMMult;
      osc_mult[1]=4.0;
      o2.phase_increment = inputConverter*osc_mult[1] ;
   
      o1.phase_increment = inputConverter*osc_mult[0] ;
      
      
    
    }
    break; 


  
  case 2://fm mode with x button pressed allows pitch bending on hi position and FM is LFO in fixed (no auto get freq).
   

    UPDATECONTROLS_FMALT();     
  
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);   
    
    FMIndexContCubing = FMIndexCont/256.0;  
    FMIndex= (uint32_t((float)(((FMIndexContCubing*FMIndexContCubing*FMIndexContCubing)+(averageaInIAvCubing*averageaInIAvCubing*averageaInIAvCubing))*(inputVOct/4.0))));
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/512.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn); 
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97; //keep away from "rails"

    //FMX_HiOffset=int32_t(mixHi*FMX_HiOffsetCont)>>10;
    if (FMFixedOn){
      float avgcubing = analogControls[3]/500.0; //change to adjust "LFO" in fm fixed
      FMMult = ((((float)(avgcubing*avgcubing*avgcubing)))+0.001);  //FM+fixed mult control 
      osc_mult[0]=FMMult;
      osc_mult[1]=4;
      FMX_HiOffset=mixHi*FMX_HiOffsetCont;
      o2.phase_increment = inputConverter*osc_mult[1] + FMX_HiOffset ;
     
      o1.phase_increment = inputConverterF*osc_mult[0] ;
  
    }
    else {
      FMMult = ((int)((analogControls[3]>>9)+1)); //FM + free 
      osc_mult[0]=FMMult;
      osc_mult[1]=4;
      FMX_HiOffset=mixHi*FMX_HiOffsetCont;
      o2.phase_increment = inputConverter*osc_mult[1]+ FMX_HiOffset ;
 
      o1.phase_increment = inputConverter*osc_mult[0] ;
   
    }
    break; 
case 1://cz

    UPDATECONTROLS_CZ();    
  
    
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047);    
    
    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);  
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97; 


    
    if (FMFixedOn){
      FMMult = (float)((((analogControls[3]>>4)/1.1))+1.0); //CZ + fixed + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverterF*osc_mult[1]; 

      o1.phase_increment = inputConverter*osc_mult[0];

    }
    else{
      FMMult = (float)((((analogControls[3]>>5)))+1.0); //CZ + free + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
      o2.phase_increment = inputConverter*osc_mult[1];
   
      o1.phase_increment = inputConverter*osc_mult[0];
  
    }
    break; 


  case 3://ALT CZ  
  

    UPDATECONTROLS_CZALT();    
  

    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2.0))),0,2047); 
    //CZMix = (CZMix *((mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn)))>>11;  //mixing index with detune buttons.  

    
    if (averageaInRAv > 4095) {
      ModRatioCubing = (averageaInRAv-4095)/256.0;
      aInModRatio = ((ModRatioCubing*ModRatioCubing*ModRatioCubing)/2048.0)+1.0;
    }   
    else aInModRatio = (averageaInRAv/4096.0); //down direction dont go past zero, or divide by zero could happen 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR 
    mixDetuneDn =  (2047-mixDetune)*0.97; 

   

    
    if (FMFixedOn){
      FMMult = (float)((((analogControls[3]>>2)+1)/3.0)); //CZ + fixed + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
    FMX_HiOffset=int32_t(mixHi*FMX_HiOffsetCont)>>10;
      o2.phase_increment = inputConverterF*osc_mult[1]; //modulation not detuned 

      o1.phase_increment = inputConverter*osc_mult[0] ;
  
      lfo.phase_increment = inputConverterF*(osc_mult[1]/8.0);
    }
    else{
      FMMult = (float)((((analogControls[3]>>5)))+1.0); //CZ + free + free         
    osc_mult[0]=4;
    osc_mult[1]=FMMult;
    FMX_HiOffset=int32_t(mixHi*FMX_HiOffsetCont)>>10;
      o2.phase_increment = inputConverter*osc_mult[1];
  
      o1.phase_increment = inputConverter*osc_mult[0];
  
      lfo.phase_increment = inputConverter*(osc_mult[1]/2.0);
    }

    break; 
   
  }
  
  
  
 
  oSQ.phase_increment = (inputConverter/PWM_Div)*4;
  if (PWM_Cont == 0){oSQ.PW = (PWM_Min<<20) + ((envVal*(4095 - (PWM_Min<<1)))<<8);}  //scale the pwm so it only reaches min/max set by PWM_MINIMUM in config 
  else {oSQ.PW = (PWM_Min<<20) + (((constrain(((2048+FMIndexCont)+(int(2048-averageaInIAv))),0,4095))    *    (4095 - (PWM_Min<<1)))<<8);}

  //BSFfreq = min((o2.phase_increment>>16),2047); 

}

void ASSIGNINCREMENTS_DRUM(){//--------------------------------------------------------drum effect
  
    UPDATECONTROLS_DRUM(); 
//    Serial.print   (CZMix);
//    Serial.print   ("      ");
    //Serial.println(inputConverter);
     
    CZMix = constrain((FMIndexCont+(2047-(averageaInIAv/2))),0,2047); 
     CZMixDn = constrain(((4095-FMIndexCont)-(2047-(averageaInIAv/2))),0,2047); 

    mixDetune = (mixLo*detuneLoOn)+(mixMid*detuneMidOn)+(mixHi*detuneHiOn);  
    mixDetuneUp = mixDetune*0.787;//because there are 5 oscillators being mixed in the detune mix of ISR
    mixDetuneDn =  (2047-mixDetune)*0.97; 
      o8.phase_increment =  ((uint32_t)(inputConverter))>>10;//borrow this for pitch>hold time

    if (FMFixedOn){
      osc_mult[0]=4.0;
      osc_mult[1]=4.0;
      o1.phase_increment = inputConverter*osc_mult[1]  ;
      o2.phase_increment = inputConverterF + detune[0];
      o3.phase_increment = inputConverterF + detune[1];
      o4.phase_increment = inputConverterF + detune[2];
      o5.phase_increment = inputConverterF + detune[3];
      
      
    }
    else {
      FMMult = ((int)((averageratio>>9)+1))*aInModRatio; //FM + free 
      osc_mult[0]=FMMult;
      osc_mult[1]=4.0;
     o1.phase_increment = inputConverter*osc_mult[1]  ;
      o2.phase_increment = inputConverter*osc_mult[1]+ detune[0];
      o3.phase_increment = inputConverter*osc_mult[1]+ detune[1];
      o4.phase_increment = inputConverter*osc_mult[1]+ detune[2];
      o5.phase_increment = inputConverter*osc_mult[1] + detune[3];
    }
 
  
  
 
  oSQ.phase_increment = (inputConverter/PWM_Div)*4;
  if (PWM_Cont == 0){oSQ.PW = (PWM_Min<<20) + ((envVal*(4095 - (PWM_Min<<1)))<<8);}  //scale the pwm so it only reaches min/max set by PWM_MINIMUM in config 
  else {oSQ.PW = (PWM_Min<<20) + (((constrain(((2048+FMIndexCont)+(int(2048-averageaInIAv))),0,4095))    *    (4095 - (PWM_Min<<1)))<<8);}

  //BSFfreq = min((o2.phase_increment>>16),2047); 

}

