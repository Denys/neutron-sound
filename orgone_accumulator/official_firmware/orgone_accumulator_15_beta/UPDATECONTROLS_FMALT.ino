void UPDATECONTROLS_FMALT(){
     

  switch (ARC+1) {

  case 7: //7 and 9 are skipped when tune lock is on, do not use.
    

    
    break;

  case 9:    
    
     
    break;

  case 3:
    buh = digitalReadFast(tuneLockSwitch); 
    if (tuneLockOn != buh){
      tuneLockOn = buh;
      digitalWriteFast(LED_TuneLock,tuneLockOn);  
    }      
    detuneAmountCont = analogControls[2];
    //detuneAmountCont = (detuneAmountContCubing*detuneAmountContCubing*detuneAmountContCubing)/1024.0;  
    
//        Serial.print(FMIndex);
//        Serial.print("    ");
//        Serial.print(detuneAmountCont);
//        
//        Serial.print("    ");
//        Serial.println(aInModDetune);

    break;

  case 4:

    switch (analogControls[5]>>9){//select middle wavetable
    case 0: 
      waveTableMidLink = sinTable; 
      break;
    case 1: 
      waveTableMidLink = triTable; 
      break;
    case 2: 
      waveTableMidLink = AKWF_symetric_0001; 
      break;
    case 3: 
      waveTableMidLink = AKWF_symetric_0010; 
      break;
    case 4: 
      waveTableMidLink = scarabTable2; 
      break;
    case 5: 
      waveTableMidLink = AKWF_symetric_0013; 
      break;
    case 6: 
      waveTableMidLink = pnoTable; 
      break;
    case 7: 
      waveTableMidLink = FMTableS180; 
      break; 
     case 8: 
      waveTableMidLink = AKWF_gapsaw_0017; 
      break;
    case 9: 
      waveTableMidLink = FMTableSQR; 
      break;
    case 10: 
      waveTableMidLink = distoTable; 
      break;
    case 11: 
      waveTableMidLink = AKWF_0003; 
      break;
    case 12: 
      waveTableMidLink = voiceTable; 
      break;
    case 13: 
      waveTableMidLink = FMTableFM98; 
      break;
    case 14: 
      waveTableMidLink = noiseTable2; 
      break;      
    case 15: 
      waveTableMidLink = AKWF_squ_0011; 
      break;    
    }      
    break;

  case 5:
    //select wave lo wave
    switch (analogControls[8]>>9){
    case 0: 
      waveTable2Link = sinTable; 
      break;
    case 1: 
      waveTable2Link = triTable; 
      break;
    case 2: 
      waveTable2Link = AKWF_symetric_0001; 
      break;
    case 3: 
      waveTable2Link = AKWF_symetric_0010; 
      break;
    case 4: 
      waveTable2Link = scarabTable2; 
      break;
    case 5: 
      waveTable2Link = AKWF_symetric_0013; 
      break;
    case 6: 
      waveTable2Link = pnoTable; 
      break;
      case 7: 
      waveTable2Link = FMTableS180; 
      break;
    case 8: 
      waveTable2Link = AKWF_gapsaw_0017; 
      break;
    case 9: 
      waveTable2Link = FMTableSQR; 
      break;
    case 10: 
      waveTable2Link = distoTable; 
      break;
    case 11: 
      waveTable2Link = AKWF_0003; 
      break;
    case 12: 
      waveTable2Link = voiceTable; 
      break;
    case 13: 
      waveTable2Link = FMTableFM98; 
      break;
    case 14: 
      waveTable2Link = noiseTable2; 
      break;      
    case 15: 
      waveTable2Link = nothingTable; 
      break;    
    }      
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

  case 8:
  primeDetuneOn = !digitalReadFast(primeSwitch);
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

  case 10:
    FMIndexCont = (int)(analogControls[1]>>2);    
    
//    else {
//      FMIndexContCubing = (analogControls[8])/1024.0;
//      FMIndexCont = (int) (FMIndexContCubing* FMIndexContCubing*FMIndexContCubing); 
//    }
    
     switch (analogControls[3]>>9){
    case 0: 
      FMTable = sinTable;
     WTShift = 23; 
      break;
    case 1: 
      FMTable = triTable;
     WTShift = 23; 
      break;
    case 2: 
      FMTable = AKWF_symetric_0011;
      WTShift = 23;
      break;
    case 3: 
      FMTable = FMTableSQ;
     WTShift = 23; 
      break;
    case 4: 
      FMTable = FMTableSQR;
     WTShift = 23; 
      break;
    case 5: 
       FMTable = AKWF_symetric_0013;
       WTShift = 23;
      break;
    case 6: 
      FMTable = AKWF_symetric_0001;
      WTShift = 23;
      break;
    case 7: 
      FMTable = bassTable1;
     WTShift = 23; 
      break;
     case 8: 
      FMTable = FMTableS180;
     WTShift = 23; 
      break;
    case 9: 
      FMTable = celloTable;
     WTShift = 23; 
      break;
    case 10: 
      FMTable = violTable; 
      WTShift = 23;
      break;
    case 11: 
      FMTable = distoTable;
     WTShift = 23; 
      break;
    case 12: 
      FMTable = blipTable;
     WTShift = 23; 
      break;
    case 13: 
      FMTable = FMTableFM98;
     WTShift = 23; 
      break;
    case 14: 
      FMTable = noiseTable2; 
      WTShift = 23;
      break;
    case 15: 
      FMTable = noiseTable3;
     WTShift = 31; 
      break;      
    }
    

    break;   


  }
}

