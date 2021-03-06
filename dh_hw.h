#ifndef _DH_HW_H_
#define _DH_HW_H_ 1

#include "systemc.h"
#include "digit.h"
#include "bonus_module.h"
#include "fsm_ctrl.h"
#include "splitter.h"
#include "simple_reg.h"
#include "multiplier.h"
#include "subtractor.h"
#include "comparator.h"
#include "multiplexer.h"
#include "left_shifter.h"
#include "right_shifter.h"

SC_MODULE(dh_hw) {
  // Constructor declaration
  dh_hw(sc_module_name);
  
  // Port declarations
  sc_in<NN_DIGIT> from_sw0;
  sc_in<NN_DIGIT> from_sw1;
  sc_in<NN_DIGIT> from_sw2;
  sc_in<NN_HALF_DIGIT> from_sw3;
  sc_out<NN_HALF_DIGIT> to_sw;
  sc_in<bool> hw_enable;
  sc_out<bool> hw_done;
  
  // Start of submodule declarations
  bonus_module bonus;
  
  fsm_ctrl controller;
  
  splitter_32to16 splitter;
  
  simple_reg<NN_DIGIT> t0_reg;
  simple_reg<NN_DIGIT> t0_tmp_reg;
  simple_reg<NN_DIGIT> t0_new_reg;
  simple_reg<NN_DIGIT> t1_reg;
  simple_reg<NN_DIGIT> t1_tmp0_reg;
  simple_reg<NN_DIGIT> t1_tmp1_reg;
  simple_reg<NN_DIGIT> t1_new_reg;
  simple_reg<NN_DIGIT> c_reg;
  simple_reg<NN_HALF_DIGIT> aLow_reg;
  simple_reg<NN_HALF_DIGIT> aLow_new_reg;
  
  multiplier mult_0;
  multiplier mult_1;
  
  subtractor<NN_DIGIT> sub_0;
  subtractor<NN_DIGIT> sub_1;
  subtractor<NN_DIGIT> sub_2;
  subtractor<NN_DIGIT> sub_3;
  subtractor<NN_DIGIT> sub_4;
  subtractor<NN_DIGIT> sub_5;
  subtractor<NN_DIGIT> sub_6;
  
  comparator<NN_DIGIT> cmp_0;
  comparator<NN_DIGIT> cmp_1;
  
  multiplexer<NN_DIGIT> mux_0;
  multiplexer<NN_DIGIT> mux_1;
  
  left_shifter Lshift;
  right_shifter Rshift;
  // End of submodule declarations
  
  // Start of internal signal declarations  
  // Bonus module output
  sc_signal<NN_HALF_DIGIT> bonus_out_sig;
  
  // Splitter outputs
  sc_signal<NN_HALF_DIGIT> splitter_low_out_sig;
  sc_signal<NN_HALF_DIGIT> splitter_high_out_sig;
  
  // Register outputs
  sc_signal<NN_DIGIT> t0_reg_out_sig;
  sc_signal<NN_DIGIT> t0_tmp_reg_out_sig;
  sc_signal<NN_DIGIT> t0_new_reg_out_sig;
  sc_signal<NN_DIGIT> t1_reg_out_sig;
  sc_signal<NN_DIGIT> t1_tmp0_reg_out_sig;
  sc_signal<NN_DIGIT> t1_tmp1_reg_out_sig;
  sc_signal<NN_DIGIT> t1_new_reg_out_sig;
  sc_signal<NN_DIGIT> c_reg_out_sig;
  sc_signal<NN_HALF_DIGIT> aLow_reg_out_sig;
  
  // Multiplier outputs
  sc_signal<NN_DIGIT> mult_0_out_sig;
  sc_signal<NN_DIGIT> mult_1_out_sig;
  
  // Subtractor outputs
  sc_signal<NN_DIGIT> sub_0_out_sig;
  sc_signal<NN_DIGIT> sub_1_out_sig;
  sc_signal<NN_DIGIT> sub_2_out_sig;
  sc_signal<NN_DIGIT> sub_3_out_sig;
  sc_signal<NN_DIGIT> sub_4_out_sig;
  sc_signal<NN_DIGIT> sub_5_out_sig;
  sc_signal<NN_DIGIT> sub_6_out_sig;
  
  // Comparator outputs
  sc_signal<bool> cmp_0_out_sig;
  sc_signal<bool> cmp_1_out_sig;
  
  // Multiplexer outputs
  sc_signal<NN_DIGIT> mux_0_out_sig;
  sc_signal<NN_DIGIT> mux_1_out_sig;
  
  // Shifter outputs
  sc_signal<NN_DIGIT> Lshift_out_sig;
  sc_signal<NN_DIGIT> Rshift_out_sig;
    
  // Constant signals
  sc_signal<NN_DIGIT> const_max_sig;
  sc_signal<NN_DIGIT> const_1_sig;
  
  // Internal control signals
  sc_in_clk clock;
  sc_signal<bool> ld_inputs;
  sc_signal<bool> ld_t0_tmp;
  sc_signal<bool> ld_t0_new;
  sc_signal<bool> ld_t1_tmp0;
  sc_signal<bool> ld_t1_tmp1;
  sc_signal<bool> ld_t1_new;
  sc_signal<bool> bonus_ready;
  sc_signal<bool> ld_output;
  // End of internal signal declarations
};

#endif /* end _DH_HW_H_ */
