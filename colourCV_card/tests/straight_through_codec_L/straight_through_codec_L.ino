//Test the colorcv accepts input and writes to output

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
AudioInputI2S            i2s1;           //xy=97,114
AudioOutputI2S           i2s2;           //xy=606,131
AudioConnection          patchCord1(i2s1, 0, i2s2, 0);
AudioControlSGTL5000 audioShield;

int reading10, reading11, reading12, reading13;

void setup() {

  AudioMemory(4);
analogReadResolution(12);
  analogWriteResolution(12);
  // Enable the audio shield and set the output volume.
  audioShield.enable();
  //audioShield.inputSelect(myInput); 
  audioShield.volume(0.0); //used for headphones but set to 0 anyways.
  audioShield.lineInLevel(10); //use full scale
  audioShield.lineOutLevel(13);
  audioShield.audioProcessorDisable();
  pinMode (A10, INPUT);
  pinMode (A11, INPUT);
  pinMode (A12, INPUT);
  pinMode (LED_RED, OUTPUT);
  pinMode (LED_GREEN, OUTPUT);
  pinMode (LED_BLUE, OUTPUT);

  
}

void loop() {
 reading10 = (4095 - analogRead(A10)) ;
  reading11 = (4095 - analogRead(A11));
  reading12 = (4095 - analogRead(A12));
    analogWrite(LED_RED, reading10);
  analogWrite(LED_GREEN, reading11);
  analogWrite(LED_BLUE, reading12);
}


