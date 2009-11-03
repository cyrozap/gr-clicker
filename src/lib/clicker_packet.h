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

#ifndef INCLUDED_CLICKER_PACKET_H
#define INCLUDED_CLICKER_PACKET_H

#include <cstdio>
#include <stdint.h>
#include <boost/enable_shared_from_this.hpp>

using namespace std;


class clicker_packet;
typedef boost::shared_ptr<clicker_packet> clicker_packet_sptr; 

clicker_packet_sptr clicker_make_packet(char *stream, int length);


class clicker_packet
{

private:

	friend clicker_packet_sptr clicker_make_packet(char *stream, int length);


	// private constructor
	clicker_packet(char *stream, int length);

	char d_response_code;
	uint32_t d_id;
	int d_count;

public:

	// hex representation of clicker response codes.
	// there's no apparent rhyme or reason to it.
	static const char A = 0x01;
	static const char B = 0x05;
	static const char C = 0x0D;
	static const char D = 0x0E;
	static const char E = 0x0A;

	static int compare_ids(char* id_1, char* id_2);

	//clicker_packet_sptr &operator=(const clicker_packet_sptr &rhs);

	char get_response_code() { return d_response_code; };
	uint32_t get_id() { return d_id; };
	int get_count() { return d_count; };

	void set_response_code(char response_code) { d_response_code = response_code; };
	void inc_count() { d_count++; };
	void print();	

	~clicker_packet();

};

#endif /* INCLUDED_CLICKER_PACKET_H */
