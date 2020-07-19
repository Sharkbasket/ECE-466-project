#ifndef _DH_HW_H_
#define _DH_HW_H_ 1

#include "systemc.h"
#include "digit.h"

SC_MODULE (dh_hw) {
  sc_in <NN_DIGIT> from_sw0, from_sw1, from_sw2;
  sc_in <NN_HALF_DIGIT> from_sw3;
  sc_out <NN_HALF_DIGIT> to_sw;
  
  sc_in <bool> hw_enable; 
  sc_out <bool> hw_done;
  
  sc_in_clk clock;
  
  void process_hw();
  
  SC_CTOR (dh_hw) {
    SC_THREAD (process_hw);
    sensitive << clock.pos();
  }
};

#endif /* end _DH_HW_H_ */
