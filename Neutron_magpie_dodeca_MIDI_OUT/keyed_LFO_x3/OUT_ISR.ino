void FASTRUN outUpdateISR_LFOs(void) {
  lfo1.phase = lfo1.phase + lfo1.phase_increment;
  lfo1.wave = (sinTable[lfo1.phase>>23] + 32768)>>4;
  analogWrite(out2pin[0],lfo1.wave);
}

