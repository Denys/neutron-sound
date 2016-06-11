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
AudioEffectDelay         delay1;         //xy=390,233
AudioOutputI2S           i2s2;           //xy=539,274
AudioConnection          patchCord1(i2s1, 0, mixer1, 0);
AudioConnection          patchCord2(mixer1, delay1);
AudioConnection          patchCord3(delay1, 0, i2s2, 0);
AudioConnection          patchCord4(delay1, 0, mixer1, 1);
// GUItool: end automatically generated code




float dtime,dfb,comp;
int reading10,reading11;

AudioControlSGTL5000 audioShield;

void setup() {
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(150);

  // Enable the audio shield and set the output volume.
  audioShield.enable();
  //audioShield.inputSelect(myInput);
  audioShield.volume(0.7);
  pinMode (A10,INPUT);
   pinMode (A11,INPUT);
  analogReadResolution(12);
  delay1.delay(0,200);
  Serial.begin(115200);
  mixer1.gain(0,1.0);
  
}

void loop() {
dtime = analogRead(A10) / 10.0;
reading11 = (analogRead(A11));
dfb = (reading11 / 4096.0);

comp = 1.0 - dfb;
delay1.delay(0,dtime);  

mixer1.gain(1,dfb);
mixer1.gain(0,comp);
//Serial.println(q);
}


