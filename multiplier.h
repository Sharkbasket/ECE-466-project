#ifndef MULTIPLIER_H
#define MULTIPLIER_H

#include "systemc.h"

template<class T>
class multiplier : public sc_module {
  // Ports
  sc_in<T> factor0;
  sc_in<T> factor1;
  sc_out<T> product;
  
  SC_CTOR(multiplier) {
    SC_METHOD(mutliply);
    sensitive << factor0 << factor1;
  }
  
  void multiply() {
    product->write(factor0->read() * factor1->read());
  }
};

#endif // MULTIPLIER_H
