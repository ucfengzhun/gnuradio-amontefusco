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

from gnuradio import gr, gru

_plot = None

def design_filter(interpolation, decimation, fractional_bw):
    """
    Given the interpolation rate, decimation rate and a fractional bandwidth,
    design a set of taps.

    @param interpolation: interpolation factor
    @type  interpolation: integer > 0
    @param decimation: decimation factor
    @type  decimation: integer > 0
    @param fractional_bw: fractional bandwidth in (0, 0.5)  0.4 works well.
    @type  fractional_bw: float
    @returns: sequence of numbers
    """

    global _plot
    
    if fractional_bw >= 0.5 or fractional_bw <= 0:
        raise ValueError, "Invalid fractional_bandwidth, must be in (0, 0.5)"

    beta = 5.0
    trans_width = 0.5 - fractional_bw
    mid_transition_band = 0.5 - trans_width/2

    taps = gr.firdes.low_pass(interpolation,                     # gain
                              1,                                 # Fs
                              mid_transition_band/interpolation, # trans mid point
                              trans_width/interpolation,         # transition width
                              gr.firdes.WIN_KAISER,
                              beta                               # beta
                              )
    # print "len(resampler_taps) =", len(taps)
    # _plot = gru.gnuplot_freqz(gru.freqz(taps, 1), 1)

    return taps



class _rational_resampler_base(gr.hier_block):
    """
    base class for all rational resampler variants.
    """
    def __init__(self, resampler_base, fg,
                 interpolation, decimation, taps=None, fractional_bw=None):
        """
        Rational resampling polyphase FIR filter.

        Either taps or fractional_bw may be specified, but not both.
        If neither is specified, a reasonable default, 0.4, is used as
        the fractional_bw.

        @param fg: flow graph
        @param interpolation: interpolation factor
        @type  interpolation: integer > 0
        @param decimation: decimation factor
        @type  decimation: integer > 0
        @param taps: optional filter coefficients
        @type  taps: sequence
        @param fractional_bw: fractional bandwidth in (0, 0.5), measured at final freq (use 0.4)
        @type  fractional_bw: float
        """

        if not isinstance(interpolation, int) or interpolation < 1:
            raise ValueError, "interpolation must be an integer >= 1"

        if not isinstance(decimation, int) or decimation < 1:
            raise ValueError, "decimation must be an integer >= 1"

        if taps is None and fractional_bw is None:
            fractional_bw = 0.4

        d = gru.gcd(interpolation, decimation)
        interpolation = interpolation // d
        decimation = decimation // d
        
        if taps is None:
            taps = design_filter(interpolation, decimation, fractional_bw)

        resampler = resampler_base(interpolation, decimation, taps)
        gr.hier_block.__init__(self, fg, resampler, resampler)



class rational_resampler_fff(_rational_resampler_base):
    def __init__(self, fg, interpolation, decimation, taps=None, fractional_bw=None):
        """
        Rational resampling polyphase FIR filter with
        float input, float output and float taps.
        """
        _rational_resampler_base.__init__(self, gr.rational_resampler_base_fff, fg,
                                          interpolation, decimation,
                                          taps, fractional_bw)

class rational_resampler_ccf(_rational_resampler_base):
    def __init__(self, fg, interpolation, decimation, taps=None, fractional_bw=None):
        """
        Rational resampling polyphase FIR filter with
        complex input, complex output and float taps.
        """
        _rational_resampler_base.__init__(self, gr.rational_resampler_base_ccf, fg,
                                          interpolation, decimation,
                                          taps, fractional_bw)

class rational_resampler_ccc(_rational_resampler_base):
    def __init__(self, fg, interpolation, decimation, taps=None, fractional_bw=None):
        """
        Rational resampling polyphase FIR filter with
        complex input, complex output and complex taps.
        """
        _rational_resampler_base.__init__(self, gr.rational_resampler_base_ccc, fg,
                                          interpolation, decimation,
                                          taps, fractional_bw)
