void FASTRUN outUpdateISR_LFOs(void) {
  lfo1.phase = lfo1.phase + lfo1.phase_increment;
  lfo1.wave1 = (((LFOsel1[lfo1.phase>>s1]*v1)>>7) + 32768)>>4;
  lfo1.wave2 = (((LFOsel1[(lfo1.phase + qPhase)>>s1]*v1)>>7) + 32768)>>4;
  lfo1.wave3 = (((LFOsel1[(lfo1.phase + (qPhase<<1))>>s1]*v1)>>7) + 32768)>>4;
  lfo1.wave4 = (((LFOsel1[(lfo1.phase + qPhase*3)>>s1]*v1)>>7) + 32768)>>4;
  analogWrite(out2pin[0],lfo1.wave1);
  analogWrite(A14,lfo1.wave2);
  analogWrite(out2pin[3],lfo1.wave3);
  analogWrite(out2pin[2],lfo1.wave4);

  
  lfo2.phase = lfo2.phase + lfo2.phase_increment;
  lfo2.wave1 = (((LFOsel2[lfo2.phase>>s2]*v2)>>7) + 32768)>>4;
  lfo2.wave2 = (((LFOsel2[(lfo2.phase + qPhase)>>s2]*v2)>>7) + 32768)>>4;
  lfo2.wave3 = (((LFOsel2[(lfo2.phase + (qPhase<<1))>>s2]*v2)>>7) + 32768)>>4;
  lfo2.wave4 = (((LFOsel2[(lfo2.phase + qPhase*3)>>s2]*v2)>>7) + 32768)>>4;
  analogWrite(out2pin[4],lfo2.wave1);
  analogWrite(out2pin[5],lfo2.wave2);
  analogWrite(out2pin[7],lfo2.wave3);
  analogWrite(out2pin[6],lfo2.wave4);

  
  lfo3.phase = lfo3.phase + lfo3.phase_increment;
  lfo3.wave1 = (((LFOsel3[lfo3.phase>>s3]*v3)>>7) + 32768)>>4;
  lfo3.wave2 = (((LFOsel3[(lfo3.phase + qPhase)>>s3]*v3)>>7) + 32768)>>4;
  lfo3.wave3 = (((LFOsel3[(lfo3.phase + (qPhase<<1))>>s3]*v3)>>7) + 32768)>>4;
  lfo3.wave4 = (((LFOsel3[(lfo3.phase + qPhase*3)>>s3]*v3)>>7) + 32768)>>4;
  analogWrite(out2pin[8],lfo3.wave1);
  analogWrite(out2pin[9],lfo3.wave2);
  analogWrite(out2pin[11],lfo3.wave3);
  analogWrite(out2pin[10],lfo3.wave4);

 
}

