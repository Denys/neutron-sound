void UPDATECONTROLS_CZALT(){

  switch (ARC+1) {

  case 8:
         
    break;

  case 10:    
    
     
    break;

  case 3:
    buh = digitalReadFast(tuneLockSwitch);
    if (tuneLockOn != buh){
      tuneLockOn = buh;
      if (tuneLockOn == 1) {digitalWriteFast(LED_TuneLock,1);}
      else {digitalWriteFast(LED_TuneLock,0);}      
    }          
    detuneAmountCont = analogControls[2];
    //detuneAmountCont = (detuneAmountContCubing*detuneAmountContCubing*detuneAmountContCubing)/1024.0; 
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
      waveTableMidLink = sawTable; 
      break;
    case 3: 
      waveTableMidLink = scarabTable1; 
      break;
    case 4: 
      waveTableMidLink = scarabTable2; 
      break;
    case 5: 
      waveTableMidLink = pulseTable; 
      break;
    case 6: 
      waveTableMidLink = pnoTable; 
      break;
    case 7: 
      waveTableMidLink = bassTable1; 
      break;
    case 8: 
      waveTableMidLink = bassTable2; 
      break;
    case 9: 
      waveTableMidLink = celloTable; 
      break;
    case 10: 
      waveTableMidLink = violTable; 
      break;
    case 11: 
      waveTableMidLink = distoTable; 
      break;
    case 12: 
      waveTableMidLink = blipTable; 
      break;
    case 13: 
      waveTableMidLink = voiceTable; 
      break;
    case 14: 
      waveTableMidLink = noiseTable2; 
      break;
    case 15: 
      waveTableMidLink = noiseTable; 
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
      waveTable2Link = sawTable; 
      break;
    case 3: 
      waveTable2Link = scarabTable1; 
      break;
    case 4: 
      waveTable2Link = scarabTable2; 
      break;
    case 5: 
      waveTable2Link = pulseTable; 
      break;
    case 6: 
      waveTable2Link = pnoTable; 
      break;
    case 7: 
      waveTable2Link = bassTable1; 
      break;
    case 8: 
      waveTable2Link = bassTable2; 
      break;
    case 9: 
      waveTable2Link = celloTable; 
      break;
    case 10: 
      waveTable2Link = violTable; 
      break;
    case 11: 
      waveTable2Link = distoTable; 
      break;
    case 12: 
      waveTable2Link = blipTable; 
      break;
    case 13: 
      waveTable2Link = noiseTable2; 
      break;
    case 14: 
      waveTable2Link = noiseTable; 
      break;
    case 15: 
      waveTable2Link = nothingTable; 
      break;
    
    }      
    break;

  case 6: //select hi wave
   
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
  primeDetuneOn = !digitalReadFast(primeSwitch);
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
   
    
//    else {
//      FMIndexContCubing = (analogControls[8])/1024.0;
//      FMIndexCont = (int) (FMIndexContCubing* FMIndexContCubing*FMIndexContCubing); 
//    }
    
     switch (analogControls[3]>>9){
       case 0: 
      FMTable = sinTable;
      FMTableAMX = DCTable; 
      break;
    case 1: 
      FMTable = sinTable;
      FMTableAMX = sinTable; 
      break;
    case 2: 
      FMTable = triTable;
      FMTableAMX = FMTableSQ; 
      break;    
    case 3: 
      FMTable = FMTableAMX = FMTableSQ; 
      break;
    case 4: 
      FMTable = FMTableAMX = FMTableSQR; 
      break;
    case 5: 
      FMTable = FMTableAMX = AKWF_0003; 
      break;
    case 6: 
      FMTable = FMTableAMX = pnoTable; 
      break;
    case 7: 
      FMTable = FMTableAMX = bassTable1; 
      break;
    case 8: 
      FMTable = FMTableAMX = bassTable2; 
      break;
    case 9: 
      FMTable = FMTableAMX = celloTable; 
      break;
    case 10: 
      FMTable = FMTableAMX = violTable; 
      break;
    case 11: 
      FMTable = FMTableAMX = FMTableFM98; 
      break;
    case 12: 
      FMTable = FMTableAMX = FMTablehvoice26; 
      break;
    case 13: 
      FMTable = AKWF_squ_0011;
      FMTableAMX = sinTable; 
      break;
    case 14: 
      FMTable = FMTableAMX = noiseTable2;//FMTableCZ;
      break;
    case 15: 
      FMTable = FMTableAMX = noiseTable; 
      break;    
    }
    

    break;   


  }
}

