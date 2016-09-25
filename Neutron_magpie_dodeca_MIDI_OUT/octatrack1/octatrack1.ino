/*
   Neutron magpie dodeca:
   Octatrack channel 1
   7 gate output respond to white notes with velocity (out 1-7)
   4 CC output respond to CC 1,2,3,4 (out 8-11)
   1 clock out on output 12
 * */

#include <MIDI.h>


// This function will be automatically called when a NoteOn is received.
// It must be a void-returning function with the correct parameters,
// see documentation ere:
// http://arduinomidilib.sourceforge.net/class_m_i_d_i___class.html


uint8_t out2pin[] = {23, 0, 22, 25, 20, 6, 21, 5, 9, 4, 10, 3};//output number to actual teensy pin, dont change.
uint8_t whitekeys[] = {1, 0, 2, 0, 3, 4, 0, 5, 0, 6, 0, 7};//midi note to 
uint8_t pulses;
uint8_t sixteenthnotes; //this is how long the drum triggers are
uint8_t quartertoggle;
uint8_t wholetoggle;
bool playing;

uint8_t bottomNote = 12; //the bottom MIDI note, the module puts out 8 octaves.
uint8_t topNote = bottomNote + 95;
uint16_t pitchOut;

//uint8_t cc2out[] = {40, 41, 42, 1, 44, 45, 46, 47, 48, 49, 50, 51};



void setup() {
  // Initiate MIDI communications, listen to all channels

  for (int i = 0; i < 12; i ++) {
    if (out2pin[i]) {
      pinMode(out2pin[i], OUTPUT);
      analogWriteFrequency(out2pin[i], 375000);
    }
  }

  analogWriteResolution(7);
  //digitalWriteFast(4, HIGH);

  for (int i = 0; i < 12; i ++) {
    for (int j = 0; j < 128; j ++) {
      if (out2pin[i] == 0) analogWrite(A14, (j ));
      else analogWrite(out2pin[i], j );
      delay(1);
    }
    if (out2pin[i] == 0) analogWrite(A14, 0);
    analogWrite(out2pin[i], 0);
  }

  MIDI.begin(MIDI_CHANNEL_OMNI);
  // Connect the Handlers to the library, so it is called upon reception.
  MIDI.setHandleNoteOn(HandleNoteOn);  // Put only the name of the function
  MIDI.setHandleControlChange(HandleControlChange);
  MIDI.setHandleNoteOff(HandleNoteOff);
  MIDI.setHandleClock(HandleClock);
  MIDI.setHandleStart(HandleStart);
  MIDI.setHandleStop(HandleStop);
  MIDI.setHandleContinue(HandleContinue);

 // countdownTimer.begin(ISR_TRIGEND, 1000);

  Serial.begin(9600);
}


void loop() {
  // Call MIDI.read the fastest you can for real-time performance.
  MIDI.read();

  // There is no need to check if there are messages incoming if they are bound to a Callback function.
}
