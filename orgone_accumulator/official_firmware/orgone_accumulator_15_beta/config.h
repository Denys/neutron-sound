//neutron orgone accumulator config file. you can save this between firmware updates. 

#define TUNEMULT 73750  //this is the base frequency. halving it will lower the entire oscillator by 1 octave 

#define NOTESIZE 72.0  // note resolution. lower value will give wider oscillator range, higher will give better resolution
//you will need to recalibrate the v/oct trimmer if you adjust this. decimal is important, even is zero.

#define LED_COMP 1000  //LED compensation. adjusts how the LEDs fade across positions

#define TUNE_LOCK_PROCESS 1

//0 = normal tune lock //dont use in this beta
//1 = bitcrush
//2 = alt modes. //dont use yet

#define CRUSHBITS 9
//this is the amount of bit reduction, (number>>CRUSHBITS)<<CRUSHBITS)
//only affected by bit crush
//valid numbers are 2 to 8 




 
