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
 * along with gr-clicker; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "clicker_packet.h"

clicker_packet_sptr
clicker_make_packet(char *stream, int length)
{
	return clicker_packet_sptr (new clicker_packet (stream, length));
}


clicker_packet::clicker_packet(char* stream, int length)
{
	char code = (stream[31]<<3) + (stream[32]<<2) + (stream[33]<<1) + (stream[34]);
	switch (code)
	{
		case 0x01: d_response_code = 'A'; break;
		case 0x05: d_response_code = 'B'; break;
		case 0x0D: d_response_code = 'C'; break;
		case 0x0E: d_response_code = 'D'; break;
		case 0x0A: d_response_code = 'E'; break;
	}
	for (int i = 0; i < 31; i++) {
		d_id += (stream[i]<<(30-i));
	}
	/*
	for (int i = 0; i < 4; i++) {
		d_id[i] = (stream[i*8]<<7) + (stream[i*8+1]<<6) + (stream[i*8+2]<<5) + (stream[i*8+3] << 4)
			+ (stream[i*8+4]<<3) + (stream[i*8+5]<<2) + (stream[i*8+6]<<1) + (stream[i*8+7]);
	}
	*/
	//printf("Clicker Packet: %c\n", d_response_code);
}

void clicker_packet::print()
{
	//printf("Clicker Packet: %x\n", d_response_code);
}

clicker_packet::~clicker_packet() {

}

//clicker_packet_sptr& clicker_packet::operator=(const clicker_packet_sptr &rhs)
//{
	//this->set_response_code(rhs.get_response_code());
	//this->set_id(rhs.get_id());
	//return *this;
//}

static int compare_ids(char* id1, char* id2)
{
	for(int i = 0; i < 4; i++)
	{
		if (id1[i] != id2[i]) return 0;
	}
	return 1;
}
