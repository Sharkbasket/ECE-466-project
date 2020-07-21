#ifndef RIGHT_SHIFTER_H
#define RIGHT_SHIFTER_H

#include "systemc.h"
#include "digit.h"

SC_MODULE(right_shifter) {
  sc_in<NN_DIGIT> in;
  sc_out<NN_DIGIT> out;
  
  SC_CTOR(right_shifter) {
    SC_METHOD(shift_right);
    sensitive << in;
  }
  
  void shift_right() {
    out->write(HIGH_HALF(in->read()));
  }
};

#endif // RIGHT_SHIFTER_H
