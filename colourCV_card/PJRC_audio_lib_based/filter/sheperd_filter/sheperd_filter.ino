//Neutron sound 8 way shepard filter for TeenCV
// 8 band pass filters continuously up or down depending on cv.

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
AudioSynthWaveformDc     dc4;            //xy=78.33332824707031,243.3333282470703
AudioSynthWaveformDc     dc3;            //xy=83.33332824707031,181.33334350585938
AudioSynthWaveformDc     dc1;            //xy=86.99998474121094,81.99999237060547
AudioSynthWaveformDc     dc2;            //xy=87.58308410644531,129.33346557617188
AudioInputI2S            i2s1;           //xy=87.33332824707031,308.3333435058594
AudioSynthWaveformDc     dc5;            //xy=89.33332824707031,373.3333282470703
AudioSynthWaveformDc     dc7;            //xy=89.33332824707031,473.3333282470703
AudioSynthWaveformDc     dc8;            //xy=90.33332824707031,534.3333282470703
AudioSynthWaveformDc     dc6;            //xy=98.33332824707031,428.3333282470703
AudioFilterStateVariable filter1;        //xy=299.33331298828125,129.33334350585938
AudioFilterStateVariable filter3;        //xy=300.33331298828125,241.33334350585938
AudioFilterStateVariable filter2;        //xy=301.33331298828125,186.33334350585938
AudioFilterStateVariable filter4;        //xy=301.33331298828125,297.33331298828125
AudioFilterStateVariable filter5;        //xy=302.33331298828125,375.33331298828125
AudioFilterStateVariable filter6;        //xy=303.33331298828125,430.3333435058594
AudioFilterStateVariable filter7;        //xy=305.33331298828125,488.3333435058594
AudioFilterStateVariable filter8;        //xy=307.33331298828125,546.3333129882812
AudioMixer4              mixer1;         //xy=634.3333129882812,206.33334350585938
AudioMixer4              mixer2;         //xy=638.3333129882812,445.3333435058594
AudioMixer4              mixer3;         //xy=796.3333129882812,340.33331298828125
AudioSynthWaveformDc     dc9;            //xy=838.3333282470703,408.3333282470703
AudioOutputI2S           i2s2;           //xy=1016.2496948242188,349.0001525878906
AudioConnection          patchCord1(dc4, 0, filter4, 1);
AudioConnection          patchCord2(dc3, 0, filter3, 1);
AudioConnection          patchCord3(dc1, 0, filter1, 1);
AudioConnection          patchCord4(dc2, 0, filter2, 1);
AudioConnection          patchCord5(i2s1, 0, filter1, 0);
AudioConnection          patchCord6(i2s1, 0, filter2, 0);
AudioConnection          patchCord7(i2s1, 0, filter3, 0);
AudioConnection          patchCord8(i2s1, 0, filter4, 0);
AudioConnection          patchCord9(i2s1, 0, filter5, 0);
AudioConnection          patchCord10(i2s1, 0, filter6, 0);
AudioConnection          patchCord11(i2s1, 0, filter7, 0);
AudioConnection          patchCord12(i2s1, 0, filter8, 0);
AudioConnection          patchCord13(dc5, 0, filter5, 1);
AudioConnection          patchCord14(dc7, 0, filter7, 1);
AudioConnection          patchCord15(dc8, 0, filter8, 1);
AudioConnection          patchCord16(dc6, 0, filter6, 1);
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
AudioConnection          patchCord28(dc9, 0, i2s2, 1);
// GUItool: end automatically generated code



uint32_t O_phase;
int32_t O_phaseInc; 
float octave = 4;
float startFreq = 200;
float freqOffset = 0;
int reading10, reading11, reading12, reading13;

const int16_t ramp_Table[256] = {
 -32511, -32255, -31998, -31743, -31487, -31231, -30974, -30719, -30463, -30207, -29951, -29695, -29439, -29183, -28927, -28671,
  -28415, -28159, -27903, -27647, -27391, -27135, -26879, -26623, -26367, -26111, -25855, -25599, -25343, -25087, -24831, -24575,
  -24319, -24063, -23807, -23551, -23295, -23039, -22783, -22527, -22271, -22015, -21759, -21503, -21247, -20991, -20735, -20479,
  -20223, -19967, -19711, -19455, -19199, -18943, -18687, -18431, -18175, -17919, -17663, -17407, -17151, -16895, -16639, -16383,
  -16127, -15871, -15615, -15359, -15103, -14847, -14591, -14335, -14079, -13823, -13567, -13311, -13055, -12799, -12543, -12287,
  -12031, -11775, -11519, -11263, -11007, -10751, -10495, -10239, -9983, -9727, -9471, -9215, -8959, -8703, -8447, -8191,
  -7935, -7679, -7423, -7167, -6911, -6655, -6399, -6143, -5887, -5631, -5375, -5119, -4863, -4608, -4351, -4095,
  -3839, -3584, -3327, -3071, -2815, -2559, -2303, -2047, -1791, -1535, -1279, -1023, -767, -511, -255, 0,
  255, 511, 767, 1023, 1279, 1535, 1791, 2047, 2303, 2559, 2815, 3071, 3327, 3584, 3839, 4095,
  4351, 4608, 4863, 5119, 5375, 5631, 5887, 6143, 6399, 6655, 6911, 7167, 7423, 7679, 7935, 8191,
  8447, 8703, 8959, 9215, 9471, 9727, 9983, 10239, 10495, 10751, 11007, 11263, 11519, 11775, 12031, 12287,
  12543, 12799, 13055, 13311, 13567, 13823, 14079, 14335, 14591, 14847, 15103, 15359, 15615, 15871, 16127, 16383,
  16639, 16895, 17151, 17407, 17663, 17919, 18175, 18431, 18687, 18943, 19199, 19455, 19711, 19967, 20223, 20479,
  20735, 20991, 21247, 21503, 21759, 22015, 22271, 22527, 22783, 23039, 23295, 23551, 23807, 24063, 24319, 24575,
  24831, 25087, 25343, 25599, 25855, 26111, 26367, 26623, 26879, 27135, 27391, 27647, 27903, 28159, 28415, 28671,
  28927, 29183, 29439, 29695, 29951, 30207, 30463, 30719, 30974, 31231, 31487, 31743, 31998, 32255, 32511, 32767,
};

const uint16_t AMP_Table[512] = {
  2,4,11,24,41,63,90,122,159,201,248,300,356,418,484,555
,631,712,798,888,983,1084,1188,1298,1412,1532,1655,1784,1917,2055,2197,2344
,2496,2652,2813,2978,3147,3322,3500,3683,3871,4062,4258,4459,4663,4872,5085,5302
,5524,5749,5979,6212,6450,6691,6937,7186,7439,7696,7957,8222,8490,8762,9037,9316
,9599,9885,10174,10467,10764,11063,11366,11672,11981,12294,12609,12928,13249,13574,13901,14231
,14564,14900,15238,15579,15923,16269,16618,16969,17322,17678,18036,18396,18759,19123,19490,19859
,20229,20602,20976,21352,21730,22109,22490,22873,23257,23642,24029,24417,24807,25197,25589,25982
,26376,26771,27167,27563,27961,28359,28757,29157,29557,29957,30358,30759,31161,31562,31964,32366
,32768,33170,33572,33974,34375,34777,35178,35579,35979,36379,36779,37177,37575,37973,38369,38765
,39160,39554,39947,40339,40729,41119,41507,41894,42279,42663,43046,43427,43806,44184,44560,44934
,45307,45677,46046,46413,46777,47140,47500,47858,48214,48567,48918,49267,49613,49957,50298,50636
,50972,51305,51635,51962,52287,52608,52927,53242,53555,53864,54170,54473,54772,55069,55362,55651
,55937,56220,56499,56774,57046,57314,57579,57840,58097,58350,58599,58845,59086,59324,59557,59787
,60012,60234,60451,60664,60873,61077,61278,61474,61665,61853,62036,62214,62389,62558,62723,62884
,63040,63192,63339,63481,63619,63752,63881,64004,64124,64238,64348,64452,64553,64648,64738,64824
,64905,64981,65052,65118,65180,65236,65288,65335,65377,65414,65446,65473,65495,65512,65525,65532
,65534,65532,65525,65512,65495,65473,65446,65414,65377,65335,65288,65236,65180,65118,65052,64981
,64905,64824,64738,64648,64553,64452,64348,64238,64124,64004,63881,63752,63619,63481,63339,63192
,63040,62884,62723,62558,62389,62214,62036,61853,61665,61474,61278,61077,60873,60664,60451,60234
,60012,59787,59557,59324,59086,58845,58599,58350,58097,57840,57579,57314,57046,56774,56499,56220
,55937,55651,55362,55069,54772,54473,54170,53864,53555,53242,52927,52608,52287,51962,51635,51305
,50972,50636,50298,49957,49613,49267,48918,48567,48214,47858,47500,47140,46777,46413,46046,45677
,45307,44934,44560,44184,43806,43427,43046,42663,42279,41894,41507,41119,40729,40339,39947,39554
,39160,38765,38369,37973,37575,37177,36779,36379,35979,35579,35178,34777,34375,33974,33572,33170
,32768,32366,31964,31562,31161,30759,30358,29957,29557,29157,28757,28359,27961,27563,27167,26771
,26376,25982,25589,25197,24807,24417,24029,23642,23257,22873,22490,22109,21730,21352,20976,20602
,20229,19859,19490,19123,18759,18396,18036,17678,17322,16969,16618,16269,15923,15579,15238,14900
,14564,14231,13901,13574,13249,12928,12609,12294,11981,11672,11366,11063,10764,10467,10174,9885
,9599,9316,9037,8762,8490,8222,7957,7696,7439,7186,6937,6691,6450,6212,5979,5749
,5524,5302,5085,4872,4663,4459,4258,4062,3871,3683,3500,3322,3147,2978,2813,2652
,2496,2344,2197,2055,1917,1784,1655,1532,1412,1298,1188,1084,983,888,798,712
,631,555,484,418,356,300,248,201,159,122,90,63,41,24,11,4,

};

AudioControlSGTL5000 audioShield;
void Oscillator(void);
void setup() {
  
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(24);
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
  dc9.amplitude(1);// for prototype mixer offset

  mixer1.gain(0, 1);
  mixer1.gain(1, 0);
  mixer1.gain(2, 0);
  mixer1.gain(3, 0);
  mixer2.gain(0, 0);
  mixer2.gain(1, 0);
  mixer2.gain(2, 0);
  mixer2.gain(3, 0);
  mixer3.gain(0, 1);
  mixer3.gain(1, 1);
 


  filter1.resonance(5);
  filter1.frequency(startFreq);
  filter1.octaveControl(octave);

  filter2.resonance(5);
  filter2.frequency(startFreq);
  filter2.octaveControl(octave);

  filter3.resonance(5);
  filter3.frequency(startFreq);
  filter3.octaveControl(octave);

  filter4.resonance(5);
  filter4.frequency(startFreq);
  filter4.octaveControl(octave);

  filter5.resonance(5);
  filter5.frequency(startFreq);
  filter5.octaveControl(octave);

  filter6.resonance(5);
  filter6.frequency(startFreq);
  filter6.octaveControl(octave);

  filter7.resonance(5);
  filter7.frequency(startFreq);
  filter7.octaveControl(octave);

  filter8.resonance(5);
  filter8.frequency(startFreq);
  filter8.octaveControl(octave);
    
}

void loop() {
  reading10 = (4095 - analogRead(A10)) ;
  reading11 = (4095 - analogRead(A11));
  reading12 = (4095 - analogRead(A12));

  O_phaseInc = int32_t(reading10-2048)<<7 ;
  
  freqOffset = reading12/4.5;

  filter1.frequency(startFreq+freqOffset);
  filter2.frequency(startFreq+freqOffset);
  filter3.frequency(startFreq+freqOffset);
  filter4.frequency(startFreq+freqOffset);
  filter5.frequency(startFreq+freqOffset);
  filter6.frequency(startFreq+freqOffset);
  filter7.frequency(startFreq+freqOffset);
  filter8.frequency(startFreq+freqOffset);  
 
Oscillator();
 
//    Serial.print("all=");
//    Serial.print(AudioProcessorUsage());
//    Serial.print(", ");
//    Serial.print(AudioProcessorUsageMax());
//    Serial.print("    ");
//    Serial.print("Memory: ");
//    Serial.print(AudioMemoryUsage());
//    Serial.print(",  ");
//    Serial.print(AudioMemoryUsageMax());
//    Serial.println("");

  analogWrite(LED_RED, reading10);
  analogWrite(LED_GREEN, reading11);
  analogWrite(LED_BLUE, reading12);
}

void FASTRUN Oscillator() {
  O_phase = O_phase + O_phaseInc;
  dc1.amplitude(float(ramp_Table[O_phase>>24])/32768.0);
  mixer1.gain(0, float(AMP_Table[O_phase>>23])/65536.0);
  dc2.amplitude(float(ramp_Table[uint32_t(O_phase+536870912)>>24])/32768.0);
  mixer1.gain(1, float(AMP_Table[uint32_t(O_phase+536870912)>>23])/65536.0);
  dc3.amplitude(float(ramp_Table[uint32_t(O_phase+1073741824)>>24])/32768.0);
  mixer1.gain(2, float(AMP_Table[uint32_t(O_phase+1073741824)>>23])/65536.0);
  dc4.amplitude(float(ramp_Table[uint32_t(O_phase+1610612736)>>24])/32768.0);
  mixer1.gain(3, float(AMP_Table[uint32_t(O_phase+1610612736)>>23])/65536.0);
  dc5.amplitude(float(ramp_Table[uint32_t(O_phase+2147483648)>>24])/32768.0);
  mixer2.gain(0, float(AMP_Table[uint32_t(O_phase+2147483648)>>23])/65536.0);
  dc6.amplitude(float(ramp_Table[uint32_t(O_phase+2684354560)>>24])/32768.0);
  mixer2.gain(1, float(AMP_Table[uint32_t(O_phase+2684354560)>>23])/65536.0);
  dc7.amplitude(float(ramp_Table[uint32_t(O_phase+3221225472)>>24])/32768.0);
  mixer2.gain(2, float(AMP_Table[uint32_t(O_phase+3221225472)>>23])/65536.0);
  dc8.amplitude(float(ramp_Table[uint32_t(O_phase+3758096384)>>24])/32768.0);
  mixer2.gain(3, float(AMP_Table[uint32_t(O_phase+3758096384)>>23])/65536.0);
  
}

