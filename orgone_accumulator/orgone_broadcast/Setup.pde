

// ==================================================================
// create Button, bump xCoord
// ==================================================================
int buttonX, buttonY;

void button(
String name, // button name 
int width, // button width
int id)      // button ID
{
  Button bb = controlP5.addButton(name, 0, buttonX, buttonY, width, 20);
  bb.setId(id);
  buttonX += width + 3;
}

// ==================================================================
// coldstart initialize all widgets, serial port
// ==================================================================

void setup() 
{
  bp = new BroadcastPacket();
  controlP5 = new ControlP5(this);
  fnt = createFont("Arial", 20, true);
  fnt2 = createFont("Arial", 11, true);
  size(FULLWIDTH+21, 535);
  frame.setTitle("Broadcast  version 1.2");
  selectSerialPort();

  // cv sliders -----------------------------
  for (int i=0; i<BROADCAST_CV; ++i) {
    int x = CVX + 7;
    int y = CVY + 15 + i * 18;
    int min = 0, max = 8200;
    switch(i) {
    case 0 : // v/oct 
      max = 4200; 
      break; 
    case 1 :  // position
      min = -4100;
      max = 4100;
      break;
    }
    cvSlider[i] = controlP5.addSlider(cvLegend[i], min, max, 0, x, y, 300, 12);
    cvSlider[i].setColorActive(color(0));
    cvSlider[i].setColorForeground(color(0));
  }

  // unused sliders -----------------------------
  for (int i=0; i<BROADCAST_UNUSED; ++i) {
    int x = UNUSEDX + 7;
    int y = UNUSEDY + 15 + i * 18;
    unusedSlider[i] = controlP5.addSlider(unusedLegend[i], 0,MAX_LONG, 0, x, y, 300, 12);
    unusedSlider[i].setColorActive(color(0));
    unusedSlider[i].setColorForeground(color(0));
  }

  // index slider -----------------------------
  index = controlP5.addSlider(indexLegend, 0, MAX_ADC, 0, MODX + 5, MODY + 22, 300, 12);
  index.captionLabel().setFont(fnt2);
  index.setColorActive(color(0));
  index.setColorForeground(color(0));

  // Freq slider -----------------------------
  freq = controlP5.addSlider(freqLegend, 0, MAX_ADC, 0, MODX + 5, MODY + 40, 300, 12);
  freq.captionLabel().setFont(fnt2);
  freq.setColorActive(color(0));
  freq.setColorForeground(color(0));

  // Mod slider -----------------------------
  mod = controlP5.addSlider(modLegend, 0, MAX_ADC, 0, MODX + 5, MODY + 58, 300, 12);
  mod.captionLabel().setFont(fnt2);
  mod.setColorActive(color(0));
  mod.setColorForeground(color(0));

  // OscMode checkbox --------------------
  oscModeCheckBox = controlP5.addCheckBox("\002\003");
  oscModeCheckBox.setPosition(MODX + 450, MODY + 20);
  oscModeCheckBox.captionLabel().setFont(fnt2);  
  oscModeCheckBox.setColorActive(color(255));
  oscModeCheckBox.setSize(15, 15);
  oscModeCheckBox.setSpacingColumn(40);
  oscModeCheckBox.setItemsPerRow(3);
  oscModeCheckBox.addItem(" X", 0);
  oscModeCheckBox.addItem(" FM", 0);
  oscModeCheckBox.addItem(" Fix", 0);

  // fine tune slider -----------------------------
  tuneFine = controlP5.addSlider(tuneFineLegend, 0, MAX_ADC, 0, TUNEX + 5, TUNEY + 40, 300, 12);
  tuneFine.captionLabel().setFont(fnt2);  
  tuneFine.setColorActive(color(0));
  tuneFine.setColorForeground(color(0));

  // tune slider -----------------------------
  tune = controlP5.addSlider(tuneLegend, 0, MAX_ADC, 0, TUNEX + 5, TUNEY + 22, 300, 12);
  tune.captionLabel().setFont(fnt2);  
  tune.setColorActive(color(0));
  tune.setColorForeground(color(0));

  freqDisplay = controlP5.addTextfield("Freq\002");
  freqDisplay.setPosition(TUNEX+420, TUNEY+20);
  freqDisplay.setSize(70, 20);
  freqDisplay.setColorForeground(100);
  freqDisplay.setColorBackground(color(80, 80, 80));

  cycleTimeDisplay = controlP5.addTextfield("Cycle Time");
  cycleTimeDisplay.setPosition(TUNEX+520, TUNEY+20);
  cycleTimeDisplay.setSize(70, 20);
  cycleTimeDisplay.setColorForeground(100);
  cycleTimeDisplay.setColorBackground(color(80, 80, 80));

  // position slider -----------------------------
  position = controlP5.addSlider(positionLegend, 0, MAX_ADC, 0, WAVEGROUPX + (WAVEGROUPXS+WAVEGROUPXGAP), WAVEGROUPY + WAVEGROUPYS+5, WAVEGROUPXS, 12);
  position.captionLabel().setFont(fnt2);  
  position.setColorActive(color(0));
  position.setColorForeground(color(0));

  // effect slider -----------------------------
  effect = controlP5.addSlider(effectAmountLegend, 0, MAX_ADC, 0, EFFECTX + 5, EFFECTY + 32, 300, 12);
  effect.captionLabel().setFont(fnt2);  
  effect.setColorActive(color(0));
  effect.setColorForeground(color(0));

  // effect drop down ----------------------------  
  effectDropDown = controlP5.addDropdownList(effectLegend);
  effectDropDown.setPosition(EFFECTX + 5, EFFECTY + 25);
  effectDropDown.setSize(220, 300);
  effectDropDown.setBarHeight(10);
  for (int j=0; j<9; ++j) 
    effectDropDown.addItem(effectNames[j], j);
  effectDropDown.setIndex(effectIndex);

  // effect enabled checkboxes --------------------
  effectEnabled = controlP5.addCheckBox("effectEnabled");
  effectEnabled.setPosition(EFFECTX + 450, EFFECTY + 30);
  effectEnabled.setColorActive(color(255));
  effectEnabled.setSize(15, 15);
  effectEnabled.setItemsPerRow(3);
  effectEnabled.setSpacingColumn(5);
  effectEnabled.addItem("\001\001", 0);
  effectEnabled.addItem("\001\002", 1);
  effectEnabled.addItem(" Enabled", 2);

  // waveform panels -----------------------------
  for (int i=0; i<3; ++i) {
    int x = WAVEGROUPX + i * (WAVEGROUPXS+WAVEGROUPXGAP) + 15;
    int y = WAVEGROUPY + 25;
    waveformSlider[i] = controlP5.addSlider(waveformPotLegend[i], 0, MAX_ADC, 0, x, y, WAVEGROUPXS2, 12);
    waveformSlider[i].setColorForeground(color(0));

    waveformDropdown[i] = controlP5.addDropdownList(waveformLegend[i]);
    waveformDropdown[i].setPosition(x, y+26);
    waveformDropdown[i].setSize(WAVEGROUPXS2, 300);
    waveformDropdown[i].setBarHeight(10);

    for (int j=0; j<16; ++j) 
      waveformDropdown[i].addItem(waveNames[j], j);

    waveformDropdown[i].setIndex(0);
  }
}

