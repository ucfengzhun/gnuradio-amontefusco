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

class test_iir (gr_unittest.TestCase):

    def setUp (self):
        self.fg = gr.flow_graph ()

    def tearDown (self):
        self.fg = None

    def test_iir_direct_001 (self):
        src_data = (1, 2, 3, 4, 5, 6, 7, 8)
        fftaps = ()
        fbtaps = ()
        expected_result = (0, 0, 0, 0, 0, 0, 0, 0)
        src = gr.vector_source_f (src_data)
        op = gr.iir_filter_ffd (fftaps, fbtaps)
        dst = gr.vector_sink_f ()
        self.fg.connect (src, op)
        self.fg.connect (op, dst)
        self.fg.run ()
        result_data = dst.data ()
        self.assertFloatTuplesAlmostEqual (expected_result, result_data)

    def test_iir_direct_002 (self):
        src_data = (1, 2, 3, 4, 5, 6, 7, 8)
        fftaps = (2,)
        fbtaps = (0,)
        expected_result = (2, 4, 6, 8, 10, 12, 14, 16)
        src = gr.vector_source_f (src_data)
        op = gr.iir_filter_ffd (fftaps, fbtaps)
        dst = gr.vector_sink_f ()
        self.fg.connect (src, op)
        self.fg.connect (op, dst)
        self.fg.run ()
        result_data = dst.data ()
        self.assertFloatTuplesAlmostEqual (expected_result, result_data)

    def test_iir_direct_003 (self):
        src_data = (1, 2, 3, 4, 5, 6, 7, 8)
        fftaps = (2, 11)
        fbtaps = (0,  0)
        expected_result = (2, 15, 28, 41, 54, 67, 80, 93)
        src = gr.vector_source_f (src_data)
        op = gr.iir_filter_ffd (fftaps, fbtaps)
        dst = gr.vector_sink_f ()
        self.fg.connect (src, op)
        self.fg.connect (op, dst)
        self.fg.run ()
        result_data = dst.data ()
        self.assertFloatTuplesAlmostEqual (expected_result, result_data)

    def test_iir_direct_004 (self):
        src_data = (1, 2, 3, 4, 5, 6, 7, 8)
        fftaps = (2, 11)
        fbtaps = (0,  -1)
        expected_result = (2, 13, 15, 26, 28, 39, 41, 52)
        src = gr.vector_source_f (src_data)
        op = gr.iir_filter_ffd (fftaps, fbtaps)
        dst = gr.vector_sink_f ()
        self.fg.connect (src, op)
        self.fg.connect (op, dst)
        self.fg.run ()
        result_data = dst.data ()
        self.assertFloatTuplesAlmostEqual (expected_result, result_data)

    def test_iir_direct_005 (self):
        src_data = (1, 2, 3, 4, 5, 6, 7, 8)
        fftaps = (2, 11,  0)
        fbtaps = (0,  -1, 3)
        expected_result = (2, 13, 21, 59, 58, 186, 68, 583)
        src = gr.vector_source_f (src_data)
        op = gr.iir_filter_ffd (fftaps, fbtaps)
        dst = gr.vector_sink_f ()
        self.fg.connect (src, op)
        self.fg.connect (op, dst)
        self.fg.run ()
        result_data = dst.data ()
        self.assertFloatTuplesAlmostEqual (expected_result, result_data)

    def test_iir_direct_006 (self):
        fftaps = (2, 11,  0)
        fbtaps = (0,  -1)
        self.assertRaises ((RuntimeError, ValueError), gr.iir_filter_ffd, fftaps, fbtaps)

    def test_iir_direct_007 (self):
        src_data = (1, 2, 3, 4, 5, 6, 7, 8)
        expected_result = (2, 13, 21, 59, 58, 186, 68, 583)
        fftaps = (2, 1)
        fbtaps = (0, -1)
        src = gr.vector_source_f (src_data)
        op = gr.iir_filter_ffd (fftaps, fbtaps)
        fftaps = (2, 11,  0)
        fbtaps = (0,  -1, 3)
        op.set_taps (fftaps, fbtaps)
        dst = gr.vector_sink_f ()
        self.fg.connect (src, op)
        self.fg.connect (op, dst)
        self.fg.run ()
        result_data = dst.data ()
        self.assertFloatTuplesAlmostEqual (expected_result, result_data)

    def test_iir_direct_008 (self):
        fftaps = (2, 1)
        fbtaps = (0, -1)
        op = gr.iir_filter_ffd (fftaps, fbtaps)
        fftaps = (2, 11)
        fbtaps = (0,  -1, 3)
        self.assertRaises ((RuntimeError, ValueError), op.set_taps, fftaps, fbtaps)

if __name__ == '__main__':
    gr_unittest.main ()
        