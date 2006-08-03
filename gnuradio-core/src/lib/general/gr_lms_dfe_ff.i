/* -*- c++ -*- */
/*
 * Copyright 2005 Free Software Foundation, Inc.
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


GR_SWIG_BLOCK_MAGIC(gr,lms_dfe_ff)

gr_lms_dfe_ff_sptr gr_make_lms_dfe_ff (float lambda_ff, float lambda_fb, 
				       unsigned int num_fftaps, unsigned int num_fbtaps);

class gr_lms_dfe_ff : public gr_sync_block
{
 private:
  gr_lms_dfe_ff (float lambda_ff, float lambda_fb, 
		 unsigned int num_fftaps, unsigned int num_fbtaps);
};