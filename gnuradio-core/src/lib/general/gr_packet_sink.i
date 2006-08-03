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

GR_SWIG_BLOCK_MAGIC(gr,packet_sink)

gr_packet_sink_sptr 
gr_make_packet_sink (const std::vector<unsigned char>& sync_vector,
		     gr_msg_queue_sptr target_queue,
		     int threshold = -1        // -1 -> use default
		     );

class gr_packet_sink : public gr_sync_block
{
 protected:
  gr_packet_sink (const std::vector<unsigned char>& sync_vector,
		  gr_msg_queue_sptr target_queue,
		  int threshold);
 public:
  ~gr_packet_sink ();

  bool carrier_sensed() const;
};