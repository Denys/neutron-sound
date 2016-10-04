void FASTRUN outUpdateISR_LFOs(void) {
  lfo1.phase = lfo1.phase + lfo1.phase_increment;
  lfo1.wave1 = (sinTable[lfo1.phase>>23] + 32768)>>4;
  lfo1.wave2 = (sinTable[(lfo1.phase + 1073741824)>>23] + 32768)>>4;
  lfo1.wave3 = 4095 - lfo1.wave1;
  lfo1.wave4 = 4095 - lfo1.wave2;
  analogWrite(out2pin[0],lfo1.wave1);
  analogWrite(A14,lfo1.wave2);
  analogWrite(out2pin[3],lfo1.wave3);
  analogWrite(out2pin[2],lfo1.wave4);

  
  lfo2.phase = lfo2.phase + lfo2.phase_increment;
  lfo2.wave1 = (sinTable[lfo2.phase>>23] + 32768)>>4;
  lfo2.wave2 = (sinTable[(lfo2.phase + 1073741824)>>23] + 32768)>>4;
  lfo2.wave3 = 4095 - lfo2.wave1;
  lfo2.wave4 = 4095 - lfo2.wave2;
  analogWrite(out2pin[4],lfo2.wave1);
  analogWrite(out2pin[5],lfo2.wave2);
  analogWrite(out2pin[7],lfo2.wave3);
  analogWrite(out2pin[6],lfo2.wave4);

  
  lfo3.phase = lfo3.phase + lfo3.phase_increment;
  lfo3.wave1 = (sinTable[lfo3.phase>>23] + 32768)>>4;
  lfo3.wave2 = (sinTable[(lfo3.phase + 1073741824)>>23] + 32768)>>4;
  lfo3.wave3 = 4095 - lfo3.wave1;
  lfo3.wave4 = 4095 - lfo3.wave2;
  analogWrite(out2pin[8],lfo3.wave1);
  analogWrite(out2pin[9],lfo3.wave2);
  analogWrite(out2pin[11],lfo3.wave3);
  analogWrite(out2pin[10],lfo3.wave4);

 
}

