

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define LED_RED 3
#define LED_GREEN 4
#define LED_BLUE 5

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=127,218
AudioMixer4              mixer1;         //xy=253,232
AudioSynthWaveformDc     dc1;            //xy=253,293
AudioSynthWaveformDc     dc2;            //xy=253,293 //needed for prototype mixer offset. remove in final
AudioFilterStateVariable filter1;        //xy=388,273
AudioFilterStateVariable filter2;        //xy=388,273
AudioFilterStateVariable filter3;        //xy=388,273
AudioOutputI2S           i2s2;           //xy=539,274
AudioConnection          patchCord1(i2s1, 0, mixer1, 0);
AudioConnection          patchCord2(mixer1, 0, filter1, 0);
AudioConnection          patchCord3(dc1, 0, filter1, 1);
AudioConnection          patchCord4(dc1, 0, filter2, 1);
AudioConnection          patchCord5(dc1, 0, filter3, 1);
AudioConnection          patchCord6(filter1, 0, filter2, 0);
AudioConnection          patchCord7(filter2, 0, filter3, 0);
AudioConnection          patchCord8(filter3, 0, i2s2, 0);
AudioConnection          patchCord9(dc2, 0, i2s2, 1); //needed for prototype mixer offset. remove in final
// GUItool: end automatically generated code




float f,q,comp;
int reading10,reading11,reading12,reading13;

AudioControlSGTL5000 audioShield;

void setup() {
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);
analogReadResolution(12);
analogWriteResolution(12);
  // Enable the audio shield and set the output volume.
  audioShield.enable();
  //audioShield.inputSelect(myInput);
  //audioShield.volume(0.7); used for headphones
  audioShield.lineInLevel(0); //use full scale
  audioShield.lineOutLevel(13);
  pinMode (A10,INPUT);
   pinMode (A11,INPUT);
   pinMode (A12,INPUT);
   pinMode (LED_RED, OUTPUT);
   pinMode (LED_GREEN, OUTPUT);
   pinMode (LED_BLUE, OUTPUT);
  
  filter1.frequency(100.0);
  filter1.octaveControl(6.0);  
  filter2.frequency(120.0);
  filter2.octaveControl(5.9);    
  filter3.frequency(130.0);
  filter3.octaveControl(5.85);  
  Serial.begin(115200);
  dc2.amplitude(1.0);
  analogWrite(A14,0);
  
}

void loop() {
reading10 = (4095- analogRead(A10)) ;
f = reading10 / 4095.0;
reading11 = (4095-analogRead(A11));
reading12 = (4095-analogRead(A12));
q = ((reading12 / 4095.0)*5.5)+0.7;
comp = 1.0 - (q / 15.0);
dc1.amplitude(f);  
filter1.resonance(q);
filter2.resonance(q);
filter3.resonance(q);
mixer1.gain(0,comp);
//Serial.println(q);
analogWrite(LED_RED,reading10);
analogWrite(LED_GREEN,reading11);
analogWrite(LED_BLUE,reading12);
}


