#include "dh_hw.h"

SC_HAS_PROCESS(dh_hw);

dh_hw::dh_hw(sc_module_name n)
// Initializer list
: sc_module(n),
  bonus("bonus"),
  controller("controller"),
  splitter("splitter"),
  t0_reg("t0_reg"),
  t0_tmp_reg("t0_tmp_reg"),
  t0_new_reg("t0_new_reg"),
  t1_reg("t1_reg"),
  t1_tmp0_reg("t1_tmp0_reg"),
  t1_tmp1_reg("t1_tmp1_reg"),
  t1_new_reg("t1_new_reg"),
  c_reg("c_reg"),
  aLow_reg("aLow_reg"),
  aLow_new_reg("aLow_new_reg"),
  mult_0("mult_0"),
  mult_1("mult_1"),
  sub_0("sub_0"),
  sub_1("sub_1"),
  sub_2("sub_2"),
  sub_3("sub_3"),
  sub_4("sub_4"),
  sub_5("sub_5"),
  sub_6("sub_6"),
  cmp_0("cmp_0"),
  cmp_1("cmp_1"),
  mux_0("mux_0"),
  mux_1("mux_1"),
  Lshift("Lshift"),
  Rshift("Rshift") {
  
  // Initialize constant signals
  const_max_sig.write(MAX_NN_DIGIT);
  const_1_sig.write(1);
  
  // Start of module interconnection
  bonus.t0_new_sig(t0_new_reg_out_sig);
  bonus.t1_new_sig(t1_new_reg_out_sig);
  bonus.c_sig(c_reg_out_sig);
  bonus.aLow_sig(aLow_reg_out_sig);
  bonus.ready_sig(bonus_ready);
  bonus.aLow_new_sig(bonus_out_sig);
  
  controller.clock(clock);
  controller.hw_enable(hw_enable);
  controller.ld_inputs(ld_inputs);
  controller.ld_t0_tmp(ld_t0_tmp);
  controller.ld_t0_new(ld_t0_new);
  controller.ld_t1_tmp0(ld_t1_tmp0);
  controller.ld_t1_tmp1(ld_t1_tmp1);
  controller.ld_t1_new(ld_t1_new);
  controller.bonus_ready(bonus_ready);
  controller.ld_output(ld_output);
  controller.hw_done(hw_done);
  
  splitter.in(c_reg_out_sig);
  splitter.low_half(splitter_low_out_sig);
  splitter.high_half(splitter_high_out_sig);
  
  t0_reg.input(from_sw0);
  t0_reg.output(t0_reg_out_sig);
  t0_reg.load(ld_inputs);
  
  t1_reg.input(from_sw1);
  t1_reg.output(t1_reg_out_sig);
  t1_reg.load(ld_inputs);
  
  c_reg.input(from_sw2);
  c_reg.output(c_reg_out_sig);
  c_reg.load(ld_inputs);
  
  aLow_reg.input(from_sw3);
  aLow_reg.output(aLow_reg_out_sig);
  aLow_reg.load(ld_inputs);
  
  t0_tmp_reg.input(sub_0_out_sig);
  t0_tmp_reg.output(t0_tmp_reg_out_sig);
  t0_tmp_reg.load(ld_t0_tmp);
  
  t0_new_reg.input(sub_3_out_sig);
  t0_new_reg.output(t0_new_reg_out_sig);
  t0_new_reg.load(ld_t0_new);
  
  t1_tmp0_reg.input(mux_0_out_sig);
  t1_tmp0_reg.output(t1_tmp0_reg_out_sig);
  t1_tmp0_reg.load(ld_t1_tmp0);
  
  t1_tmp1_reg.input(mux_1_out_sig);
  t1_tmp1_reg.output(t1_tmp1_reg_out_sig);
  t1_tmp1_reg.load(ld_t1_tmp1);
  
  t1_new_reg.input(sub_6_out_sig);
  t1_new_reg.output(t1_new_reg_out_sig);
  t1_new_reg.load(ld_t1_new);
  
  aLow_new_reg.input(bonus_out_sig);
  aLow_new_reg.output(to_sw);
  aLow_new_reg.load(ld_output);
  
  mult_0.factor0(aLow_reg_out_sig);
  mult_0.factor1(splitter_low_out_sig);
  mult_0.product(mult_0_out_sig);
  
  mult_1.factor0(aLow_reg_out_sig);
  mult_1.factor1(splitter_high_out_sig);
  mult_1.product(mult_1_out_sig);
  
  sub_0.minuend(t0_reg_out_sig);
  sub_0.subtrahend(mult_0_out_sig);
  sub_0.difference(sub_0_out_sig);
  
  sub_1.minuend(const_max_sig);
  sub_1.subtrahend(mult_0_out_sig);
  sub_1.difference(sub_1_out_sig);
  
  sub_2.minuend(t1_reg_out_sig);
  sub_2.subtrahend(const_1_sig);
  sub_2.difference(sub_2_out_sig);
  
  sub_3.minuend(t0_tmp_reg_out_sig);
  sub_3.subtrahend(Lshift_out_sig);
  sub_3.difference(sub_3_out_sig);
  
  sub_4.minuend(const_max_sig);
  sub_4.subtrahend(Lshift_out_sig);
  sub_4.difference(sub_4_out_sig);
  
  sub_5.minuend(t1_tmp0_reg_out_sig);
  sub_5.subtrahend(const_1_sig);
  sub_5.difference(sub_5_out_sig);
  
  sub_6.minuend(t1_tmp1_reg_out_sig);
  sub_6.subtrahend(Rshift_out_sig);
  sub_6.difference(sub_6_out_sig);
  
  cmp_0.a(t0_tmp_reg_out_sig);
  cmp_0.b(sub_1_out_sig);
  cmp_0.out(cmp_0_out_sig);
  
  cmp_1.a(t0_new_reg_out_sig);
  cmp_1.b(sub_4_out_sig);
  cmp_1.out(cmp_1_out_sig);
  
  mux_0.in0(t1_reg_out_sig);
  mux_0.in1(sub_2_out_sig);
  mux_0.select(cmp_0_out_sig);
  mux_0.out(mux_0_out_sig);
  
  mux_1.in0(t1_tmp0_reg_out_sig);
  mux_1.in1(sub_5_out_sig);
  mux_1.select(cmp_1_out_sig);
  mux_1.out(mux_1_out_sig);
  
  Lshift.in(mult_1_out_sig);
  Lshift.out(Lshift_out_sig);
  
  Rshift.in(mult_1_out_sig);
  Rshift.out(Rshift_out_sig);
  // End of module interconnection
}
