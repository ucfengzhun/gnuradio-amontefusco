/* -*- c++ -*- */
/*
 * Copyright 2006 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <atsc_bit_timing_loop.h>
#include <gr_io_signature.h>
#include <atsc_consts.h>

float input_rate = 20e6;
double ratio_of_rx_clock_to_symbol_freq = input_rate / ATSC_SYMBOL_RATE;


atsc_bit_timing_loop_sptr
atsc_make_bit_timing_loop()
{
  return atsc_bit_timing_loop_sptr(new atsc_bit_timing_loop());
}


atsc_bit_timing_loop::atsc_bit_timing_loop()
  : gr_block("atsc_bit_timing_loop",
		  gr_make_io_signature(1, 1, sizeof(float)),
		  gr_make_io_signature(2, 2, sizeof(float))),
		  d_interp(ratio_of_rx_clock_to_symbol_freq), d_next_input(0),
		  d_rx_clock_to_symbol_freq (ratio_of_rx_clock_to_symbol_freq)
{
  reset();
}

void
atsc_bit_timing_loop::forecast (int noutput_items, gr_vector_int &ninput_items_required)
{
  unsigned ninputs = ninput_items_required.size();
  for (unsigned i = 0; i < ninputs; i++)
    ninput_items_required[i] = noutput_items * d_rx_clock_to_symbol_freq + 1500 - 1;

  inputs0_size = noutput_items * d_rx_clock_to_symbol_freq + 1500 - 1;
  inputs0_index = d_next_input;
}

int
atsc_bit_timing_loop::general_work (int noutput_items,
                                 gr_vector_int &ninput_items,
                                 gr_vector_const_void_star &input_items,
                                 gr_vector_void_star &output_items)
{
  int   r = work (noutput_items, input_items, output_items);
  if (r > 0)
    consume_each (r * d_rx_clock_to_symbol_freq);
  return r;
}


int
atsc_bit_timing_loop::work (int noutput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items)
{
  const float *in = (const float *) input_items[0];
  float *out_sample = (float *) output_items[0];
  atsc::syminfo *out_tag = (atsc::syminfo *) output_items[1];

  assert(sizeof(float) == sizeof(atsc::syminfo));

  // We are tasked with producing output.size output samples.
  // We will consume approximately 2 * output.size input samples.

  int           si = 0;         // source index
  unsigned int  k;              // output index

  float         interp_sample;
  int           symbol_index;
  double        timing_adjustment = 0;
  bool          seg_locked;
  atsc::syminfo    tag;

  memset (&tag, 0, sizeof (tag));

  
  for (k = 0; k < noutput_items; k++){
    if (!d_interp.update (in, inputs0_size, &si, timing_adjustment, &interp_sample)){
      fprintf (stderr, "GrAtscBitTimingLoop3: ran short on data...\n");
      break;
    }

    d_sssr.update (interp_sample, &seg_locked, &symbol_index, &timing_adjustment);
    out_sample[k] = interp_sample;
    tag.valid = seg_locked;
    tag.symbol_num = symbol_index;
    out_tag[k] = tag;

  }

  d_next_input += si;    // update next_input so forecast can get us what we need
  return k;
}