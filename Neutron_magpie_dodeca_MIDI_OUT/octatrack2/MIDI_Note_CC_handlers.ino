void HandleNoteOn(byte channel, byte pitch, byte velocity) {
  if (channel == CHAN) {    
    if (velocity != 0) {
        analogWrite(out2pin[2], velocity<<5);
        analogWrite(A14, pitch<<5);
        analogWrite(out2pin[0], 127<<5); 
        numNotes ++;
      }
      else bothNoteOff(channel,pitch,velocity);   
    }    
  }

void HandleNoteOff(byte channel, byte pitch, byte velocity) {
  bothNoteOff(channel,pitch,velocity);
}  

//this is called by handle noteoff and note on when velocity = 0 not part of MIDI lib.
void bothNoteOff(byte channel, byte pitch, byte velocity) { 
  if (channel == CHAN) {
    numNotes --;
    if (numNotes < 1){//only end gate if all notes are off.
      analogWrite(out2pin[2], 0);
      analogWrite(A14, 0);
      analogWrite(out2pin[0], 0); 
      numNotes = 0; //safety feature in case too many note offs recieved.
    }    
  }
}
  
void HandlePitchBend (byte channel, int bend){
  if (channel == CHAN){
  Serial.println(bend);//to be fixed add pb to note value
  }
}

void HandleControlChange (byte channel, byte number, byte value){
  if (channel == CHAN){
  for (int i = 3;i < 13;i ++){
    if (number == cc2out[i]){           
    analogWrite(out2pin[i],value<<5);    
      }
    }
  } 
}




