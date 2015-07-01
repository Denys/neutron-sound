void controlEvent(ControlEvent theEvent) 
{
  // pots -------------------------------
  if (theEvent.isController()) { 
    sliderReading = (int)theEvent.controller().value();
    for (int i=0; i<3; ++i) 
      if (theEvent.controller().name()== waveformPotLegend[i]) updatePot(i);

    if (!packetReceivedUpdate) {
      for (int i=0; i<BROADCAST_CV; ++i) 
        if (theEvent.controller().name()== cvLegend[i]) updateCV(i);
    }

    if (theEvent.controller().name()== positionLegend) updatePot(PT_POSITION);
    if (theEvent.controller().name()== effectAmountLegend) updatePot(PT_EFFECT);
    if (theEvent.controller().name()== tuneLegend) updatePot(PT_TUNE);
    if (theEvent.controller().name()== indexLegend) updatePot(PT_INDEX);
    if (theEvent.controller().name()== freqLegend) updatePot(PT_FREQ);
    if (theEvent.controller().name()== modLegend) updatePot(PT_MOD);
  }

  if (theEvent.isGroup()) {
    // 3 waveform drop downs -----------------
    for (int i=0; i<3; ++i) {
      if (theEvent.group().name() == waveformLegend[i]) {
        int v = 256 + int(theEvent.group().value()) * 512;
        if (v != bp.pt[i]) {       
          bp.pt[i] = v;

          return;
        }
      }
    }

    // effect drop down -------------------
    if (theEvent.group().name() == effectLegend) {
      byte v = byte(theEvent.group().value());
      if (v != effectIndex) {     
        effectIndex = v;  
        return;
      }
    }
  }

  // check boxes ------------------------------
  boolean changed = false;
  byte v;
  if (theEvent.isFrom(effectEnabled)) {
    for (int i=0; i<3; ++i) {
      v = (byte)effectEnabled.getArrayValue()[i];
      if (v != bp.sw[SW_DETUNE1+i]) {
        bp.sw[SW_DETUNE1+i] = v; 
        changed = true;
      }
    }
  }

  // monitor oscMode buttons only when NOT reacting to a packet from the OA
  if (!packetReceivedUpdate) {
    v = (byte)oscModeCheckBox.getArrayValue()[0];
    byte v2 = (byte)oscModeCheckBox.getArrayValue()[1];
    byte newOscMode = (byte)(v*2 + (1-v2));
    if (newOscMode != oscModeIndex) {
      oscModeIndex = newOscMode; 
      changed = true;
    }

    v = (byte)oscModeCheckBox.getArrayValue()[2]; 
    if (v != bp.sw[SW_FIX]) {
      bp.sw[SW_FIX] = v; 
      changed = true;
    }
  }
}

// ==================================================================
// on OA: 
//   bPacket.unused[0] = pcounter;
//   bPacket.unused[1] = (uint32_t)inputConverter;
// ==================================================================

void updateFreqCycleTimeDisplays()
{
  float cycleTime = (float)bp.unused[0];
  float freq = (((float)bp.unused[1])/1073741824.0)*(1.0/(((float)bp.unused[2])*0.000001));
  String s;

   s = String.format("%.2f Hz", freq);
  freqDisplay.setText(s);

  s = String.format("%.0f us",cycleTime);
  cycleTimeDisplay.setText(s);
}

