#ifndef SIMPLE_REG_H
#define SIMPLE_REG_H

#include "systemc.h"

template<class T>
SC_MODULE(simple_reg) {
  sc_in<T> input;
  sc_out<T> output;
  sc_in<bool> load;
  
  SC_CTOR(simple_reg) {
    SC_METHOD(load_output);
    sensitive << load;
    value = 0;
  }
  
  void load_output() {
    if (load->read() == true) {
      value = input->read();
      output->write(value);
    }
  }
  
  T value;
};

#endif // SIMPLE_REG_H
