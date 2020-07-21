#ifndef SUBTRACTOR_H
#define SUBTRACTOR_H

#include "systemc.h"

template<class T>
class subtractor : public sc_module {
  public:
    // Ports
    sc_in<T> minuend;
    sc_in<T> subtrahend;
    sc_out<T> difference;
  
    SC_CTOR(subtractor) {
      SC_METHOD(subtract);
      sensitive << minuend << subtrahend;
    }
  
    void subtract() {
      difference->write(minuend->read() - subtrahend->read());
    }
};

#endif // SUBTRACTOR_H
