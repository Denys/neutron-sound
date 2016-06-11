// FFT Test
//
// Compute a 1024 point Fast Fourier Transform (spectrum analysis)
// on audio connected to the Left Line-In pin.  By changing code,
// a synthetic sine wave can be input instead.
//
// The first 40 (of 512) frequency analysis bins are printed to
// the Arduino Serial Monitor.  Viewing the raw data can help you
// understand how the FFT works and what results to expect when
// using the data to control LEDs, motors, or other fun things!
//
// This example code is in the public domain.

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=127,218
AudioMixer4              mixer1;         //xy=253,232
AudioSynthWaveformDc     dc1;            //xy=253,293
AudioFilterStateVariable filter1;        //xy=388,273
AudioOutputI2S           i2s2;           //xy=539,274
AudioConnection          patchCord1(i2s1, 0, mixer1, 0);
AudioConnection          patchCord2(mixer1, 0, filter1, 0);
AudioConnection          patchCord3(dc1, 0, filter1, 1);
AudioConnection          patchCord4(filter1, 0, i2s2, 0);
// GUItool: end automatically generated code




float f,q,comp;
int reading10,reading11;

AudioControlSGTL5000 audioShield;

void setup() {
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);

  // Enable the audio shield and set the output volume.
  audioShield.enable();
  //audioShield.inputSelect(myInput);
  audioShield.volume(0.7);
  pinMode (A10,INPUT);
   pinMode (A11,INPUT);
  analogReadResolution(12);
  filter1.frequency(100.0);
  filter1.octaveControl(5.0);  
  Serial.begin(115200);
  
}

void loop() {
f = analogRead(A10) / 4096.0;
reading11 = (analogRead(A11));
q = ((reading11 / 4096.0)*5.3)+0.7;
comp = 0.4 - (reading11 / 20480.0);
dc1.amplitude(f);  
filter1.resonance(q);
mixer1.gain(0,comp);
Serial.println(q);
}


