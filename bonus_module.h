#ifndef BONUS_MODULE_H
#define BONUS_MODULE_H

#include "systemc.h"
#include "digit.h"

SC_MODULE(bonus_module) {
  sc_in<NN_DIGIT> t0_new_sig, t1_new_sig, c_sig;
  sc_in<NN_HALF_DIGIT> aLow_sig;
  sc_in<bool> ready_sig;
  sc_out<NN_HALF_DIGIT> aLow_new_sig;
  
  SC_CTOR(bonus_module) {
    SC_METHOD(bonus_method);
    sensitive << ready_sig;
  }
  
  void bonus_method() {
    if (ready_sig->read() == true) {
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
};

#endif // BONUS_MODULE_H
