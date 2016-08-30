//Neutron sound 12 stage octave phaser for TeenCV
// 12 all pass filters in series controlled by cv input.

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
AudioInputI2S            i2s1;           //xy=86.33332824707031,255.33334350585938
AudioSynthWaveformDc     dc1;            //xy=86.99998474121094,416
AudioFilterStateVariable filter1;        //xy=299.33331298828125,129.33334350585938
AudioFilterStateVariable filter3;        //xy=300.33331298828125,241.33334350585938
AudioFilterStateVariable filter2;        //xy=301.33331298828125,186.33334350585938
AudioFilterStateVariable filter4;        //xy=301.33331298828125,297.33331298828125
AudioFilterStateVariable filter5;        //xy=302.33331298828125,375.33331298828125
AudioFilterStateVariable filter6;        //xy=303.33331298828125,430.3333435058594
AudioFilterStateVariable filter7;        //xy=305.33331298828125,488.3333435058594
AudioFilterStateVariable filter8;        //xy=309.33331298828125,553.3333282470703
AudioMixer4              mixer1;         //xy=485.33331298828125,217.33334350585938
AudioMixer4              mixer2;         //xy=489.33331298828125,456.3333435058594
AudioMixer4              mixer3;         //xy=705.3333282470703,360.3333282470703
AudioSynthWaveformDc     dc2;            //xy=794.5830688476562,472.3334655761719
AudioOutputI2S           i2s2;           //xy=914.2496948242188,377.0001525878906
AudioConnection          patchCord1(i2s1, 0, filter1, 0);
AudioConnection          patchCord2(i2s1, 0, filter2, 0);
AudioConnection          patchCord3(i2s1, 0, filter3, 0);
AudioConnection          patchCord4(i2s1, 0, filter4, 0);
AudioConnection          patchCord5(i2s1, 0, filter5, 0);
AudioConnection          patchCord6(i2s1, 0, filter6, 0);
AudioConnection          patchCord7(i2s1, 0, filter7, 0);
AudioConnection          patchCord8(i2s1, 0, filter8, 0);
AudioConnection          patchCord9(dc1, 0, filter1, 1);
AudioConnection          patchCord10(dc1, 0, filter2, 1);
AudioConnection          patchCord11(dc1, 0, filter3, 1);
AudioConnection          patchCord12(dc1, 0, filter4, 1);
AudioConnection          patchCord13(dc1, 0, filter5, 1);
AudioConnection          patchCord14(dc1, 0, filter6, 1);
AudioConnection          patchCord15(dc1, 0, filter7, 1);
AudioConnection          patchCord16(dc1, 0, filter8, 1);
AudioConnection          patchCord17(filter1, 1, mixer1, 0);
AudioConnection          patchCord18(filter3, 1, mixer1, 2);
AudioConnection          patchCord19(filter2, 1, mixer1, 1);
AudioConnection          patchCord20(filter4, 1, mixer1, 3);
AudioConnection          patchCord21(filter5, 1, mixer2, 0);
AudioConnection          patchCord22(filter6, 1, mixer2, 1);
AudioConnection          patchCord23(filter7, 1, mixer2, 2);
AudioConnection          patchCord24(filter8, 1, mixer2, 3);
AudioConnection          patchCord25(mixer1, 0, mixer3, 0);
AudioConnection          patchCord26(mixer2, 0, mixer3, 1);
AudioConnection          patchCord27(mixer3, 0, i2s2, 0);
AudioConnection          patchCord28(dc2, 0, i2s2, 1);
// GUItool: end automatically generated code


float f, regen, regenComp;
float q = 0.7;
float octave = 7;
float startFreq = 40;
int reading10, reading11, reading12, reading13;

AudioControlSGTL5000 audioShield;

void setup() {
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(19);
  analogReadResolution(12);
  analogWriteResolution(12);
  // Enable the audio shield and set the output volume.
  audioShield.enable();
  //audioShield.inputSelect(myInput);
  audioShield.volume(0.0); //used for headphones but set to 0 anyways.
  audioShield.lineInLevel(0); //use full scale
  audioShield.lineOutLevel(13);
  pinMode (A10, INPUT);
  pinMode (A11, INPUT);
  pinMode (A12, INPUT);
  pinMode (LED_RED, OUTPUT);
  pinMode (LED_GREEN, OUTPUT);
  pinMode (LED_BLUE, OUTPUT);


  Serial.begin(115200);

  analogWrite(A14, 0); // for prototype mixer offset
  dc2.amplitude(1);// for prototype mixer offset

  mixer1.gain(0, 1);
  mixer1.gain(1, 1);
  mixer1.gain(2, 1);
  mixer1.gain(3, 1);
  mixer2.gain(0, 1);
  mixer2.gain(1, 1);
  mixer2.gain(2, 1);
  mixer2.gain(3, 1);
  mixer3.gain(0, 1);
  mixer3.gain(1, 1);
 


  filter1.resonance(q);
  filter1.frequency(startFreq);
  filter1.octaveControl(octave);

  filter2.resonance(q);
  filter2.frequency(startFreq * 2);
  filter2.octaveControl(octave);

  filter3.resonance(q);
  filter3.frequency(startFreq * 3);
  filter3.octaveControl(octave);

  filter4.resonance(q);
  filter4.frequency(startFreq * 4);
  filter4.octaveControl(octave);

  filter5.resonance(q);
  filter5.frequency(startFreq * 5);
  filter5.octaveControl(octave);

  filter6.resonance(q);
  filter6.frequency(startFreq * 6);
  filter6.octaveControl(octave);

  filter7.resonance(q);
  filter7.frequency(startFreq * 7);
  filter7.octaveControl(octave);

  filter8.resonance(q);
  filter8.frequency(startFreq * 8);
  filter8.octaveControl(octave);

  
}

void loop() {
  reading10 = (4095 - analogRead(A10)) ;
  reading11 = (4095 - analogRead(A11));
  reading12 = (4095 - analogRead(A12));

  f = reading10 / 4095.0;
  dc1.amplitude(f);

  regen = reading12 / 952.5;
  regenComp = 1.0 - (regen / 12.0);
  mixer3.gain(0, regenComp);
  mixer3.gain(1, regenComp);

  filter1.resonance(q + regen);
  filter2.resonance(q + regen);
  filter3.resonance(q + regen);
  filter4.resonance(q + regen);
  filter5.resonance(q + regen);
  filter6.resonance(q + regen);
  filter7.resonance(q + regen);
  filter8.resonance(q + regen);
  
  //mixer1.gain(2,regen);//global regen level


  //  Serial.print("all=");
  //  Serial.print(AudioProcessorUsage());
  //  Serial.print(",");
  //  Serial.print(AudioProcessorUsageMax());
  //  Serial.print("    ");
  //  Serial.print("Memory: ");
  //  Serial.print(AudioMemoryUsage());
  //  Serial.print(",");
  //  Serial.print(AudioMemoryUsageMax());
  //  Serial.println("    ");

  analogWrite(LED_RED, reading10);
  analogWrite(LED_GREEN, reading11);
  analogWrite(LED_BLUE, reading12);
}


