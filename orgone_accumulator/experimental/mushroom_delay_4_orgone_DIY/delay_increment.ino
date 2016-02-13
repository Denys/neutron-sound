void FASTRUN Delay_increment(void) {

delayCounter = delayCounter + 16;
delayCounterShift = delayCounter >> 4 ;
delayTimeShift = uint16_t(delayCounter + ((4095 - delayCounts) << 4)) >> 4;

 if(gateOn){
 delayTable[delayCounterShift] = delayOut; 
 delayOut = delayTable[delayTimeShift];
finalOut = delayOut;
 }
 else {
 audioIn = (adc->analogRead(Audio_input_pin))-2047;
 delayTable[delayCounterShift] = (audioIn)+((delayOut * delayFeedback)>>12);
 delayOut = delayTable[delayTimeShift];
finalOut = ((delayOut * (delayMix))>>12) + ((audioIn * (4096 - delayMix))>>12);
 }

 
 analogWrite (A14, (finalOut<<4)+32768);
}

