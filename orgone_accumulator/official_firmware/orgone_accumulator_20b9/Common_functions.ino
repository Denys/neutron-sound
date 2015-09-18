void WRITE2EEPROM() { //only write if it is different
  if (FXi != EEPROM.read(0))EEPROM.write(0, FXi);
  if (IsHW2) {
    if (detuneLoOn != EEPROM.read(1))EEPROM.write(1, detuneLoOn);
    if (detuneMidOn != EEPROM.read(2))EEPROM.write(2, detuneMidOn);
    if (detuneHiOn != EEPROM.read(3))EEPROM.write(3, detuneHiOn);
    if (xModeOn != EEPROM.read(4))EEPROM.write(4, xModeOn);
    if (FMmodeOn != EEPROM.read(5))EEPROM.write(5, FMmodeOn);
    if (FMFixedOn != EEPROM.read(6))EEPROM.write(6, FMFixedOn);
    if (pulsarOn != EEPROM.read(7))EEPROM.write(7, pulsarOn);
  }
}

void ARMED_FX() {
  if (detuneLoButton.update()) {
    if (detuneLoButton.fallingEdge()) {
      FX = 0;
      SELECT_ISRS();
    }
  }
  if (pulsarButton.update()) {
    if (pulsarButton.fallingEdge()) {
      FX = 1;

      SELECT_ISRS();
    }
  }
  if (detuneMidButton.update()) {
    if (detuneMidButton.fallingEdge()) {
      FX = 2;

      SELECT_ISRS();
    }
  }
  if (FXCycleButton.update()) {
    if (FXCycleButton.fallingEdge()) {
      FX = 3;
      SELECT_ISRS();
    }
  }
  if (detuneHiButton.update()) {
    if (detuneHiButton.fallingEdge()) {
      FX = 4;
      SELECT_ISRS();
    }
  }
  if (xModeButton.update()) {
    if (xModeButton.fallingEdge()) {
      FX = 5;
      SELECT_ISRS();
    }
  }
  if (FMmodeButton.update()) {
    if (FMmodeButton.fallingEdge()) {
      FX = 6;
      SELECT_ISRS();
    }
  }
  if (FMFixedButton.update()) {
    if (FMFixedButton.fallingEdge()) {
      FX = 7;
      SELECT_ISRS();
    }
  }
}



void READ_POTS() {

  if (IsHW2 == 0) {
    analogControls[ARC] = analogRead(potPinTable_DIY[ARC]);
  }//step through control knob readings one per cycle, humans are slow
  else
  {
    analogControls[ARC] = analogRead(potPinTable_ret[ARC]);
  }
}


void TUNELOCK_TOGGLE()
{
  if (IsHW2 == 0) {

    buh = digitalReadFast(tuneLockSwitch);
    if (TUNELOCK_SWITCH == 0) {
      if (tuneLockOn != buh) {
        tuneLockOn = buh;
        digitalWriteFast(LED_TuneLock, tuneLockOn);
        
      }
    }
    else {
      if (pulsarOn != buh) {
        pulsarOn = buh;
        digitalWriteFast(LED_TuneLock, pulsarOn);
        SELECT_ISRS();
      }
    }
  }

  else {
    if (tuneLockButton.update()) {
      if (tuneLockButton.fallingEdge()) {
        tuneLockOn = !tuneLockOn;

      }
    }
  }

}

void FX_TOGGLES() {
  if (IsHW2 == 0) {
    detuneLoOn = digitalReadFast(detuneLoSwitch);
    detuneMidOn = !digitalReadFast(detuneMidSwitch);
    detuneHiOn = !digitalReadFast(detuneHiSwitch);
  }
  else if (FXSelArmed[0] == 0) {

    if (detuneLoButton.update()) {
      if (detuneLoButton.fallingEdge()) {
        detuneLoOn = !detuneLoOn;
        QUIET_MCD = QUIET_MST;
      }
    }

    if (detuneMidButton.update()) {
      if (detuneMidButton.fallingEdge()) {
        detuneMidOn = !detuneMidOn;
        QUIET_MCD = QUIET_MST;
      }
    }

    if (detuneHiButton.update()) {
      if (detuneHiButton.fallingEdge()) {
        detuneHiOn = !detuneHiOn;
        QUIET_MCD = QUIET_MST;
      }
    }

    if (pulsarButton.update()) {
      if (pulsarButton.fallingEdge()) {
        pulsarOn = ! pulsarOn;
        QUIET_MCD = QUIET_MST;
        SELECT_ISRS();
      }
    }

  }
}

void OSC_MODE_TOGGLES() {
  if (IsHW2 == 0) {
    FMFixedOn = digitalReadFast(FMFixedSwitch);
    xModeOn = !(digitalReadFast(xModeSwitch));
    FMmodeOn = !(digitalReadFast(FMmodeSwitch));
  }

  else if (FXSelArmed[0] == 0) {
    if (FMFixedButton.update()) {
      if (FMFixedButton.fallingEdge()) {
        FMFixedOn = !FMFixedOn;
        QUIET_MCD = QUIET_MST;
      }
    }

    if (FMmodeButton.update()) {
      if (FMmodeButton.fallingEdge()) {
        FMmodeOn = !FMmodeOn;
        QUIET_MCD = QUIET_MST;
      }
    }

    if (xModeButton.update()) {
      if (xModeButton.fallingEdge()) {
        xModeOn = !xModeOn;
        QUIET_MCD = QUIET_MST;
      }
    }

    
  }
  oscMode = ((xModeOn) << 1) + (!FMmodeOn);
}

void SELECT_ISRS() {

  if (IsHW2 == 0) {
    LED_MCD = LED_MST;
  }

  FXSelArmed[0] = 0;
  FXchangedSAVE = 1;
  chord[0] = chord[1] = chord[2] = chord[3] = 1.0;
  detune[0] = detune[1] = detune[2] = detune[3] = 0;

  if (!pulsarOn) {
    switch (FX) {
      case 0:
        outUpdateTimer.end();
        o3.phaseOffset = o1.phaseOffset = 0;
        outUpdateTimer.begin(outUpdateISR_MAIN, ISRrate);

        break;
      case 1:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_WAVE_TWIN, ISRrate);

        break;
      case 2:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_DISTS, ISRrate);
        break;
      case 3:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_DISTS, ISRrate);
        break;
      case 4:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_MAIN, ISRrate);
        break;
      case 5:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_SPECTRUM, ISRrate);
        break;
      case 6:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_WAVE_DELAY, ISRrate);
        break;
      case 7:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_DRUM, ISRrate);
        break;
    }
  }
  else
    switch (FX) {
      case 0:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_PULSAR_CHORD, ISRrate);
        break;
      case 1:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_PULSAR_TWIN, ISRrate);
        break;
      case 2:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_PULSAR_DISTS, ISRrate);
        break;
      case 3:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_PULSAR_DISTS, ISRrate);
        break;
      case 4:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_PULSAR_CHORD, ISRrate);//under isr detune
        break;
      case 5:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_SPECTRUM, ISRrate);
        break;
      case 6:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_PULSAR_DELAY, ISRrate);
        break;
      case 7:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_DRUM, ISRrate);
        break;


    }

}



void GRADUALWAVE() {
  switch (oscMode) {
    case 0:
      GWTlo1 = FMWTselLo[analogControls[8] >> 9]; //select "from" wave
      GWTlo2 = FMWTselLo[(((analogControls[8] >> 9) + 1) << 27) >> 27]; //select "to" wave and modulo 16
      GremLo = (uint32_t)((uint32_t)((analogControls[8] << 23)) >> 23); //get remainder for mix amount

      GWTmid1 = FMWTselMid[analogControls[5] >> 9];
      GWTmid2 = FMWTselMid[(((analogControls[5] >> 9) + 1) << 27) >> 27];
      GremMid = (uint32_t)((uint32_t)((analogControls[5] << 23)) >> 23);

      GWThi1 = FMWTselHi[analogControls[4] >> 9];
      GWThi2 = FMWTselHi[(((analogControls[4] >> 9) + 1) << 27) >> 27];
      GremHi = (uint32_t)((uint32_t)((analogControls[4] << 23)) >> 23);

      break;
    case 2:
      GWTlo1 = FMAltWTselLo[analogControls[8] >> 9];
      GWTlo2 = FMAltWTselLo[(((analogControls[8] >> 9) + 1) << 27) >> 27];
      GremLo = (uint32_t)((uint32_t)((analogControls[8] << 23)) >> 23);

      GWTmid1 = FMAltWTselMid[analogControls[5] >> 9];
      GWTmid2 = FMAltWTselMid[(((analogControls[5] >> 9) + 1) << 27) >> 27];
      GremMid = (uint32_t)((uint32_t)((analogControls[5] << 23)) >> 23);
      break;

    case 1:
      GWTlo1 = CZWTselLo[analogControls[8] >> 9];
      GWTlo2 = CZWTselLo[(((analogControls[8] >> 9) + 1) << 27) >> 27];
      GremLo = (uint32_t)((uint32_t)((analogControls[8] << 23)) >> 23);

      GWTmid1 = CZWTselMid[analogControls[5] >> 9];
      GWTmid2 = CZWTselMid[(((analogControls[5] >> 9) + 1) << 27) >> 27];
      GremMid = (uint32_t)((uint32_t)((analogControls[5] << 23)) >> 23);

      GWThi1 = CZWTselHi[analogControls[4] >> 9];
      GWThi2 = CZWTselHi[(((analogControls[4] >> 9) + 1) << 27) >> 27];
      GremHi = (uint32_t)((uint32_t)((analogControls[4] << 23)) >> 23);

      break;
    case 3:
      GWTlo1 = CZAltWTselLo[analogControls[8] >> 9];
      GWTlo2 = CZAltWTselLo[(((analogControls[8] >> 9) + 1) << 27) >> 27];
      GremLo = (uint32_t)((uint32_t)((analogControls[8] << 23)) >> 23);

      GWTmid1 = CZAltWTselMid[analogControls[5] >> 9];
      GWTmid2 = CZAltWTselMid[(((analogControls[5] >> 9) + 1) << 27) >> 27];
      GremMid = (uint32_t)((uint32_t)((analogControls[5] << 23)) >> 23);



      break;
  }
}

