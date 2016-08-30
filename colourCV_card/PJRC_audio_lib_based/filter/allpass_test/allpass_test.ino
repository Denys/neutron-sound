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
AudioFilterStateVariable filter1;        //xy=161.3333282470703,147.33333587646484
AudioFilterStateVariable filter11;       //xy=162.4164581298828,695.9168090820312
AudioFilterStateVariable filter9;        //xy=164.16647338867188,585.416748046875
AudioFilterStateVariable filter7;        //xy=164.6664581298828,480.91668701171875
AudioFilterStateVariable filter3;        //xy=166.08326721191406,271.5833435058594
AudioFilterStateVariable filter5;        //xy=166.6665496826172,378.9166564941406
AudioMixer4              mixer1;         //xy=317.33331298828125,144.33333587646484
AudioMixer4              mixer3;         //xy=325.083251953125,260.58335876464844
AudioMixer4              mixer5;         //xy=328.16656494140625,366.1666564941406
AudioMixer4              mixer9;         //xy=327.66644287109375,580.166748046875
AudioMixer4              mixer7;         //xy=328.91644287109375,468.91668701171875
AudioMixer4              mixer11;        //xy=328.91644287109375,689.6668090820312
AudioFilterStateVariable filter2;        //xy=488.33331298828125,154.33333587646484
AudioFilterStateVariable filter4;        //xy=494.083251953125,267.5833435058594
AudioFilterStateVariable filter8;        //xy=494.16644287109375,488.41668701171875
AudioFilterStateVariable filter10;       //xy=494.66644287109375,593.666748046875
AudioFilterStateVariable filter12;       //xy=497.16644287109375,701.1668090820312
AudioFilterStateVariable filter6;        //xy=498.91656494140625,378.1666564941406
AudioMixer4              mixer2;         //xy=662.3333129882812,155.33331298828125
AudioMixer4              mixer6;         //xy=661.6665496826172,376.6666564941406
AudioMixer4              mixer8;         //xy=665.4164428710938,477.91668701171875
AudioMixer4              mixer4;         //xy=673.083251953125,245.5833282470703
AudioMixer4              mixer10;        //xy=676.6663818359375,601.666748046875
AudioMixer4              mixer12;        //xy=689.1664428710938,724.1668090820312
AudioSynthWaveformDc     dc2;            //xy=864.5830497741699,728.3334465026855
AudioOutputI2S           i2s2;           //xy=1018.2497215270996,655.0001182556152
AudioConnection          patchCord1(i2s1, 0, filter1, 0);
AudioConnection          patchCord2(dc1, 0, filter1, 1);
AudioConnection          patchCord3(dc1, 0, filter2, 1);
AudioConnection          patchCord4(dc1, 0, filter3, 1);
AudioConnection          patchCord5(dc1, 0, filter4, 1);
AudioConnection          patchCord6(dc1, 0, filter5, 1);
AudioConnection          patchCord7(dc1, 0, filter6, 1);
AudioConnection          patchCord8(dc1, 0, filter7, 1);
AudioConnection          patchCord9(dc1, 0, filter8, 1);
AudioConnection          patchCord10(dc1, 0, filter9, 1);
AudioConnection          patchCord11(dc1, 0, filter10, 1);
AudioConnection          patchCord12(dc1, 0, filter11, 1);
AudioConnection          patchCord13(dc1, 0, filter12, 1);
AudioConnection          patchCord14(filter1, 0, mixer1, 0);
AudioConnection          patchCord15(filter1, 2, mixer1, 1);
AudioConnection          patchCord16(filter11, 0, mixer11, 0);
AudioConnection          patchCord17(filter11, 2, mixer11, 1);
AudioConnection          patchCord18(filter9, 0, mixer9, 0);
AudioConnection          patchCord19(filter9, 2, mixer9, 1);
AudioConnection          patchCord20(filter7, 0, mixer7, 0);
AudioConnection          patchCord21(filter7, 2, mixer7, 1);
AudioConnection          patchCord22(filter3, 0, mixer3, 0);
AudioConnection          patchCord23(filter3, 2, mixer3, 1);
AudioConnection          patchCord24(filter5, 0, mixer5, 0);
AudioConnection          patchCord25(filter5, 2, mixer5, 1);
AudioConnection          patchCord26(mixer1, 0, filter2, 0);
AudioConnection          patchCord27(mixer3, 0, filter4, 0);
AudioConnection          patchCord28(mixer5, 0, filter6, 0);
AudioConnection          patchCord29(mixer9, 0, filter10, 0);
AudioConnection          patchCord30(mixer7, 0, filter8, 0);
AudioConnection          patchCord31(mixer11, 0, filter12, 0);
AudioConnection          patchCord32(filter2, 0, mixer2, 0);
AudioConnection          patchCord33(filter2, 2, mixer2, 1);
AudioConnection          patchCord34(filter4, 0, mixer4, 0);
AudioConnection          patchCord35(filter4, 2, mixer4, 1);
AudioConnection          patchCord36(filter8, 0, mixer8, 0);
AudioConnection          patchCord37(filter8, 2, mixer8, 1);
AudioConnection          patchCord38(filter10, 0, mixer10, 0);
AudioConnection          patchCord39(filter10, 2, mixer10, 1);
AudioConnection          patchCord40(filter12, 0, mixer12, 0);
AudioConnection          patchCord41(filter12, 2, mixer12, 1);
AudioConnection          patchCord42(filter6, 0, mixer6, 0);
AudioConnection          patchCord43(filter6, 2, mixer6, 1);
AudioConnection          patchCord44(mixer2, 0, filter3, 0);
AudioConnection          patchCord45(mixer6, 0, filter7, 0);
AudioConnection          patchCord46(mixer8, 0, filter9, 0);
AudioConnection          patchCord47(mixer4, 0, filter5, 0);
AudioConnection          patchCord48(mixer10, 0, filter11, 0);
AudioConnection          patchCord49(mixer12, 0, i2s2, 0);
AudioConnection          patchCord50(dc2, 0, i2s2, 1);
// GUItool: end automatically generated code







float f, regen, regenComp;
float q = 1.2;//don't go lower for resonance on this one or it blows up due to high frequency filters.
float octave = 7;
float startFreq = 25;
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
  mixer2.gain(0, 1);
  mixer2.gain(1, 1);
  mixer3.gain(0, 1);
  mixer3.gain(1, 1);
  mixer4.gain(0, 1);
  mixer4.gain(1, 1);
  mixer5.gain(0, 1);
  mixer5.gain(1, 1);
  mixer6.gain(0, 1);
  mixer6.gain(1, 1);
  mixer7.gain(0, 1);
  mixer7.gain(1, 1);
  mixer8.gain(0, 1);
  mixer8.gain(1, 1);
  mixer8.gain(2, 0);
  mixer9.gain(1, 1);
  mixer9.gain(2, 0);
  mixer10.gain(1, 1);
  mixer10.gain(2, 0);
  mixer11.gain(1, 1);
  mixer11.gain(2, 0);
  mixer12.gain(1, 1);
  mixer12.gain(2, 0);


  filter1.resonance(q);
  filter1.frequency(startFreq);
  filter1.octaveControl(octave);

  filter2.resonance(q);
  filter2.frequency(startFreq);
  filter2.octaveControl(octave);

  filter3.resonance(q);
  filter3.frequency(startFreq * 2);
  filter3.octaveControl(octave);

  filter4.resonance(q);
  filter4.frequency(startFreq * 2);
  filter4.octaveControl(octave);

  filter5.resonance(q);
  filter5.frequency(startFreq * 4);
  filter5.octaveControl(octave);

  filter6.resonance(q);
  filter6.frequency(startFreq * 4);
  filter6.octaveControl(octave);

  filter7.resonance(q);
  filter7.frequency(startFreq * 8);
  filter7.octaveControl(octave);

  filter8.resonance(q);
  filter8.frequency(startFreq * 8);
  filter8.octaveControl(octave);

  filter9.resonance(q);
  filter9.frequency(startFreq * 16);
  filter9.octaveControl(octave);

  filter10.resonance(q);
  filter10.frequency(startFreq * 16);
  filter10.octaveControl(octave);

  filter11.resonance(q);
  filter11.frequency(startFreq * 32);
  filter11.octaveControl(octave);

  filter12.resonance(q);
  filter12.frequency(startFreq * 32);
  filter12.octaveControl(octave);
}

void loop() {
  reading10 = (4095 - analogRead(A10)) ;
  reading11 = (4095 - analogRead(A11));
  reading12 = (4095 - analogRead(A12));

  f = reading10 / 4095.0;
  dc1.amplitude(f);

  regen = reading12 / 1024.0;
  regenComp = 1.0 - (regen / 12.0);
  mixer1.gain(0, regenComp);
  mixer1.gain(1, regenComp);

  filter1.resonance(q + regen);
  filter2.resonance(q + regen);
  filter3.resonance(q + regen);
  filter4.resonance(q + regen);
  filter5.resonance(q + regen);
  filter6.resonance(q + regen);
  filter7.resonance(q + regen);
  filter8.resonance(q + regen);
  filter9.resonance(q + regen);
  filter10.resonance(q + regen);
  filter11.resonance(q + regen);
  filter12.resonance(q + regen);
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


