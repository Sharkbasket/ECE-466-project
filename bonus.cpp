#include "bonus.h"

SC_HAS_PROCESS(bonus);

bonus::bonus(sc_module_name n) : sc_module(n) {
  SC_METHOD(bonus_method);
  sensitive << ready_sig;
}

void bonus::bonus_method() {
  if (ready_sig->read() == true) {
    // Sample inputs
    NN_DIGIT t0_new(t0_new_sig->read());
    NN_DIGIT t1_new(t1_new_sig->read());
    NN_DIGIT c(c_sig->read());
    NN_HALF_DIGIT aLow(aLow_sig->read());
    
    while ((t1_new > 0) || ((t1_new == 0) && (t0_new >= c))) {
      if ((t0_new -= c) > (MAX_NN_DIGIT - c)) {
        t1_new--;
      }
      aLow++;
    }
    aLow_new_sig->write(aLow);
  }
}
