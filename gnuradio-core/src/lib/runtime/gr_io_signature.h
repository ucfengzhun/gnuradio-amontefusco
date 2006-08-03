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

#ifndef INCLUDED_IO_SIGNATURE_H
#define INCLUDED_IO_SIGNATURE_H

#include <gr_runtime.h>

/*!
 * \brief i/o signature for input and output ports.
 *
 * For now, we restrict all streams to be the same type.
 * We can fix this later.
 */
  
class gr_io_signature {
 public:

  static const int IO_INFINITE = -1;
    
  ~gr_io_signature ();
    
  int min_streams () const { return d_min_streams; }
  int max_streams () const { return d_max_streams; }
  size_t sizeof_stream_item (int index) const { return d_sizeof_stream_item; }

  // ----------------------------------------------------------------------------

 private:
  
  int		d_min_streams;
  int		d_max_streams;
  size_t	d_sizeof_stream_item;

  gr_io_signature (int min_streams, int max_streams, size_t sizeof_stream_item);

  friend gr_io_signature_sptr gr_make_io_signature (int min_streams,
						   int max_streams,
						   size_t sizeof_stream_item);
};

gr_io_signature_sptr
gr_make_io_signature (int min_streams, int max_streams, size_t sizeof_stream_item);


#endif /* INCLUDED_IO_SIGNATURE_H */