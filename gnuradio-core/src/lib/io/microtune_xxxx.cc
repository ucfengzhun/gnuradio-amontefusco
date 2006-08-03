/* -*- c++-*- */
/*
 * Copyright 2001,2003,2004 Free Software Foundation, Inc.
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

#include "microtune_xxxx.h"

microtune_xxxx::~microtune_xxxx ()
{
  // nop
}

double
microtune_xxxx::set_RF_freq (double target_freq)
{
  double actual_freq = 0.0;

  if (set_RF_freq (target_freq, &actual_freq))
    return actual_freq;

  return 0.0;
}

  