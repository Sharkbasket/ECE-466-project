#ifndef BONUS_H
#define BONUS_H

#include "systemc.h"
#include "digit.h"

SC_MODULE(bonus) {
  // Ports
  sc_in<NN_DIGIT> t0_new_sig, t1_new_sig, c_sig;
  sc_in<NN_HALF_DIGIT> aLow_sig;
  sc_in<bool> ready_sig;
  sc_out<NN_HALF_DIGIT> aLow_new_sig;
  
  // Constructor
  bonus(sc_module_name);
  
  // Processes
  void bonus_method();
};

#endif // BONUS_H
