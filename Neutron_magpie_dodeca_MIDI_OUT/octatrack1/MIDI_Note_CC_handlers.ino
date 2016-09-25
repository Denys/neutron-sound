void HandleControlChange (byte channel, byte number, byte value) {
  if (channel == 1 | number < 5) { //ignore wrong channel or CC numbers
    analogWrite(out2pin[number + 6], value); //output on 8,9,10,11
  }
}

void bothNoteOff(byte channel, byte pitch, byte velocity) { //this is called by handle noteoff and note on when velocity = 0
  if (channel == 1) {
    int modNote = whitekeys[pitch % 12]-1;
    if (out2pin[modNote]) {
      analogWrite(out2pin[modNote], 0);
    }
    else analogWrite(A14, 0);
  }
}

void HandleNoteOn(byte channel, byte pitch, byte velocity) {
  if (channel == 1) {
    int modNote = whitekeys[pitch % 12]-1;
    if (velocity != 0) {
      if (out2pin[modNote]) {
        analogWrite(out2pin[modNote], velocity);
      }
      else analogWrite(A14, velocity);    
    }

    else bothNoteOff(channel,pitch,velocity);
  }


  
}
void HandleNoteOff(byte channel, byte pitch, byte velocity) {
  bothNoteOff(channel,pitch,velocity);
}



