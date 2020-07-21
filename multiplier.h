#ifndef MULTIPLIER_H
#define MULTIPLIER_H

#include "systemc.h"

SC_MODULE(multiplier) {
  // Ports
  sc_in<NN_HALF_DIGIT> factor0;
  sc_in<NN_HALF_DIGIT> factor1;
  sc_out<NN_DIGIT> product;
  
  SC_CTOR(multiplier) {
    SC_METHOD(multiply);
    sensitive << factor0 << factor1;
  }
  
  void multiply() {
    product->write((NN_DIGIT)factor0->read() * (NN_DIGIT)factor1->read());
  }
};

#endif // MULTIPLIER_H
