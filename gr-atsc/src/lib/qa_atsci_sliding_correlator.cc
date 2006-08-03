/* -*- c++ -*- */
/*
 * Copyright 2002 Free Software Foundation, Inc.
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

#include <cppunit/TestAssert.h>
#include <qa_atsci_sliding_correlator.h>
#include <cstdio>

void
qa_atsci_sliding_correlator::t0 ()
{

#if 0
  int	count = 0;
  int	i;
  for (i = 0; i < 100; i++)
    printf ("%6d: %3d\n", count++, corr.input_bit (i & 1));

  for (i = 0; i < 511; i++)
    printf ("%6d: %3d\n", count++, corr.input_bit (atsc_pn511[i]));

  for (i = 0; i < 100; i++)
    printf ("%6d: %3d\n", count++, corr.input_bit ((i & 2) != 0));

  for (i = 0; i < 511; i++)
    printf ("%6d: %3d\n", count++, corr.input_bit (atsc_pn511[i] ^ 1));

  for (i = 0; i < 100; i++)
    printf ("%6d: %3d\n", count++,
	    corr.input_bit (atsc_pn511[i] ^ atsc_pn511[i+31]));
#endif

}