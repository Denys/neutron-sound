void UPDATECONTROLS_CZ(){

  switch (ARC+1) {

  case 8:

    break;

  case 10:   

    Serial.println(analogControls[0]);
    //outputs the frequency on USB serial. tune lock, FM and X must be off

    break;

  case 3:
   
    detuneAmountCont = analogControls[2];
    //detuneAmountCont = (detuneAmountContCubing*detuneAmountContCubing*detuneAmountContCubing)/1024.0; 
    
    //modmod depreciate in to "range"
     switch (analogControls[2]>>9){
    case 0: 
      FMTableMM = sinTable;      
      break;
    case 1: 
      FMTableMM = triTable;     
      break;
    case 2: 
      FMTableMM = AKWF_symetric_0011;     
      break;
    case 3: 
      FMTableMM = FMTableSQ;     
      break;
    case 4: 
      FMTableMM = FMTableSQR;    
      break;
    case 5: 
       FMTableMM = AKWF_symetric_0013;     
      break;
    case 6: 
      FMTableMM = AKWF_symetric_0001;    
      break;
    case 7: 
      FMTableMM = bassTable1;     
      break;
     case 8: 
      FMTableMM = FMTableS180;     
      break;
    case 9: 
      FMTableMM = celloTable;      
      break;
    case 10: 
      FMTableMM = violTable;      
      break;
    case 11: 
      FMTableMM = distoTable;     
      break;
    case 12: 
      FMTableMM = blipTable;     
      break;
    case 13: 
      FMTableMM = FMTableFM98;      
      break;
    case 14: 
      FMTableMM = noiseTable2;       
      break;
    case 15: 
      FMTableMM = noiseTable3;
     
      break;      
    }
    
     
    break;

  case 4:
  
  TUNELOCK_TOGGLE();

  waveTableMidLink = CZWTselMid[analogControls[5]>>9];
           
    break;

  case 5:
  
waveTable2Link = CZWTselLo[analogControls[8]>>9];
  

    break;

  case 6: //select hi wave
  
 waveTableLink = CZWTselHi[analogControls[4]>>9];   
    
    break;  

  case 1:     
    mixPos = (analogControls[6]>>5)<<4;     

    FMFixedOn = digitalReadFast(FMFixedSwitch);
    if (FMFixedOn){
      inputConverterF = 200000;
    } //sets fixed frequency to current frequency when fixed is pushed.


    oscMode = (!digitalReadFast(xModeSwitch)<<1)+ digitalReadFast(CZmodeSwitch);   
    break; 

  case 7:
    
    detuneLoOn = digitalReadFast(detuneLoSwitch); 
    detuneMidOn = !digitalReadFast(detuneMidSwitch); 
    detuneHiOn = !digitalReadFast(detuneHiSwitch);    

    break;

  case 2:
    totalratio = totalratio - readingsratio[controlAveragingIndex]; 
    readingsratio[controlAveragingIndex] = analogControls[0];
    totalratio = totalratio + readingsratio[controlAveragingIndex];
    controlAveragingIndex = controlAveragingIndex + 1;
    if (controlAveragingIndex >= numreadingsratio) controlAveragingIndex = 0;
    averageratio = totalratio / numreadingsratio;    
    break; 

  case 9:
    FMIndexCont = (int)(analogControls[1]>>2);    
    FMTable = CZWTselFM[analogControls[3]>>9];

    break;   


  }
}
//--------------------------------------------------------------------CZ-ALT--------------------------------------------------
void UPDATECONTROLS_CZALT(){

  switch (ARC+1) {

  case 8:
         
    break;

  case 10:    
    
     
    break;

  case 3:
    TUNELOCK_TOGGLE();     
    detuneAmountCont = analogControls[2];
    //detuneAmountCont = (detuneAmountContCubing*detuneAmountContCubing*detuneAmountContCubing)/1024.0; 
    break;

  case 4:

 waveTableMidLink = CZAltWTselMid[analogControls[5]>>9];
           
    break;

  case 5:
  
waveTable2Link = CZAltWTselLo[analogControls[8]>>9];
  
    break;

  case 6: //no hi wave in alt(x) mode
   
   FMX_HiOffsetContCub = (analogControls[4]>>3)-512; 
   FMX_HiOffsetCont = (int32_t)(FMX_HiOffsetContCub*FMX_HiOffsetContCub*FMX_HiOffsetContCub)>>20;
    //FMX_HiOffsetCont = FMX_HiOffsetContCub*FMX_HiOffsetContCub*FMX_HiOffsetContCub  ;      

  case 1:     
    mixPos = (analogControls[6]>>5)<<4;     
    
    FMFixedOn = digitalReadFast(FMFixedSwitch);
    if (FMFixedOn){inputConverterF = 20000;} //sets lowest fixed modulator frequency       
    
    oscMode = (!digitalReadFast(xModeSwitch)<<1)+ digitalReadFast(CZmodeSwitch);
    break; 

  case 7:
  
    detuneLoOn = digitalReadFast(detuneLoSwitch); 
    detuneMidOn = !digitalReadFast(detuneMidSwitch); 
    detuneHiOn = !digitalReadFast(detuneHiSwitch);    

    break;

  case 2:
    totalratio = totalratio - readingsratio[controlAveragingIndex]; 
    readingsratio[controlAveragingIndex] = analogControls[0];
    totalratio = totalratio + readingsratio[controlAveragingIndex];
    controlAveragingIndex = controlAveragingIndex + 1;
    if (controlAveragingIndex >= numreadingsratio) controlAveragingIndex = 0;
    averageratio = totalratio / numreadingsratio;    
     break; 

  case 9:
    FMIndexCont = (int)(analogControls[1]>>2);    

 FMTable = CZAltWTselFM[analogControls[3]>>9]; 
 FMTableAMX = CZAltWTselFMAMX[analogControls[3]>>9]; //am mod on hi position   
    

    break;   


  }
}
//----------------------------------------------------------------FM--------------------------------------------------------
void UPDATECONTROLS_FM(){     

  switch (ARC+1) {
  case 8: //8 and 10 are skipped when tune lock is on, do not use.    
    break;
  case 10:      
    break;

  case 3:
    TUNELOCK_TOGGLE();
    detuneAmountCont = analogControls[2];
    //detuneAmountCont = (detuneAmountContCubing*detuneAmountContCubing*detuneAmountContCubing)/1024.0;  
    
//        Serial.print(FMIndex);
//        Serial.print("    ");
//        Serial.print(detuneAmountCont);
//        
//        Serial.print("    ");
//        Serial.println(aInModDetune);

   switch (analogControls[2]>>9){
    case 0: 
      FMTableMM = sinTable;      
      break;
    case 1: 
      FMTableMM = triTable;     
      break;
    case 2: 
      FMTableMM = AKWF_symetric_0011;     
      break;
    case 3: 
      FMTableMM = FMTableSQ;     
      break;
    case 4: 
      FMTableMM = FMTableSQR;    
      break;
    case 5: 
       FMTableMM = AKWF_symetric_0013;     
      break;
    case 6: 
      FMTableMM = AKWF_symetric_0001;    
      break;
    case 7: 
      FMTableMM = bassTable1;     
      break;
     case 8: 
      FMTableMM = FMTableS180;     
      break;
    case 9: 
      FMTableMM = celloTable;      
      break;
    case 10: 
      FMTableMM = violTable;      
      break;
    case 11: 
      FMTableMM = distoTable;     
      break;
    case 12: 
      FMTableMM = blipTable;     
      break;
    case 13: 
      FMTableMM = FMTableFM98;      
      break;
    case 14: 
      FMTableMM = noiseTable2;       
      break;
    case 15: 
      FMTableMM = noiseTable3;
     
      break;      
    }
    break;
    
  case 4: //mid wave
    waveTableMidLink = FMWTselMid[analogControls[5]>>9];           
    break;

  case 5:  //lo wave
waveTable2Link = FMWTselLo[analogControls[8]>>9];
    break;

  case 6: //select hi wave  
 waveTableLink = FMWTselHi[analogControls[4]>>9]; 

    break;  

  case 1:     
    mixPos = (analogControls[6]>>1); 
    
    FMFixedOn = digitalReadFast(FMFixedSwitch);
    if (FMFixedOn){inputConverterF = 20000;} //sets fixed frequency to current frequency when fixed is pushed.
           
    
    oscMode = (!digitalReadFast(xModeSwitch)<<1)+ digitalReadFast(CZmodeSwitch);
    break; 

  case 7:
  
    detuneLoOn = digitalReadFast(detuneLoSwitch); 
    detuneMidOn = !digitalReadFast(detuneMidSwitch); 
    detuneHiOn = !digitalReadFast(detuneHiSwitch);    

    break;

  case 2:
    totalratio = totalratio - readingsratio[controlAveragingIndex]; 
    readingsratio[controlAveragingIndex] = analogControls[0]; //fm ratio control smoothing in FM
    totalratio = totalratio + readingsratio[controlAveragingIndex];
    controlAveragingIndex = controlAveragingIndex + 1;
    if (controlAveragingIndex >= numreadingsratio) controlAveragingIndex = 0;
    averageratio = totalratio / numreadingsratio;    
     break; 

  case 9:
    FMIndexCont = (int)(analogControls[1]>>2);    
    
//    else {
//      FMIndexContCubing = (analogControls[8])/1024.0;
//      FMIndexCont = (int) (FMIndexContCubing* FMIndexContCubing*FMIndexContCubing); 
//    }
    
    FMTable = FMWTselFM[analogControls[3]>>9];
    if ((analogControls[3]>>9) == 15) WTShift = 31;
    else WTShift = 23;
    
     
    break;   


  }
}
//--------------------------------------------------------------------------FMALT--------------------------------------------------------------

void UPDATECONTROLS_FMALT(){
     

  switch (ARC+1) {

  case 8: //7 and 9 are skipped when tune lock is on, do not use.
    

    
    break;

  case 10:    
    
     
    break;

  case 3:
    TUNELOCK_TOGGLE();
    detuneAmountCont = analogControls[2];
    //detuneAmountCont = (detuneAmountContCubing*detuneAmountContCubing*detuneAmountContCubing)/1024.0;  
    
//        Serial.print(FMIndex);
//        Serial.print("    ");
//        Serial.print(detuneAmountCont);
//        
//        Serial.print("    ");
//        Serial.println(aInModDetune);

 switch (analogControls[2]>>9){
    case 0: 
      FMTableMM = nothingTable;      
      break;
    case 1: 
      FMTableMM = triTable;     
      break;
    case 2: 
      FMTableMM = AKWF_symetric_0011;     
      break;
    case 3: 
      FMTableMM = FMTableSQ;     
      break;
    case 4: 
      FMTableMM = FMTableSQR;    
      break;
    case 5: 
       FMTableMM = AKWF_symetric_0013;     
      break;
    case 6: 
      FMTableMM = AKWF_symetric_0001;    
      break;
    case 7: 
      FMTableMM = bassTable1;     
      break;
     case 8: 
      FMTableMM = FMTableS180;     
      break;
    case 9: 
      FMTableMM = celloTable;      
      break;
    case 10: 
      FMTableMM = violTable;      
      break;
    case 11: 
      FMTableMM = distoTable;     
      break;
    case 12: 
      FMTableMM = blipTable;     
      break;
    case 13: 
      FMTableMM = FMTableFM98;      
      break;
    case 14: 
      FMTableMM = noiseTable2;       
      break;
    case 15: 
      FMTableMM = noiseTable3;
     
      break;      
    }

    break;

  case 4:
   waveTableMidLink = FMAltWTselMid[analogControls[5]>>9];           
    break;

  case 5:  
waveTable2Link = FMAltWTselLo[analogControls[8]>>9];
    break;

  case 6: //select hi pitch offset
    FMX_HiOffsetContCub = ((analogControls[4])-2048)/164.0 ;
    FMX_HiOffsetCont = FMX_HiOffsetContCub*FMX_HiOffsetContCub*FMX_HiOffsetContCub  ; 

    break;  

  case 1:     
    mixPos = (analogControls[6]>>1); 
    
    FMFixedOn = digitalReadFast(FMFixedSwitch);
    if (FMFixedOn){inputConverterF = 10000;} //sets fixed frequency to suitable LFO.
             
    
    oscMode = (!digitalReadFast(xModeSwitch)<<1)+ digitalReadFast(CZmodeSwitch); 
    break; 

  case 7:
  
    detuneLoOn = digitalReadFast(detuneLoSwitch); 
    detuneMidOn = !digitalReadFast(detuneMidSwitch); 
    detuneHiOn = !digitalReadFast(detuneHiSwitch);    

    break;

  case 2:
    totalratio = totalratio - readingsratio[controlAveragingIndex]; 
    readingsratio[controlAveragingIndex] = analogControls[0]; //fm ratio control smoothing in FM
    totalratio = totalratio + readingsratio[controlAveragingIndex];
    controlAveragingIndex = controlAveragingIndex + 1;
    if (controlAveragingIndex >= numreadingsratio) controlAveragingIndex = 0;
    averageratio = totalratio / numreadingsratio;    
     break; 

  case 9:
    FMIndexCont = (int)(analogControls[1]>>2);    
    
//    else {
//      FMIndexContCubing = (analogControls[8])/1024.0;
//      FMIndexCont = (int) (FMIndexContCubing* FMIndexContCubing*FMIndexContCubing); 
//    }
    
     FMTable = FMWTselFM[analogControls[3]>>9];
    if ((analogControls[3]>>9) == 15) WTShift = 31;
    else WTShift = 23;

    break;   


  }
}


