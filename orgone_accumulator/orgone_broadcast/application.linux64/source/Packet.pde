// ==================================================================
// ask user which COM port to use
// ==================================================================
String COMx, COMlist = "";

final int ASK_FOR_PORT = 0;

void selectSerialPort()
{
  try {
    printArray(Serial.list());
    int i = Serial.list().length;
    if (i != 0) {

      // comment out this section to automatically grab the Last listed serial port
      if (ASK_FOR_PORT != 0) {
        if (i >= 2) {
          for (int j = 0; j < i; ) {
            COMlist += char(j+'a') + " = " + Serial.list()[j];
            if (++j < i) COMlist += ", \n";
          }
          COMx = showInputDialog("Which COM port connects to Orgone Accumulator? (a,b,..):\n"+COMlist);
          if (COMx == null) exit();
          if (COMx.isEmpty()) exit();
          i = int(COMx.toLowerCase().charAt(0) - 'a') + 1;
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

void broadcastPacketReceived()
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

int bytesToInt()
{
  int v = (int)lowByte;
  if (v < 0) v = 256+v;

  return v + (int)highByte * 256;
}

long bytesToLong()
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

void monitorSerialPort() 
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

void sendRequestForData()
{
  port.write(ETX);  //   any character will do
}

