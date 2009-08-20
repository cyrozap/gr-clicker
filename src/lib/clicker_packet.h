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

#ifndef INCLUDED_CLICKER_PACKET_H
#define INCLUDED_CLICKER_PACKET_H

class clicker_packet;
typedef boost::shared_ptr<clicker_packet> clicker_packet_sptr; 

clicker_packet_sptr clicker_make_packet(char *stream);

class clicker_packet
{

private:

	friend clicker_packet_sptr clicker_make_packet(char *stream);

	// private constructor
	clicker_packet(char *stream)

	char d_response_code;

public:

	char get_response_code() { return d_response_code };	

	~clicker_packet();

}

#endif /* INCLUDED_CLICKER_PACKET_H */
