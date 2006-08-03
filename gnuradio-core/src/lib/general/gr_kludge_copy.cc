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
#include "config.h"
#endif

#include <gr_kludge_copy.h>
#include <gr_io_signature.h>
#include <string.h>

gr_kludge_copy_sptr
gr_make_kludge_copy(size_t itemsize)
{
  return gr_kludge_copy_sptr(new gr_kludge_copy(itemsize));
}

gr_kludge_copy::gr_kludge_copy(size_t itemsize)
  : gr_sync_block ("kludge_copy",
		   gr_make_io_signature (1, -1, sizeof (float)),
		   gr_make_io_signature (1, -1, sizeof (float))),
    d_itemsize(itemsize)
{
}

bool
gr_kludge_copy::check_topology(int ninputs, int noutputs)
{
  return ninputs == noutputs;
}

int
gr_kludge_copy::work(int noutput_items,
		     gr_vector_const_void_star &input_items,
		     gr_vector_void_star &output_items)
{
  const float **in = (const float **) &input_items[0];
  float **out = (float **) &output_items[0];

  int ninputs = input_items.size();
  for (int i = 0; i < ninputs; i++){
    memcpy(out[i], in[i], noutput_items * d_itemsize);
  }
  return noutput_items;
}