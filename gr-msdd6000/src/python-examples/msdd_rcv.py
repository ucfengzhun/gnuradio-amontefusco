#!/usr/bin/env python
#
# Copyright 2005,2006,2007 Free Software Foundation, Inc.
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gru, eng_notation
from gnuradio import msdd
from gnuradio import blks2
from gnuradio.eng_option import eng_option
from gnuradio.wxgui import slider, powermate
from gnuradio.wxgui import stdgui2, form
from gnuradio.wxgui import fftsink2
from optparse import OptionParser
#from usrpm import usrp_dbid
import sys
import math
import wx

class wfm_rx_block (stdgui2.std_top_block):
    def __init__(self,frame,panel,vbox,argv):
        stdgui2.std_top_block.__init__ (self,frame,panel,vbox,argv)

        parser=OptionParser(option_class=eng_option)        
#        parser.add_option("-R", "--rx-subdev-spec", type="subdev", default=None,
#                          help="select MSDD Rx side A or B (default=A)")
        parser.add_option("-f", "--freq", type="eng_float", default=100.1e6,
                          help="set frequency to FREQ", metavar="FREQ")
        parser.add_option("-g", "--gain", type="eng_float", default=40,
                          help="set gain in dB (default is midpoint)")
#        parser.add_option("-V", "--volume", type="eng_float", default=None,
#                          help="set volume (default is midpoint)")
#        parser.add_option("-O", "--audio-output", type="string", default="",
#                          help="pcm device name.  E.g., hw:0,0 or surround51 or /dev/dsp")

        (options, args) = parser.parse_args()
        if len(args) != 0:
            parser.print_help()
            sys.exit(1)
        
        self.frame = frame
        self.panel = panel
        
        self.vol = 0
        self.gain_range = (10, 70, .5)
        self.state = "FREQ"
        self.freq = 0
        msdd_decim = 2

        # build graph
        self.fft_size = 8192
        self.sample_rate = 200
        self.u = msdd.source_c(0, 1, "10.45.4.44", 10000)
        self.u.set_decim_rate(4)
        self.u.set_desired_packet_size(0, 1460*100)        


        #self.u.set_decim_rate(msdd_decim)
#        usrp_rate = adc_rate / msdd_decim           # 320 kS/s
#        chanfilt_decim = 1
#        demod_rate = usrp_rate / chanfilt_decim
#        audio_decimation = 10
#        audio_rate = demod_rate / audio_decimation  # 32 kHz
#
#        if options.rx_subdev_spec is None:
#            options.rx_subdev_spec = pick_subdevice(self.u)
#
#        self.u.set_mux(usrp.determine_rx_mux_value(self.u, options.rx_subdev_spec))
#        self.subdev = usrp.selected_subdev(self.u, options.rx_subdev_spec)
#        print "Using RX d'board %s" % (self.subdev.side_and_name(),)
#
#
#        chan_filt_coeffs = optfir.low_pass (1,           # gain
#                                            usrp_rate,   # sampling rate
#                                            80e3,        # passband cutoff
#                                            115e3,       # stopband cutoff
#                                            0.1,         # passband ripple
#                                            60)          # stopband attenuation
#        #print len(chan_filt_coeffs)
#        chan_filt = gr.fir_filter_ccf (chanfilt_decim, chan_filt_coeffs)
#
#        self.guts = blks2.wfm_rcv (demod_rate, audio_decimation)
#
#        self.volume_control = gr.multiply_const_ff(self.vol)
#
#        # sound card as final sink
#        audio_sink = audio.sink (int (audio_rate),
#                                 options.audio_output,
#                                 False)  # ok_to_block
        
        # now wire it all together
        #self.connect (self.u, chan_filt, self.guts, self.volume_control, audio_sink)

        self._build_gui(vbox)

        if options.gain is None:
            # if no gain was specified, use the mid-point in dB
            #g = self.subdev.gain_range()
            g = self.gain_range
            options.gain = float(g[0]+g[1])/2
#
#        if options.volume is None:
#            g = self.volume_range()
#            options.volume = float(g[0]+g[1])/2
#            
#        if abs(options.freq) < 1e6:
#            options.freq *= 1e6

        # set initial values
#
        self.set_gain(options.gain)
#        self.set_vol(options.volume)
        if not(self.set_freq(options.freq)):
            self._set_status_msg("Failed to set initial frequency")
        print "Frequency: ", self.u.rx_freq(0)


    def _set_status_msg(self, msg, which=0):
        self.frame.GetStatusBar().SetStatusText(msg, which)


    def _build_gui(self, vbox):

        def _form_set_freq(kv):
            return self.set_freq(kv['freq'])

        self.src_fft = None
        if 1:
            self.src_fft = fftsink2.fft_sink_c(self.panel, title="Data from MSDD",
                                               fft_size=512, sample_rate=512)
#            self.s2f1 = gr.short_to_float()
#            self.scope = scopesink2.scope_sink_f(self.panel, sample_rate=self.sample_rate*self.fft_size)
            
            self.connect (self.u, self.src_fft)
            #self.connect (self.s2f1, self.scope)
            vbox.Add (self.src_fft.win, 4, wx.EXPAND)
#
#        if 1:
#            post_filt_fft = fftsink2.fft_sink_f(self.panel, title="Post Demod", 
#                                                fft_size=1024, sample_rate=usrp_rate,
#                                                y_per_div=10, ref_level=0)
#            self.connect (self.guts.fm_demod, post_filt_fft)
#            vbox.Add (post_filt_fft.win, 4, wx.EXPAND)
#
#        if 0:
#            post_deemph_fft = fftsink2.fft_sink_f(self.panel, title="Post Deemph",
#                                                  fft_size=512, sample_rate=audio_rate,
#                                                  y_per_div=10, ref_level=-20)
#            self.connect (self.guts.deemph, post_deemph_fft)
#            vbox.Add (post_deemph_fft.win, 4, wx.EXPAND)

        
        # control area form at bottom
        self.myform = myform = form.form()

        hbox = wx.BoxSizer(wx.HORIZONTAL)
        hbox.Add((5,0), 0)
        myform['freq'] = form.float_field(
            parent=self.panel, sizer=hbox, label="Freq", weight=1,
            callback=myform.check_input_and_call(_form_set_freq, self._set_status_msg))

        hbox.Add((5,0), 0)
        myform['freq_slider'] = \
            form.quantized_slider_field(parent=self.panel, sizer=hbox, weight=3,
                                        range=(30e6, 6e9, 1e6),
                                        callback=self.set_freq)
        hbox.Add((5,0), 0)
        vbox.Add(hbox, 0, wx.EXPAND)

        hbox = wx.BoxSizer(wx.HORIZONTAL)
        hbox.Add((5,0), 0)
#
#        myform['volume'] = \
#            form.quantized_slider_field(parent=self.panel, sizer=hbox, label="Volume",
#                                        weight=3, range=self.volume_range(),
#                                        callback=self.set_vol)
#        hbox.Add((5,0), 1)

        myform['gain'] = \
            form.quantized_slider_field(parent=self.panel, sizer=hbox, label="Gain",
                                        weight=3, range=self.gain_range,
                                        callback=self.set_gain)
        hbox.Add((5,0), 0)
        vbox.Add(hbox, 0, wx.EXPAND)
#
#        try:
#            self.knob = powermate.powermate(self.frame)
#            self.rot = 0
#            powermate.EVT_POWERMATE_ROTATE (self.frame, self.on_rotate)
#            powermate.EVT_POWERMATE_BUTTON (self.frame, self.on_button)
#        except:
#            print "FYI: No Powermate or Contour Knob found"


    def on_rotate (self, event):
        self.rot += event.delta
        if (self.state == "FREQ"):
            if self.rot >= 3:
                self.set_freq(self.freq + .1e6)
                self.rot -= 3
            elif self.rot <=-3:
                self.set_freq(self.freq - .1e6)
                self.rot += 3
        else:
            step = self.volume_range()[2]
            if self.rot >= 3:
                self.set_vol(self.vol + step)
                self.rot -= 3
            elif self.rot <=-3:
                self.set_vol(self.vol - step)
                self.rot += 3
            
    def on_button (self, event):
        if event.value == 0:        # button up
            return
        self.rot = 0
        if self.state == "FREQ":
            self.state = "VOL"
        else:
            self.state = "FREQ"
        self.update_status_bar ()
#        
#
#    def set_vol (self, vol):
#        g = self.volume_range()
#        self.vol = max(g[0], min(g[1], vol))
#        self.volume_control.set_k(10**(self.vol/10))
#        self.myform['volume'].set_value(self.vol)
#        self.update_status_bar ()
                                        
    def set_freq(self, target_freq):
        """
        Set the center frequency we're interested in.

        @param target_freq: frequency in Hz
        @rypte: bool

        Tuning is a two step process.  First we ask the front-end to
        tune as close to the desired frequency as it can.  Then we use
        the result of that operation and our target_frequency to
        determine the value for the digital down converter.
        """
        r = self.u.set_rx_freq(0, target_freq);
        
        if r:
            self.freq = target_freq
            self.myform['freq'].set_value(target_freq)         # update displayed value
            self.myform['freq_slider'].set_value(target_freq)  # update displayed value
            self.update_status_bar()
            self._set_status_msg("OK", 0)
            return True

        self._set_status_msg("Failed", 0)
        return False

    def set_gain(self, gain):
        self.myform['gain'].set_value(gain)     # update displayed value
        self.u.set_pga(0,gain)
        
    def update_status_bar (self):
        msg = "Volume:%r  Setting:%s" % (self.vol, self.state)
        self._set_status_msg(msg, 1)
        #self.src_fft.set_baseband_freq(self.freq)
#
#    def volume_range(self):
#        return (-20.0, 0.0, 0.5)
        

if __name__ == '__main__':
    app = stdgui2.stdapp (wfm_rx_block, "MSDD FFT RX")
    app.MainLoop ()
