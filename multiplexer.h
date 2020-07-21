#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

#include "systemc.h"

template<class T>
class multiplexer : public sc_module {
  public:
    sc_in<T> in0;
    sc_in<T> in1;
    sc_in<bool> select;
    sc_out<T> out;
  
    SC_CTOR(multiplexer) {
      SC_METHOD(mux_it);
      sensitive << in0 << in1 << select;
    }
  
    void mux_it() {
      if (select->read() == false) {
        out->write(in0->read());
      } else {
        out->write(in1->read());
      }
    }
};

#endif MULTIPLEXER_H
