//just outputs a non interpolated sine on the SGTL5000 left channel.

#include "control_sgtl5000.h"//change to "sgtl5k.h" if using loopback
#include "kinetis.h"

uint16_t ramp;
int32_t left_sampleOut;
int32_t l_samp_bipol, left_sampleIn, right_sampleIn;
int32_t l_samp_wavemod;

const int16_t distoTable[] = {
  774,
  3255, 5130, 5823, 5674, 5738, 6628, 7769, 8453, 8125, 6772, 5433, 5936, 8441, 11545, 14187, 16225,
  17799, 19114, 20245, 21268, 22183, 23027, 23800, 24515, 25173, 25777, 26329, 26829, 27286, 27697, 28070, 28406,
  28714, 28990, 29245, 29472, 29686, 29877, 30056, 30218, 30371, 30510, 30640, 30759, 30871, 30975, 31070, 31162,
  31246, 31326, 31401, 31471, 31536, 31599, 31657, 31711, 31764, 31812, 31858, 31902, 31944, 31985, 32021, 32057,
  32092, 32123, 32155, 32184, 32211, 32238, 32263, 32287, 32311, 32333, 32354, 32376, 32394, 32412, 32432, 32448,
  32464, 32480, 32495, 32508, 32524, 32536, 32549, 32561, 32573, 32583, 32595, 32604, 32615, 32624, 32633, 32641,
  32648, 32659, 32665, 32672, 32679, 32685, 32691, 32697, 32703, 32708, 32714, 32719, 32723, 32728, 32731, 32734,
  32739, 32743, 32746, 32748, 32750, 32753, 32755, 32758, 32760, 32761, 32763, 32765, 32764, 32765, 32766, 32766,
  32766, 32766, 32766, 32766, 32765, 32765, 32764, 32763, 32762, 32759, 32757, 32754, 32752, 32750, 32747, 32744,
  32742, 32738, 32734, 32730, 32726, 32722, 32717, 32712, 32708, 32702, 32697, 32691, 32683, 32678, 32670, 32664,
  32656, 32648, 32641, 32631, 32622, 32613, 32604, 32593, 32582, 32571, 32560, 32549, 32537, 32522, 32510, 32495,
  32481, 32465, 32448, 32434, 32415, 32398, 32379, 32359, 32338, 32316, 32294, 32269, 32244, 32219, 32192, 32164,
  32133, 32103, 32070, 32035, 31999, 31960, 31920, 31878, 31834, 31786, 31737, 31684, 31627, 31569, 31506, 31438,
  31367, 31291, 31210, 31124, 31032, 30932, 30825, 30711, 30586, 30453, 30309, 30151, 29978, 29791, 29587, 29362,
  29115, 28842, 28539, 28201, 27825, 27401, 26923, 26382, 25765, 25057, 24240, 23286, 22073, 20404, 18362, 16720,
  16216, 16589, 17105, 17205, 16646, 15618, 14781, 14472, 14157, 13269, 11908, 10288, 8022, 5041, 2044, -673,
  -3179, -5047, -5747, -5585, -5663, -6546, -7702, -8376, -8056, -6688, -5353, -5842, -8368, -11477, -14139, -16178,
  -17763, -19077, -20220, -21239, -22162, -23006, -23782, -24497, -25158, -25765, -26316, -26820, -27275, -27689, -28062, -28399,
  -28706, -28986, -29239, -29470, -29680, -29875, -30051, -30215, -30367, -30506, -30637, -30756, -30868, -30973, -31069, -31161,
  -31245, -31324, -31399, -31469, -31534, -31597, -31655, -31709, -31762, -31811, -31858, -31902, -31944, -31983, -32021, -32057,
  -32090, -32123, -32153, -32183, -32211, -32238, -32263, -32286, -32310, -32334, -32354, -32375, -32394, -32412, -32430, -32448,
  -32463, -32480, -32494, -32509, -32524, -32535, -32548, -32560, -32573, -32584, -32593, -32604, -32613, -32623, -32632, -32640,
  -32649, -32657, -32664, -32672, -32679, -32685, -32691, -32697, -32703, -32708, -32714, -32719, -32723, -32728, -32731, -32735,
  -32738, -32742, -32745, -32748, -32751, -32753, -32755, -32758, -32758, -32761, -32763, -32763, -32765, -32764, -32766, -32766,
  -32766, -32766, -32766, -32766, -32765, -32764, -32763, -32762, -32760, -32759, -32757, -32754, -32752, -32750, -32747, -32744,
  -32741, -32738, -32734, -32730, -32726, -32722, -32716, -32712, -32707, -32702, -32696, -32690, -32684, -32677, -32671, -32663,
  -32655, -32647, -32640, -32631, -32622, -32613, -32603, -32593, -32582, -32571, -32560, -32548, -32535, -32523, -32509, -32495,
  -32480, -32464, -32449, -32432, -32415, -32397, -32377, -32357, -32337, -32314, -32292, -32269, -32243, -32218, -32193, -32163,
  -32132, -32102, -32069, -32034, -31998, -31961, -31919, -31878, -31833, -31785, -31735, -31682, -31627, -31567, -31504, -31438,
  -31366, -31289, -31208, -31122, -31031, -30930, -30823, -30709, -30584, -30449, -30306, -30146, -29977, -29787, -29584, -29357,
  -29111, -28835, -28533, -28194, -27817, -27390, -26914, -26370, -25752, -25040, -24224, -23265, -22051, -20374, -18324, -16679,
  -16171, -16550, -17059, -17167, -16600, -15582, -14726, -14432, -14099, -13227, -11843, -10241, -7938, -4989, -1915,
};

uint32_t reading10, reading11, reading12, reading13;

#define LED_RED 3
#define LED_GREEN 4
#define LED_BLUE 5
#define SWITCH_OPTION_0 0
#define SWITCH_OPTION_1 1
#define SWITCH_CVIN_0 2
#define SWITCH_CVIN_1 3


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

static inline int16_t saturate16(int32_t val) __attribute__((always_inline, unused));
static inline int16_t saturate16(int32_t val)
{
  int32_t out;
  int32_t tmp;
  asm volatile("ssat %0, %1, %2" : "=r" (tmp) : "I" (16), "r" (val) );
  out = (int16_t) (tmp); // not sure if the & 0xffff is necessary. test.
  return out;
}

AudioControlSGTL5000 audioShield;

//static inline int16_t saturate16(int32_t val) __attribute__((always_inline, unused));

void setup() {
  Serial.begin(250000);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Serial.print("Serial Clock: ");
  Serial.println(MCLK_SRC);
  Serial.print(" ");
  setup_i2s();
  analogWriteResolution(12);
  analogReadResolution(12);
  analogWrite(A14, 0); //temp for colorCV card prototype that has offset
  pinMode (A10, INPUT);
  pinMode (A11, INPUT);
  pinMode (A12, INPUT);
  pinMode (LED_RED, OUTPUT);
  pinMode (LED_GREEN, OUTPUT);
  pinMode (LED_BLUE, OUTPUT);

  audioShield.disable();
  delay(200);
  audioShield.enable();
  audioShield.volume(0.40);
  audioShield.audioProcessorDisable();
  audioShield.inputSelect(AUDIO_INPUT_LINEIN);
  //audioShield.write(0x000A, 0x0011);//loopback for testing REMINDER! loopback only works with custom sgtl5k.h

  //audioShield.audioPostProcessorEnable();
  //audioShield.autoVolumeControl(2, 1, 1, -18.5, 10.0, 10.0);//would like to use this compressor, but makes the output really low
  //audioShield.autoVolumeEnable();
  audioShield.lineInLevel(0); //use full scale
  audioShield.dacVolume(1.0);
  audioShield.lineOutLevel(9);

}

void loop() {
  //reading10 = (4095 - analogRead(A10)) ;
  //reading11 = (4095 - analogRead(A11));
  reading12 = (4095 - analogRead(A12));
  analogWrite(LED_RED, reading10);
  analogWrite(LED_GREEN, reading11);
  analogWrite(LED_BLUE, reading12);

  Serial.println(left_sampleOut);
  //Serial.println(left_sampleIn);

}


