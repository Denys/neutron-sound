void UPDATECONTROLS_CZ(){

  switch (ARC+1) {

  case 8:

    break;

  case 10:   

    Serial.println((float)o1.phase_increment/51550); 
    //outputs the frequency on USB serial. tune lock, FM and X must be off



    break;

  case 3:
   
    detuneAmountCont = analogControls[2];
    //detuneAmountCont = (detuneAmountContCubing*detuneAmountContCubing*detuneAmountContCubing)/1024.0; 
    
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
      waveTable2Link = voiceTable; 
      break;
    case 14: 
      waveTable2Link = primeTable; 
      break;
    case 15: 
      waveTable2Link = nothingTable; 
      break;

    }      
    break;

  case 6: //select hi wave
    switch (analogControls[4]>>9){
    case 0: 
      waveTableLink = sinTable; 
      break;
    case 1: 
      waveTableLink = triTable; 
      break;
    case 2: 
      waveTableLink = sawTable; 
      break;
    case 3: 
      waveTableLink = scarabTable1; 
      break;
    case 4: 
      waveTableLink = scarabTable2; 
      break;
    case 5: 
      waveTableLink = pulseTable; //change
      break;
    case 6: 
      waveTableLink = pnoTable; 
      break;
    case 7: 
      waveTableLink = bassTable1; 
      break;
    case 8: 
      waveTableLink = bassTable2; 
      break;
    case 9: 
      waveTableLink = celloTable; 
      break;
    case 10: 
      waveTableLink = violTable; 
      break;
    case 11: 
      waveTableLink = distoTable; 
      break;
    case 12: 
      waveTableLink = blipTable; //change
      break;
    case 13: 
      waveTableLink = voiceTable; 
      break;
    case 14: 
      waveTableLink = noiseTable2; 
      break;
    case 15: 
      waveTableLink = noiseTable; 
      break;    
    }

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


    switch (analogControls[3]>>9){
    case 0: 
      FMTable = sinTable; 
      break;
    case 1: 
      FMTable = triTable; 
      break;
    case 2: 
      FMTable = FMTableS180; 
      break;
    case 3: 
      FMTable = FMTableSQ; 
      break;
    case 4: 
      FMTable = FMTableSQR; 
      break;
    case 5: 
      FMTable = AKWF_0003; 
      break;
    case 6: 
      FMTable = pnoTable; 
      break;
    case 7: 
      FMTable = bassTable1; 
      break;
    case 8: 
      FMTable = bassTable2; 
      break;
    case 9: 
      FMTable = celloTable; 
      break;
    case 10: 
      FMTable = violTable; 
      break;
    case 11: 
      FMTable = FMTableFM98; 
      break;
    case 12: 
      FMTable = FMTablehvoice26; 
      break;
    case 13: 
      FMTable = AKWF_squ_0011; 
      break;
    case 14: 
      FMTable = noiseTable2;//FMTableCZ;
      break;
    case 15: 
      FMTable = noiseTable; 
      break;    
    }


    break;   


  }
}


