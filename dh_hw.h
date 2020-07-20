#ifndef _DH_HW_H_
#define _DH_HW_H_ 1

#include "systemc.h"
#include "digit.h"
#include "bonus.h"

SC_MODULE(dh_hw) {
  // Ports
  sc_in<NN_DIGIT> from_sw0, from_sw1, from_sw2;
  sc_in<NN_HALF_DIGIT> from_sw3;
  sc_out<NN_HALF_DIGIT> to_sw;
  sc_in<bool> hw_enable;
  sc_out<bool> hw_done;
  
  // Internal signals
  sc_in_clk clock;
  sc_signal<NN_DIGIT> bonus_in0, bonus_in1;
  sc_signal<NN_HALF_DIGIT> bonus_out;
  
  // Internal control signals
  sc_signal<bool> ld_inputs, ld_t0_tmp, ld_t1_tmp0, ld_t0_new,
                  ld_t1_tmp1, ld_t1_new, bonus_ready, ld_output;
  
  // Submodule declarations
  bonus bonus_module;
  fsm_ctrl controller;
  
  // Constructor
  dh_hw(sc_module_name);
  
  // Processes
  void process_hw();
};

#endif /* end _DH_HW_H_ */
