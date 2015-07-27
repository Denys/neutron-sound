//neutron orgone accumulator config file. 


#define TUNEMULT 73750  
//this is the base frequency. halving it will lower the entire oscillator by 1 octave 
//real frequency is sent to the broadcast application for tuning

extern const int tuneStep = 1;//this is how many semitones the tuning knob steps in.

#define NOTESIZE 72.0 
// note resolution. lower value will give wider oscillator range, higher will give better resolution
//you will need to recalibrate the v/oct trimmer if you adjust this. decimal is important, even if zero.

#define LED_COMP 0 //dim the LEDSs higher number = lower brightness. (only for the position LEDs)

//DIY hardware 1.x boards--------------------------------------------------------------------start

#define LED_MODESWITCH_TIME 5000 //time LEDs stay on when mode is switched in main loop cycles, about 2-3000 per second depending on am/fm effects etc.

//LED compensation. adjusts how the LEDs fade across positions

#define FX_SWITCH 1

//0 = momentary
//1 = toggle

#define FX_N 7 //7 max (actually 8 due to binary counting)

//assign effects to slots in the rotation

#define FX0 0
#define FX1 1
#define FX2 5
#define FX3 10
#define FX4 12
#define FX5 4
#define FX6 2
#define FX7 11

//0 original orgone detune (D)eclick 
//1 original orgone detune with prime (D)
//2 delay effect (s)
//3 pulsar (D) (s)
//4 bit crush (D)(s)mooth waveselect
//5 wave folding (D) (s)
//6 modmod the modulation waveform can be changed with FX and FX CV EXPERIMENTAL (clicks)
//7 chords (equal temprement)
//8 chords (just tuning)
//9 Automatic Double Tracker (Another type of detune) EXPERIMENTAL no worky
//10 self multiplication with mod wave.  (D)(s)
//11 drum voice (D)
//12 XORible  (D)(s)

//DIY hardware 1.x boards--------------------------------------------------------------------end

#define PWM_SUB 2

//divider to use the PWM as a sub oscillator. DO NOT ENTER ZERO.
//1 = same as main.
//2 = 1 octave down
//4 = 2 octaves etc. 

#define PWM_MINIMUM 4

//128ths of a cycle the thinnest pulse can be. 0 will allow silence to fall.

#define PWM_CONTROL 1

//0 = position control and CV controls PWM across range
//1 = index controls PWM minimum PW to 50%, modified by index CV

// Broadcast ---------------------------
extern int BROADCAST;
// Broadcast ---------------------------

//chord intervals each group of 3 numbers is the triplet. dont change the amount of entries!
extern const int chordTable[] = {
  1, 3, 5,
  1, 4, 7,
  1, 3, 7,
  1, 4, 6,
  1, 3, 6,
  1, 5, 9,
  1, 4, 8,
  1, 3, 8,
  1, 4, 9,
};

#define DECLICK 32
//declicking. 4000 = normal operation
//higher number is faster ramp
//do not change the



 
