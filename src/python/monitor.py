#!/usr/bin/python
# -*- coding: utf-8 -*-
# Copyright 2009 Jordan Riggs

from gnuradio import gr, eng_notation, blks2, usrp

from gnuradio import clicker
from gnuradio.eng_option import eng_option
from optparse import OptionParser

AC = "101100001011000010110000"

class my_top_block(gr.top_block):

	def __init__(self):
		gr.top_block.__init__(self)

		usage="%prog: [options]"
		parser = OptionParser(option_class=eng_option, usage=usage)
		parser.add_option("-c", "--channel", type="string", default='AA',
								help="two-letter channel code (default: AA)")
		parser.add_option("-a", "--automatic", action="store_true", default=False,
						help="automatically determine and transmit reponse")
		parser.add_option("-R", "--rx-subdev-spec", type="subdev", default=(0, 0),
						help="select USRP Rx side A or B (default=A)")
		parser.add_option("-g", "--gain", type="eng_float", default=None,
						help="set USRP gain in dB (default is midpoint)")

		(options, args) = parser.parse_args ()

		inf_str = None
		symbol_rate = 152.34e3
		
		if len(args) != 0:
			inf_str = args[0]

		squelch = gr.pwr_squelch_cc(70, 0.1, 0, True)
		demod = gr.quadrature_demod_cf(1.0)
		cr = gr.clock_recovery_mm_ff(6.5643, 0.00765625, 0, 0.175, 0.005)
		slicer = gr.binary_slicer_fb()
		corr = gr.correlate_access_code_bb(AC, 0)
		sink = clicker.sniffer()

		if inf_str is not None:
			print "Reading from: " + inf_str
			src = gr.file_source(gr.sizeof_gr_complex, inf_str, False)
		
		else:
			freqs = {
				'AA':917.0e6, 'AB':913.0e6, 'AC':914.0e6, 'AD':915.0e6,
				'BA':916.0e6, 'BB':919.0e6, 'BC':920.0e6, 'BD':921.0e6,
				'CA':922.0e6, 'CB':923.0e6, 'CC':907.0e6, 'CD':908.0e6,
				'DA':905.5e6, 'DB':909.0e6, 'DC':911.0e6, 'DD':910.0e6}

			frequency = freqs[options.channel]
			print "Channel: " + options.channel + " (" + str(frequency/1e6) + "MHz)"

			src = usrp.source_c(128) #500k Samp/sec
			subdev = usrp.selected_subdev(u, options.rx_subdev_spec)
			print "Using RX board %s" % (subdev.side_and_name())
			r = src.tune(0, subdev, frequency)
			if not r:
				raise SystemExit, "Failed to tune USRP. Are you using a 900MHz board?"
			if options.gain is None:
				# if no gain was specified, use the mid-point in dB
				g = subdev.gain_range()
				options.gain = float(g[0]+g[1])/2
			subdev.set_gain(options.gain)
			print "Gain: " + float(options.gain) + "dB"

		self.connect(src, squelch, demod, cr, slicer, corr, sink)



if __name__ == '__main__':
	try:
		my_top_block().run()
	except KeyboardInterrupt:
		pass
