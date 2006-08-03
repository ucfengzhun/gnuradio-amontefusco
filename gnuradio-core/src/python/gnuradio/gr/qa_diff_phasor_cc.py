#!/usr/bin/env python
#
# Copyright 2004 Free Software Foundation, Inc.
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

from gnuradio import gr, gr_unittest
import math

class test_complex_ops (gr_unittest.TestCase):

    def setUp (self):
        self.fg = gr.flow_graph ()

    def tearDown (self):
        self.fg = None

    def test_diff_phasor_cc (self):
        src_data = (0+0j, 1+0j, -1+0j, 3+4j, -3-4j, -3+4j)
        expected_result = (0+0j, 0+0j, -1+0j, -3-4j, -25+0j, -7-24j)
        src = gr.vector_source_c (src_data)
        op = gr.diff_phasor_cc ()
        dst = gr.vector_sink_c ()
        self.fg.connect (src, op)
        self.fg.connect (op, dst)
        self.fg.run ()               # run the graph and wait for it to finish
        actual_result = dst.data ()  # fetch the contents of the sink
        self.assertComplexTuplesAlmostEqual (expected_result, actual_result)



if __name__ == '__main__':
    gr_unittest.main ()
