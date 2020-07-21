#ifndef LEFT_SHIFTER_H
#define LEFT_SHIFTER_H

#include "systemc.h"
#include "digit.h"

SC_MODULE(left_shifter) {
  sc_in<NN_DIGIT> in;
  sc_out<NN_DIGIT> out;
  
  SC_CTOR(left_shifter) {
    SC_METHOD(shift_left);
    sensitive << in;
  }
  
  void shift_left() {
    out->write(TO_HIGH_HALF(in->read()));
  }
};

#endif // LEFT_SHIFTER_H
