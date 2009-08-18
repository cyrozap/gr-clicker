#!/usr/bin/python

import struct, sys
	
badge_id_length = 61 # in bits
badge_id_offset = 16 # number of symbols from start of frame sync to start of badge id
samples_per_symbol = 5
frame_sync = [0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1]
correlation_threshold = len(frame_sync)
correlation_threshold = 100
minimum_span = 5 # minimum number of adjacent correlations

data = open('outfile').read()
raw_samples = struct.unpack('f1'*(len(data)/4), data)
samples = []
symbols = []

# normalize samples
total_value = 0
total_deviation = 0
count = 0
for sample in raw_samples:
	total_value += sample
	count += 1
	total_deviation += abs(sample)
	#print count, sample
mean_value = total_value / count
mean_deviation = total_deviation / count
for sample in raw_samples:
	samples.append((sample - mean_value) / mean_deviation)
#print samples

badge_id = 0
first = 0
last = 0
interesting = 0

def manchester_decode(pair):
	if pair == [0, 1]:
		return 0
	elif pair == [1, 0]:
		return 1
	else:
		print "manchester decoding error"
		sys.exit()
	
# correlate frame sync
for i in range(len(samples) - len(frame_sync) * samples_per_symbol):
	correlation = 0
	for j in range(len(frame_sync)):
		correlation += ((frame_sync[j] * 2) - 1) * samples[i + j * samples_per_symbol]
	#print i, correlation
	if interesting:
		if correlation < correlation_threshold:
			if i >= (first + minimum_span):
				last = i
				break
			else:
				first = 0
				interesting = 0
	elif correlation >= correlation_threshold:
		print "Found something " + str(i)
		first = i
		interesting = 1

# decode badge id
if last:
	center = first + ((last - first) // 2)
	#print center
	for i in range(center, len(samples), samples_per_symbol):
		#print i, samples[i]
		symbol = 0
		if samples[i] > 0: symbol = 1
		symbols.append(symbol)
	#print symbols
	parity = 0
	for i in range(badge_id_length):
		j = (i * 2) + badge_id_offset
		bit = manchester_decode(symbols[j:j+2])
		#print symbols[j:j+2], bit
		badge_id += bit << ((badge_id_length - 1) - i)
		parity += bit
	# this parity check is wrong.  maybe it covers more than badge id?
	parity_check = manchester_decode(symbols[j+2:j+4])
	if parity_check == parity % 2:
		print "parity incorrect"
	else:
		print "parity correct"
	print badge_id
else:
	print "frame detection failure"
