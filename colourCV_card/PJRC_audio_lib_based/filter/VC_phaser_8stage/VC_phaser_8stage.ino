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
AudioFilterStateVariable filter7;        //xy=182.9166259765625,569.1666870117188
AudioFilterStateVariable filter1;        //xy=187.3333282470703,136.33334350585938
AudioFilterStateVariable filter3;        //xy=193.3333282470703,294.3333282470703
AudioFilterStateVariable filter5;        //xy=192.91665649414062,436.66668701171875
AudioMixer4              mixer7;         //xy=339.1666259765625,579.1666870117188
AudioMixer4              mixer1;         //xy=345.33331298828125,152.33334350585938
AudioMixer4              mixer3;         //xy=345.33331298828125,301.3333435058594
AudioMixer4              mixer5;         //xy=355.4166564941406,432.91668701171875
AudioFilterStateVariable filter2;        //xy=500.33331298828125,139.33334350585938
AudioFilterStateVariable filter4;        //xy=513.3333282470703,303.3333282470703
AudioFilterStateVariable filter6;        //xy=514.1666564941406,437.91668701171875
AudioFilterStateVariable filter8;        //xy=520.4166259765625,576.6666870117188
AudioMixer4              mixer2;         //xy=662.3333129882812,155.33331298828125
AudioMixer4              mixer6;         //xy=672.9166564941406,445.41668701171875
AudioMixer4              mixer4;         //xy=674.3333282470703,284.3333282470703
AudioMixer4              mixer8;         //xy=681.6666259765625,574.1666870117188
AudioSynthWaveformDc     dc2;            //xy=690.833251953125,699.5833129882812
AudioOutputI2S           i2s2;           //xy=844.4999237060547,626.2499847412109
AudioConnection          patchCord1(i2s1, 0, filter1, 0);
AudioConnection          patchCord2(i2s1, 0, mixer8, 2);
AudioConnection          patchCord3(dc1, 0, filter1, 1);
AudioConnection          patchCord4(dc1, 0, filter2, 1);
AudioConnection          patchCord5(dc1, 0, filter3, 1);
AudioConnection          patchCord6(dc1, 0, filter4, 1);
AudioConnection          patchCord7(dc1, 0, filter5, 1);
AudioConnection          patchCord8(dc1, 0, filter6, 1);
AudioConnection          patchCord9(dc1, 0, filter7, 1);
AudioConnection          patchCord10(dc1, 0, filter8, 1);
AudioConnection          patchCord11(filter7, 0, mixer7, 0);
AudioConnection          patchCord12(filter7, 2, mixer7, 1);
AudioConnection          patchCord13(filter1, 0, mixer1, 0);
AudioConnection          patchCord14(filter1, 2, mixer1, 1);
AudioConnection          patchCord15(filter3, 0, mixer3, 0);
AudioConnection          patchCord16(filter3, 2, mixer3, 1);
AudioConnection          patchCord17(filter5, 0, mixer5, 0);
AudioConnection          patchCord18(filter5, 2, mixer5, 1);
AudioConnection          patchCord19(mixer7, 0, filter8, 0);
AudioConnection          patchCord20(mixer1, 0, filter2, 0);
AudioConnection          patchCord21(mixer3, 0, filter4, 0);
AudioConnection          patchCord22(mixer5, 0, filter6, 0);
AudioConnection          patchCord23(filter2, 0, mixer2, 0);
AudioConnection          patchCord24(filter2, 2, mixer2, 1);
AudioConnection          patchCord25(filter4, 0, mixer4, 0);
AudioConnection          patchCord26(filter4, 2, mixer4, 1);
AudioConnection          patchCord27(filter6, 0, mixer6, 0);
AudioConnection          patchCord28(filter6, 2, mixer6, 1);
AudioConnection          patchCord29(filter8, 0, mixer8, 0);
AudioConnection          patchCord30(filter8, 2, mixer8, 1);
AudioConnection          patchCord31(mixer2, 0, filter3, 0);
AudioConnection          patchCord32(mixer6, 0, filter7, 0);
AudioConnection          patchCord33(mixer4, 0, filter5, 0);
AudioConnection          patchCord34(mixer8, 0, i2s2, 0);
AudioConnection          patchCord35(dc2, 0, i2s2, 1);
// GUItool: end automatically generated code






float f, regen, regenComp;
float q = 0.7;
float octave = 5;
float startFreq = 200;
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

  filter1.resonance(q);
  filter1.frequency(startFreq);
  filter1.octaveControl(octave);

  filter2.resonance(q);
  filter2.frequency(startFreq);
  filter2.octaveControl(octave);

  filter3.resonance(q);
  filter3.frequency(startFreq*2);
  filter3.octaveControl(octave);

  filter4.resonance(q);
  filter4.frequency(startFreq*2);
  filter4.octaveControl(octave);

  filter5.resonance(q);
  filter5.frequency(startFreq*4);
  filter5.octaveControl(octave);

  filter6.resonance(q);
  filter6.frequency(startFreq*4);
  filter6.octaveControl(octave);

  filter7.resonance(q);
  filter7.frequency(startFreq*8);
  filter7.octaveControl(octave);

  filter8.resonance(q);
  filter8.frequency(startFreq*8);
  filter8.octaveControl(octave);
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


