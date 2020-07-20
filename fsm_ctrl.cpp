#include "fsm_ctrl.h"

SC_HAS_PROCESS(fsm_ctrl);

fsm_ctrl::fsm_ctrl(sc_module_name n) : sc_module(n), state(RESET) {
  SC_THREAD(fsm_process);
  sensitive << clock.pos();
}

void fsm_ctrl::fsm_process() {
  while (true) {
    switch (state) {
      case RESET:
        ld_inputs->write(false);
        ld_t0_tmp->write(false);
        ld_t1_tmp0->write(false);
        ld_t0_new->write(false);
        ld_t1_tmp1->write(false);
        ld_t1_new->write(false);
        bonus_ready->write(false);
        ld_output->write(false);
        hw_done->write(false);
        state = WAIT;
        break;
      
      case WAIT:
        if (hw_enable->read() == true) {
          state = INPUT;
        }
        break;
      
      case INPUT:
        ld_inputs->write(true);
        state = EXE_0;
        break;
      
      case EXE_0:
        ld_inputs->write(false);
        ld_t0_tmp->write(true);
        state = EXE_1;
        break;
      
      case EXE_1:
        ld_t0_tmp->write(false);
        ld_t1_tmp0->write(true);
        state = EXE_2;
        break;
      
      case EXE_2:
        ld_t1_tmp0->write(false);
        ld_t0_new->write(true);
        state = EXE_3;
        break;
      
      case EXE_3:
        ld_t0_new->write(false);
        ld_t1_tmp1->write(true);
        state = EXE_4;
        break;
      
      case EXE_4:
        ld_t1_tmp1->write(false);
        ld_t1_new->write(true);
        state = EXE_5;
        break;
      
      case EXE_5:
        ld_t1_new->write(false);
        bonus_ready->write(true);
        state = OUTPUT;
        break;
      
      case OUTPUT:
        bonus_ready->write(false);
        ld_output->write(true);
        state = DONE;
        break;
      
      case DONE:
        if (hw_enable->read() == true) {
          ld_output->write(false);
          hw_done->write(true);
        } else {
          hw_done->write(false);
          state = WAIT;
        }
        break;
    } // end switch
    wait();
  } // end while
} // end fsm_process
