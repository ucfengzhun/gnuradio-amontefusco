/* -*- c++ -*- */
/*
 * Copyright 2001 Free Software Foundation, Inc.
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

#ifndef _ATSC_RANDOMIZER_H_
#define _ATSC_RANDOMIZER_H_

#include <atsc_types.h>

/*! 
 * \brief ATSC data "whitener"
 *
 * The data randomizer described in ATSC standard A/53B.  
 * See figure D4 on page 54.
 */

class atsci_randomizer {
  friend class qa_atsci_randomizer;
  
 public:
  atsci_randomizer();

  /*! \brief reset randomizer LFSR
   *
   * must be called during the Data Segment Sync interval prior to the
   * first data segment.  I.e., the LFSR is reset prior to the first
   * field of each VSB data frame.
   */
  void reset ();

  //! randomize (whiten) mpeg packet and remove leading MPEG-2 sync byte
  void randomize (atsc_mpeg_packet_no_sync &out, const atsc_mpeg_packet &in);

  //! derandomize (de-whiten) mpeg packet and add leading MPEG-2 sync byte
  void derandomize (atsc_mpeg_packet &out, const atsc_mpeg_packet_no_sync &in);

  unsigned int state() const { return d_state; }

 private:
  static void initialize_output_map ();
  static unsigned char slow_output_map (int st);

  static unsigned char fast_output_map (int st){
    return s_output_map[(st & 0xb23c) >> 2]; // Magic const with 8 bits set improves cache 
                                             // utilization.  The bits correspond to the taps
					     // used in output calculation.  Others may be 
					     // safely ignored.
  }
    
  //! return current output value
  unsigned char output (){
    return fast_output_map (d_state);
  }

  //! clock LFSR; advance to next state.
  void clk (){
    if (d_state & 0x1)
      d_state = ((d_state ^ MASK) >> 1) | 0x8000;
    else
      d_state = d_state >> 1;
  }

  //! return current output value and advance to next state
  unsigned char output_and_clk (){
    unsigned char r = output ();
    clk ();
    return r;
  }

  unsigned int		    d_state;

  static const unsigned int PRELOAD_VALUE = 0x018f; /* 0xf180 bit reversed */
  static const unsigned int MASK = 0xa638;
  static unsigned char 	    s_output_map[1 << 14];
  static bool 		    s_output_map_initialized_p;
};

#endif /* _ATSC_RANDOMIZER_H_ */