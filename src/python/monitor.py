#!/usr/bin/python
# -*- coding: utf-8 -*-
# Copyright 2009 Jordan Riggs

from gnuradio import gr, eng_notation, blks2

#from gnuradio import clicker
from gnuradio.eng_option import eng_option
from optparse import OptionParser

class my_top_block(gr.top_block):

	def __init__(self):
		gr.top_block.__init__(self)

		usage="%prog: [options]"
		parser = OptionParser(option_class=eng_option, usage=usage)
		parser.add_option("-c", "--channel", type="string", default='AA',
								help="two-letter channel code (default: AA)")
		parser.add_option("-a", "--automatic", action="store_true", default=False,
						help="automatically determine and transmit reponse")

		(options, args) = parser.parse_args ()

		inf_str = None
		symbol_rate = 152.34e3
		
		if len(args) != 0:
			inf_str = args[0]

		if inf_str is not None:
			print "Reading from: " + inf_str
			inf = gr.file_source(inf_str, ,False)
		
		else:
			freqs = {
				'AA':917.0e6, 'AB':913.0e6, 'AC':914.0e6, 'AD':915.0e6,
				'BA':916.0e6, 'BB':919.0e6, 'BC':920.0e6, 'BD':921.0e6,
				'CA':922.0e6, 'CB':923.0e6, 'CC':907.0e6, 'CD':908.0e6,
				'DA':905.5e6, 'DB':909.0e6, 'DC':911.0e6, 'DD':910.0e6}

			frequency = freqs[options.channel]

			print "Channel: " + options.channel + " (" + str(frequency/1e6) + " MHz)"



if __name__ == '__main__':
	try:
		my_top_block().run()
	except KeyboardInterrupt:
		pass
