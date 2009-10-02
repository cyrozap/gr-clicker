/* -*- c++ -*- */
/*
 * Copyright 2009 Jordan Riggs
 * Copyright 2005, 2006 Free Software Foundation, Inc.
 * 
 * This file is part of gr-clicker
 * 
 * gr-clicker is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * gr-clicker is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with gr-bluetooth; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include "clicker_packet.h"

clicker_packet_sptr clicker_make_packet(char* stream, int length) {
	return new clicker_packet(stream, length);
}

clicker_packet::clicker_packet(char* stream, int length) {
	d_response_code = stream[31]<<3 + stream[32]<<2 + stream[33]<<1 + stream[34];
	for (int i = 0; i < 4; i++) {
		d_id[i] = stream[i*8]<<7 + stream[i*8+1]<<6 + stream[i*8+2]<<5 + stream[i*8+3] << 4
			+ stream[i*8+4]<<3 + stream[i*8+5]<<2 + stream[i*8+6]<<1 + stream[i*8+7];
	}
}

clicker_packer::~clicker_packet() {

}
