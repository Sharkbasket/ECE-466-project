#include "systemc.h"
#include "digit.h"
#include "dh_hw.h"

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
      
      if ((t[0] -= u) > (MAX_NN_DIGIT - u)) t[1]--;
      if ((t[0] -= TO_HIGH_HALF (v)) > (MAX_NN_DIGIT - TO_HIGH_HALF (v))) t[1]--;
      t[1] -= HIGH_HALF (v);
      
      /*** Bonus part (optional: Extra Datapath + Extra Control) ***/
      while ((t[1] > 0) || ((t[1] == 0) && t[0] >= c)) {
        if ((t[0] -= c) > (MAX_NN_DIGIT - c)) t[1]--;
        aLow++;
      }
    
      // Write outputs
      to_sw.write(aLow);
      
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
