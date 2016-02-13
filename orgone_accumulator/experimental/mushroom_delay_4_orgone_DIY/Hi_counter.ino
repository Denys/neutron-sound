void FASTRUN Hi_counter(void) {
  Hi_count = Hi_count + Hi_count_rate;
  digitalWriteFast(Hi_counter_pin, Hi_count>>31);  
}
