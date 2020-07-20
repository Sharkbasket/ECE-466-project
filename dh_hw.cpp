#include "systemc.h"
#include "digit.h"
#include "dh_hw.h"

SC_HAS_PROCESS(dh_hw);

dh_hw::dh_hw(sc_module_name n) : sc_module(n), bonus_module("bonus_module") {
  SC_THREAD(process_hw);
  sensitive << clock.pos();
  
  bonus_module.t0_new_sig(bonus_in0);
  bonus_module.t1_new_sig(bonus_in1);
  bonus_module.c_sig(from_sw2);
  bonus_module.aLow_sig(from_sw3);
  bonus_module.ready_sig(bonus_ready);
  bonus_module.aLow_new_sig(bonus_out);
}

void dh_hw::process_hw() {
  NN_DIGIT t[2], c, u, v;
  NN_HALF_DIGIT aLow, cLow, cHigh;
  
  for (;;) {
    if (hw_enable->read() == true) {
      // Read inputs
      t[0] = from_sw0.read();
      t[1] = from_sw1.read();
      c = from_sw2.read();
      aLow = from_sw3.read();
      
      // Original code from NN_DigitDivLH():
      
      /*** Required part (to do: Datapath + Control) ***/
      cHigh = (NN_HALF_DIGIT)HIGH_HALF (c);
      cLow = (NN_HALF_DIGIT)LOW_HALF (c);
      
      u = (NN_DIGIT)aLow * (NN_DIGIT)cLow;
      v = (NN_DIGIT)aLow * (NN_DIGIT)cHigh;
      
      if ((t[0] -= u) > (MAX_NN_DIGIT - u)) {
        t[1]--;
      }
      if ((t[0] -= TO_HIGH_HALF (v)) > (MAX_NN_DIGIT - TO_HIGH_HALF (v))) {
        t[1]--;
      }
      t[1] -= HIGH_HALF (v);
      
      // Pass values to bonus module via signals
      bonus_in0.write(t[0]);
      bonus_in1.write(t[1]);
      bonus_ready.write(true);
      wait(); // Suspend process so bonus module can compute result
      bonus_ready.write(false);
      
      /*** Bonus part (optional: Extra Datapath + Extra Control) ***/
      // This is now implemented in bonus.cpp
//       while ((t[1] > 0) || ((t[1] == 0) && t[0] >= c)) {
//         if ((t[0] -= c) > (MAX_NN_DIGIT - c)) t[1]--;
//         aLow++;
//       }
      
      // Get result from bonus module
      to_sw->write(bonus_out.read());
      
      // Handshaking protocol
      hw_done->write(true);
      
      do {
        wait(); // Wait for de-assertion of hw_enable
      } while (hw_enable->read() == true);
      
      hw_done->write(false);
    } // end if
    
    wait();
  } // end for
} // end process_hw
