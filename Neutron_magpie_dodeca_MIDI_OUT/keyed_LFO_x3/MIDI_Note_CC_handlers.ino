void HandleNoteOn(byte channel, byte pitch, byte velocity) {
if (velocity > 0){
  switch (channel){
    
  case CHAN:  
    LFO_rate_mult[0] = keyDivs[pitch % 12]; 
    v1 = velocity;
    s1 = LFOselLen[LFO_wavenum1];
    LFOsel1 = LFOpool[LFO_wavenum1];
    lfo1.phase = lfo1.phaseOffset;
    break;  
      
    case (CHAN+1):  
    LFO_rate_mult[1] = keyDivs[pitch % 12]; 
    v2 = velocity;
    s2 = LFOselLen[LFO_wavenum2];
    LFOsel2 = LFOpool[LFO_wavenum2];
    lfo2.phase = lfo2.phaseOffset;
    break;   
     
    case (CHAN + 2):      
    LFO_rate_mult[2] = keyDivs[pitch % 12]; 
    v3 = velocity;
    s3 = LFOselLen[LFO_wavenum3];
    LFOsel3 = LFOpool[LFO_wavenum3];
    lfo3.phase = lfo3.phaseOffset;
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
  switch (channel){
  case CHAN: 
  if (number == CC_A) lfo1.phaseOffset = value << 25;
 if (number == CC_B) LFO_wavenum1 = value >> 5;
 break;
 case (CHAN+1): 
 if (number == CC_A) lfo2.phaseOffset = value << 25;
 if (number == CC_B) LFO_wavenum2 = value >> 5;
 break;
 case (CHAN+2): 
 if (number == CC_A) lfo3.phaseOffset = value << 25;
 if (number == CC_B) LFO_wavenum3 = value >> 5;
 break;
  }
}



