void DO_INCREMENTS(void) {
  lfo1.phase_increment = LFO_rate_mult[0] * intBPM * rateScaler;
  lfo2.phase_increment = LFO_rate_mult[1] * intBPM * rateScaler;
  lfo3.phase_increment = LFO_rate_mult[2] * intBPM * rateScaler;
}

