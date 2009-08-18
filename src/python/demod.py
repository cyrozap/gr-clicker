#!/usr/bin/env python

"""
FSK iClicker demodulation
"""

from gnuradio import gr, gru, blks2
import math

class my_graph(gr.top_block):

	def __init__(self):
		gr.top_block.__init__(self)
		input_sample_rate = 1e6
		symbol_rate = 152.34e3
		output_samples_per_symbol = 5
		output_sample_rate = output_samples_per_symbol * symbol_rate
		# least common multiple
		lcm = gru.lcm(input_sample_rate, output_sample_rate)
		intrp = int(lcm // input_sample_rate)
		decim = int(lcm // output_sample_rate)
		print intrp
		print decim
		resampler = blks2.rational_resampler_ccc(intrp, decim, None, None)
		src = gr.file_source(gr.sizeof_gr_complex, "infile")
		sink = gr.file_sink(gr.sizeof_float, "outfile")
		f2c = gr.float_to_complex()
		c2r = gr.complex_to_real()
		#ddc_coeffs = \
			#gr.firdes.low_pass (1.0,           # gain
				#input_sample_rate,   # sampling rate
				#2e3,         # low pass cutoff freq
				#6e3,         # width of trans. band
				#gr.firdes.WIN_HANN)
		# just grab the lower sideband:
		#ddc =  gr.freq_xlating_fir_filter_ccf(1,ddc_coeffs,-111.5e3,input_sample_rate)
		qdemod = gr.quadrature_demod_cf(1.0)
		lp_coeffs = \
			gr.firdes.low_pass (1.0,           # gain
				output_sample_rate,   # sampling rate
				symbol_rate,         # low pass cutoff freq
				symbol_rate,         # width of trans. band
				gr.firdes.WIN_HANN)
		lp = gr.fir_filter_fff (1,lp_coeffs)
		self.connect(src,resampler,qdemod,lp,sink)

if __name__ == '__main__':
	try:
		my_graph().run()
	except KeyboardInterrupt:
		pass
