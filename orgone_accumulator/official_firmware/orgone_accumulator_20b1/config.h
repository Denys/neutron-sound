//neutron orgone accumulator config file. 

#define TUNEMULT 73750  
//this is the base frequency. halving it will lower the entire oscillator by 1 octave 

#define NOTESIZE 72.0 
// note resolution. lower value will give wider oscillator range, higher will give better resolution
//you will need to recalibrate the v/oct trimmer if you adjust this. decimal is important, even if zero.

#define LED_COMP 1000  

//LED compensation. adjusts how the LEDs fade across positions

#define FX_SWITCH 0

//0 = momentary
//1 = toggle

#define FX_N 4

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

#define FX_SELECT_EXT 0

//do not change, for effect select sub panel.

 




 
