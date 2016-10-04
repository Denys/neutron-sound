void HandleNoteOn(byte channel, byte pitch, byte velocity) {

  switch (channel){
  case CHAN:  
    LFO_rate_mult[0] = keyDivs[pitch % 12]; 
    break;    
    case (CHAN+1):  
    LFO_rate_mult[1] = keyDivs[pitch % 12]; 
    break;    
    case (CHAN + 2):  
    LFO_rate_mult[2] = keyDivs[pitch % 12]; 
    break;    
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



