//WARNING WILL ROBINSON!!!!!!!!!!!!!!!!!!
//THIS IS NOT FINAL CODE, JUST A TEST FOR THE ANALOG INPUTS HIDDEN OPN THE SMD INPUTS OF THE TEENSY
//SET SERIAL MONITOR TO 28800





int CVinNOTE;
int CVinPOS;
int CVinDETUNE;
int CVinINDEX;
int CVinFREQ;

int LEDToggle;

int SWC;



#define LED_TuneLock 8
#define LED_Lo 25
#define LED_Mid 9
#define LED_Hi 10

//int waveIncrement = 1;

#define oSQout 11 //square wave out
#define gateIn 12

int aout2 = A14; //dac out




// the setup routine runs once when you press reset:
void setup() {                 
  
  pinMode(aout2, OUTPUT);
  //pinMode(ISRtestPin, OUTPUT); 
  //pinMode(aReadTestPin, OUTPUT);
  pinMode(oSQout, OUTPUT); 
  pinMode(13, OUTPUT);     
  pinMode(A0, INPUT); 
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  pinMode(A8, INPUT);
  pinMode(A9, INPUT);
  pinMode(A10, INPUT);
  pinMode(A11, INPUT);
  pinMode(A12, INPUT);
  pinMode(A15, INPUT);
  pinMode(A16, INPUT);
  pinMode(A17, INPUT);
  
  pinMode(0, INPUT_PULLUP);
  digitalWrite(0, HIGH);
  pinMode(1, INPUT_PULLUP);
  digitalWrite(1, HIGH);
  pinMode(2, INPUT_PULLUP);
  digitalWrite(2, HIGH);
  pinMode(3, INPUT_PULLUP);
  digitalWrite(3, HIGH);
  pinMode(4, INPUT_PULLUP);
  digitalWrite(4, HIGH);
  pinMode(5, INPUT_PULLUP);
  digitalWrite(5, HIGH);
  pinMode(6, INPUT_PULLUP);
  digitalWrite(6, HIGH);
  pinMode(7, INPUT_PULLUP);
  digitalWrite(7, HIGH);   
  pinMode(gateIn, INPUT);
  
  pinMode(LED_TuneLock, OUTPUT);
pinMode(LED_Lo, OUTPUT);
pinMode(LED_Mid, OUTPUT);
pinMode(LED_Hi, OUTPUT);
//pinMode(LED_PWM, OUTPUT);
  
  digitalWrite(13, HIGH);
  
  analogReference(EXTERNAL);
  analogWriteResolution(13); 
  analogReadResolution(13); 
  analogReadAveraging(32);  
  //analogWriteFrequency(14, 80000);
  //outUpdateTimer.begin(outUpdateISR, 12); //this is the output update rate in uS
 

 

  Serial.begin(38400);
}

//see other pages for 
//MAIN_LOOP = void loop() work happens between main ISR.
//MODMODEASSIGN void ASSIGNINCREMENTS() sets which oscs get what increment depending on mode. rate is 1 per main loop.
//UPDATECONTROLS void UPDATECONTROLS()do things that can be slow, steps through a different control each main loop with ARC.
//OSC_ISR void outUpdateISR(void) this happens at the update frequency set by outUpdateTimer.begin only put time critical stuff here.










