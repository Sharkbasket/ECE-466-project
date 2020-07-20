#include "systemc.h"
#include "digit.h"
#include "dh_hw.h"

SC_HAS_PROCESS(dh_hw);

dh_hw::dh_hw(sc_module_name n)
: sc_module(n), bonus_module("bonus_module"), controller("controller") {
  SC_THREAD(process_hw);
  sensitive << clock.pos();
  
  bonus_module.t0_new_sig(bonus_in0);
  bonus_module.t1_new_sig(bonus_in1);
  bonus_module.c_sig(from_sw2);
  bonus_module.aLow_sig(from_sw3);
  bonus_module.ready_sig(bonus_ready);
  bonus_module.aLow_new_sig(bonus_out);
  
  controller.clock(clock);
  controller.hw_enable(hw_enable);
  controller.ld_inputs(ld_inputs);
  controller.ld_t0_tmp(ld_t0_tmp);
  controller.ld_t1_tmp0(ld_t1_tmp0);
  controller.ld_t0_new(ld_t0_new);
  controller.ld_t1_tmp1(ld_t1_tmp1);
  controller.ld_t1_new(ld_t1_new);
  controller.bonus_ready(bonus_ready);
  controller.ld_output(ld_output);
  controller.hw_done(hw_done);
}

void dh_hw::process_hw() {
  NN_DIGIT t[2] {0, 0}, c(0), u(0), v(0), t0_tmp(0),
           t0_new(0), t1_tmp0(0), t1_tmp1(0), t1_new(0);
  NN_HALF_DIGIT aLow(0), cLow(0), cHigh(0), aLow_new(0);
  
  while (true) {
    if (ld_inputs.read() == true) {
      t[0] = from_sw0->read();
      t[1] = from_sw1->read();
      c = from_sw2->read();
      aLow = from_sw3->read();
      
      cHigh = (NN_HALF_DIGIT)HIGH_HALF (c);
      cLow = (NN_HALF_DIGIT)LOW_HALF (c);
      
      u = (NN_DIGIT)aLow * (NN_DIGIT)cLow;
      v = (NN_DIGIT)aLow * (NN_DIGIT)cHigh;
    }
    
    if (ld_t0_tmp.read() == true) {
      t0_tmp = t[0] - u;
    }
    
    if (ld_t1_tmp0.read() == true) {
      if (t0_tmp > (MAX_NN_DIGIT - u)) {
        t1_tmp0 = t[1] - 1;
      } else {
        t1_tmp0 = t[1];
      }
    }
    
    if (ld_t0_new.read() == true) {
      t0_new = t0_tmp - TO_HIGH_HALF(v);
      bonus_in0.write(t0_new);
    }
    
    if (ld_t1_tmp1.read() == true) {
      if (t0_new > (MAX_NN_DIGIT - TO_HIGH_HALF(v))) {
        t1_tmp1 = t1_tmp0 - 1;
      } else {
        t1_tmp1 = t1_tmp0;
      }
    }
    
    if (ld_t1_new.read() == true) {
      t1_new = t1_tmp1 - HIGH_HALF(v);
      bonus_in1.write(t1_new);
    }
    
    if (ld_output.read() == true) {
      aLow_new = bonus_out.read();
      to_sw->write(aLow_new);
    }
    
    wait();
  } // end while
//   for (;;) {
//     if (hw_enable->read() == true) {
//       // Read inputs
//       t[0] = from_sw0.read();
//       t[1] = from_sw1.read();
//       c = from_sw2.read();
//       aLow = from_sw3.read();
//       
//       // Original code from NN_DigitDivLH():
//       
//       /*** Required part (to do: Datapath + Control) ***/
//       cHigh = (NN_HALF_DIGIT)HIGH_HALF (c);
//       cLow = (NN_HALF_DIGIT)LOW_HALF (c);
//       
//       u = (NN_DIGIT)aLow * (NN_DIGIT)cLow;
//       v = (NN_DIGIT)aLow * (NN_DIGIT)cHigh;
//       
//       if ((t[0] -= u) > (MAX_NN_DIGIT - u)) {
//         t[1]--;
//       }
//       if ((t[0] -= TO_HIGH_HALF (v)) > (MAX_NN_DIGIT - TO_HIGH_HALF (v))) {
//         t[1]--;
//       }
//       t[1] -= HIGH_HALF (v);
//       
//       // Pass values to bonus module via signals
//       bonus_in0.write(t[0]);
//       bonus_in1.write(t[1]);
//       bonus_ready.write(true);
//       wait(); // Suspend process so bonus module can compute result
//       bonus_ready.write(false);
//       
//       /*** Bonus part (optional: Extra Datapath + Extra Control) ***/
//       // This is now implemented in bonus.cpp
// //       while ((t[1] > 0) || ((t[1] == 0) && t[0] >= c)) {
// //         if ((t[0] -= c) > (MAX_NN_DIGIT - c)) t[1]--;
// //         aLow++;
// //       }
//       
//       // Get result from bonus module
//       to_sw->write(bonus_out.read());
//       
//       // Handshaking protocol
//       hw_done->write(true);
//       
//       do {
//         wait(); // Wait for de-assertion of hw_enable
//       } while (hw_enable->read() == true);
//       
//       hw_done->write(false);
//     } // end if
//     
//     wait();
//   } // end for
} // end process_hw
