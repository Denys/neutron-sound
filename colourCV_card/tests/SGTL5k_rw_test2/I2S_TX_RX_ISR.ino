void i2s0_rx_isr(void) {//this ISR is not used when in sync mode. if it is enabled then audio has glitches
  
  left_sampleIn = int32_t(I2S0_RDR0);       // read channel 0 
  I2S0_RCSR |= I2S_RCSR_FR; // reset fifo fixed "divide" problem.
  
  if (I2S0_RCSR & I2S_RCSR_FEF) I2S0_RCSR |= I2S_RCSR_FEF; // clear if underrun
  if (I2S0_RCSR & I2S_RCSR_SEF) I2S0_RCSR |= I2S_RCSR_SEF; // clear if frame sync error
}


void FASTRUN i2s0_tx_isr(void) {
  if (I2S0_TCSR & I2S_TCSR_FEF) {
    I2S0_TCSR |= I2S_TCSR_FEF;
  }
  while (I2S0_TCSR & I2S_TCSR_FRF) {
    I2S0_TDR0 = left_sampleOut;        
  }
  ramp++;

 
  
  left_sampleOut = ((left_sampleIn * reading12)>>13); //pot on a12 should act as attenuator.
  //left_sampleOut = distoTable[ramp>>7];  //should output the wavetable at ramp speed (not using input)
}
