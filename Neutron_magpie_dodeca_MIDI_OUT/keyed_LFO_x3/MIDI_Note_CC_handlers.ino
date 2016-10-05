void HandleNoteOn(byte channel, byte pitch, byte velocity) {
if (velocity > 0){
  switch (channel){
  case CHAN:  
    LFO_rate_mult[0] = keyDivs[pitch % 12]; 
    LFO_wavenum1 = velocity >> 5;
    s1 = LFOselLen[LFO_wavenum1];
    LFOsel1 = LFOpool[LFO_wavenum1];
    lfo1.phase = 0;
    break;    
    case (CHAN+1):  
    LFO_rate_mult[1] = keyDivs[pitch % 12]; 
    LFO_wavenum2 = velocity >> 5;
    s2 = LFOselLen[LFO_wavenum2];
    LFOsel2 = LFOpool[LFO_wavenum2];
    lfo2.phase = 0;
    break;    
    case (CHAN + 2):  
    LFO_rate_mult[2] = keyDivs[pitch % 12]; 
    LFO_wavenum3 = velocity >> 5;
    s3 = LFOselLen[LFO_wavenum3];
    LFOsel3 = LFOpool[LFO_wavenum3];
    lfo3.phase = 0;
    break;    
    }    
  }
}

void HandleNoteOff(byte channel, byte pitch, byte velocity) {
//  bothNoteOff(channel, pitch, velocity);
}

void bothNoteOff(byte channel, byte pitch, byte velocity) { //this is called by handle noteoff and note on when velocity = 0
//  if (channel == CHAN) {
//    int modNote = keyDivs[pitch % 12] - 1;
//    if (out2pin[modNote]) {
//      analogWrite(out2pin[modNote], 0);
//    }
//    else analogWrite(A14, 0);
//  }
}

void HandleControlChange (byte channel, byte number, byte value) {
//  if (channel == CHAN && number < 4) { //ignore wrong channel or CC numbers
//    analogWrite(out2pin[number + 7], value); //output on ,9,10,11
//  }
}



