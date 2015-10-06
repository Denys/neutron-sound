void loop() { 
  
//  SWC ++;
//  if (SWC > 1000){
    
    
  Serial.print("\t");
  Serial.print("A16,pos CV = ");  
  Serial.print(CVinPOS);
  
  Serial.print("\t");
  Serial.print("A12,detune CV = "); 
  Serial.print(CVinDETUNE);
  
  Serial.print("\t");
  Serial.print("A15,Index CV = ");   
  Serial.print(CVinINDEX);
  
  Serial.print("\t");
  Serial.print("A17,freq CV = ");  
  Serial.println(CVinFREQ); 

 analogWrite(aout2, CVinDETUNE);
  
  LEDToggle = ! LEDToggle;
 
 SWC = 0; 
  
  
    
  
  
  //--------------------------------------------------------  
  CVinNOTE = analogRead(A0); //main v/oct CV in. only use 12 bits of analog in SEPERATE AINS BY CODE 
  //--------------------------------------------------------  

  //------------------------------Position CV---------------------
  CVinPOS = analogRead(A16) ;  
  //------------------------------------------------------------------
 
  //---------------------------------------------------------------------  
CVinFREQ = analogRead(A17);


  //---------------------------Detune CV----------------
  CVinDETUNE = analogRead(A12);  
  //--------------------------------------------------

  
  //---------------------------Index CV---------------------------------
  CVinINDEX = analogRead(A15);
  //----------------------------------------------------------------------

  

  UPDATE_LEDS();

}




