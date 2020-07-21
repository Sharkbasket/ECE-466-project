#ifndef FSM_CTRL_H
#define FSM_CTRL_H

#include "systemc.h"
#include "digit.h"

SC_MODULE(fsm_ctrl) {
  // Define states
  enum State {
    RESET, WAIT, INPUT, EXE_0, EXE_1, EXE_2, EXE_3, EXE_4, EXE_5, OUTPUT, DONE
  };
  
  // Ports
  sc_in_clk clock;
  sc_in<bool> hw_enable;
  sc_out<bool> ld_inputs;
  sc_out<bool> ld_t0_tmp;
  sc_out<bool> ld_t1_tmp0;
  sc_out<bool> ld_t0_new;
  sc_out<bool> ld_t1_tmp1;
  sc_out<bool> ld_t1_new;
  sc_out<bool> bonus_ready;
  sc_out<bool> ld_output;
  sc_out<bool> hw_done;
  
  // Constructor
  fsm_ctrl(sc_module_name);
  
  // Processes
  void fsm_process();
  
  // Data members
  State state;
};

#endif // FSM_CTRL_H
