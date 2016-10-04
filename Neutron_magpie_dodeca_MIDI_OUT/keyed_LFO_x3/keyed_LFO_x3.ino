/*
   Neutron magpie dodeca:
   keyed LFO x 3
   3 LFOs on MIDI channel 1,2,3
   LFO frequency based on MIDI clock
   White notes are even dividers/multipliers black are odd
   each group of 4 outputs are thye same LFO with 90% phase shift.
   velocity will shift the LFO phase
   defaults to sine, 15 other waves can be selected with MIDI CC 1 
 * */
//SO FAR ONLY WORKING ON OUT 1, more to come! 

#include <MIDI.h>

const uint8_t CHAN = 1;//set the first MIDI channel here! it will use the following 2 so dont go past 14, strange things might happen!
const uint8_t ISRrate = 25;

const uint8_t out2pin[] = {23, 0, 22, 25, 20, 6, 21, 5, 9, 4, 10, 3};//output number to actual teensy pin, dont change.
const uint8_t keyDivs[] = {4, 6 , 8, 12, 16, 32, 48, 64, 96, 128, 1, 2};//clock division for each key 4=1bar
const uint32_t rateScaler = 13400; //calculate this properly according to ISRrate when brain is working better

const int16_t sinTable[] = {
  0, 402, 804, 1206, 1607, 2009, 2410, 2811, 3211, 3611, 4011, 4409, 4807, 5205, 5601, 5997, 6392,
  6786, 7179, 7571, 7961, 8351, 8739, 9126, 9511, 9895, 10278, 10659, 11038, 11416, 11792, 12166, 12539,
  12909, 13278, 13645, 14009, 14372, 14732, 15090, 15446, 15799, 16150, 16499, 16845, 17189, 17530, 17868, 18204,
  18537, 18867, 19194, 19519, 19840, 20159, 20474, 20787, 21096, 21402, 21705, 22004, 22301, 22594, 22883, 23169,
  23452, 23731, 24006, 24278, 24546, 24811, 25072, 25329, 25582, 25831, 26077, 26318, 26556, 26789, 27019, 27244,
  27466, 27683, 27896, 28105, 28309, 28510, 28706, 28897, 29085, 29268, 29446, 29621, 29790, 29955, 30116, 30272,
  30424, 30571, 30713, 30851, 30984, 31113, 31236, 31356, 31470, 31580, 31684, 31785, 31880, 31970, 32056, 32137,
  32213, 32284, 32350, 32412, 32468, 32520, 32567, 32609, 32646, 32678, 32705, 32727, 32744, 32757, 32764, 32767,
  32764, 32757, 32744, 32727, 32705, 32678, 32646, 32609, 32567, 32520, 32468, 32412, 32350, 32284, 32213, 32137,
  32056, 31970, 31880, 31785, 31684, 31580, 31470, 31356, 31236, 31113, 30984, 30851, 30713, 30571, 30424, 30272,
  30116, 29955, 29790, 29621, 29446, 29268, 29085, 28897, 28706, 28510, 28309, 28105, 27896, 27683, 27466, 27244,
  27019, 26789, 26556, 26318, 26077, 25831, 25582, 25329, 25072, 24811, 24546, 24278, 24006, 23731, 23452, 23169,
  22883, 22594, 22301, 22004, 21705, 21402, 21096, 20787, 20474, 20159, 19840, 19519, 19194, 18867, 18537, 18204,
  17868, 17530, 17189, 16845, 16499, 16150, 15799, 15446, 15090, 14732, 14372, 14009, 13645, 13278, 12909, 12539,
  12166, 11792, 11416, 11038, 10659, 10278, 9895, 9511, 9126, 8739, 8351, 7961, 7571, 7179, 6786, 6392,
  5997, 5601, 5205, 4807, 4409, 4011, 3611, 3211, 2811, 2410, 2009, 1607, 1206, 804, 402, 0,
  -402, -804, -1206, -1607, -2009, -2410, -2811, -3211, -3611, -4011, -4409, -4807, -5205, -5601, -5997, -6392,
  -6786, -7179, -7571, -7961, -8351, -8739, -9126, -9511, -9895, -10278, -10659, -11038, -11416, -11792, -12166, -12539,
  -12909, -13278, -13645, -14009, -14372, -14732, -15090, -15446, -15799, -16150, -16499, -16845, -17189, -17530, -17868, -18204,
  -18537, -18867, -19194, -19519, -19840, -20159, -20474, -20787, -21096, -21402, -21705, -22004, -22301, -22594, -22883, -23169,
  -23452, -23731, -24006, -24278, -24546, -24811, -25072, -25329, -25582, -25831, -26077, -26318, -26556, -26789, -27019, -27244,
  -27466, -27683, -27896, -28105, -28309, -28510, -28706, -28897, -29085, -29268, -29446, -29621, -29790, -29955, -30116, -30272,
  -30424, -30571, -30713, -30851, -30984, -31113, -31236, -31356, -31470, -31580, -31684, -31785, -31880, -31970, -32056, -32137,
  -32213, -32284, -32350, -32412, -32468, -32520, -32567, -32609, -32646, -32678, -32705, -32727, -32744, -32757, -32764, -32767,
  -32764, -32757, -32744, -32727, -32705, -32678, -32646, -32609, -32567, -32520, -32468, -32412, -32350, -32284, -32213, -32137,
  -32056, -31970, -31880, -31785, -31684, -31580, -31470, -31356, -31236, -31113, -30984, -30851, -30713, -30571, -30424, -30272,
  -30116, -29955, -29790, -29621, -29446, -29268, -29085, -28897, -28706, -28510, -28309, -28105, -27896, -27683, -27466, -27244,
  -27019, -26789, -26556, -26318, -26077, -25831, -25582, -25329, -25072, -24811, -24546, -24278, -24006, -23731, -23452, -23169,
  -22883, -22594, -22301, -22004, -21705, -21402, -21096, -20787, -20474, -20159, -19840, -19519, -19194, -18867, -18537, -18204,
  -17868, -17530, -17189, -16845, -16499, -16150, -15799, -15446, -15090, -14732, -14372, -14009, -13645, -13278, -12909, -12539,
  -12166, -11792, -11416, -11038, -10659, -10278, -9895, -9511, -9126, -8739, -8351, -7961, -7571, -7179, -6786, -6392,
  -5997, -5601, -5205, -4807, -4409, -4011, -3611, -3211, -2811, -2410, -2009, -1607, -1206, -804, -402,
};


uint8_t pulses;
bool playing;
uint32_t MIDIclockRate;
float BPM;

uint16_t pitchOut;
uint32_t LFO_rate_mult[] = {1,1,1};
uint32_t intBPM;
uint8_t quarters; 

struct oscillator1
{
  uint32_t phase = 0;    
  int32_t phaseRemain = 0;
  int32_t phaseOffset = 0;  
  uint32_t phaseOld = 0;
  int32_t wave;
  int32_t nextwave;  
  int32_t phase_increment = 0;
}
lfo1;

struct oscillator3
{
  uint32_t phase = 0;    
  int32_t phaseRemain = 0;
  int32_t phaseOffset = 0;  
  uint32_t phaseOld = 0;  
  int32_t wave;
  int32_t nextwave;  
  int32_t phase_increment = 0;
}
lfo3;

struct oscillator2
{
  uint32_t phase = 0;    
  int32_t phaseRemain = 0;
  int32_t phaseOffset = 0;  
  uint32_t phaseOld = 0;
  int32_t wave;
  int32_t nextwave;  
  int32_t phase_increment = 0;  
}
lfo2;

//uint8_t cc2out[] = {40, 41, 42, 1, 44, 45, 46, 47, 48, 49, 50, 51};

//elapsedMicros waitPrint;
elapsedMillis MIDIclockRateIn;

IntervalTimer LFOtimer;

void outUpdateISR_LFOs(void);

void setup() {
  // Initiate MIDI communications, listen to all channels

  for (int i = 0; i < 12; i ++) {
    if (out2pin[i]) {
      pinMode(out2pin[i], OUTPUT);
      analogWriteFrequency(out2pin[i], 40000);
    }
  }

  analogWriteResolution(12);
  
   for (int i = 0; i < 12; i ++) {//start up LED animation
    for (int j = 0; j < 128; j ++) {
      if (out2pin[i] == 0) analogWrite(A14, (j ));
      else analogWrite(out2pin[i], j );
      delay(1);
    }
    if (out2pin[i] == 0) analogWrite(A14, 0);
    analogWrite(out2pin[i], 0);
  }//end of start up animantion

  MIDI.begin(MIDI_CHANNEL_OMNI);
  // Connect the Handlers to the library, so it is called upon reception.
  MIDI.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
  MIDI.setHandleControlChange(HandleControlChange);
  MIDI.setHandleNoteOff(HandleNoteOff);
  MIDI.setHandleClock(HandleClock);
  MIDI.setHandleStart(HandleStart);
  MIDI.setHandleStop(HandleStop);
  MIDI.setHandleContinue(HandleContinue);

LFOtimer.begin(outUpdateISR_LFOs, ISRrate);
  
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Serial.println("dodeca measured MIDI clock rate");  
}

void loop() {
  
  MIDI.read();  

  DO_INCREMENTS();
  
}
