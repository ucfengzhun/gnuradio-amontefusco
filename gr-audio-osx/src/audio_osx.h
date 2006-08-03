/* -*- c++ -*- */
/*
 * Copyright 2006 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio.
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

#ifndef INCLUDED_AUDIO_OSX_H
#define INCLUDED_AUDIO_OSX_H

#define CheckErrorAndThrow(err,what,throw_str) \
if (err) { \
  OSStatus error = static_cast<OSStatus>(err); \
  fprintf (stderr, "%s\n  Error# %ld ('%4s')\n  %s:%d\n", \
	   what, error, (char*)(&err), __FILE__, __LINE__); \
  fflush (stdout); \
  throw std::runtime_error (throw_str); \
}

#define CheckError(err,what) \
if (err) { \
  OSStatus error = static_cast<OSStatus>(err); \
  fprintf (stderr, "%s\n  Error# %ld ('%4s')\n  %s:%d\n", \
	   what, error, (char*)(&err), __FILE__, __LINE__); \
  fflush (stdout); \
}

#ifdef WORDS_BIGENDIAN
#define GR_PCM_ENDIANNESS kLinearPCMFormatFlagIsBigEndian
#else
#define GR_PCM_ENDIANNESS 0
#endif

#endif /* INCLUDED_AUDIO_OSX_H */