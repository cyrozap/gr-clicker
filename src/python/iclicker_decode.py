#!/usr/bin/python

# to be used with grc demodulator

import struct
	
data = open('/tmp/iclicker.out').read()
symbols = struct.unpack('B1'*len(data), data)

def decode_frame(start):
	print
	print "decoding frame"
	for i in range(43):
		print symbols[start+i] & 1,
	
# look for correlations flagged by gr_correlate_access_code_bb
for i in range(len(symbols) - 90):
	if symbols[i] & 2:
		decode_frame(i)
