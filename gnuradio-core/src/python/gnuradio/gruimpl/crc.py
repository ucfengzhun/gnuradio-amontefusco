#
# Copyright 2005 Free Software Foundation, Inc.
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
# 
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
# 

from gnuradio import gr
from hexint import *
import struct

def gen_and_append_crc32(s):
    crc = gr.crc32(s)
    return s + struct.pack(">I", hexint(crc))

def check_crc32(s):
    msg = s[:-4]
    #print "msg = '%s'" % (msg,)
    actual = gr.crc32(msg)
    (expected,) = struct.unpack(">I", s[-4:])
    # print "actual =", hex(actual), "expected =", hex(expected)
    return (actual == expected, msg)