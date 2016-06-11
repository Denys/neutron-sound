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
AudioInputI2S            i2s1;           //xy=97,114
AudioEffectBitcrusher    bitcrusher2;    //xy=258,132
AudioEffectBitcrusher    bitcrusher1;    //xy=259,93
AudioMixer4              mixer1;         //xy=428,125
AudioOutputI2S           i2s2;           //xy=606,131
AudioConnection          patchCord1(i2s1, 0, bitcrusher1, 0);
AudioConnection          patchCord2(i2s1, 1, bitcrusher2, 0);
AudioConnection          patchCord3(bitcrusher2, 0, mixer1, 1);
AudioConnection          patchCord4(bitcrusher1, 0, mixer1, 0);
AudioConnection          patchCord5(mixer1, 0, i2s2, 0);
// GUItool: end automatically generated code




int crush1,sampl1;
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
  mixer1.gain(0,1.0);
  Serial.begin(115200);  
}

void loop() {
reading10 = analogRead(A10);
reading11 = analogRead(A11);
crush1 = reading10 >> 8;
sampl1 = reading11 * 10.7;
bitcrusher1.bits(crush1);
bitcrusher1.sampleRate(sampl1);

}


