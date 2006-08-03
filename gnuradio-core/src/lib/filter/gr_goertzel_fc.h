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

#ifndef INCLUDED_GR_GOERTZEL_FC_H
#define INCLUDED_GR_GOERTZEL_FC_H

#include <gri_goertzel.h>
#include <gr_sync_decimator.h>

class gr_goertzel_fc;
typedef boost::shared_ptr<gr_goertzel_fc> gr_goertzel_fc_sptr;

// public constructor
gr_goertzel_fc_sptr gr_make_goertzel_fc(int rate, int len, float freq);

/*!
 * \brief Goertzel single-bin DFT calculation.
 * \ingroup filter
 */
class gr_goertzel_fc : public gr_sync_decimator
{
private:
  friend gr_goertzel_fc_sptr gr_make_goertzel_fc (int rate, int len, float freq);

  gr_goertzel_fc(int rate, int len, float freq);
  gri_goertzel d_goertzel;
  int          d_len;

public:
  int work(int noutput_items,
	   gr_vector_const_void_star &input_items,
	   gr_vector_void_star &output_items);
};

#endif /* INCLUDED_GR_GOERTZEL_FC_H */
