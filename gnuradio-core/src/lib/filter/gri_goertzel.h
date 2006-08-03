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

#ifndef INCLUDED_GRI_GOERTZEL_H
#define INCLUDED_GRI_GOERTZEL_H

#include <gr_types.h>

/*!
 * \brief implements Goertzel single-bin DFT calculation
 */

class gri_goertzel
{
public:
  gri_goertzel() {}
  gri_goertzel(int rate, int len, float freq);

  // Process a input array
  gr_complex batch(float *in);

  // Process sample by sample
  void input(const float &in);
  gr_complex output();
  bool ready() const { return d_processed == d_len; }
    
private:
  float d_d1;
  float d_d2;
  float d_wr;
  float d_wi;
  int   d_len;
  int   d_processed;
};

#endif /* INCLUDED_GRI_GOERTZEL_H */