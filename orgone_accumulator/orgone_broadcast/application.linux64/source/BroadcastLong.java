import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 
import controlP5.*; 
import static javax.swing.JOptionPane.*; 
import java.awt.event.MouseEvent.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class BroadcastLong extends PApplet {

// Broadcast version 1.0






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

final int BLUECOLOR = color(19, 52, 82);
final int HIGHLIGHTCOLOR = color(255, 0, 0);

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

public void draw() 
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
  float v = (float)bp.pt[PT_POSITION]/8192.0f;
  float[] vc = new float[3];
  float low = 0.5f;    
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

public void updatePot(
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

public void updateCV(
int index) // pot index 0..BROADCAST_CV-1
{
  int old = bp.cv[index];
  bp.cv[index] = sliderReading;
}

// ==================================================================
// keyboard method to alter slider
// ==================================================================

public void changeCV(
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

public void changeEffect(
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

public void changepot(
int index, // pot index 0..BROADCAST_PT-1
int amount) // delta value 
{
  sliderReading = constrain(bp.pt[index] + amount, 0, MAX_ADC);
  updatePot(index);
}

// ==================================================================
// if keycode matches specifed codes, alter pot value 
// ==================================================================

public void keyCommandPot(
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

public void controlEvent(ControlEvent theEvent) 
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
        int v = 256 + PApplet.parseInt(theEvent.group().value()) * 512;
        if (v != bp.pt[i]) {       
          bp.pt[i] = v;

          return;
        }
      }
    }

    // effect drop down -------------------
    if (theEvent.group().name() == effectLegend) {
      byte v = PApplet.parseByte(theEvent.group().value());
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

public void updateFreqCycleTimeDisplays()
{
  float cycleTime = (float)bp.unused[0];
  float freq = (((float)bp.unused[1])/1073741824.0f)*(1.0f/(((float)bp.unused[2])*0.000001f));
  String s;

   s = String.format("%.2f Hz", freq);
  freqDisplay.setText(s);

  s = String.format("%.0f us",cycleTime);
  cycleTimeDisplay.setText(s);
}

// ==================================================================
// ask user which COM port to use
// ==================================================================
String COMx, COMlist = "";

final int ASK_FOR_PORT = 0;

public void selectSerialPort()
{
  try {
    printArray(Serial.list());
    int i = Serial.list().length;
    if (i != 0) {

      // comment out this section to automatically grab the Last listed serial port
      if (ASK_FOR_PORT != 0) {
        if (i >= 2) {
          for (int j = 0; j < i; ) {
            COMlist += PApplet.parseChar(j+'a') + " = " + Serial.list()[j];
            if (++j < i) COMlist += ", \n";
          }
          COMx = showInputDialog("Which COM port connects to Orgone Accumulator? (a,b,..):\n"+COMlist);
          if (COMx == null) exit();
          if (COMx.isEmpty()) exit();
          i = PApplet.parseInt(COMx.toLowerCase().charAt(0) - 'a') + 1;
        }
      }      
      // comment out this section to automatically grab the Last listed serial port      

      String portName = Serial.list()[i-1];
      println(portName);
      port = new Serial(this, portName, 115200);
      port.buffer(10000); // 10303);
    } else {
      showMessageDialog(frame, "Device is not connected to the PC");
      exit();
    }
  }
  catch (Exception e)
  { 
    //showMessageDialog(frame, "COM port is not available (maybe in use by another program)");
    //println("Error:", e);
    exit();
  }
}

// ==================================================================
// received broadcastPacket from OA. update widgets to match
// ==================================================================

public void broadcastPacketReceived()
{
  packetReceivedUpdate = true;

  byte oscModeIndex = bp.oscMode;
  byte newFix = bp.sw[SW_FIX];

  for (int i=0; i<3; ++i) {
    if (bp.sw[SW_DETUNE1+i] != (byte)effectEnabled.getArrayValue()[i]) 
      effectEnabled.toggle(i);
    waveformSlider[i].setValue((float)bp.pt[i]);
  }

  for (int i=0; i<BROADCAST_CV; ++i) 
    cvSlider[i].setValue((float)bp.cv[i]);

  for (int i=0; i<BROADCAST_UNUSED; ++i) 
    unusedSlider[i].setValue((float)bp.unused[i]);

  position.setValue((float)bp.pt[PT_POSITION]);
  effect.setValue((float)bp.pt[PT_EFFECT]);
  tune.setValue((float)bp.pt[PT_TUNE]);
  tuneFine.setValue((float)bp.pt[PT_TUNE_FINE]);
  index.setValue((float)bp.pt[PT_INDEX]);
  freq.setValue((float)bp.pt[PT_FREQ]);
  mod.setValue((float)bp.pt[PT_MOD]);

  effectDropDown.setIndex(bp.effect);

  oscModeCheckBox.deactivateAll();
  if (oscModeIndex >= 2) oscModeCheckBox.activate(0);  
  if ((oscModeIndex & 1)==0) oscModeCheckBox.activate(1);
  if (newFix == 1) oscModeCheckBox.activate(2);

  packetReceivedUpdate = false;

  updateFreqCycleTimeDisplays();
}

// ==================================================================
// convert 2 bytes read from serial port into int value
// convert 4 bytes read from serial port into long value
// ==================================================================

byte lowByte, highByte;
byte[] lb = new byte[4];

public int bytesToInt()
{
  int v = (int)lowByte;
  if (v < 0) v = 256+v;

  return v + (int)highByte * 256;
}

public long bytesToLong()
{
  long total = 0;
  for (int i=0; i<4; ++i) {
    int v = (int)lb[i];
    if (v < 0) v = 256+v;

    total = total * 256 + v;
  }

  return total;
}

// ==================================================================
// monitor serial port for packets from OA
// note: normal ASCII data received will be printed in console
// ==================================================================

int state = 0;
int count;

public void monitorSerialPort() 
{
  if (port == null) return;

  while (port.available () > 0) {
    int val = port.read();
    byte bval = (byte)val;

    // debug packet
    //    int v = (int)bval;
    //    if (v < 0) v = 256+v;
    //    String s = String.format("%02x(%d) ", v, state);
    //    print(s);
    //    if (v==3) println();    

    switch(state) {
    case 0 :
      if (bval == STX) {
        bp.stx = bval;
        state = 1;
      }
      break;
    case 1 :
      if (bval == PACKET_BROADCAST) {
        bp.typeCode = bval;
        state = 2;
        count = 0;
      }
      break;

      // pt ------------------
    case 2 :
      lowByte = bval;
      ++state;
      break;
    case 3 :
      highByte = bval;
      bp.pt[count] = bytesToInt();

      if (++count == BROADCAST_PT) {
        state = 4;
        count = 0;
      } else
        state = 2;
      break;

      // cv ------------------
    case 4 :
      lowByte = bval;
      ++state;
      break;
    case 5 :
      highByte = bval;
      bp.cv[count] = bytesToInt();
      if (++count == BROADCAST_CV) {
        state = 6;
        count = 0;
      } else
        state = 4;
      break;

      // sw ------------------
    case 6 :
      bp.sw[count] = bval;
      if (++count == BROADCAST_SW) {
        state = 7;
        count = 0;
      }
      break;

      // unused (long ints) ------------------
    case 7 :
      lb[3] = bval;
      ++state;
      break;
    case 8 :
      lb[2] = bval;
      ++state;
      break;
    case 9 :
      lb[1] = bval;
      ++state;
      break;
    case 10 :
      lb[0] = bval;
      bp.unused[count] = bytesToLong();
      if (++count == BROADCAST_UNUSED) 
        state = 11;
      else
        state = 7;
      break;

      // effect, oscMode --------------
    case 11 :
      bp.effect = bval;
      ++state;
      break;
    case 12 :
      bp.oscMode = bval;
      ++state;
      break;

    case 13 :
      if (bval == ETX) 
        broadcastPacketReceived();
      state = 0;
      break;
    }
  }
}

// ---------------------------------------

public void sendRequestForData()
{
  port.write(ETX);  //   any character will do
}



// ==================================================================
// create Button, bump xCoord
// ==================================================================
int buttonX, buttonY;

public void button(
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

public void setup() 
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

  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "BroadcastLong" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
