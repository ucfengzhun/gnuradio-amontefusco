/* -*- c++ -*- */
/*
 * Copyright 2004 Free Software Foundation, Inc.
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

GR_SWIG_BLOCK_MAGIC(gr, fft_vcc)

gr_fft_vcc_sptr 
gr_make_fft_vcc (int fft_size, bool forward, const std::vector<float> window);

class gr_fft_vcc : public gr_sync_block
{
 protected:
  gr_fft_vcc (int fft_size, bool forward, const std::vector<float> window);

 public:
  bool set_window(const std::vector<float> window);
};