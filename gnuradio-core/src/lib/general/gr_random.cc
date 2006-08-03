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

/*
 *  Copyright 1997 Massachusetts Institute of Technology
 * 
 *  Permission to use, copy, modify, distribute, and sell this software and its
 *  documentation for any purpose is hereby granted without fee, provided that
 *  the above copyright notice appear in all copies and that both that
 *  copyright notice and this permission notice appear in supporting
 *  documentation, and that the name of M.I.T. not be used in advertising or
 *  publicity pertaining to distribution of the software without specific,
 *  written prior permission.  M.I.T. makes no representations about the
 *  suitability of this software for any purpose.  It is provided "as is"
 *  without express or implied warranty.
 * 
 */

#include <math.h>
#include <gr_random.h>

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)


gr_random::gr_random (long seed)
{
  reseed (seed);
}

void
gr_random::reseed (long seed)
{
  d_seed = seed;
  d_iy = 0;
  for (int i = 0; i < NTAB; i++)
    d_iv[i] = 0;
  d_iset = 0;
  d_gset = 0;
}

/*
 * This looks like it returns a uniform random deviate between 0.0 and 1.0
 * It looks similar to code from "Numerical Recipes in C".
 */
float gr_random::ran1()
{
  int j;
  long k;
  float temp;
  
  if (d_seed <= 0 || !d_iy)  {
    if (-d_seed < 1) 
      d_seed=1;
    else 
      d_seed = -d_seed;
    for (j=NTAB+7;j>=0;j--) {
      k=d_seed/IQ;
      d_seed=IA*(d_seed-k*IQ)-IR*k;
      if (d_seed < 0) 
	d_seed += IM;
      if (j < NTAB) 
	d_iv[j] = d_seed;
    }
    d_iy=d_iv[0];
  }
  k=(d_seed)/IQ;
  d_seed=IA*(d_seed-k*IQ)-IR*k;
  if (d_seed < 0)
    d_seed += IM;
  j=d_iy/NDIV;
  d_iy=d_iv[j];
  d_iv[j] = d_seed;
  temp=AM * d_iy;
  if (temp > RNMX)
    temp = RNMX;
  return temp;
}

/*
 * Returns a normally distributed deviate with zero mean and variance 1.
 * Also looks like it's from "Numerical Recipes in C".
 */
float gr_random::gasdev()
{
  float fac,rsq,v1,v2;
  d_iset = 1 - d_iset;
  if  (d_iset) {
    do {
      v1=2.0*ran1()-1.0;
      v2=2.0*ran1()-1.0;
      rsq=v1*v1+v2*v2;
    } while (rsq >= 1.0 || rsq == 0.0);
    fac= sqrt(-2.0*log(rsq)/rsq);
    d_gset=v1*fac;
    return v2*fac;
  }
  return d_gset;
}

/*
 * Copied from The KC7WW / OH2BNS Channel Simulator
 * FIXME Need to check how good this is at some point
 */

float gr_random::laplacian()
{
  float z = ran1();
  if (z < 0.5)
    return log(2.0 * z) / M_SQRT2;
  else
    return -log(2.0 * (1.0 - z)) / M_SQRT2;
}

/*
 * Copied from The KC7WW / OH2BNS Channel Simulator
 * FIXME Need to check how good this is at some point
 */

  // 5 => scratchy, 8 => Geiger

float gr_random::impulse(float factor = 5)
{
  float z = -M_SQRT2 * log(ran1());
  if (fabsf(z) <= factor)		
    return 0.0;
  else 
    return z;
}

/*
 * Complex rayleigh is really gaussian I and gaussian Q
 * It can also be generated by real rayleigh magnitude and
 * uniform random angle 
 * Adapted from The KC7WW / OH2BNS Channel Simulator
 * FIXME Need to check how good this is at some point
 */

gr_complex gr_random::rayleigh_complex()
{
  return gr_complex(gasdev(),gasdev());
}

/*   Other option
     mag = rayleigh();
     ang = 2.0 * M_PI * RNG();
     *Rx = rxx * cos(z);
     *Iy = rxx * sin(z);
*/


float gr_random::rayleigh()
{
  return sqrt(-2.0 * log(ran1()));
}