#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "systemc.h"

template<class T>
class comparator : public sc_module {
  sc_in<T> a;
  sc_in<T> b;
  sc_out<bool> out;
  
  SC_CTOR(comparator) {
    SC_METHOD(compare);
    sensitive << a << b;
  }
  
  void compare() {
    out->write(a->read() > b->read());
  }
};

#endif // COMPARATOR_H
