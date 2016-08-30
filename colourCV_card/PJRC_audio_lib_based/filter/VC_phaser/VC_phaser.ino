//Neutron sound dual stage random phaser for TeenCV
// 2 all pass filters in series controlled by low pass filtered pink noise.

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#define LED_RED 3
#define LED_GREEN 4
#define LED_BLUE 5
#define SWITCH_OPTION_0 0
#define SWITCH_OPTION_1 1
#define SWITCH_CVIN_0 2
#define SWITCH_CVIN_1 3

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=72.33332824707031,60.333335876464844
AudioSynthWaveformDc     dc1;            //xy=73.33332824707031,20
AudioSynthWaveformDc     dc2;            //added for temporary mixer out offset fix
AudioFilterStateVariable filter1;        //xy=187.3333282470703,136.33334350585938
AudioFilterStateVariable filter3;        //xy=193.3333282470703,294.3333282470703
AudioMixer4              mixer1;         //xy=345.33331298828125,152.33334350585938
AudioMixer4              mixer3;         //xy=345.33331298828125,301.3333435058594
AudioFilterStateVariable filter2;        //xy=500.33331298828125,139.33334350585938
AudioFilterStateVariable filter4;        //xy=513.3333282470703,303.3333282470703
AudioMixer4              mixer2;         //xy=662.3333129882812,155.33331298828125
AudioMixer4              mixer4;         //xy=674.3333282470703,284.3333282470703
AudioOutputI2S           i2s2;           //xy=776,346
AudioConnection          patchCord1(i2s1, 0, filter1, 0);
AudioConnection          patchCord2(dc1, 0, filter1, 1);
AudioConnection          patchCord3(dc1, 0, filter2, 1);
AudioConnection          patchCord4(dc1, 0, filter3, 1);
AudioConnection          patchCord5(dc1, 0, filter4, 1);
AudioConnection          patchCord6(filter1, 0, mixer1, 0);
AudioConnection          patchCord7(filter1, 2, mixer1, 1);
AudioConnection          patchCord8(filter3, 0, mixer3, 0);
AudioConnection          patchCord9(filter3, 2, mixer3, 1);
AudioConnection          patchCord10(mixer1, 0, filter2, 0);
AudioConnection          patchCord11(mixer3, 0, filter4, 0);
AudioConnection          patchCord12(filter2, 0, mixer2, 0);
AudioConnection          patchCord13(filter2, 2, mixer2, 1);
AudioConnection          patchCord14(filter4, 0, mixer4, 0);
AudioConnection          patchCord15(filter4, 2, mixer4, 1);
AudioConnection          patchCord16(mixer2, 0, filter3, 0);
AudioConnection          patchCord17(mixer4, 0, i2s2, 0);
AudioConnection          patchCord18(mixer4, 0, mixer1, 2);
AudioConnection          patchCord19(dc2, 0, i2s2, 1);
// GUItool: end automatically generated code




float f,regen,regenComp;
float q = 0.7;
int reading10,reading11,reading12,reading13;


AudioControlSGTL5000 audioShield;

void setup() {
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(16);
analogReadResolution(12);
analogWriteResolution(12);
  // Enable the audio shield and set the output volume.
  audioShield.enable();
  //audioShield.inputSelect(myInput);
  audioShield.volume(0.0); //used for headphones but set to 0 anyways.
  audioShield.lineInLevel(0); //use full scale
  audioShield.lineOutLevel(13);
  pinMode (A10,INPUT);
   pinMode (A11,INPUT);
   pinMode (A12,INPUT);
   pinMode (LED_RED, OUTPUT);
   pinMode (LED_GREEN, OUTPUT);
   pinMode (LED_BLUE, OUTPUT);
  
 
  Serial.begin(115200);
  
  analogWrite(A14,0);// for prototype mixer offset
  dc2.amplitude(1);// for prototype mixer offset

  mixer1.gain(0,0.6);
  mixer1.gain(1,0.6);
  mixer1.gain(2,0.4);//regen level
  mixer2.gain(0,1);
  mixer2.gain(1,1);
  mixer3.gain(0,1);
  mixer3.gain(1,1);
  mixer4.gain(0,0.8);
  mixer4.gain(1,0.8);
  
  
  filter1.resonance(q);
  filter1.frequency(60.0);
  filter1.octaveControl(6.4);
  
  filter2.resonance(q);
  filter2.frequency(75.0);
  filter2.octaveControl(5.7); 
  
  filter3.resonance(q);
  filter3.frequency(130.0);
  filter3.octaveControl(5.2); 

  filter4.resonance(q);
  filter4.frequency(220.0);
  filter4.octaveControl(4.1); 
}

void loop() {
reading10 = (4095- analogRead(A10)) ;
reading11 = (4095-analogRead(A11));
reading12 = (4095-analogRead(A12));

f = reading10 / 4095.0;
dc1.amplitude(f);

   regen = reading12 / 1024.0; 
   regenComp = 1.0 - (regen/12.0);
  mixer1.gain(0,regenComp);
  mixer1.gain(1,regenComp);

filter1.resonance(q+regen);
filter2.resonance(q+regen);
filter3.resonance(q+regen);
filter4.resonance(q+regen);
  //mixer1.gain(2,regen);//global regen level 


Serial.print("all=");
  Serial.print(AudioProcessorUsage());
  Serial.print(",");
  Serial.print(AudioProcessorUsageMax());
  Serial.print("    ");
  Serial.print("Memory: ");
  Serial.print(AudioMemoryUsage());
  Serial.print(",");
  Serial.print(AudioMemoryUsageMax());
  Serial.println("    ");
  
analogWrite(LED_RED,reading10);
analogWrite(LED_GREEN,reading11);
analogWrite(LED_BLUE,reading12);
}


