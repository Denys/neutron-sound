just outputs a non interpolated sine on the SGTL5000 left channel.

#include "control_sgtl5000.h"
#include "kinetis.h"

#define LED_RED 3
#define LED_GREEN 4
#define LED_BLUE 5
#define SWITCH_OPTION_0 0
#define SWITCH_OPTION_1 1
#define SWITCH_CVIN_0 2
#define SWITCH_CVIN_1 3

const uint16_t Sine_Table[512] = {
  0, 402, 804, 1206, 1607, 2009, 2410, 2811, 3211, 3611, 4011, 4409, 4807, 5205, 5601, 5997, 6392,
  6786, 7179, 7571, 7961, 8351, 8739, 9126, 9511, 9895, 10278, 10659, 11038, 11416, 11792, 12166, 12539,
  12909, 13278, 13645, 14009, 14372, 14732, 15090, 15446, 15799, 16150, 16499, 16845, 17189, 17530, 17868, 18204,
  18537, 18867, 19194, 19519, 19840, 20159, 20474, 20787, 21096, 21402, 21705, 22004, 22301, 22594, 22883, 23169,
  23452, 23731, 24006, 24278, 24546, 24811, 25072, 25329, 25582, 25831, 26077, 26318, 26556, 26789, 27019, 27244,
  27466, 27683, 27896, 28105, 28309, 28510, 28706, 28897, 29085, 29268, 29446, 29621, 29790, 29955, 30116, 30272,
  30424, 30571, 30713, 30851, 30984, 31113, 31236, 31356, 31470, 31580, 31684, 31785, 31880, 31970, 32056, 32137,
  32213, 32284, 32350, 32412, 32468, 32520, 32567, 32609, 32646, 32678, 32705, 32727, 32744, 32757, 32764, 32767,
  32764, 32757, 32744, 32727, 32705, 32678, 32646, 32609, 32567, 32520, 32468, 32412, 32350, 32284, 32213, 32137,
  32056, 31970, 31880, 31785, 31684, 31580, 31470, 31356, 31236, 31113, 30984, 30851, 30713, 30571, 30424, 30272,
  30116, 29955, 29790, 29621, 29446, 29268, 29085, 28897, 28706, 28510, 28309, 28105, 27896, 27683, 27466, 27244,
  27019, 26789, 26556, 26318, 26077, 25831, 25582, 25329, 25072, 24811, 24546, 24278, 24006, 23731, 23452, 23169,
  22883, 22594, 22301, 22004, 21705, 21402, 21096, 20787, 20474, 20159, 19840, 19519, 19194, 18867, 18537, 18204,
  17868, 17530, 17189, 16845, 16499, 16150, 15799, 15446, 15090, 14732, 14372, 14009, 13645, 13278, 12909, 12539,
  12166, 11792, 11416, 11038, 10659, 10278, 9895, 9511, 9126, 8739, 8351, 7961, 7571, 7179, 6786, 6392,
  5997, 5601, 5205, 4807, 4409, 4011, 3611, 3211, 2811, 2410, 2009, 1607, 1206, 804, 402, 0,
  -402, -804, -1206, -1607, -2009, -2410, -2811, -3211, -3611, -4011, -4409, -4807, -5205, -5601, -5997, -6392,
  -6786, -7179, -7571, -7961, -8351, -8739, -9126, -9511, -9895, -10278, -10659, -11038, -11416, -11792, -12166, -12539,
  -12909, -13278, -13645, -14009, -14372, -14732, -15090, -15446, -15799, -16150, -16499, -16845, -17189, -17530, -17868, -18204,
  -18537, -18867, -19194, -19519, -19840, -20159, -20474, -20787, -21096, -21402, -21705, -22004, -22301, -22594, -22883, -23169,
  -23452, -23731, -24006, -24278, -24546, -24811, -25072, -25329, -25582, -25831, -26077, -26318, -26556, -26789, -27019, -27244,
  -27466, -27683, -27896, -28105, -28309, -28510, -28706, -28897, -29085, -29268, -29446, -29621, -29790, -29955, -30116, -30272,
  -30424, -30571, -30713, -30851, -30984, -31113, -31236, -31356, -31470, -31580, -31684, -31785, -31880, -31970, -32056, -32137,
  -32213, -32284, -32350, -32412, -32468, -32520, -32567, -32609, -32646, -32678, -32705, -32727, -32744, -32757, -32764, -32767,
  -32764, -32757, -32744, -32727, -32705, -32678, -32646, -32609, -32567, -32520, -32468, -32412, -32350, -32284, -32213, -32137,
  -32056, -31970, -31880, -31785, -31684, -31580, -31470, -31356, -31236, -31113, -30984, -30851, -30713, -30571, -30424, -30272,
  -30116, -29955, -29790, -29621, -29446, -29268, -29085, -28897, -28706, -28510, -28309, -28105, -27896, -27683, -27466, -27244,
  -27019, -26789, -26556, -26318, -26077, -25831, -25582, -25329, -25072, -24811, -24546, -24278, -24006, -23731, -23452, -23169,
  -22883, -22594, -22301, -22004, -21705, -21402, -21096, -20787, -20474, -20159, -19840, -19519, -19194, -18867, -18537, -18204,
  -17868, -17530, -17189, -16845, -16499, -16150, -15799, -15446, -15090, -14732, -14372, -14009, -13645, -13278, -12909, -12539,
  -12166, -11792, -11416, -11038, -10659, -10278, -9895, -9511, -9126, -8739, -8351, -7961, -7571, -7179, -6786, -6392,
  -5997, -5601, -5205, -4807, -4409, -4011, -3611, -3211, -2811, -2410, -2009, -1607, -1206, -804, -402,

};


int reading10, reading11, reading12, reading13;

struct oscillator1
{
  uint32_t phase = 0;  
  int32_t phase_increment = 0;
}o1;


AudioControlSGTL5000 audioShield;

void next_sample(int16_t *left_sample, int16_t *right_sample)
{
    o1.phase = o1.phase + o1.phase_increment;
    *left_sample = Sine_Table[o1.phase>>23];
    *right_sample = 32767;
}

void config_i2s(void)
{
    // MCLK needs to be 48e6 / 1088 * 256 = 11.29411765 MHz ->
    // 44.117647 kHz sample rate
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
    #elif F_CPU == 16000000
      #define MCLK_MULT 12
      #define MCLK_DIV  17
    #else
      #error "This CPU Clock Speed is not supported by the Audio library";
    #endif

    #if F_CPU >= 20000000
      #define MCLK_SRC  3  // the PLL
    #else
      #define MCLK_SRC  0  // system clock
    #endif

    SIM_SCGC6 |= SIM_SCGC6_I2S;

    // enable MCLK output
    I2S0_MCR = I2S_MCR_MICS(MCLK_SRC) | I2S_MCR_MOE;
    I2S0_MDR = I2S_MDR_FRACT((MCLK_MULT-1)) | I2S_MDR_DIVIDE((MCLK_DIV-1));

    // configure transmitter
    I2S0_TMR = 0;
    I2S0_TCR1 = I2S_TCR1_TFW(1);  // watermark at half fifo size
    I2S0_TCR2 = I2S_TCR2_SYNC(0) | I2S_TCR2_BCP | I2S_TCR2_MSEL(1)
              | I2S_TCR2_BCD | I2S_TCR2_DIV(3);
    I2S0_TCR3 = I2S_TCR3_TCE;
    I2S0_TCR4 = I2S_TCR4_FRSZ(1) | I2S_TCR4_SYWD(15) | I2S_TCR4_MF
              | I2S_TCR4_FSE | I2S_TCR4_FSP | I2S_TCR4_FSD;
    I2S0_TCR5 = I2S_TCR5_WNW(15) | I2S_TCR5_W0W(15) | I2S_TCR5_FBT(15);

    // configure pin mux for 3 clock signals
    CORE_PIN23_CONFIG = PORT_PCR_MUX(6); // pin 23, PTC2, I2S0_TX_FS (LRCLK)
    CORE_PIN9_CONFIG  = PORT_PCR_MUX(6); // pin  9, PTC3, I2S0_TX_BCLK
    CORE_PIN11_CONFIG = PORT_PCR_MUX(6); // pin 11, PTC6, I2S0_MCLK
    CORE_PIN22_CONFIG = PORT_PCR_MUX(6); // pin 22, PTC1, I2S0_TXD0
}

void setup_i2s()
{
    config_i2s();
    NVIC_ENABLE_IRQ(IRQ_I2S0_TX);
    I2S0_TCSR |= I2S_TCSR_TE
               | I2S_TCSR_BCE
               | I2S_TCSR_FR
               | I2S_TCSR_FRIE
               | I2S_TCSR_FEIE;
}

void i2s0_tx_isr(void)
{
    if (I2S0_TCSR & I2S_TCSR_FEF)
        I2S0_TCSR |= I2S_TCSR_FEF;
    while (I2S0_TCSR & I2S_TCSR_FRF) {
        int16_t left_sample, right_sample;
        next_sample(&left_sample, &right_sample);
        I2S0_TDR0 = left_sample;
        I2S0_TDR0 = right_sample;
    }
}

void setup()
{
    setup_i2s();
    audioShield.enable();    
    audioShield.volume(0.80); 
    analogReadResolution(12);
     pinMode (A10, INPUT);
  pinMode (A11, INPUT);
  pinMode (A12, INPUT);
  pinMode (LED_RED, OUTPUT);
  pinMode (LED_GREEN, OUTPUT);
  pinMode (LED_BLUE, OUTPUT);
}

void loop(){
 reading10 = (4095 - analogRead(A10)) ;
  reading11 = (4095 - analogRead(A11));
  reading12 = (4095 - analogRead(A12));
  o1.phase_increment = reading11 << 15;
   analogWrite(LED_RED, reading10);
  analogWrite(LED_GREEN, reading11);
  analogWrite(LED_BLUE, reading12);
}
