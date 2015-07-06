// Broadcast version 1.0

import processing.serial.*;
import controlP5.*;
import static javax.swing.JOptionPane.*;
import java.awt.event.MouseEvent.*;

PFont fnt, fnt2;         
Serial port;
ControlP5 controlP5;

final int WAVEGROUPX = 10;    // panel positions and sizes
final int WAVEGROUPY = 10;
final int WAVEGROUPXS = 200;
final int WAVEGROUPXS2 = WAVEGROUPXS-30;
final int WAVEGROUPXGAP = 5;
final int WAVEGROUPYS = 55;
final int FULLWIDTH = (WAVEGROUPXS+4)*3;

final int EFFECTX = WAVEGROUPX;
final int EFFECTY = WAVEGROUPY + WAVEGROUPYS + 30;
final int EFFECTXS = FULLWIDTH;
final int EFFECTXS2 = EFFECTXS-30;
final int EFFECTYS = 45;

final int TUNEX = WAVEGROUPX;
final int TUNEY = EFFECTY + EFFECTYS + 15;
final int TUNEXS = FULLWIDTH;
final int TUNEXS2 = TUNEXS-30;
final int TUNEYS = 60;

final int MODX = WAVEGROUPX;
final int MODY = TUNEY + TUNEYS + 15;
final int MODXS = FULLWIDTH;
final int MODXS2 = MODXS-30;
final int MODYS = 72;

final int CVX = WAVEGROUPX;
final int CVY = MODY + MODYS + 15;
final int CVXS = FULLWIDTH;
final int CVXS2 = CVXS-30;
final int CVYS = 100;
final int CVGX  = CVX + 370;
final int CVGY  = CVY + 15;

final int UNUSEDX = WAVEGROUPX;
final int UNUSEDY = CVY + CVYS + 15;
final int UNUSEDXS = FULLWIDTH;
final int UNUSEDXS2 = UNUSEDXS-30;
final int UNUSEDYS = 90;
final int UNUSEDGX  = UNUSEDX + 370;
final int UNUSEDGY  = UNUSEDY + 15;

final color BLUECOLOR = color(19, 52, 82);
final color HIGHLIGHTCOLOR = color(255, 0, 0);

final byte STX = 2;
final byte ETX = 3;
final byte PACKET_BROADCAST = 0x58; // packet type code

final int MAX_ADC = 8191;
final int MAX_LONG = 0x7FFFFFFF;

final int PT_WAVEFORM1 = 0;  // fields in control p[acket
final int PT_WAVEFORM2 = 1;
final int PT_WAVEFORM3 = 2;
final int PT_MOD       = 3;
final int PT_TUNE      = 4;
final int PT_TUNE_FINE = 5;
final int PT_POSITION = 6;
final int PT_EFFECT = 7;
final int PT_INDEX = 8;
final int PT_FREQ = 9;
final int BROADCAST_PT = 10;

final int CV_VOCT_IN = 0;
final int CV_POSITION_IN = 1;
final int CV_DETUNE_IN = 2;
final int CV_INDEX_IN = 3;
final int CV_FREQ_IN = 4;
final int BROADCAST_CV = 5;

final int SW_DETUNE1 = 0;
final int SW_DETUNE2 = 1;
final int SW_DETUNE3 = 2;
final int SW_FIX     = 3;
final int SW_TUNELOCK= 4;
final int BROADCAST_SW = 5;

final int BROADCAST_UNUSED = 4;

class BroadcastPacket { 
  byte  stx;
  byte  typeCode;
  int[] pt = new int[BROADCAST_PT];   // 18 bytes
  int[] cv = new int[BROADCAST_CV];   // 12 
  byte[] sw = new byte[BROADCAST_SW]; // 5
  long[] unused = new long[BROADCAST_UNUSED];   // 10*2
  byte effect;
  byte oscMode; 
  byte  etx;
}

BroadcastPacket bp;

Slider[] waveformSlider = new Slider[3];
Slider[] cvSlider = new Slider[BROADCAST_CV];
Slider[] unusedSlider = new Slider[BROADCAST_UNUSED];
Slider position, effect, tune, tuneFine, index, freq, mod;
DropdownList[] waveformDropdown = new DropdownList[3];
DropdownList effectDropDown;
CheckBox effectEnabled, tuneLock, oscModeCheckBox;
Textfield freqDisplay, cycleTimeDisplay;

byte oscModeIndex = 0;
byte effectIndex = 0;

int requestDataCount = 0;
final int REQUEST_TIME = 25;  // #draw cycles before request data

// --------------------------------------------------

final String[] waveformLegend = { 
  "Waveform 1", "Waveform 2", "Waveform 3"
};
final String[] waveformPotLegend = {  
  "\001", "\002", "\003"
};
final String[] cvLegend = { 
  "V/Oct", "P-CV", "D-CV", "I-CV", "F-CV"
};
final String[] unusedLegend = { 
  "0\001", "1\001", "2\001", "3\001", "4\001", 
  "5\001", "6\001", "7\001", "8\001", "9\001",
};
final String[] waveNames = { 
  " 1: Sine", " 2: Triangle", " 3: Saw", " 4: Scarab 1", " 5: Scarab 2", " 6: Pulse", " 7: Piano", " 8: Bass 1", 
  " 9: Bass 2", "10: Cello", "11: Viola", "12: Distortion", "13: Blip", "14: Voice", "15: Noise 1", "16: Noise 2"
};
final String[] effectNames = { 
  "Orgone detune", 
  "Orgone detune with Prime", 
  "Delay", 
  "Pulsar", 
  "Bit Crush", 
  "Wave Folding", 
  "ModMod", 
  "Chords (equal temperment)", 
  "Chords (just)"
};

final String positionLegend = "Position";
final String effectLegend = "\004";
final String effectAmountLegend = "Amount";
final String tuneLegend = "Tune";
final String tuneFineLegend = "Fine Tune";
final String indexLegend = "Index";
final String freqLegend = "Freq";
final String modLegend = "Mod waveform";
final String[] effectEnabledLegend = { 
  "\005", "\006", "\007"
};

// ==================================================================
// draw everything
// ==================================================================

void draw() 
{
  background(80, 80, 80);

  // panel frames -----------
  fill(100);
  rect(WAVEGROUPX-5, WAVEGROUPY-5, (WAVEGROUPXS+7)*3, WAVEGROUPYS+25);
  rect(EFFECTX-5, EFFECTY-5, EFFECTXS+9, EFFECTYS+10);
  rect(TUNEX-5, TUNEY-5, TUNEXS+9, TUNEYS+10);
  rect(MODX-5, MODY-5, MODXS+9, MODYS+10);
  rect(CVX-5, CVY-5, CVXS+9, CVYS+10);
  rect(UNUSEDX-5, UNUSEDY-5, UNUSEDXS+9, UNUSEDYS+10);

  // color waveform panels according to 'position pot'
  float v = (float)bp.pt[PT_POSITION]/8192.0;
  float[] vc = new float[3];
  float low = 0.5;    
  vc[0] = constrain(low-v, 0, 1); 
  vc[1] = constrain(low-abs(v-low), 0, 1);
  vc[2] = constrain(v-low, 0, 1);

  for (int i=0; i<3; ++i) {
    int x = WAVEGROUPX + i * (WAVEGROUPXS+WAVEGROUPXGAP);
    int y = WAVEGROUPY;
    fill(128, 128+vc[i]*128, 128);
    rect(x, y, WAVEGROUPXS, WAVEGROUPYS);
  }

  // panel legends -------------
  for (int i=0; i<3; ++i) {
    int x = WAVEGROUPX + i * (WAVEGROUPXS+WAVEGROUPXGAP);
    int y = WAVEGROUPY;
    textFont(fnt, 14);
    fill(0);
    text(waveformLegend[i], x+45, y+16);
  }

  text("Effects", EFFECTX + 280, EFFECTY+10);
  text("Tune", TUNEX + 285, TUNEY+10);
  text("Modulation", MODX + 270, MODY+10);
  text("Control Voltages", CVX + 270, CVY+10);
  text("Unused", UNUSEDX + 270, UNUSEDY+10);

  monitorSerialPort();

  // periodically request new data
  if (++requestDataCount >= REQUEST_TIME) {
    requestDataCount = 0;
    sendRequestForData();
  }
}

// ==================================================================
// Pot slider callback from event handler
// update packet contents, send to OA (if slider was altered)
// update companion wavetable drop down for waveform sliders
// ==================================================================

int sliderReading;
boolean backDoorUpdate = false;

void updatePot(
int pIndex) // pot index 0..BROADCAST_PT-1
{
  if (backDoorUpdate) return;

  int old = bp.pt[pIndex];
  bp.pt[pIndex] = sliderReading;

  backDoorUpdate = true;

  switch(pIndex) {
  case PT_WAVEFORM1 :
  case PT_WAVEFORM2 :
  case PT_WAVEFORM3 :
    pIndex -= PT_WAVEFORM1;
    waveformDropdown[pIndex].setIndex(sliderReading/512);    
    waveformSlider[pIndex].setValue((float)bp.pt[pIndex]);
    break;
  case PT_POSITION : 
    position.setValue((float)bp.pt[PT_POSITION]); 
    break;
  case PT_EFFECT    :  
    effect.setValue((float)bp.pt[PT_EFFECT]); 
    break;
  case PT_TUNE :  
    tune.setValue((float)bp.pt[PT_TUNE]); 
    break;
  case PT_TUNE_FINE :  
    tuneFine.setValue((float)bp.pt[PT_TUNE_FINE]); 
    break;
  case PT_INDEX :  
    index.setValue((float)bp.pt[PT_INDEX]); 
    break;
  case PT_FREQ : 
    freq.setValue((float)bp.pt[PT_FREQ]); 
    break;
  case PT_MOD :  
    mod.setValue((float)bp.pt[PT_MOD]); 
    break;
  }

  backDoorUpdate = false;
}

// ==================================================================
// CV slider callback from event handler
// update packet contents, send to OA (if slider was altered)
// ==================================================================

void updateCV(
int index) // pot index 0..BROADCAST_CV-1
{
  int old = bp.cv[index];
  bp.cv[index] = sliderReading;
}

// ==================================================================
// keyboard method to alter slider
// ==================================================================

void changeCV(
int index, // pot index 0..BROADCAST_CV-1
int amount)  // delta value 
{
  sliderReading = constrain(bp.cv[index] + amount, 0, MAX_ADC);
  updateCV(index);
}

// ==================================================================
// event handler
// ==================================================================

// marker used when we want to update widget vales without triggering a packet send
boolean packetReceivedUpdate = false;

// ==================================================================
// alter 'effect' field by specified amount (round robin)
// update companion dropdownlist
// send updated packet to OA
// ==================================================================

void changeEffect(
int amount) // delta amount
{
  int v = bp.effect + amount;
  if (v < 0) v = 7; 
  else if (v > 7) v = 0;

  bp.effect = (byte)v;

  effectDropDown.setIndex(bp.effect);
}

// ==================================================================
// keyboard method to alter slider
// ==================================================================

void changepot(
int index, // pot index 0..BROADCAST_PT-1
int amount) // delta value 
{
  sliderReading = constrain(bp.pt[index] + amount, 0, MAX_ADC);
  updatePot(index);
}

// ==================================================================
// if keycode matches specifed codes, alter pot value 
// ==================================================================

void keyCommandPot(
int potIndex, // packet p[] index (0..BROADCAST_PT-1) 
int keyCode, // keycode just pressed 
char lower, // keycode to match for decrease command
char raise, // keycode to match for increase command
int amount)  // delta amount
{
  if (keyCode == lower)
    changepot(potIndex, -amount);
  if (keyCode == raise)
    changepot(potIndex, +amount);
}

