/* -*- c++ -*- */
/*
 * Copyright 2004,2005 Free Software Foundation, Inc.
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

GR_SWIG_BLOCK_MAGIC(gr,fft_filter_ccc)

gr_fft_filter_ccc_sptr 
gr_make_fft_filter_ccc (int decimation,
			const std::vector<gr_complex> &taps
			) throw (std::invalid_argument);

class gr_fft_filter_ccc : public gr_sync_decimator
{
 private:
  gr_fft_filter_ccc (int decimation, const std::vector<gr_complex> &taps);

 public:
  ~gr_fft_filter_ccc ();

  void set_taps (const std::vector<gr_complex> &taps);
};