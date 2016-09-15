//just outputs a non interpolated sine on the SGTL5000 left channel.

#include "sgtl5k.h"
#include "kinetis.h"

volatile int16_t left_sampleOut, left_sampleIn;
volatile uint32_t in_c, out_c = 0;


// MCLK needs to be 48e6 / 1088 * 256 = 11.29411765 MHz -> 44.117647 kHz sample rate
//
#if F_CPU == 96000000 || F_CPU == 48000000 || F_CPU == 24000000
// PLL is at 96 MHz in these modes
#define MCLK_MULT 2
#define MCLK_DIV  17
#elif F_CPU == 72000000
#define MCLK_MULT 8
#define MCLK_DIV  51
#elif F_CPU == 120000000
#define MCLK_MULT 8
#define MCLK_DIV  85
#elif F_CPU == 144000000
#define MCLK_MULT 4
#define MCLK_DIV  51
#elif F_CPU == 168000000
#define MCLK_MULT 8
#define MCLK_DIV  119
#elif F_CPU == 180000000
#define MCLK_MULT 16
#define MCLK_DIV  255
#define MCLK_SRC  0
#elif F_CPU == 192000000
#define MCLK_MULT 1
#define MCLK_DIV  17
#elif F_CPU == 216000000
#define MCLK_MULT 8
#define MCLK_DIV  153
#define MCLK_SRC  0
#elif F_CPU == 240000000
#define MCLK_MULT 4
#define MCLK_DIV  85
#elif F_CPU == 16000000
#define MCLK_MULT 12
#define MCLK_DIV  17
#else
#error "This CPU Clock Speed is not supported by the Audio library";
#endif

#ifndef MCLK_SRC
#if F_CPU >= 20000000
#define MCLK_SRC  3  // the PLL
#else
#define MCLK_SRC  0  // system clock
#endif
#endif

void config_i2s() {
SIM_SCGC6 |= SIM_SCGC6_I2S; // System Gate from I2S

// if either transmitter or receiver is enabled, do nothing
if (I2S0_TCSR & I2S_TCSR_TE) return;
if (I2S0_RCSR & I2S_RCSR_RE) return;

Serial.printf("***Not Enabled");

// enable MCLK output
I2S0_MCR = I2S_MCR_MICS(MCLK_SRC) | I2S_MCR_MOE;
while (I2S0_MCR & I2S_MCR_DUF) ;
I2S0_MDR = I2S_MDR_FRACT((MCLK_MULT - 1)) | I2S_MDR_DIVIDE((MCLK_DIV - 1));

// configure transmitter
I2S0_TMR = 0;
I2S0_TCR1 = I2S_TCR1_TFW(1);  // watermark at half fifo size
I2S0_TCR2 = I2S_TCR2_SYNC(0) | I2S_TCR2_BCP | I2S_TCR2_MSEL(1)
            | I2S_TCR2_BCD | I2S_TCR2_DIV(3);
I2S0_TCR3 = I2S_TCR3_TCE;
I2S0_TCR4 = I2S_TCR4_FRSZ(1) | I2S_TCR4_SYWD(15) | I2S_TCR4_MF
            | I2S_TCR4_FSE | I2S_TCR4_FSP | I2S_TCR4_FSD;
I2S0_TCR5 = I2S_TCR5_WNW(15) | I2S_TCR5_W0W(15) | I2S_TCR5_FBT(15);

// configure receiver (sync'd to transmitter clocks)
I2S0_RMR = 0;
I2S0_RCR1 = I2S_RCR1_RFW(1);
I2S0_RCR2 = I2S_RCR2_SYNC(1) | I2S_TCR2_BCP | I2S_RCR2_MSEL(1)
            | I2S_RCR2_BCD | I2S_RCR2_DIV(3);
I2S0_RCR3 = I2S_RCR3_RCE;
I2S0_RCR4 = I2S_RCR4_FRSZ(1) | I2S_RCR4_SYWD(15) | I2S_RCR4_MF
            | I2S_RCR4_FSE | I2S_RCR4_FSP | I2S_RCR4_FSD;
I2S0_RCR5 = I2S_RCR5_WNW(15) | I2S_RCR5_W0W(15) | I2S_RCR5_FBT(15);

// configure pin mux for 3 clock signals
CORE_PIN23_CONFIG = PORT_PCR_MUX(6); // pin 23, PTC2, I2S0_I2STX_FS (LRCLK)
CORE_PIN9_CONFIG  = PORT_PCR_MUX(6); // pin  9, PTC3, I2S0_TX_BCLK
CORE_PIN11_CONFIG = PORT_PCR_MUX(6); // pin 11, PTC6, I2S0_MCLK


CORE_PIN22_CONFIG = PORT_PCR_MUX(6); // pin 22, PTC1, I2S0_TXD0

// Run and use plotter, get zigzag. Unncomment below, run againt, straight line at 255
CORE_PIN13_CONFIG = PORT_PCR_MUX(4); // pin 13, PTC5, I2S0_RXD0

}


void setup_i2s()
{
  config_i2s();
  
  NVIC_ENABLE_IRQ(IRQ_I2S0_RX);
  I2S0_RCSR |= I2S_RCSR_RE
               | I2S_RCSR_BCE
               | I2S_RCSR_FR
               | I2S_RCSR_FRIE;
               
  
  NVIC_ENABLE_IRQ(IRQ_I2S0_TX);  
  I2S0_TCSR |= I2S_TCSR_TE
               | I2S_TCSR_BCE
               | I2S_TCSR_FR
               | I2S_TCSR_FRIE;               

}


void i2s0_rx_isr(void) {
  in_c++;
  left_sampleIn = I2S0_RDR0;

  // Call your function to handle the data
  //   fnI2SCallback( _i2s_Rx_Buffer );
  if (I2S0_RCSR & I2S_RCSR_FEF) I2S0_RCSR |= I2S_RCSR_FEF; // clear if underrun
  if (I2S0_RCSR & I2S_RCSR_SEF) I2S0_RCSR |= I2S_RCSR_SEF; // clear if frame sync error
}


void i2s0_tx_isr(void) {
  out_c++;
  if (I2S0_TCSR & I2S_TCSR_FEF) {
    I2S0_TCSR |= I2S_TCSR_FEF;
  }

  while (I2S0_TCSR & I2S_TCSR_FRF) {
    next_sample();
    I2S0_TDR0 = left_sampleOut;
  }
}

AudioControlSGTL5000 audioShield;

void setup() {
  Serial.begin(230400);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Serial.print("Serial Clock: ");
  Serial.println(MCLK_SRC);
  Serial.println();
  setup_i2s();
  audioShield.enable();
  audioShield.volume(0.50);
  audioShield.audioProcessorDisable();
  audioShield.inputSelect(AUDIO_INPUT_LINEIN);
  //audioShield.write(0x000A, 0x0011);
  audioShield.lineInLevel(5); //use full scale
  audioShield.lineOutLevel(5);

}

void loop() {
//  Serial.println('-'); 
 // Serial.println(left_sampleOut);
//  Serial.println(left_sampleIn);
//  Serial.println(out_c);
//  Serial.println(in_c);
  delay(10);
  
}

void next_sample() {
  left_sampleOut = out_c++;
}
