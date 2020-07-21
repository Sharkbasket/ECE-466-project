#ifndef SPLITTER_H
#define SPLITTER_H

#include "systemc.h"
#include "digit.h"

SC_MODULE(splitter_32to16) {
  sc_in<NN_DIGIT> in;
  sc_out<NN_HALF_DIGIT> low_half, high_half;
  
  SC_CTOR(splitter_32to16) {
    SC_METHOD(split);
    sensitive << in;
  }
  
  void split() {
    NN_DIGIT input = in->read();
    low_half->write((NN_HALF_DIGIT)LOW_HALF(input));
    high_half->write((NN_HALF_DIGIT)HIGH_HALF(input));
  }
};

#endif // SPLITTER_H
