/* -*- c++ -*- */
/*
 * Copyright 2003 Free Software Foundation, Inc.
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

#ifndef _GR_COUNT_BITS_H_
#define _GR_COUNT_BITS_H_

unsigned int gr_count_bits8(unsigned int x);	// return number of set bits in the low  8 bits of x
unsigned int gr_count_bits16(unsigned int x);	// return number of set bits in the low 16 bits of x
unsigned int gr_count_bits32(unsigned int x);	// return number of set bits in the low 32 bits of x
unsigned int gr_count_bits64(unsigned long long int x);

#endif /* _GR_COUNT_BITS_H_ */